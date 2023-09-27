#ifndef GearBoxE_h
#define GearBoxE_h
void GB__vSetup();
void GB__vChooseGear();


static struct stGearBox
{
    bool parking;
    bool neutral;
    bool reverse;
    bool drive;
}GearBoxStruct;

#endif