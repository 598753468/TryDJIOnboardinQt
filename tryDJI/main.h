#ifndef MAIN_H_
#define MAIN_H_
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

double pi=3.14159265358979326226;
//参数由matlab获得
const float fc1= 685.753598683736 / 1.6*2.25,
fc2 = 686.632925917435 / 1.6*2.25,
cc1 = 564.317943775214 / 1.6*2.25,
cc2 = 360.798124289830 / 1.6*2.25,
kc1 = -0.307489100043000,
kc2 = 0.0791349291021755,
kc3 = 0.00508,
kc4 = -0.00051;
float distorsionCoeff[]={kc1,kc2,kc3,kc4};
CameraCalibration calibration(fc1,fc2,cc1,cc2,distorsionCoeff);
MarkerDetector markerDetector(calibration);
cv::VideoCapture cap;
#endif
