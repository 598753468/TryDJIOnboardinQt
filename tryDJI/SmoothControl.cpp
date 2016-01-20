#include"SmoothControl.h"
#include"math.h"

SmoothControl::SmoothControl()
{
    command=0;
    dcommand=0;
    ddcommand=0;
    intervalMS=50;
    maxCommandDiffPerSec=2;
    ddcommandRate=0.01;
}

double SmoothControl::SendCommand(double targetCommand)
{
    targetSGN=sgn(targetCommand);
    SGN=sgn(command);
    if((SGN!=0)&&(SGN!=targetSGN))
    {
        command=targetCommand;
        dcommand=0;
    }
    else
    {
        diff=targetCommand-command;
        ddcommand=diff*ddcommandRate;
        dcommand=dcommand+ddcommand;
        if(dcommand>(maxCommandDiffPerSec/intervalMS))
        command=command+dcommand;
    }
    return command;
}

int SmoothControl::sgn(double input)
{
    if(input>0.0001)
    {
        return 1;
    }
    else if(input<-0.0001)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

