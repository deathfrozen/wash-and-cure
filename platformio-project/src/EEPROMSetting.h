#ifndef _HW2_EEPROMSetting_H
#define _HW2_EEPROMSetting_H
struct EEPROMSetting
{
    unsigned int WashingSpeed = 6500;
    unsigned int CureSpeed = 100;
    unsigned int WashingCycleTime = 120000;
    unsigned int CureCycleTime = 120000;
    unsigned int WashingSlot1Time = 600000;
    unsigned int WashingSlot2Time = 1200000;
    unsigned int WashingSlot3Time = 2400000;
    unsigned int WashingSlot4Time = 4800000;
    unsigned int CureSlot1Time = 600000;
    unsigned int CureSlot2Time = 1200000;
    unsigned int CureSlot3Time = 2400000;
    unsigned int CureSlot4Time = 4800000;
    unsigned int Acceleration = 1000;
};
#endif