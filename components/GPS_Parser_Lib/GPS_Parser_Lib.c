#include <stdio.h>
#include "GPS_Parser_Lib.h"

GPS_Data parse_gps_data(char packet[]){
    char params[NUM_PARAMS][LENGTH_PARAMS];
    char *sliced_string;
    sliced_string = strtok(packet, ",");
    int i = 0;
    while(sliced_string != NULL){
        params[i][LENGTH_PARAMS] = sliced_string;
        sliced_string = strtok(NULL, ",");
        i++;
    }

}