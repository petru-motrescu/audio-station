#include <algorithm>
#include <iostream>
#include <cmath>
#include <mutex>
#include <list>
#include <AudioToolbox/AudioToolbox.h>
#include "audio-renderer.hpp"
#include "wave-rendering.hpp"
using namespace audiostation;

constexpr unsigned int SAMPLE_RATE = 44100;
constexpr unsigned int BUFFER_SIZE = 512;
constexpr unsigned SIZE_OF_DOUBLE = sizeof(double);

struct RenderState {
    double phase;
};

struct audiostation::AudioRendererImpl {
    RenderState render_state;
    AudioComponentInstance audio_unit;
};

double render_sample(RenderState& state) {
    auto frequency = 100;
    auto amplitude = 0.5;
    double sample = render_wave(Waveform::Sine, state.phase) * amplitude;
    state.phase = next_phase(state.phase, frequency, SAMPLE_RATE);
    return sample;
}

static OSStatus render_audio(
    void* client_data,
    AudioUnitRenderActionFlags* flags,
    const AudioTimeStamp* time,
    UInt32 bus_number,
    UInt32 frame_count,
    AudioBufferList* buffers
) {
    RenderState* state = (RenderState*) client_data;
    double* buffer_left = (double*) buffers->mBuffers[0].mData;
    double* buffer_right = (double*) buffers->mBuffers[1].mData;

    for (int frame = 0; frame < frame_count; frame++) {
        double sample = render_sample(*state);
        buffer_left[frame] = sample;
        buffer_right[frame] = sample;
    }
    
    return 0;
}

audiostation::AudioRenderer::AudioRenderer()
    : impl(std::make_unique<AudioRendererImpl>()) { }

audiostation::AudioRenderer::~AudioRenderer() {
    AudioUnitUninitialize(this->impl->audio_unit);
    AudioComponentInstanceDispose(this->impl->audio_unit);
    this->impl.reset();
    std::cout << "❌ Audio disposed" << std::endl;
}

void audiostation::AudioRenderer::init() {
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
    callback.inputProcRefCon = &this->impl->render_state;

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

void audiostation::AudioRenderer::play() {
    AudioOutputUnitStart(this->impl->audio_unit);
    std::cout << "▶️ Audio playing" << std::endl;
}

void audiostation::AudioRenderer::stop() {
    AudioOutputUnitStop(this->impl->audio_unit);
    std::cout << "⏹️ Audio stopped" << std::endl;
}
