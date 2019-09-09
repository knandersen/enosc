#include "spi_adc.hh"
#include "debug.hh"
extern Debug debug;

void (*spi_adc_isr)();
void register_spi_adc_isr(void f()) { spi_adc_isr = f; }

extern "C" void MAX11666_SPI_IRQHANDLER(void) {
  spi_adc_isr();
}

SpiAdc *SpiAdc::spiadc_instance_;
uint32_t SpiAdc::os_idx[NUM_SPI_ADC_CHANNELS]={0};
uint8_t SpiAdc::cur_chan;


void SpiAdc::spiadc_ISR__IN_ITCM_() {
  uint32_t itflag = SpiAdc::spiadc_instance_->spih.Instance->SR;
  uint32_t itsource = SpiAdc::spiadc_instance_->spih.Instance->CR2;

  if ((itflag & SPI_FLAG_RXNE) && (itsource & SPI_IT_RXNE))
  {
    uint16_t adc_val = SpiAdc::spiadc_instance_->spih.Instance->DR;

    debug.set(1+cur_chan, true);
    SpiAdc::spiadc_instance_->values[cur_chan][os_idx[cur_chan]] = u1_15::of_repr(adc_val);

    if (os_idx[cur_chan]++ <= OVERSAMPLING_AMT) //overwrite twice
      SpiAdc::spiadc_instance_->spih.Instance->DR = cur_chan ? MAX11666_CONTINUE_READING_CH2 : MAX11666_CONTINUE_READING_CH1;

    os_idx[cur_chan] &= OVERSAMPLING_MASK;

    debug.set(1+cur_chan, false);
  }
}
