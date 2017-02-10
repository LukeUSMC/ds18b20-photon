#include <DS18B20.h>
#include <math.h>

DS18B20 ds18b20(D2, true); //Sets Pin D2 for Water Temp Sensor and 
                           // this is the only sensor on bus
char szInfo[64];
double celsius;
double fahrenheit;
unsigned int Metric_Publish_Rate = 30000;
unsigned int MetricLastPublishTime;
unsigned int DS18B20lastSampleTime;
unsigned int DS18B20_SAMPLE_INTERVAL = 2500;

void setup() {
  Time.zone(-5);
  Particle.variable("tempHotWater", &fahrenheit, DOUBLE);
  Serial.begin(115200);
}

void loop() {
  if (millis() - DS18B20lastSampleTime >= DS18B20_SAMPLE_INTERVAL){
    getTemp();
  }

  if (millis() - MetricLastPublishTime >= Metric_Publish_Rate){
    Serial.println("Publishing now.");
    publishData();
  }
}

void publishData(){
  if(!ds18b20.crcCheck()){      //make sure the value is correct
    return;
  }
  sprintf(szInfo, "%2.2f", fahrenheit);
  Particle.publish("dsTmp", szInfo, PRIVATE);
  MetricLastPublishTime = millis();
}

void getTemp(){
  float _temp;
  do {
    _temp = ds18b20.getTemperature();
  } while (!ds18b20.crcCheck() && DS18B20_MAXRETRY > i++);

  if (i < DS18B20_MAXRETRY) {
    celsius = _temp;
    fahrenheit = ds18b20.convertToFahrenheit(_temp);
    Serial.println(fahrenheit);
  }
  else {
    celsius = fahrenheit = NAN;
    Serial.println("Invalid reading");
  }
  DS18B20lastSampleTime = millis();
}
