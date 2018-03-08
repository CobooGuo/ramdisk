/*
    ramdisk.c
    author:yuanGuo <coboo2013@126.com>
 */
#include "ramdisk.h"

#include <stdlib.h>
#include <string.h>

#define RAMDISK_DEBUG

#ifdef RAMDISK_DEBUG
#include <stdio.h>
#define rd_printf(x...) printf(x)
#else
#define rd_printf()
#endif // RAMDISK_DEBUG

ramdisk_t *ramdisk_create(size_t capacity)
{
    ramdisk_t *ramdisk;
    ramdisk = (ramdisk_t*) malloc(sizeof(ramdisk_t));
    if(NULL == ramdisk){
        rd_printf("ramdisk malloc error!\n");
        return NULL;
    }

    ramdisk->pdata_addr = (char*) malloc(capacity);
    if(NULL == ramdisk->pdata_addr){
        rd_printf("ramdisk capacity malloc error!\n");
        free(ramdisk);
        return NULL;
    }

    ramdisk->disksize = capacity;
    ramdisk->sector_count = capacity / RAMDISK_SECTOR_SIZE;
    ramdisk->pdata_index = 0;

    rd_printf("debug %s:\n", __func__);
    rd_printf("ramdisk addr:%p\nramdisk pdata_addr:%p\nramdisk capacity:%d\n",ramdisk,ramdisk->pdata_addr,capacity);
    return ramdisk;
}

int ramdisk_open(ramdisk_t *ramdisk)
{
    if(NULL == ramdisk)
        return RD_ERR;
    ramdisk->status |= (0x1);

    rd_printf("debug %s:\n", __func__);
    //rd_printf("ramdisk addr:%p\nramdisk pdata_addr:%p\nramdisk capacity:%d\n",ramdisk,addr,capacity);
    return RD_OK;
}
int ramdisk_delete(ramdisk_t *ramdisk)
{
    if(NULL == ramdisk)
        return RD_PNULL;

    char *addr = ramdisk->pdata_addr;
    if(NULL != addr)
        free(addr);

    free(ramdisk);
    ramdisk = NULL;

    rd_printf("debug %s:\n", __func__);
    //rd_printf("ramdisk addr:%p\nramdisk pdata_addr:%p\nramdisk capacity:%d\n",ramdisk,addr,capacity);
    return RD_OK;
}

/* if error ret=0*/
uint32_t ramdisk_get_capacity(ramdisk_t *ramdisk)
{
    if(NULL == ramdisk)
        return 0;

    return ramdisk->disksize;
}
uint32_t ramdisk_get_sector_count(ramdisk_t *ramdisk)
{
    if(NULL == ramdisk)
        return 0;

    return ramdisk->sector_count;
}
uint32_t ramdisk_get_data_index(ramdisk_t *ramdisk)
{
    if(NULL == ramdisk)
        return 0;

    return ramdisk->pdata_index;
}

int ramdisk_write_bytes(ramdisk_t *ramdisk,uint32_t waddr, char* buffer, size_t bufsize)
{
    if(NULL == ramdisk)
        return RD_PNULL;
    if(waddr+bufsize > ramdisk->disksize){
        rd_printf("debug %s:RD_NOSPACE\n", __func__);
        return RD_NOSPACE;
    }

    memcpy((char*)ramdisk->pdata_addr+waddr, (char*)buffer, bufsize);
    ramdisk->pdata_index = waddr+bufsize;

    rd_printf("debug %s:\n", __func__);
    //rd_printf("ramdisk addr:%p\nramdisk pdata_addr:%p\nramdisk capacity:%d\n",ramdisk,addr,capacity);

    return RD_OK;
}
int ramdisk_read_bytes(ramdisk_t *ramdisk,uint32_t raddr, char* buffer, size_t bufsize)
{
    if(NULL == ramdisk)
        return RD_PNULL;
    if(raddr+bufsize > ramdisk->disksize)
        return RD_OVERFLOW_READ;

    memcpy((char*)buffer, (char*)(ramdisk->pdata_addr+raddr), bufsize);
    ramdisk->pdata_index = raddr+bufsize;

    rd_printf("debug %s:\n", __func__);
    //rd_printf("ramdisk addr:%p\nramdisk pdata_addr:%p\nramdisk capacity:%d\n",ramdisk,addr,capacity);

    return RD_OK;
}

int ramdisk_write_sectors(ramdisk_t *ramdisk,uint32_t wsector /* write from sector */, char* buffer, size_t bufsize)
{
    if(NULL == ramdisk)
        return RD_PNULL;
    if(wsector+ bufsize/RAMDISK_SECTOR_SIZE + bufsize%RAMDISK_SECTOR_SIZE > ramdisk->sector_count){
        rd_printf("debug %s:RD_NOSPACE\n", __func__);
        return RD_NOSPACE;
    }

    memcpy(ramdisk->pdata_addr+wsector*RAMDISK_SECTOR_SIZE, buffer, bufsize);
    ramdisk->pdata_index = wsector*RAMDISK_SECTOR_SIZE+bufsize;

    rd_printf("debug %s:\n", __func__);
    //rd_printf("ramdisk addr:%p\nramdisk pdata_addr:%p\nramdisk capacity:%d\n",ramdisk,addr,capacity);
    if(bufsize%RAMDISK_SECTOR_SIZE){
        rd_printf("debug %s:RD_NOFULLSECTORSIZE\n", __func__);
        return RD_NOFULLSECTORSIZE;
    }
    return RD_OK;
}
int ramdisk_read_sectors(ramdisk_t *ramdisk,uint32_t rsector /* read from sector */, char* buffer, size_t bufsize)
{
    if(NULL == ramdisk)
        return RD_PNULL;
    if(rsector+ bufsize/RAMDISK_SECTOR_SIZE + bufsize%RAMDISK_SECTOR_SIZE > ramdisk->sector_count)
        return RD_OVERFLOW_READ;

    memcpy(buffer, ramdisk->pdata_addr+rsector*RAMDISK_SECTOR_SIZE, bufsize);
    ramdisk->pdata_index = rsector*RAMDISK_SECTOR_SIZE+bufsize;

    rd_printf("debug %s:\n", __func__);
    //rd_printf("ramdisk addr:%p\nramdisk pdata_addr:%p\nramdisk capacity:%d\n",ramdisk,addr,capacity);
    if(bufsize%RAMDISK_SECTOR_SIZE){
        rd_printf("debug %s:RD_NOFULLSECTORSIZE\n", __func__);
        return RD_NOFULLSECTORSIZE;
    }
    return RD_OK;
}

// other
