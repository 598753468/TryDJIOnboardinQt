#include"Transmission.h"

double Transmission::Latitude=0;
double Transmission::Longitude=0;
bool Transmission::IsValid=false;
int Transmission::dataLength=18;
struct itimerval Transmission::tick={{0,5000000},{0,5000000}};

Transmission::Transmission()
{
    //signal(SIGALRM, OnTimeOut);
}

void Transmission::UpdatePositionCallBack(unsigned char *buf,unsigned char len)
{
    unsigned char data[len];
    memcpy(data,buf,len);
    if((len==dataLength)&&(data[len-1]==CheckSum(data)))
    {
        memcpy(&Transmission::Latitude,&data[0],8);
        memcpy(&Transmission::Longitude,&data[8],8);
        Transmission::IsValid=data[16];
        //setitimer(ITIMER_REAL,&Transmission::tick,NULL);
    }
    else
    {
        Transmission::IsValid=false;
    }
}


unsigned char Transmission::CheckSum(unsigned char buf[])
{
    unsigned char sum=0;
    for(int j=0;j<Transmission::dataLength-1;j++)
    {
        sum=(unsigned char)(sum+buf[j]);
    }
    return sum;
}
void  Transmission::OnTimeOut(int )
{
    Transmission::IsValid=false;
}

