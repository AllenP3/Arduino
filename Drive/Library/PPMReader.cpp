#include "PPMReader.h"

PPMReader::PPMReader(byte interruptPin, byte channelAmount) {
    if (interruptPin > 0 && channelAmount > 0) {
        this->channelAmount = channelAmount;
        rawValues = new unsigned long[channelAmount];
        validValues = new unsigned long[channelAmount];
        for (int i = 0; i < channelAmount; ++i) {
            rawValues[i] = 0;
            validValues[i] = 0;
        }
        
        this->interruptPin = interruptPin;
        pinMode(interruptPin, INPUT);
        attachInterrupt(digitalPinToInterrupt(interruptPin), RISING);
    }
}

PPMReader::~PPMReader() {
    detachInterrupt(digitalPinToInterrupt(interruptPin));
    delete [] rawValues;
    delete [] validValues;
}

void PPMReader::handleInterrupt(int8_t interruptNum) {
    
    unsigned long previousMicros = microsAtLastPulse;
    microsAtLastPulse = micros();
    unsigned long time = microsAtLastPulse - previousMicros;

    if (time > blankTime) {
        
        pulseCounter = 0;
    }
    else {
        
        if (pulseCounter < channelAmount) {
            rawValues[pulseCounter] = time;
            if (time >= minChannelValue - channelValueMaxError && time <= maxChannelValue + channelValueMaxError) {
                validValues[pulseCounter] = constrain(time, minChannelValue, maxChannelValue);
            }
        }
        ++pulseCounter;
    }
}

unsigned long PPMReader::rawChannelValue(byte channel) {
    unsigned long value = 0;
    if (channel >= 1 && channel <= channelAmount) {
        noInterrupts();
        value = rawValues[channel-1];
        interrupts();
    }
    return value;
}

unsigned long PPMReader::latestValidChannelValue(byte channel, unsigned long defaultValue) {
    
    unsigned long value = defaultValue;
    if (channel >= 1 && channel <= channelAmount) {
        noInterrupts();
        value = validValues[channel-1];
        interrupts();
    }
    return value;
}
