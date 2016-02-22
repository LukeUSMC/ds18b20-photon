#include "Particle-OneWire.h"
#include "application.h"

#define MAX_NAME 8
#define MAX_RETRIES 3

// Device resolution
#define TEMP_9_BIT  0x1F //  9 bit
#define TEMP_10_BIT 0x3F // 10 bit
#define TEMP_11_BIT 0x5F // 11 bit
#define TEMP_12_BIT 0x7F // 12 bit
//Parasite Powered or Not
#define READPOWERSUPPLY 0xB4

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
    void setResolution(uint8_t newResolution);
    bool readPowerSupply();
    void getROM(char szROM[]);
    byte getChipType();
    char* getChipName();
    float getTemperature();
    float convertToFahrenheit(float celsius);
    bool crcCheck();
};
