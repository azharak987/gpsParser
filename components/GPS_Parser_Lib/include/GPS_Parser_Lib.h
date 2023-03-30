#ifndef GPS_PARSER_LIB_H
#define GPS_PARSER_LIB_H
#define NUM_PARAMS 14
#include<string.h>
//A struct to store GPS Data
typedef struct{
    char time[9], lat_direction,
    long_direction, reference_Station_ID[4];
    int GPS_fix_quality, no_of_satellites, checksum;
    float altitude, Geoid_separation, differential_age, latitude, longitude, hdop;
} GPS_Data;
//A function which takes String as input and returns the GPS_Data struct 
GPS_Data parse_gps_data(char packet[]);
#endif