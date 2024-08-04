#include <algorithm>
#include <iostream>
#include <cmath>
#include <AudioToolbox/AudioToolbox.h>
#include "audio-station.hpp"
#include "config.hpp"
using namespace audiostation;

constexpr unsigned SIZE_OF_DOUBLE = sizeof(double);

struct audiostation::AudioStationImpl {
    AudioSignalSource* audio_signal_source = nullptr;
    AudioComponentInstance audio_unit = 0;
};

static OSStatus render_audio(
    void* client_data,
    AudioUnitRenderActionFlags* flags,
    const AudioTimeStamp* time,
    UInt32 bus_number,
    UInt32 frame_count,
    AudioBufferList* buffers
) {
    // ⚠️ No locks and no IO allowed here.
    
    AudioStationImpl* station = (AudioStationImpl*) client_data;
    if (station->audio_signal_source == nullptr) {
        return 0;
    }

    double* buffer_left = (double*) buffers->mBuffers[0].mData;
    double* buffer_right = (double*) buffers->mBuffers[1].mData;

    for (int frame = 0; frame < frame_count; frame++) {
        double sample = station->audio_signal_source->render();
        buffer_left[frame] = sample;
        buffer_right[frame] = sample;
    }
    
    return 0;
}

audiostation::AudioStation::AudioStation() {
    this->impl = std::make_unique<AudioStationImpl>();
    this->impl->audio_signal_source = nullptr;
}

audiostation::AudioStation::~AudioStation() {
    AudioUnitUninitialize(this->impl->audio_unit);
    AudioComponentInstanceDispose(this->impl->audio_unit);
    this->impl.reset();
    std::cout << "❌ Audio disposed" << std::endl;
}

void audiostation::AudioStation::init() {
    std::cout << "⏳ Audio initializing" << std::endl;

    AudioComponentDescription audio_unit_config {
        .componentType = kAudioUnitType_Output,
        .componentSubType = kAudioUnitSubType_DefaultOutput,
        .componentManufacturer = kAudioUnitManufacturer_Apple,
        .componentFlags = 0,
        .componentFlagsMask = 0
    };

    auto audio_component = AudioComponentFindNext(nullptr, &audio_unit_config);
    AudioComponentInstanceNew(audio_component, &this->impl->audio_unit);

    AURenderCallbackStruct callback;
    callback.inputProc = render_audio;
    callback.inputProcRefCon = this->impl.get();

    AudioUnitSetProperty(
        this->impl->audio_unit,
        kAudioUnitProperty_SetRenderCallback,
        kAudioUnitScope_Input,
        0,
        &callback,
        sizeof(callback)
    );

    AudioStreamBasicDescription stream_format {
        .mSampleRate = Config::SAMPLE_RATE,
        .mFormatID = kAudioFormatLinearPCM,
        .mFormatFlags = kAudioFormatFlagIsFloat | kAudioFormatFlagIsNonInterleaved,
        .mBytesPerPacket = SIZE_OF_DOUBLE,
        .mBytesPerFrame = SIZE_OF_DOUBLE,
        .mBitsPerChannel = 8 * SIZE_OF_DOUBLE,
        .mFramesPerPacket = 1,
        .mChannelsPerFrame = 2
    };

    AudioUnitSetProperty(
        this->impl->audio_unit,
        kAudioUnitProperty_StreamFormat,
        kAudioUnitScope_Input,
        0,
        &stream_format,
        sizeof(stream_format)
    );

    AudioUnitSetProperty(
        this->impl->audio_unit,
        kAudioUnitProperty_MaximumFramesPerSlice,
        kAudioUnitScope_Global,
        0,
        &Config::BUFFER_SIZE,
        sizeof(Config::BUFFER_SIZE)
    );

    AudioUnitInitialize(this->impl->audio_unit);
    std::cout << "🎛️ Audio initialized" << std::endl;
}

void audiostation::AudioStation::play(AudioSignalSource* audio_signal_source) {
    this->impl->audio_signal_source = audio_signal_source;
    AudioOutputUnitStart(this->impl->audio_unit);
    std::cout << "▶️ Audio live" << std::endl;
}

void audiostation::AudioStation::stop() {
    AudioOutputUnitStop(this->impl->audio_unit);
    this->impl->audio_signal_source = nullptr;
    std::cout << "⏹️ Audio stopped" << std::endl;
}
