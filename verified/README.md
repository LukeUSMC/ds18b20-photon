
## Library verification for DS18B20.
The propuse of this test is to verfify the current DS18B20 temperature library from our community.To make sure all the others can feel
confortable to use this library in their project. 
This verification code is performed under the unit-test system and also based the particle platform.

## preparation for running this firmware.
* Electron/Photon/Core.
* DS18b20 or DS1822 one-wire temperature sensor.
* Breadboard.
* Resistor.Value varies from 1K to 10K.
* microUSB cable.
* Particle WEB IDE or DEV
* `Particle-cli` had been installed on computer.

## Library version list
* unit-test library `0.1.3`
* ds18b20 library `0.1.03`
* onewrire library `1.4.1`

## Verify process
  1. Setup the hardware system based on the `ds18b20.fzz` diagarm file. You may need to install Fritzing from [this website](http://fritzing.org/download/).You can also wire the hardware like the picture below.
 ![Image of wireDiagram](https://github.com/spark/ds18b20-photon/blob/verification/verified/wireDiagram.png)
  2. Create a project from WEB IED or Particle DEV and then. Add the `libraryTest_DS18B20.ino` file into that project.
  3. Add the `UNIT-TEST` and `DS18B20` library before compile that firmware.
  4. Once compiled successfully.Flash the firmware to your particle device.
  5. Make sure the device is connected to the computure and it can be recognized as a serial port on computer.
  6. run `Particle serial monitor` from terminal.
  7. After the serial port had been recognized, type in `t` to start the verification test.
  8. Follw the test instruction and run the test.
  
  
  
  




