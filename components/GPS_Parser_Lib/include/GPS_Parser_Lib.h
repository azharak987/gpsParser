#ifndef GPS_PARSER_LIB_H
#define GPS_PARSER_LIB_H
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#define NUM_PARAMS 15
#define INT_FLOAT_MISSING_CODE -111
#define STR_MISSING_CODE "MIS"
#define CHAR_MISSING_CODE 'M'

//A struct to store GPS Data
typedef struct {
    char time[9];
    char lat_direction;
    char packet_type[9];
    char long_direction;
    char reference_Station_ID[4];
    int GPS_fix_quality;
    int no_of_satellites;
    int checksum;
    float altitude;
    float Geoid_separation;
    float latitude;
    float longitude;
    float hdop;
    float differential_age;
    bool checksum_integrity;
} GPS_Data;
//A function which takes String as input and returns the GPS_Data struct 
GPS_Data parse_gps_data(char packet[]);
#endif