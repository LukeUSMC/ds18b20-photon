#include "Particle-OneWire.h"
#include "application.h"

#define MAX_NAME 8
#define MAX_RETRIES 3

class DS18B20{
private:
    OneWire* ds;
    byte data[12];
    byte addr[8];
    byte type_s;
    byte chiptype;
    byte _dataCRC;
    byte _readCRC;
    char szName[MAX_NAME];

public:
    DS18B20(uint16_t pin);
    boolean search();
    void resetsearch();
    void getROM(char szROM[]);
    byte getChipType();
    char* getChipName();
    float getTemperature();
    float convertToFahrenheit(float celsius);
    bool crcCheck();
};
