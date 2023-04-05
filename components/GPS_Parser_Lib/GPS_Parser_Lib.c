#include <stdio.h>
#include "GPS_Parser_Lib.h"

GPS_Data parse_gps_data(char packet[]){
    //Struct GPS_Data to store the data
    GPS_Data data;
    data.altitude= 0; data.checksum =0; 
    //For getting the comma separated strings
    char *params[NUM_PARAMS];
    int params_count = 0, missing_params = 15;   
    int missing_params_pos[15];
    int empty_params = 0;
    //Identifying empty packets and storing their position in array.
    for (int i = 0; i < strlen(packet); i++) {
        if(packet[i] == ','){
            params_count++;
        }
        if (packet[i] == ',' && packet[i+1] == ',') {
            missing_params_pos[empty_params] = params_count;
            empty_params++;
        }
    }
    if(!strcmp(packet, "") || packet == NULL){
        printf("Empty Packet");
        return;
    }
    else{
        //Sliced string based on Comma
        char *sliced_string = strtok(packet, ",");
        int i = 0, j = 0;
        //Splitting the packet and then storing it in params.
        while (sliced_string != NULL && i < NUM_PARAMS) {
            //Adding "Missing", in place of missing parameter.
            if(i == missing_params_pos[j]){
                params[i] = (char*)"Missing";
                i++;j++;
            }
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

            //GPS Quality Indicator
            data.GPS_fix_quality = atoi(params[6]);
            
            //Number of Satelites used
            data.no_of_satellites = atoi(params[7]);

            //Horizontal Dilution of Precision
            data.hdop = atof(params[8]);

            //Geoid Separation
            data.Geoid_separation = atof(params[11]);


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