#include <TimeLib.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 12  // Data pin connected to the DS18B20

const int senderPins[] = {2,3,4,5,6,7,8,9};
const int receiverPin = 10;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

class Sender: public CommonClass  {
  public:
    String name;
    int send_start;
    int send_end;
    int sending_delay;

    Sender(String name, int send_start, int send_end, int delay, bool print = false): CommonClass(print), sending_delay(delay){
      name = name;
      send_start = send_start;
      send_end = send_end;
    }

    void init() override {
      for (int i= 0; i< 8; i++) {
        pinMode(senderPins[i], OUTPUT);
      }
      pinMode(receiverPin, INPUT);
      printIfConfigured("Started as Sender");
      sensors.begin();
    }

    bool receiveStartSignal() {
      byte receivedNumber = 0;
      bitWrite(receivedNumber, 0, digitalRead(receiverPin));
      CommonClass::printIfConfigured("Received value: " + String(receivedNumber));
      return receivedNumber == 1;
    }

    int readSecondOfMin(){
      time_t time_now = now();
      return second(time_now);
    }

    void waitForStartSignalAndSend(){
      if(receiveStartSignal()){
        printIfConfigured("Signal received");
        delay(sending_delay);
        int temp = (int)getTemp();
        sendNumber(temp);
        printIfConfigured("Number sent");
      }
    }

    float getTemp(){
      sensors.requestTemperatures();
      float temperature = sensors.getTempCByIndex(0);
      Serial.print("Temperature: " + String(temperature));
      return temperature;
    }

    void sendNumber(byte number){
      printIfConfigured("Arduino "+ name +" sending");
      
      for(int i=0; i<8; i++){
        digitalWrite(senderPins[i], bitRead(number, i));
      }

      printIfConfigured("Send Number " + String(number));
    }
};