#include <algorithm>
#include <iostream>
#include <cmath>
#include <AudioToolbox/AudioToolbox.h>
#include "audio-station.hpp"
#include "audio-renderer.hpp"
#include "wave-renderer.hpp"
using namespace audiostation;

constexpr unsigned int SAMPLE_RATE = 44100;
constexpr unsigned int BUFFER_SIZE = 512;
constexpr unsigned SIZE_OF_DOUBLE = sizeof(double);

struct audiostation::AudioStationImpl {
    AudioStationImpl(unsigned sample_rate);
    AudioRenderer audio_renderer;
    AudioComponentInstance audio_unit;
};

audiostation::AudioStationImpl::AudioStationImpl(unsigned sample_rate) 
    : audio_renderer(sample_rate)
    , audio_unit(0)
    { }

static OSStatus render_audio(
    void* client_data,
    AudioUnitRenderActionFlags* flags,
    const AudioTimeStamp* time,
    UInt32 bus_number,
    UInt32 frame_count,
    AudioBufferList* buffers
) {
    AudioRenderer* renderer = (AudioRenderer*) client_data;
    double* buffer_left = (double*) buffers->mBuffers[0].mData;
    double* buffer_right = (double*) buffers->mBuffers[1].mData;

    for (int frame = 0; frame < frame_count; frame++) {
        double sample = renderer->render();
        buffer_left[frame] = sample;
        buffer_right[frame] = sample;
    }
    
    return 0;
}

audiostation::AudioStation::AudioStation() {
    this->impl = std::make_unique<AudioStationImpl>(SAMPLE_RATE);
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
    callback.inputProcRefCon = &this->impl->audio_renderer;

    AudioUnitSetProperty(
        this->impl->audio_unit,
        kAudioUnitProperty_SetRenderCallback,
        kAudioUnitScope_Input,
        0,
        &callback,
        sizeof(callback)
    );

    AudioStreamBasicDescription stream_format {
        .mSampleRate = SAMPLE_RATE,
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
        &BUFFER_SIZE,
        sizeof(BUFFER_SIZE)
    );

    AudioUnitInitialize(this->impl->audio_unit);
    std::cout << "🎛️ Audio initialized" << std::endl;
}

void audiostation::AudioStation::add_oscillator(audiostation::Oscillator* oscillator) {
    this->impl->audio_renderer.add_oscillator(oscillator);
}

void audiostation::AudioStation::add_synth(audiostation::Synth* synth) {
    this->impl->audio_renderer.add_synth(synth);
}

void audiostation::AudioStation::play() {
    AudioOutputUnitStart(this->impl->audio_unit);
    std::cout << "▶️ Audio playing" << std::endl;
}

void audiostation::AudioStation::stop() {
    AudioOutputUnitStop(this->impl->audio_unit);
    std::cout << "⏹️ Audio stopped" << std::endl;
}
