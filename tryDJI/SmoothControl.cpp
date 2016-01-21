#include"SmoothControl.h"

SmoothControl::SmoothControl()
{
    command=0;
    dcommand=0;
    ddcommand=0;
    intervalMS=50;
    maxCommandDiffPerSec=5;
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
        if(abs(dcommand)>(maxCommandDiffPerSec/(1000/intervalMS)))
        {
            command=command+sgn(dcommand)*maxCommandDiffPerSec/(1000/intervalMS);
        }
        else
        {
            command=command+dcommand;
        }
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

double SmoothControl::abs(double input)
{
    if(input<0)
    {
        input=-input;
    }
    return input;
}

