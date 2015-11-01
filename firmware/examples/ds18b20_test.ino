
DS18B20 ds18b20 = DS18B20(D2); //Sets Pin D2 for Water Temp Sensor
int led = D7;
char szInfo[64];
float pubTemp;
double celsius;
double fahrenheit;
unsigned int Metric_Publish_Rate = 30000;
unsigned int MetricnextPublishTime;
int DS18B20nextSampleTime;
int DS18B20_SAMPLE_INTERVAL = 2500;
int dsAttempts = 0;

void setup() {
    Time.zone(-5);
    Particle.syncTime();
    pinMode(D2, INPUT);
    Particle.variable("tempHotWater", &fahrenheit, DOUBLE);
    Serial.begin(115200);
}

void loop() {

if (millis() > DS18B20nextSampleTime){
  getTemp();
  }

  if (millis() > MetricnextPublishTime){
    Serial.println("Publishing now.");
    publishData();
  }
}


void publishData(){
  if(!ds18b20.crcCheck()){
    return;
  }
  sprintf(szInfo, "%2.2f", fahrenheit);
  Particle.publish("dsTmp", szInfo, PRIVATE);
  MetricnextPublishTime = millis() + Metric_Publish_Rate;
}

void getTemp(){
    if(!ds18b20.search()){
      ds18b20.resetsearch();
      celsius = ds18b20.getTemperature();
      Serial.println(celsius);
      while (!ds18b20.crcCheck() && dsAttempts < 4){
        Serial.println("Caught bad value.");
        dsAttempts++;
        Serial.print("Attempts to Read: ");
        Serial.println(dsAttempts);
        if (dsAttempts == 3){
          delay(1000);
        }
        ds18b20.resetsearch();
        celsius = ds18b20.getTemperature();
        continue;
      }
      dsAttempts = 0;
      fahrenheit = ds18b20.convertToFahrenheit(celsius);
      DS18B20nextSampleTime = millis() + DS18B20_SAMPLE_INTERVAL;
      Serial.println(fahrenheit);
    }
}
