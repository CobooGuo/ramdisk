#include "ramdisk.h"

#include <stdlib.h> // malloc
#include <stdlib.h>

int ramdisk_test(void)
{
    ramdisk_t *ramdisk;
    size_t capacity = 1024*1024; // 1MB

    uint32_t rcap,seccount, dataindex;
    char write_buf[4096];
    char read_buf[578];

    // create
    // open
    ramdisk = ramdisk_create(capacity);
    if(NULL == ramdisk){
        printf("ramdisk malloc error!\n");
        return -1;
    }

    ramdisk_open(ramdisk);

    // get attribute
/* if error ret=0*/
    rcap = ramdisk_get_capacity(ramdisk);
    seccount = ramdisk_get_sector_count(ramdisk);
    dataindex = ramdisk_get_data_index(ramdisk);
    printf("rcap:%d\nsector count:%d\ndataindex:%d\n\n", rcap, seccount, dataindex);

    // read/write
    uint32_t waddr,raddr;
    waddr = raddr = 377;
    ramdisk_write_bytes(ramdisk, waddr, write_buf, sizeof(write_buf));


    rcap = ramdisk_get_capacity(ramdisk);
    seccount = ramdisk_get_sector_count(ramdisk);
    dataindex = ramdisk_get_data_index(ramdisk);
    printf("rcap:%d\nsector count:%d\ndataindex:%d\n\n", rcap, seccount, dataindex);

    ramdisk_read_bytes(ramdisk, raddr, read_buf, (sizeof(read_buf)));

    rcap = ramdisk_get_capacity(ramdisk);
    seccount = ramdisk_get_sector_count(ramdisk);
    dataindex = ramdisk_get_data_index(ramdisk);
    printf("rcap:%d\nsector count:%d\ndataindex:%d\n\n", rcap, seccount, dataindex);
    // compare data

    int comp_size = sizeof(write_buf) > sizeof(read_buf) ? sizeof(read_buf) : size(write_buf);
    for(int i=0; i < comp_size; i++)
    {
        if(write_buf[i] != read_buf[i])
            printf("ramdisk_write_bytes and ramdisk_read_bytes error!\n");
    }
    printf("ramdisk_write_bytes and ramdisk_read_bytes ok!\n");
/*
    if bufsize%RAMDISK_SECTOR_SIZE != 0, ret=RD_NOFULLSECTORSIZE, but will read/write disk,
    last write will not stuff auto

*/
    uint32_t wsector,rsector;
    wsector = rsector = 12;
    ramdisk_write_sectors(ramdisk, wsector /* write from sector */, write_buf, sizeof(write_buf));
    ramdisk_read_sectors(ramdisk, rsector /* read from sector */, read_buf , (sizeof(read_buf)));
    for(int i=0; i < comp_size; i++)
    {
        if(write_buf[i] != read_buf[i])
            printf("ramdisk_write_sectors and ramdisk_read_sectors error!\n");
    }
    printf("ramdisk_write_sectors and ramdisk_read_sectors ok!\n");
    // delete
    ramdisk_delete(ramdisk);
}
