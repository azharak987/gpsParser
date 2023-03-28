#include <stdio.h>
#include "GPS_Parser_Lib.h"

GPS_Data parse_gps_data(char packet[]){
    GPS_Data data;
    data.altitude= 0; data.checksum =0; 
    char *params[NUM_PARAMS];
    char *sliced_string = strtok(packet, ",");
    int i = 0;    
    while (sliced_string != NULL && i < NUM_PARAMS) {
        params[i++] = sliced_string;
        sliced_string = strtok(NULL, ",");
    }
    for(int i = 0; i<NUM_PARAMS; i++){
        printf("%s \n", params[i]);
    }
    return data;
}