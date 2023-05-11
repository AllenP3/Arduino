#ifndef PPM_READER
#define PPM_READER

#include <Arduino.h>
#include <InterruptHandler.h>


class PPMReader : InterruptHandler {

    public:
    
    // The range of a channel's possible values
    unsigned long minChannelValue = 1000;
    unsigned long maxChannelValue = 2000;

    /* The maximum error (in either direction) in channel value
     * with which the channel value is still considered valid */
    unsigned long channelValueMaxError = 10;

    /* The minimum value (time) after which the signal frame is considered to
     * be finished and we can start to expect a new signal frame. */
    unsigned long blankTime = 2100;


    private:

    // The pin from which to listen for interrupts
    byte interruptPin = 0;

    // The amount of channels to be expected from the PPM signal.
    byte channelAmount = 0;

    // Arrays for keeping track of channel values
    volatile unsigned long *rawValues = NULL;
    volatile unsigned long *validValues = NULL;

  
    volatile byte pulseCounter = 0;

   
    volatile unsigned long microsAtLastPulse = 0;


    public:
    PPMReader(byte interruptPin, byte channelAmount);
    ~PPMReader();

    /* Returns the latest raw (not necessarily valid) value for the
     * channel (starting from 1). */
    unsigned long rawChannelValue(byte channel);

    /* Returns the latest received value that was considered valid for the channel (starting from 1).
     * Returns defaultValue if the given channel hasn't received any valid values yet. */
    unsigned long latestValidChannelValue(byte channel, unsigned long defaultValue);

    private:

    // An interrupt service routine for handling the interrupts activated by PPM pulses
    virtual void handleInterrupt(int8_t interruptNum);

};
#endif
