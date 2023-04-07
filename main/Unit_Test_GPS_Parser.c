#include "GPS_Parser_Lib.h"
//Unit test for parse_gps_data function
bool gps_parser_tester(GPS_Data parsed_data, GPS_Data expected_data){
        if(strcmp(parsed_data.time,expected_data.time) || parsed_data.latitude != expected_data.latitude
        || parsed_data.lat_direction != expected_data.lat_direction || parsed_data.longitude != expected_data.longitude||
        parsed_data.long_direction != expected_data.long_direction || parsed_data.GPS_fix_quality != expected_data.GPS_fix_quality||
        parsed_data.no_of_satellites != expected_data.no_of_satellites || parsed_data.hdop != expected_data.hdop||
        parsed_data.altitude != expected_data.altitude || parsed_data.Geoid_separation != expected_data.Geoid_separation ||
        parsed_data.differential_age != expected_data.differential_age || strcmp(parsed_data.reference_Station_ID,expected_data.reference_Station_ID) ||
        parsed_data.checksum != expected_data.checksum || parsed_data.checksum_integrity != expected_data.checksum_integrity){
                return false;
        }
        else{
                return true;
        }
}
void app_main(void)
{   
    while(1){
        char packet[] = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E";
        parse_gps_data(packet);
        printf("dataa received");
    }
}
