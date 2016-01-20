#include"CTimer.h"

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
};
