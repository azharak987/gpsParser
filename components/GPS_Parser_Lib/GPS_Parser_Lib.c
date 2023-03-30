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
           printf("Valid Data. \n");
            //Time
            //Extract time from the data.
            int hours = (atof(params[1]))/10000;
            int mins = (atof(params[1])-(hours*10000))/100;
            int secs = (atof(params[1])-((hours*10000) + (mins*100)));
            //Join Hours, Mins, and Secs into one string.
            sprintf(data.time, "HH:MM:SS: %d:%d:%d", hours, mins, secs);
            //Tested Time.

            //Latitude
            //Extract Latitude in degrees from the data
            int degrees = (atof(params[2]))/100;
            //Converting minutes into degrees
            float mins_to_degrees= ((atof(params[2]))-degrees*100)/60;
            //Storing in GPS_Data
            data.latitude = degrees+mins_to_degrees;
            //Latitude Direction
            data.lat_direction = *params[3];
            //Tested Latitude
            
            //Longitude 
            //Extract Longitude in degrees from the data
            degrees = (atof(params[4]))/100;
            //Converting minutes into degrees
            mins_to_degrees= ((atof(params[4]))-degrees*100)/60;
            //Storing in GPS_Data
            data.longitude = degrees+mins_to_degrees;
            //Longitude Direction
            data.long_direction = *params[5];
            //Tested Longitude
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