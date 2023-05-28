#include "mux.h"
#include <Arduino.h>

mux::mux(const unsigned int muxSig, const unsigned int muxS0, const unsigned int muxS1, const unsigned int muxS2, const unsigned int muxS3){
  this->muxSig = muxSig;
  this->muxS0 = muxS0;
  this->muxS1 = muxS1;
  this->muxS2 = muxS2;
  this->muxS3 = muxS3;
}

unsigned int mux::readMux(int pin){
  digitalWrite(this->muxS0, bitRead(pin, 0));
  digitalWrite(this->muxS1, bitRead(pin, 1));
  digitalWrite(this->muxS2, bitRead(pin, 2));
  digitalWrite(this->muxS3, bitRead(pin, 3));

  unsigned int output = digitalRead(this->muxSig);

  return output;
}