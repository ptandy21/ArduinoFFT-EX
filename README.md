# ArduinoFFT-EX
Example of a working Arduino FFT

For the competition RoboSub, an Arduino-Due needs to be able to sample and compute a Fast Fourier transform on an incoming ping. Since there are mutiple pingers in the pool, the submersible needs to identify individual pingers from their unqiue frequnecy. 

Currently we are only sampling through the Analog in pins on the Due. Our sampling software right now is not where it needs to be to in order to get all three signals in at the same time. 

On start up the code begins to sample the three pins and then once the data is gathered the FFT will be computed to produce a major peak to identify the indivudal pingers. 


