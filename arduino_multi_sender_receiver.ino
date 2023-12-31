#include "common_class.h"
#include "sender.h"
#include "receiver.h"

const bool is_receiver = true;
const Receiver receiver = Receiver("receiver", true);
const Sender sender = Sender("sender", 0, 10, 3, true);
//const Sender sender = Sender("sender", 10, 20, true);

void setup() {
  Serial.begin(9600);

  if(is_receiver){
    receiver.init();
  }else {
    // is sender
    sender.init();
  }
}

void loop() {
  if(is_receiver){
      receiver.sendStartSignal();
      receiver.receiveNumber();
      delay(1000);
  }else {
    // is_sender
    for (byte i =0; i <= 255; i++){
      sender.waitForStartSignalAndSend();
      delay(1000);
    }
  }
}