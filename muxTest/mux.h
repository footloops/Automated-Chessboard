#ifndef MUX_H
#define MUX_H

class mux
{
  public:
    mux(const unsigned int muxSig, const unsigned int muxS0, const unsigned int muxS1, const unsigned int muxS2, const unsigned int muxS3);

    unsigned int readMux(int pin);

    void clearSig();
  private:
    unsigned int muxSig;
    unsigned int muxS0;
    unsigned int muxS1;
    unsigned int muxS2;
    unsigned int muxS3;
};

#endif
