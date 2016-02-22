#DS18B20 Library for Particle Core, Photon and P1
Modified DS18BXX Lib copied from
https://github.com/krvarma/Dallas_DS18B20_SparkCore
Sample application using Particle Photon and Dallas DS18B20 Digital Temperature
Sensor.
The OneWire source code is taken from this link by @tidwelltimj.
I just separated this into two classes OneWire and DS18B20.
The sample code publishes a variable named tmpinfo with temperature value.

Requires Particle-OneWire (included) from
https://github.com/balbano/OneWire-Particle/tree/master/firmware
Wiring:
Power to 3.3/5V
GND to GND
Signal to D2 (with 4.7k pullup resistor)

Use crcCheck() to verify the sensor was successfully read.
