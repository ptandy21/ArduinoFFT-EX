int input = A0;
int input1 = A1;
int input2 = A2;
int led = 13;
int val;
int val2;
int val3;

void setup()
{
  pinMode(input, INPUT);
  pinMode(led, OUTPUT);
  // Setup all registers
  pmc_enable_periph_clk(ID_ADC); // To use peripheral, we must enable clock distributon to it
  adc_init(ADC, SystemCoreClock, ADC_FREQ_MAX, ADC_STARTUP_FAST); // initialize, set maximum posibble speed
  adc_disable_interrupt(ADC, 0xFFFFFFFF);
  adc_set_resolution(ADC, ADC_12_BITS);
  adc_configure_power_save(ADC, 0, 0); // Disable sleep
  adc_configure_timing(ADC, 0, ADC_SETTLING_TIME_3, 1); // Set timings - standard values
  adc_set_bias_current(ADC, 1); // Bias current - maximum performance over current consumption
  adc_stop_sequencer(ADC); // not using it
  adc_disable_tag(ADC); // it has to do with sequencer, not using it
  adc_disable_ts(ADC); // deisable temperature sensor
  adc_disable_channel_differential_input(ADC, ADC_CHANNEL_7);
  adc_disable_channel_differential_input(ADC, ADC_CHANNEL_6);
  adc_disable_channel_differential_input(ADC, ADC_CHANNEL_5);
  adc_configure_trigger(ADC, ADC_TRIG_SW, 1); // triggering from software, freerunning mode
  adc_disable_all_channel(ADC);
  adc_enable_channel(ADC, ADC_CHANNEL_7); // just one channel enabled
  adc_start(ADC);

}

void loop()
{

  for (int i = 0; i < 128; i++)
  {
    adc_enable_channel(ADC, ADC_CHANNEL_7);

    PIO_Set(PIOB, PIO_PB27B_TIOB0);
    while ((adc_get_status(ADC) & ADC_ISR_DRDY) != ADC_ISR_DRDY)
    {}; //Wait for end of conversion
    PIO_Clear(PIOB, PIO_PB27B_TIOB0);
    val = adc_get_latest_value(ADC);

    adc_disable_channel(ADC, ADC_CHANNEL_7);
    adc_enable_channel(ADC, ADC_CHANNEL_6);

    PIO_Set(PIOB, PIO_PB27B_TIOB0);
    while ((adc_get_status(ADC) & ADC_ISR_DRDY) != ADC_ISR_DRDY)
    {}; //Wait for end of conversion
    PIO_Clear(PIOB, PIO_PB27B_TIOB0);
    val = adc_get_latest_value(ADC);

    adc_disable_channel(ADC, ADC_CHANNEL_6);
    adc_enable_channel(ADC, ADC_CHANNEL_5);

    PIO_Set(PIOB, PIO_PB27B_TIOB0);
    while ((adc_get_status(ADC) & ADC_ISR_DRDY) != ADC_ISR_DRDY)
    {}; //Wait for end of conversion
    PIO_Clear(PIOB, PIO_PB27B_TIOB0);
    val = adc_get_latest_value(ADC);

    adc_disable_channel(ADC, ADC_CHANNEL_5);

    return 0;







  }

}
