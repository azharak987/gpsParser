#include "GPS_Parser_Lib.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//Unit test for parse_gps_data function
bool gps_parser_test(GPS_Data parsed_data, GPS_Data expected_data){
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

void print_parsed_data(GPS_Data data_received){
    char toStr[40];
    sprintf(toStr, "Packet Type: %s\n",data_received.packet_type);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }
    sprintf(toStr, "Time: %s\n",data_received.time);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }
    sprintf(toStr, "Latitude: %f\n", data_received.latitude);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }
    sprintf(toStr, "Latitude Direction %c\n", data_received.lat_direction);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }

    sprintf(toStr, "Longitude: %f\n", data_received.longitude);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }

    sprintf(toStr, "Longitude Direction: %c\n", data_received.long_direction);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }

    sprintf(toStr, "GPS Quality Indicator: %d\n", data_received.GPS_fix_quality);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }

    sprintf(toStr, "Number of Satelites used: %d\n", data_received.no_of_satellites);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }

    sprintf(toStr, "HDOP: %0.2f\n", data_received.hdop);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }

    sprintf(toStr, "Altitude: %0.2f\n", data_received.altitude);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }

    sprintf(toStr, "Geoidal Separation: %0.2f\n", data_received.Geoid_separation);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }

    sprintf(toStr, "Age of Differential GPS Data: %0.2f\n", data_received.differential_age);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }

    sprintf(toStr, "Reference Station ID: %s\n",data_received.reference_Station_ID);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }

    sprintf(toStr, "CheckSum Value: %d\n", data_received.checksum);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    };

    sprintf(toStr, "Packet Integrity Verification: %d\n", data_received.checksum_integrity);
    uart_write_bytes(UART_NUM_0, toStr, strlen(toStr));
    for (int i = 0; i < 40; i++) {
        toStr[i] = NULL;
    }
}

uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
};
void app_main(void)
{
        //UART Configuration to Print data on Serial
        uart_param_config(UART_NUM_0, &uart_config);
        uart_set_pin(UART_NUM_0, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
        uart_driver_install(UART_NUM_0, 1024, 0, 0, NULL, 0);
    while(1){
        //Instruction Message
        char msg[] = "Missing, Miss, MIS, M, -111, -111.00 represents Missing Parameters\n";
        char separator[] = "\n****************************************\n";
        uart_write_bytes(UART_NUM_0, msg, strlen(msg));
        uart_write_bytes(UART_NUM_0, "..\n", 3);
        uart_write_bytes(UART_NUM_0, "..\n", 3);
        //Printing the Packet
        uart_write_bytes(UART_NUM_0, "Packet to be Parsed: ", 22);
        char packet[] = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E";
        uart_write_bytes(UART_NUM_0, packet, strlen(packet));
        uart_write_bytes(UART_NUM_0, " \n", 3);
        //Parsing GPS Data
        GPS_Data received_data = parse_gps_data(packet);
        //Printing the parsed Data
        print_parsed_data(received_data);
        GPS_Data expected_data;
        //Expected Data for the Packet
        strcpy(expected_data.time, "0:21:53");
        expected_data.latitude = 33.711029;
        expected_data.lat_direction = 'N';
        expected_data.longitude = 117.856430;
        expected_data.long_direction = 'W';
        expected_data.GPS_fix_quality = 1;
        expected_data.no_of_satellites = 10;
        expected_data.hdop = 1.20;
        expected_data.Geoid_separation = -34.20;
        expected_data.altitude = 27.00;
        expected_data.differential_age = -111.00;
        strcpy(expected_data.reference_Station_ID, "0000");
        expected_data.checksum = 94;
        expected_data.checksum_integrity = 1;
        //Performing test and checking result
        if(gps_parser_test(received_data, expected_data)){
            uart_write_bytes(UART_NUM_0, "Test Passed\n", 12);
        }
        else{
            uart_write_bytes(UART_NUM_0, "Test Failed\n", 12);
        }

        uart_write_bytes(UART_NUM_0, separator, strlen(separator));
        uart_write_bytes(UART_NUM_0, "Missing Paramters\n", 18);
        //Missing Parameters, Latitude is missing
        char packet2[] = "$GPGGA,002153.000,,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E";
        //Printing the Packet
        uart_write_bytes(UART_NUM_0, "Packet to be Parsed: ", 22);
        uart_write_bytes(UART_NUM_0, packet2, strlen(packet2));
        uart_write_bytes(UART_NUM_0, " \n", 3);
        //Parsing GPS Data
        GPS_Data received_data2 = parse_gps_data(packet2);
        //Printing the parsed Data
        print_parsed_data(received_data2);
        //Expected Data for the Packet
        strcpy(expected_data.time, "0:21:53");
        expected_data.latitude = -111.00;
        expected_data.lat_direction = 'N';
        expected_data.longitude = 117.856430;
        expected_data.long_direction = 'W';
        expected_data.GPS_fix_quality = 1;
        expected_data.no_of_satellites = 10;
        expected_data.hdop = 1.20;
        expected_data.Geoid_separation = -34.20;
        expected_data.altitude = 27.00;
        expected_data.differential_age = -111.00;
        strcpy(expected_data.reference_Station_ID, "0000");
        expected_data.checksum = 94;
        expected_data.checksum_integrity = 0;
        //Performing test and checking result
        if(gps_parser_test(received_data2, expected_data)){
            uart_write_bytes(UART_NUM_0, "Test Passed\n", 12);
        }
        else{
            uart_write_bytes(UART_NUM_0, "Test Failed\n", 12);
        }

        uart_write_bytes(UART_NUM_0, separator, strlen(separator));
        uart_write_bytes(UART_NUM_0, "Empty Packet\n", 18);
        //Empty Packet
        char packet3[] = "";
        //Printing the Packet
        uart_write_bytes(UART_NUM_0, "Packet to be Parsed: ", 22);
        uart_write_bytes(UART_NUM_0, packet3, strlen(packet3));
        uart_write_bytes(UART_NUM_0, " \n", 3);
        //Parsing GPS Data
        GPS_Data received_data3 = parse_gps_data(packet3);
        //Printing the parsed Data
        print_parsed_data(received_data3);
        //Expected Data for the Packet
        strcpy(expected_data.time, "MIS");
        expected_data.latitude = -111.00;
        expected_data.lat_direction = 'M';
        expected_data.longitude = -111.00;
        expected_data.long_direction = 'M';
        expected_data.GPS_fix_quality = -111;
        expected_data.no_of_satellites = -111;
        expected_data.hdop = -111.00;
        expected_data.Geoid_separation = -111.00;
        expected_data.altitude = -111.00;
        expected_data.differential_age = -111.00;
        strcpy(expected_data.reference_Station_ID, "MIS");
        expected_data.checksum = -111;
        expected_data.checksum_integrity = 0;
        //Performing test and checking result
        if(gps_parser_test(received_data3, expected_data)){
            uart_write_bytes(UART_NUM_0, "Test Passed\n", 12);
        }
        else{
            uart_write_bytes(UART_NUM_0, "Test Failed\n", 12);
        }

        uart_write_bytes(UART_NUM_0, separator, strlen(separator));
        uart_write_bytes(UART_NUM_0, "Invalid data\n", 18);
        //Invalid Data, not GPGGA data.
        char packet4[] = "$GPRMC,184353.000,A,3723.2475,N,12158.3416,W,0.01,128.62,220811,,*1E";
        //Printing the Packet
        uart_write_bytes(UART_NUM_0, "Packet to be Parsed: ", 22);
        uart_write_bytes(UART_NUM_0, packet4, strlen(packet4));
        uart_write_bytes(UART_NUM_0, " \n", 3);
        //Parsing GPS Data
        GPS_Data received_data4 = parse_gps_data(packet4);
        //Printing the parsed Data
        print_parsed_data(received_data4);
        //Expected Data for the Packet
        strcpy(expected_data.time, "MIS");
        expected_data.latitude = -111.00;
        expected_data.lat_direction = 'M';
        expected_data.longitude = -111.00;
        expected_data.long_direction = 'M';
        expected_data.GPS_fix_quality = -111;
        expected_data.no_of_satellites = -111;
        expected_data.hdop = -111.00;
        expected_data.Geoid_separation = -111.00;
        expected_data.altitude = -111.00;
        expected_data.differential_age = -111.00;
        strcpy(expected_data.reference_Station_ID, "MIS");
        expected_data.checksum = -111;
        expected_data.checksum_integrity = 0;
        //Performing test and checking result
        if(gps_parser_test(received_data4, expected_data)){
            uart_write_bytes(UART_NUM_0, "Test Passed\n", 12);
        }
        else{
            uart_write_bytes(UART_NUM_0, "Test Failed\n", 12);
        }
        break;
    }
}
