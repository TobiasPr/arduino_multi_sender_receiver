#include <TimeLib.h>

const int senderPins[] = {2,3,4,5,6,7,8,9};

class Sender: public CommonClass  {
  public:
    String name;
    int send_start;
    int send_end;

    Sender(String name, int send_start, int send_end, bool print = false): CommonClass(print){
      name = name;
      send_start = send_start;
      send_end = send_end;
      printInfo = printInfo;
    }

    void init() override {
      for (int i= 0; i< 8; i++) {
        pinMode(senderPins[i], OUTPUT);
      }
      printIfConfigured("Started as Sender");
    }

    int readSecondOfMin(){
      time_t time_now = now();
      return second(time_now);
    }

    void sendNumber(byte number){
      // Check if 30 seconds have passed
      if (sec_of_min >= send_start && sec_of_min <= send_end) {
        printIfConfigured("Arduino "+ name +" sending");
        
        for(int i=0; i<8; i++){
          digitalWrite(senderPins[i], bitRead(number, i));
        }

        printIfConfigured("Send Number " + String(number));
      }
    }
};