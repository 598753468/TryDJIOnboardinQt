#ifndef Transmission_H_
#define Transmission_H_
#include<sys/time.h>
#include<signal.h>
#include <iostream>
#include <stdio.h>
#include <string.h>


class Transmission
{
public:
    static double Latitude,Longitude,Altitude,Speed,Accuracy;
    static bool IsValid;
    static int dataLength;
    static struct itimerval tick;
    Transmission();
    static void UpdatePositionCallBack(unsigned char *buf,unsigned char len);
private:
    static unsigned char CheckSum(unsigned char buf[]);
    static void  OnTimeOut(int hehe);
};
#endif

