

// This #include statement was automatically added by the Particle IDE.
#include "unit-test.h"
// This #include statement was automatically added by the Particle IDE.
#include "DS18B20.h"

#define UPDATE_INTERVAL 1000     //the udpate speed for the sensor

/**
 * Demonstrates a simple test that passes and one that fails.
 * Input/Output via serial.
 * To start the test, press 't'.
 *
 * The tests are run in alphabetical order.
 */

 DS18B20 ds18b20 = DS18B20(D4);

 unsigned long updateTime=0;
 int c=0;
 double current_temperature=0;
 double hot_temperature=0;
 double cool_temperature=0;
 char String[20]={};
 uint8_t retryTime=0;


//this is the first step, which need to wire up the sensor based on the diagram from Fritzing .
test(010_sensor_wireup)
{
    c = Serial.read();
    while (c!=-1) {     //this is used to clear up the catch in the serial buffer.
        c = Serial.read();
    }
    Serial.println("Please connect the sensor with photon/electron/core as Fritzing shows");
    Serial.println("Please type 'y' when you are ready");
    c = Serial.read();
    while((c!='Y')&&(c!='y'))
    {
        c = Serial.read();
    }
    assertEqual(c, 'y');
}

//this step is used to read oout all the info related with sensor, such as chip type and sensor name.
test(020_sensor_type)
{

    Serial.println("Please type 'y' when the sensor type and name is correct otherwise type 'n'");
    c= Serial.read();
    while((c!='n')&&(c!='y'))
    {
        c = Serial.read();
        if(millis()-updateTime>UPDATE_INTERVAL)         //setup the interval time to make sure the sensor will print out the info every 1 second
        {
            updateTime=millis();
            if(ds18b20.search())
            {
                Serial.printf("This chip type is: %x\r\n",ds18b20.getChipType());
                Serial.printf("This sensor name is: %s\r\n",ds18b20.getChipName());
                ds18b20.getROM(String);
               // ds18b20.resetsearch();         //need to reset the search???
                Serial.printf("The id is %s\r\n",String);           //get the id of ds18b20
            }
            else
                Serial.println("There is no chip had been found");
            Serial.println("Please type 'y' when the sensor type and name is correct otherwise type 'n'");
        }
    }
    assertEqual(c,'y');         //a system function which is from unit-test library
}

//This step is used to read out the temperature  from the sensor, that value should be very close to the REAL temperature.
test(030_sensor_value_normal)
{
    Serial.println("Please Check the temperature and press 'y' if it's normal temperature");
    c=Serial.read();
    while((c!='n')&&(c!='y'))
    {
        c=Serial.read();
        if(millis()-updateTime>UPDATE_INTERVAL)
        {
            updateTime = millis();
            current_temperature = ds18b20.getTemperature();
            if(!ds18b20.crcCheck()&&(retryTime<4))      //make sure the value is correct by checking the crc value,assume to stop the test once it cannot read out the value correclty four times.
            {
                Serial.printf("Get a bad value.Retry %d times\r\n",retryTime+1);
                retryTime++;
                if(retryTime==4)
                {
                    Serial.println("No temperature sensor is online now! Need to type 'n' to stop the test");
                }
            }
            else
            {
                retryTime=0;
                Serial.print("Current temperature is:");
                Serial.print(current_temperature);
                Serial.println(" celcuis");
                Serial.println("Type 'y' when the temeprature is reasonable otherwise type 'n'");
            }
        }
    }
    assertEqual(c,'y');
}

//This step is used to meassure the temperature when it's close to a heat source, which means the value should be higher than the last step's value.
test(040_sensor_value_hot)
{
    Serial.println("Put the sensor close to a heat source and type 'y' when you are ready");
    c=Serial.read();
    while(c!='y')           //waiting for the operator to start the test after attach the sensor to a heat source.
    {
        c=Serial.read();
    }
    c=0;    //clear the value.
    while((c!='n')&&(c!='y'))
    {
        c=Serial.read();
        if(millis()-updateTime>UPDATE_INTERVAL)
        {
            updateTime = millis();
            hot_temperature = ds18b20.getTemperature();
            if(!ds18b20.crcCheck()&&(retryTime<4))
            {
                Serial.printf("Get a bad value.Retry %d times\r\n",retryTime+1);
                retryTime++;
                if(retryTime==4)
                {
                    Serial.println("No temperature sensor is online now! Need to stop the test");
                }
            }
            else
            {
                retryTime=0;
                Serial.print("Current temperature is:");
                Serial.print(hot_temperature);
                Serial.println(" celcuis");
                Serial.println("Type 'y' when the temeprature is hotter than last step,otherwise type 'n'");
            }
        }
    }
    assertMore(hot_temperature,current_temperature);
}


//This step is used to measure the temperature when it's close to a cool source, which means the value should be lower than the last step's value
test(050_sensor_value_cool)
{
    Serial.println("Put the sensor close to a cool source and type 'y' when you are ready");
    c=Serial.read();
    while(c!='y')           //waiting for the operator to start the test after attach the sensor to a heat source.
    {
        c=Serial.read();
    }
    c=0;    //clear the value
    while((c!='n')&&(c!='y'))
    {
        c=Serial.read();
        if(millis()-updateTime>UPDATE_INTERVAL)
        {
            updateTime = millis();
            cool_temperature = ds18b20.getTemperature();
            if(!ds18b20.crcCheck()&&(retryTime<4))
            {
                Serial.printf("Get a bad value.Retry %d times\r\n",retryTime+1);
                retryTime++;
                if(retryTime==4)
                {
                    Serial.println("No temperature sensor is online now! Need to stop the test");
                }
            }
            else
            {
                retryTime=0;
                Serial.print("Current temperature is:");
                Serial.print(cool_temperature);
                Serial.println(" celcuis");
                Serial.println("Type 'y' when the temeprature is cooler than last step,otherwise type 'n'");
            }
        }
    }
    assertLess(cool_temperature,current_temperature);
}


//This step is used to measure the temperature when there is no power on VCC pin BUT the pull-up resistor on Data pin should still apply power.
test(060_sensor_parasite)
{
    Serial.println("Remove the power from VCC pin on temperature sensor and type 'y' when you are ready");
    c=Serial.read();
    while(c!='y')           //waiting for the operator to start the test after attach the sensor to a heat source.
    {
        c=Serial.read();
    }
    c=0;    //clear the value.
    while((c!='n')&&(c!='y'))
    {
        c=Serial.read();
        if(millis()-updateTime>UPDATE_INTERVAL)
        {
            updateTime = millis();
            current_temperature = ds18b20.getTemperature();
            if(!ds18b20.crcCheck()&&(retryTime<4))
            {
                Serial.printf("Get a bad value.Retry %d times\r\n",retryTime+1);
                retryTime++;
                if(retryTime==4)
                {
                    Serial.println("No temperature sensor is online now! Need to stop the test");
                }
            }
            else
            {
                retryTime=0;
                Serial.print("Current temperature is:");
                Serial.print(current_temperature);
                Serial.println(" celcuis");
                if(ds18b20.readPowerSupply())
                    Serial.println("The sensor works in parasite power mode now");
                else
                    Serial.println("The sensor isn't work in parasite power mode,please check the wire connection");
                Serial.println("Type 'y' when the temeprature is normal without the power on VCC pin,otherwise type 'n'");
            }
        }
    }
    assertEqual(c,'y');
}

//This step is used to verify the funtion of cascading sensor from one wire.Make sure the Data line of all those sensors are connected to the D4
test(070_sensor_cascade)
{

    Serial.println("Put two sensor with exactly the same circuit and type `y` when you are ready");
    c=Serial.read();
    while(c!='y')
    {
        c=Serial.read();
    }
    c=0;
    while((c!='y')&&(c!='n'))
    {
        c=Serial.read();
        if(millis()-updateTime>UPDATE_INTERVAL)
        {
            updateTime=millis();
            if(ds18b20.search())    //the searched value will be differenet if there are at least two sensor attaced to the same data line.
            {
                Serial.printf("This chip type is: %x\r\n",ds18b20.getChipType());
                Serial.printf("This sensor name is: %s\r\n",ds18b20.getChipName());
                ds18b20.getROM(String);
               // ds18b20.resetsearch();         //need to reset the search???
                Serial.printf("The id is %s\r\n",String);
            }
            else
                Serial.println("There is no chip had been found");
            Serial.println("Please type 'y' when you find two sensors otherwise type 'n'");
        }
    }
}

UNIT_TEST_APP()
