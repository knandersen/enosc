#include <cstdio>
#include "parameters.hh"
#include "dsp.hh"
#include "data.hh"
#include "wav_files.hh"
#include "polyptic_oscillator.hh"

constexpr int kDuration = 10;    // seconds

struct Main {
  WavWriter<short, 1> wav_{"test.wav", kDuration * kSampleRate};
  Main() {
    int size = kDuration * kSampleRate;

    PolypticOscillator osc;

    CubicOnePoleLp<1> filt;

    for (int time=0; time<1500; time++) {

      // noisy input generation
      float input;
      if (time<300) input=0.0f;
      else if (time<500) input=((float)time-300.0f)/(500.0f-300.0f);
      else if (time<700) input=1.0f;
      else if (time<1000)
        input = cos(time * 0.1f) * 0.1f + 0.5f;
      else input=0.0f;
      f inp = f(input);
      inp += (Random::Float01() * 2_f - 1_f) * 0.05_f;
      inp *= 0.8_f;
      inp += 0.1_f;

      s1_15 in = s1_15(inp);
      s1_15 out = filt.Process(in);

      printf("%d, %f\n", time, out.to_float().repr());

    }

    while(size -= kBlockSize) {

      Float out[kBlockSize];

      osc.Process(out, kBlockSize);

      short output[kBlockSize];
      for(int i=0; i<kBlockSize; i++) {
        output[i] = s1_15::inclusive(out[i]).repr();
      }
      // write
      wav_.Write(output, kBlockSize);
    }
  }
} _;

int main() {}
