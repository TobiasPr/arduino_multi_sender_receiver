const int receiverPins[] = {2,3,4,5,7,8,9,10};
const int senderPin = 0;

const unsigned long interval = 20000;

class Receiver : public CommonClass {
  public:
    String name;
    unsigned long previousMillis;

    Receiver(String name, bool print = false): CommonClass(print){
      name = name;
    }

    void init() override {
      for (int i= 0; i< 8; i++) {
        pinMode(receiverPins[i], INPUT);
      }
      CommonClass::printIfConfigured("Started as Receiver");
    }

    byte receiveNumber() {
      byte receivedNumber = 0;
      for(int i=0; i < 8; i++) {
        bitWrite(receivedNumber, i, digitalRead(receiverPins[i]));
      }
      CommonClass::printIfConfigured("Received value: " + String(receivedNumber));
      return receivedNumber;
    }

    void sendStartSignal(){
      unsigned long currentMillis = millis();

      // Check if 30 seconds have passed
      if (currentMillis - previousMillis >= interval) {
        // Perform your action here

        // Update the previousMillis for the next interval
        previousMillis = currentMillis;
        int start_signal = 1;

        digitalWrite(senderPin, bitRead(start_signal, senderPin));

        printIfConfigured("Send Start Signal " + String(start_signal));
      }
    }
};