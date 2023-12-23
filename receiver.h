const int receiverPins[] = {2,3,4,5,7,8,9,10};

class Receiver : public CommonClass {
  public:
    String name;

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
};