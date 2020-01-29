#include <arduinoFFT.h>

arduinoFFT FFT = arduinoFFT();
#define CHANNEL A0

const uint16_t samples = 128; //number of smaples 
const double samplingFrequency = 80000;  


double vReal[samples]; //array for initial samples from ADC
double vImag[samples]; //array for calculated complex part of the signal
unsigned int sampling_period_us; 
unsigned long microseconds;

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03





void setup() {
  
  sampling_period_us = 1000000*(1.0/samplingFrequency); 
  Serial.begin(9600);
  


}

void loop() {
  // put your main code here, to run repeatedly:

    microseconds = micros(); //number of microseconds since the Arduino has been turned on 
    for(int i=0; i<samples; i++)
    {
        vReal[i] = analogRead(CHANNEL);
        vImag[i] = 0; //need to set values to 0
        while(micros() - microseconds < sampling_period_us){ 
          //empty loop that delays 
        }
        microseconds += sampling_period_us;
    }
    //sampling 
      //Serial.println("Data:");
      PrintVector(vReal, samples, SCL_TIME);
      FFT.Windowing(vReal, samples, FFT_WIN_TYP_HAMMING, FFT_FORWARD); /* Weigh data */
      //Serial.println("Weighed data:");
      //PrintVector(vReal, samples, SCL_TIME);
      FFT.Compute(vReal, vImag, samples, FFT_FORWARD); /* Compute FFT */
      //Serial.println("Computed Real values:");
      //PrintVector(vReal, samples, SCL_INDEX);
      //Serial.println("Computed Imaginary values:");
      //PrintVector(vImag, samples, SCL_INDEX);
      FFT.ComplexToMagnitude(vReal, vImag, samples); /* Compute magnitudes */
      //Serial.println("Computed magnitudes:");
      //PrintVector(vReal, (samples >> 1), SCL_FREQUENCY);
      double x;
      x = FFT.MajorPeak(vReal, samples, samplingFrequency);
      Serial.print(x, 2);
      Serial.print(' ');
     
        
      while(1); /* Run Once */
      // delay(2000); /* Repeat after delay */
}

void PrintVector(double *vData, uint16_t bufferSize, uint8_t scaleType)
{
  for (uint16_t i = 0; i < bufferSize; i++)
  {
    double abscissa;
    /* Print abscissa value */
    switch (scaleType)
    {
      case SCL_INDEX:
        abscissa = (i * 1.0);
  break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / samplingFrequency);
  break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * samplingFrequency) / samples);
  break;
    }
    Serial.print(abscissa, 6);
    if(scaleType==SCL_FREQUENCY)
      Serial.print("Hz");
    Serial.print(" ");
    Serial.println(vData[i], 4);
  }
  Serial.println();
}
