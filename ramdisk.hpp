/*
    ramdisk.hpp
    a ramdisk class wrapper.

    author:yuanGuo <coboo2013@126.com>
*/
#ifndef __RAMDISK_HPP__
#define __RAMDISK_HPP__

#include <stdio.h>
#include "ramdisk.h"

class RAMDisk {
private:
    ramdisk_t *ramdisk;

public:
    #define DEF_CAP 1024*512 // 512KB
    // constructor and destruct function
    // For Multi ramdisk use
    RAMDisk(){printf("%s\n",__func__); ramdisk = ramdisk_create(DEF_CAP);};
    RAMDisk( size_t capacity){printf("%s\n",__func__); ramdisk = ramdisk_create(capacity);};

    //int ramdisk_delete(ramdisk_t *ramdisk);
    ~RAMDisk(void){printf("%s\n",__func__);ramdisk_delete(ramdisk);};

    //int ramdisk_open(ramdisk_t *ramdisk);
    int ramd_open(void){printf("%s\n",__func__);ramdisk_open(ramdisk);};

    /* if error ret=0*/
//    uint32_t ramdisk_get_capacity(ramdisk_t *ramdisk);
//    uint32_t ramdisk_get_sector_count(ramdisk_t *ramdisk);
//    uint32_t ramdisk_get_data_index(ramdisk_t *ramdisk);
//    int ramdisk_write_bytes(ramdisk_t *ramdisk,uint32_t waddr, char* buffer, size_t bufsize);
//    int ramdisk_read_bytes(ramdisk_t *ramdisk,uint32_t raddr, char* buffer, size_t bufsize);

    /*
        if bufsize%RAMDISK_SECTOR_SIZE != 0, ret=RD_NOFULLSECTORSIZE, but will read/write disk,
        last write will not stuff auto

    */
    //int ramdisk_write_sectors(ramdisk_t *ramdisk,uint32_t wsector /* write from sector */, char* buffer, size_t bufsize);
    //int ramdisk_read_sectors(ramdisk_t *ramdisk,uint32_t rsector /* read from sector */, char* buffer, size_t bufsize);

};

#endif // __RAMDISK_HPP__
