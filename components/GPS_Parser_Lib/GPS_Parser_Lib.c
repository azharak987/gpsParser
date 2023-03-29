#include <stdio.h>
#include "GPS_Parser_Lib.h"

GPS_Data parse_gps_data(char packet[]){
    //Struct GPS_Data to store the data
    GPS_Data data;
    data.altitude= 0; data.checksum =0; 
    //For getting the comma separated strings
    char *params[NUM_PARAMS];
    if(!strcmp(packet, "") || packet == NULL){
        printf("Empty Packet");
        return;
    }
    else{
        //Sliced string based on Comma
        char *sliced_string = strtok(packet, ",");
        int i = 0;
        //Splitting the packet and then storing it in params.
        while (sliced_string != NULL && i < NUM_PARAMS) {
            params[i++] = sliced_string;
            sliced_string = strtok(NULL, ",");
        }
        //Comparing the first substring with the packet type to check validity.
        if(!strcmp(params[0], "$GPGGA")){
            printf("Valid Data");
        }
        else{
            return;
        }
    }
    for(int i = 0; i<NUM_PARAMS; i++){
        printf("%s \n", params[i]);
    }
    return data;
}