#include <stdio.h>
#include "GPS_Parser_Lib.h"

GPS_Data parse_gps_data(char packet[]){
    //Struct GPS_Data to store the data
    GPS_Data data;
    //Initializing the data with error codes.
    strcpy(data.time, STR_MISSING_CODE);
    data.lat_direction = CHAR_MISSING_CODE;
    data.long_direction = CHAR_MISSING_CODE;
    strcpy(data.reference_Station_ID, STR_MISSING_CODE);
    data.GPS_fix_quality = INT_FLOAT_MISSING_CODE;
    data.no_of_satellites = INT_FLOAT_MISSING_CODE;
    data.checksum = INT_FLOAT_MISSING_CODE;
    data.altitude = INT_FLOAT_MISSING_CODE;
    data.Geoid_separation = INT_FLOAT_MISSING_CODE;
    data.latitude = INT_FLOAT_MISSING_CODE;
    data.longitude = INT_FLOAT_MISSING_CODE;
    data.hdop = INT_FLOAT_MISSING_CODE;
    data.differential_age = INT_FLOAT_MISSING_CODE;
    data.checksum_integrity = false;
    //For getting the comma separated strings
    char *params[NUM_PARAMS];
    int params_count = 0, missing_params = 15;   
    int missing_params_pos[15];
    int empty_params = 0;
    int calculated_checksum = 0; 
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
    //Check for any parameters missing at the end of packet
    if(params_count < 15){
        params_count++;
        //Adding the missing parameters positions to missing_params_pos Array
        for(; params_count<15;params_count++){
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
        //Adding Missing for parameters missed at the end of packet
        for(;i<15;i++){
            if(i == missing_params_pos[j]){
                params[i] = (char*)"Missing";
                j++;  
            }
        }
        //Comparing the first substring with the packet type to check validity.
        if(!strcmp(params[0], "$GPGGA")){
            //Printf Statement
            //Time
            if(strcmp(params[1], "Missing")){
                //Extract time from the data.
                int hours = (atof(params[1]))/10000;
                int mins = (atof(params[1])-(hours*10000))/100;
                int secs = (atof(params[1])-((hours*10000) + (mins*100)));
                //Join Hours, Mins, and Secs into one string.
                sprintf(data.time, "HH:MM:SS: %d:%d:%d", hours, mins, secs);
                //Tested Time.
            }
            else{
                strcpy(data.time, STR_MISSING_CODE);
            }
            //Latitude
            if(strcmp(params[2], "Missing")){
                //Extract Latitude in degrees from the data
                int degrees = (atof(params[2]))/100;
                //Converting minutes into degrees
                float mins_to_degrees= ((atof(params[2]))-degrees*100)/60;
                //Storing in GPS_Data
                data.latitude = degrees+mins_to_degrees;
            }
            else{
                data.latitude = INT_FLOAT_MISSING_CODE;
            }
            //Latitude Direction
            if(strcmp(params[3], "Missing")){
                data.lat_direction = *params[3];
            }
            else{
                data.lat_direction = CHAR_MISSING_CODE;
            }
            //Longitude 
            if(strcmp(params[4], "Missing")){
                //Extract Longitude in degrees from the data
                int degrees = (atof(params[4]))/100;
                //Converting minutes into degrees
                float mins_to_degrees= ((atof(params[4]))-degrees*100)/60;
                //Storing in GPS_Data
                data.longitude = degrees+mins_to_degrees;
            }
            else{
                data.longitude = INT_FLOAT_MISSING_CODE;
            }
            //Longitude Direction
            if(strcmp(params[5], "Missing")){
                data.long_direction = *params[5];
            }
            else{
                data.long_direction = 'M';
            }
            //GPS Quality Indicator
            if(strcmp(params[6], "Missing")){
                data.GPS_fix_quality = atoi(params[6]);
            }
            else{
                data.GPS_fix_quality = INT_FLOAT_MISSING_CODE;
            }
            //Number of Satelites used
            if(strcmp(params[7], "Missing")){
                data.no_of_satellites = atoi(params[7]);
            }
            else{
                data.no_of_satellites = INT_FLOAT_MISSING_CODE;
            }
            //HDOP
            if(strcmp(params[8], "Missing")){
                data.hdop = atof(params[8]);
            }
            else{
                data.hdop = INT_FLOAT_MISSING_CODE;
            }

            //Altitude
            if(strcmp(params[9], "Missing")){
                data.altitude = atof(params[9]);
            }
            else{
                data.altitude = INT_FLOAT_MISSING_CODE;
            }
            //Geoid Separation
            if(strcmp(params[11], "Missing")){
                data.Geoid_separation = atof(params[11]);
            }
            else{
                data.Geoid_separation = INT_FLOAT_MISSING_CODE;
            }
            //Differential Age
            if(strcmp(params[13], "Missing")){
                data.differential_age = atof(params[13]);
            }
            else{
                data.differential_age = INT_FLOAT_MISSING_CODE;
            }
            //Getting Check sum and Reference Station ID
            //If the data is present in the packet
            if(strcmp(params[14], "Missing")){
                //Splitting by *
                char *substring = strtok(params[14], "*");
                char *substring_data[2];
                i=0;
                while (substring != NULL && i < 2) {
                    substring_data[i++] = substring;
                    substring = strtok(NULL, "*");
                }
                //If Reference station ID is missing
                //That is the first character of the string will be *
                //Then getting only the checksum
                if(params[14][0] == '*'){
                    data.checksum = strtol(substring_data[0], NULL, 16);
                    strcpy(data.reference_Station_ID, "MISS");
                }
                //If the Reference ID is present then saving the data in the variables.
                else{
                    strcpy(data.reference_Station_ID, substring_data[0]);
                    data.checksum = strtol(substring_data[1], NULL, 16);
                }
            }
            else{
                strcpy(data.reference_Station_ID, STR_MISSING_CODE);
                data.checksum = INT_FLOAT_MISSING_CODE;
                printf(data.reference_Station_ID);
            }
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