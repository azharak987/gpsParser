Author: Azhar Ali Khan
Library:
    The library is written as ESP32 component. It is in the components directory, named GPS_Parser_Lib
    GPS_PARSER
       |
        --GPS_Parser_Lib
            |
            --include
            --GPS_Parser_Lib.c

Unit Test: 
    Unit test is written in the main file of the project named, Unit_Test_GPS_Parser.c. It is inside the main folder in the project.    

Problem Solving Approach:
    1. The function parse_gps_data is created with input string and return type a struct which stores the GPS Data.
    2. The struct GPS_Data is created to store all the parameters of the GGA packet.
    3. First all the members of GPS_Data are initialized with the error codes/missing parameter code. It is because if some parameters in the data is missing the member associated with that parameter will automatically have a missing value. If the parameter is not missing then the member associated to it will be updated later in the code. 
    4. The packet is checked if it is not empty.
    5. If not empty, got all the count of commas in the string, this will give me the number of parameters present in the packet.
    6. If there are two consecutive commas present in the string it means that there is a parameter missing.
    7. If a parameter is missing then its position which is determined by params_count (parameters count: which shows how many parameters are present in the code) is stored in missing_params_pos[] array.
    8. A variable empty_params keep track of how many parameters are missing and is incremented whenever there is a missing          parameter.
    9. Then the checksum is calculated and stored in the variable.
    10. Then parameters missing at the end of the packet is checked by comparing the params_count with the total number of parameters in the GGA packet that is 15.
    11. If a parameter is missing at the end of the packet, then its position is added to the missing_params_pos array.
    12. The packet is split by commas and stored each substring in another array called params[]. 
    13. While splitting and iterating the packet, the iterator i is compared with the missing_params_pos[] to check if the missing parameter position has come or not, if the position has come then a string "Missing" is added in the params[] instead of that parameter value from the packet.
    14. After splitting by comma is done, then "Missing" was added for the parameters which were missed at the end of the packet.
    15. Then the first member of params[] is compared with "GPGGA" to check if the packet is valid, if not then the packet_type variable is set to invalid and the function is returned.
    16. If the packet is valid, then the parameters stored in the params[] are manipulated and stored in the respective GPS_Data struct object.
    17. For the last parameter which consists of Reference station ID and Checksum Value, separated by '*' is split by '*'.
    18. Then the first element of the first substring is matched with '*', if it matches it means that the Reference Station ID is missing and then adding "Missing" in place of Reference Station ID.
    19. If Reference Station ID is not missing, then the first substring got from the split is set as the Reference Station ID of the GPS_Data object and then the second substring is first converted from hex to decimal and then stored in the GPS_Data object variable.
    20. The checksum obtained from the above step is then matched with the checksum obtained in step 9. 
    21. If matched, then the packet_integrity variable is set to 1, if not then it is set to 0.

Testing:
    1. 4 tests are performed on the function parse_gps_data.
    2. First test is testing with the valid data.
    3. Second test is testing with valid data but missing parameter.
    4. Third test is testing with empty data packet.
    5. Fourth test is testing with invalid data.
    6. Each member of GPS_data object is printed for every test.
    7. Missing, MIS, Miss, M, -111, -111.00 these are missing parameter codes. They represents that this parameter is missing. 