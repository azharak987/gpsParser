#ifndef GPS_PARSER_LIB_H
#define GPS_PARSER_LIB_H
#define NUM_PARAMS 14
#define LENGTH_PARAMS 15
#include<string.h>
//A struct to store GPS Data
typedef struct{
    char time[9], latitude[9], lat_direction[1],
    longitude[10], long_direction[1], reference_Station_ID[4];
    int GPS_fix_quality, no_of_satellites, checksum;
    float altitude, Geoid_separation, differential_age;
} GPS_Data;
//A function which takes String as input and returns the GPS_Data struct 
GPS_Data parse_gps_data(char packet[]);
#endif