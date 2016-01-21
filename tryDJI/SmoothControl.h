#ifndef SmoothControl_H_
#define SmoothControl_H_
#include"Transmission.h"
class SmoothControl
{
public:
    SmoothControl();
    double SendCommand(double targetCommand);
    int intervalMS;
    double maxCommandDiffPerSec;
    double ddcommandRate;
private:
    double command,dcommand,ddcommand,diff;
    int targetSGN,SGN;
    int sgn(double input);
    double abs(double input);
};

class GPSFilter
{
public:
    GPSFilter();

private:


};
#endif
