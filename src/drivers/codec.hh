#pragma once

#include "util.hh"
#include "parameters.hh"
#include "hal.hh"

struct Codec : Nocopy {

  struct Callback {
    virtual void Process(Frame* in, Frame *out, int size) = 0;
  };

  Codec(Callback *callback, int sample_rate) :
    callback_(callback) {
    instance_ = this;

    // Setup PLL clock for codec
    init_SAI_clock(sample_rate);

   	//De-init the codec to force it to reset
    i2c_.DeInit();

    //Start Codec I2C
    gpio_.Init();
    i2c_.Init(sample_rate);

    //Start Codec SAI
    SAI_init(sample_rate);
    init_audio_DMA();
  }

  void Start();

  static Codec *instance_;
  Callback *callback_;

  DMA_HandleTypeDef hdma_rx;
  DMA_HandleTypeDef hdma_tx;

  volatile int32_t tx_buffer[kBlockSize * 2];
  volatile int32_t rx_buffer[kBlockSize * 2];

private:

  struct GPIO {
    // TODO init with constructor
    void Init();
  } gpio_;

  struct I2C {
    void Init(uint32_t sample_rate);
    void DeInit();
    void PowerDown();
  private:
    void Write(uint8_t addr, uint16_t value);
    I2C_HandleTypeDef handle_;
  } i2c_;

  void Reboot(uint32_t sample_rate);

  // TODO cleanup: SAI & DMA
  void init_SAI_clock(uint32_t sample_rate);
  void SAI_init(uint32_t sample_rate);
  void DeInit_I2S_Clock();
  void DeInit_SAIDMA();
  void init_audio_DMA();

  SAI_HandleTypeDef hsai_rx;
  SAI_HandleTypeDef hsai_tx;

};
