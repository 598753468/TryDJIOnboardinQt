/* 
* CTimer.cpp 
* 
* Created on: 2009-7-13 
*      Author: DEAN 
*/  
  
#include "CTimer.h"  
#include <iostream>  
#include <sys/select.h>  
#include <time.h>  
#include <pthread.h>  
  
using namespace std;  
//////////////////////////public methods//////////////////////////  
CTimer::CTimer()
{  
    m_second=0;
    m_microsecond=0;
    Callback=0;
}  
  
CTimer::CTimer(long second, long microsecond)
{  
    m_second=second;
    m_microsecond=microsecond;
    Callback=0;
}  
  
CTimer::~CTimer()  
{  
}  
  
void CTimer::SetTimer(long second, long microsecond)  
{  
    m_second = second;  
    m_microsecond = microsecond;  
}  
  
void CTimer::StartTimer(CTimerCallBack callback)
{  
    Callback=callback;
    pthread_create(&thread_timer, NULL, OnTimer_stub, this);  
}  
  
void CTimer::StopTimer()  
{  
    pthread_cancel(thread_timer);  
    pthread_join(thread_timer, NULL); //wait the thread stopped  
}  
  
//////////////////////////private methods//////////////////////////  
void CTimer::thread_proc()  
{  
    while (true)  
    {  
        Callback(1);
        //OnTimer();
        pthread_testcancel();  
        struct timeval tempval;  
        tempval.tv_sec = m_second;  
        tempval.tv_usec = m_microsecond;  
        select(0, NULL, NULL, NULL, &tempval);  
    }  
}  
