#include "GPS_Parser_Lib.h"
#include "driver/uart.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
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

void print_parsed_data(GPS_Data data_received){
    char toStr[40];
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
        char msg[] = "Missing, Miss, M, -111, -111.00 represents Missing Parameters\n";
        uart_write_bytes(UART_NUM_0, msg, strlen(msg));
        uart_write_bytes(UART_NUM_0, "..\n", 3);
        uart_write_bytes(UART_NUM_0, "..\n", 3);
        char packet[] = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E";
        GPS_Data received_data = parse_gps_data(packet);
        print_parsed_data(received_data);
        GPS_Data expected_data;
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
        
        if(gps_parser_tester(received_data, expected_data)){
            uart_write_bytes(UART_NUM_0, "Test Passed", 12);
        }
        else{
            uart_write_bytes(UART_NUM_0, "Test Failed", 12);
        }
        break;
    }
}
