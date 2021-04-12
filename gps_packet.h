#ifndef GPS_PACKET_H
#define GPS_PACKET_H
// data_format/gps_packet.h
#pragma once
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <ctime>
using namespace std;

class GpsPacket {
public:
    GpsPacket();
    //int initialize(const char *devicename);

    /* DATA */ // 참고: https://github.com/SammyB428/NMEA0183/blob/master/GGA.HPP
    time_t Time;
    double Latitude;
    int NorthSouth;
    double Longitude;
    int EastWest;
    int GPSQuality;
    int NumberOfSatellitesInUse;
    double HorizontalDilutionOfPrecision;
    double AntennaAltitudeMeters;
    double GeoidalSeparationMeters;
    double AgeOfDifferentialGPSDataSeconds;
    int DifferentialReferenceStationID;

};

GpsPacket::GpsPacket(){
    Time = 0;
    Latitude = 0.0;
    NorthSouth = 0;
    Longitude = 0.0;
    EastWest = 0;
    GPSQuality = 0;
    NumberOfSatellitesInUse = 0;
    HorizontalDilutionOfPrecision = 0.0;
    AntennaAltitudeMeters = 0.0 ;
    GeoidalSeparationMeters = 0.0;
    AgeOfDifferentialGPSDataSeconds = 0.0 ;
    DifferentialReferenceStationID= 0;
}
#endif // GPS_PACKET_H
