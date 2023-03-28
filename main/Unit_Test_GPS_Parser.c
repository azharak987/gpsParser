#include <stdio.h>
#include "GPS_Parser_Lib.h"
void app_main(void)
{   
    while(1){
        char packet[] = "$GPGGA,002153.000,3342.6618,N,11751.3858,W,1,10,1.2,27.0,M,-34.2,M,,0000*5E";
        parse_gps_data(packet);
        printf("dataa received");
    }
}
