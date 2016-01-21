//============================================================================
// Name        : main.cpp
// Author      : wuyuwei
// Version     :
// Copyright   : DJI Inc
// Description : DJI Onboard API test in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "DJI_LIB/DJI_Pro_Sample.h"
#include "math.h"
#include"Transmission.h"
#include<opencv2/opencv.hpp>
#include"CTimer.h"
#include"SmoothControl.h"


#include"OpenCV_LIB/Marker.hpp"
#include"OpenCV_LIB/MarkerDetector.hpp"
#include"OpenCV_LIB/BGRAVideoFrame.h"

using namespace std;

extern  bool IsSerialPortOpened;
extern bool IsActivated;
extern bool IsUnderControl;
api_pos_data_t pos;


void DJI_Pro_User_Activate_Callback(unsigned short ack);
void GetControl_CallBack(unsigned short res);
void OnTime_handle(int);

void Dji_Followme(void);
double  lati_mobile;
double  longti_mobile;
double GetLatDistance(double DestLat,double TargetLat);
double GetLngDistance(double lat, double DestLng, double TargetLng);
attitude_data_t fellowData = {0b10000000,0,0,0,0};
activate_data_t user_act_data;
SmoothControl xcontrol,ycontrol;

//debug
/////////


int main(int argc,char **argv)
{
    //Message
    if(argc == 2 && strcmp(argv[1],"-v") == 0)
    {
        printf("\nDJI Onboard API Cmdline Test,Ver 1.0.0\n\n");
        return 0;
    }
    printf("\nDJI Onboard API Cmdline Test,Ver 1.1.0\n\n");
    //Callback
    DJI_Pro_Register_Transparent_Transmission_Callback(Transmission::UpdatePositionCallBack);
    //SerialPort
    if(DJI_Sample_Setup() < 0)
    {
        printf("Serial Port Open ERROR\n");
        IsSerialPortOpened = false;
        return 0;
    }
    else
    {
        IsSerialPortOpened = true;
    }
    //user key
    char temp_buf[65];
    char app_bundle_id[32] = "1234567890";
    user_act_data.app_key = temp_buf;
    user_act_data.app_ver = SDK_VERSION;
    strcpy((char*)user_act_data.app_bundle_id, app_bundle_id);
    if(DJI_Pro_Get_Cfg(NULL,NULL,&user_act_data.app_id,&user_act_data.app_api_level,user_act_data.app_key) == 0)
    {
        /* user setting */
        printf("--------------------------\n");
        printf("app id=%d\n",user_act_data.app_id);
        printf("app api level=%d\n",user_act_data.app_api_level);
        printf("app key=%s\n",user_act_data.app_key);
        printf("--------------------------\n");
    }
    else
    {
        printf("ERROR:There is no user account\n");
        return 0;
    }
    DJI_Pro_Activate_API(&user_act_data,DJI_Pro_User_Activate_Callback);
    CTimer timer(0,50);                                                                                   //wzL
    timer.StartTimer(&OnTime_handle);                                                        //
    //debug

    /////////
    //loop forbid exit
    while(1)
    {
        cv::waitKey(0);
    }
    double pi=3.14159265358979326226;
    //参数由matlab获得
    float fc1, fc2, cc1, cc2, kc1, kc2, kc3, kc4;
    fc1 = 685.753598683736 / 1.6*2.25;
    fc2 = 686.632925917435 / 1.6*2.25;
    cc1 = 564.317943775214 / 1.6*2.25;
    cc2 = 360.798124289830 / 1.6*2.25;
    kc1 = -0.307489100043000;
    kc2 = 0.0791349291021755;
    kc3 = 0.00508;
    kc4 = -0.00051;
    float distorsionCoeff[]={kc1,kc2,kc3,kc4};
    CameraCalibration calibration(fc1,fc2,cc1,cc2,distorsionCoeff);
    MarkerDetector markerDetector(calibration);
    markerDetector.ChangeMarkerSize(0.9);
    cv::VideoCapture cap;
    cap.open(0);
    return 0;
}
void Dji_Followme(void)
{
    if(Transmission::IsValid)
    {
        DJI_Pro_Get_GPS(&pos);
        lati_mobile=Transmission::Latitude*3.141592654/180;
        longti_mobile=Transmission::Longitude*3.141592654/180;
        //fellowData.roll_or_x = GetLatDistance(pos.lati, lati_mobile);
        //fellowData.pitch_or_y = GetLngDistance(lati_mobile, pos.longti,longti_mobile);
        fellowData.roll_or_x=xcontrol.SendCommand(GetLatDistance(pos.lati, lati_mobile));
        fellowData.pitch_or_y=ycontrol.SendCommand( GetLngDistance(lati_mobile, pos.longti,longti_mobile));
        fellowData.yaw = 0;
        DJI_Pro_Attitude_Control(&fellowData);
    }
    else
    {
        fellowData.ctrl_flag = 0b01000000;
        fellowData.pitch_or_y = 0;
        fellowData.roll_or_x = 0;
        fellowData.thr_z = 0;
        fellowData.yaw = 0;
        DJI_Pro_Attitude_Control(&fellowData);
    }
}
// 2016-01-16 wei
void OnTime_handle(int )
{
    static int count=0;
    count++;
    //    api_ctrl_info_data_t ctrl_info;
    if (!IsSerialPortOpened)
    {
        DJI_Sample_Setup();
    }
    else if (!IsActivated)
    {
        if(count==20)
        {
            DJI_Pro_Activate_API(&user_act_data,DJI_Pro_User_Activate_Callback);
            count=0;
        }
    }
    else
    {
        if(count==20)
        {
            DJI_Pro_Control_Management(1,GetControl_CallBack);
            count=0;
        }
        if(IsUnderControl)
        {
            Dji_Followme();
        }
    }
}
double GetLatDistance(double DestLat, double TargetLat)
{
    double mod;
    mod=6371393.0*acos(sin(DestLat)*sin(TargetLat)+cos(DestLat)*cos(TargetLat));
    if(DestLat>TargetLat)
    {
        mod=-mod;
    }
    return mod;
}

double GetLngDistance(double lat, double DestLng, double TargetLng)
{
    double mod;
    mod=6371393.0*acos(sin(lat)*sin(lat)+cos(lat)*cos(lat)*cos(DestLng-TargetLng));
    if(DestLng>TargetLng)
    {
        mod=-mod;
    }
    return mod;
}
