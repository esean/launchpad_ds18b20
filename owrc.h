
#define MAX_SN_LEN  6

typedef struct
{
    int family_code;
    int sn[MAX_SN_LEN];
    int crc;

} ow_dev;


// returns temp, or -1 if no devices found
int owrc_read_temp();

// issues 'read rom' and returns one device info struct
ow_dev owrc_read_rom();


#if 0
// returns the number of devices found
int owrc_search_rom();
#endif
