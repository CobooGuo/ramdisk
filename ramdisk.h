/*
    ramdisk.c/h
    a project to test ramdisk tech for me.

    author:yuanGuo <coboo2013@126.com>
*/
#ifndef __RAMDISK_H__
#define __RAMDISK_H__

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#include <stdint.h>
#include <stddef.h>

#define RAMDISK_SECTOR_SIZE 512 // 512BYTE
#define RAMDISK_CAPACITY_SIZE 256*1024*1024     // 256MB //

#define RAMDISK_NAME_MAX_SIZE 256 //
typedef struct _ramdisk_t{
    char disk_name[RAMDISK_NAME_MAX_SIZE];
    uint32_t disksize;
    uint32_t sector_count; /* =disksize/RAMDISK_SECTOR_SIZE */
    uint32_t status; // bit[0] = 1:opened ,bit[0] = 0:closed
    uint32_t pdata_index; //
    char *pdata_addr;
}ramdisk_t;

enum RAMDISK_STATUS{
    RD_ERR = -1,
    RD_OK = 0,
    RD_NOSPACE, /* ramdisk no space */
    RD_OVERFLOW_READ, /* Overflow read */
    RD_PNULL, /* IN ramdisk_t param NULL */
    RD_PDATANULL, /* IN ramdisk:pdata_addr NULL */
    RD_WERR,    /* write error */
    RD_RERR,     /* read error */
    RD_NOFULLSECTORSIZE /* No full sector size */
    // .. other status
};

// For Multi ramdisk use
ramdisk_t *ramdisk_create( size_t capacity);
int ramdisk_open(ramdisk_t *ramdisk);
int ramdisk_delete(ramdisk_t *ramdisk);

/* if error ret=0*/
uint32_t ramdisk_get_capacity(ramdisk_t *ramdisk);
uint32_t ramdisk_get_sector_count(ramdisk_t *ramdisk);
uint32_t ramdisk_get_data_index(ramdisk_t *ramdisk);

int ramdisk_write_bytes(ramdisk_t *ramdisk,uint32_t waddr, char* buffer, size_t bufsize);
int ramdisk_read_bytes(ramdisk_t *ramdisk,uint32_t raddr, char* buffer, size_t bufsize);

/*
    if bufsize%RAMDISK_SECTOR_SIZE != 0, ret=RD_NOFULLSECTORSIZE, but will read/write disk,
    last write will not stuff auto

*/
int ramdisk_write_sectors(ramdisk_t *ramdisk,uint32_t wsector /* write from sector */, char* buffer, size_t bufsize);
int ramdisk_read_sectors(ramdisk_t *ramdisk,uint32_t rsector /* read from sector */, char* buffer, size_t bufsize);

// For single ramdisk use   // you can implement with above function
int create_ramdisk(void);
int delete_ramdisk(void);

/* if error ret=0 */
uint32_t get_ramdisk_capacity(void);
uint32_t get_ramdisk_sector_count(void);
uint32_t get_ramdisk_data_index(void);

int write_bytes_to_ramdisk(uint32_t waddr, char* buffer, size_t bufsize);
int read_bytes_to_ramdisk(uint32_t raddr, char* buffer, size_t bufsize);

int write_sectors_to_ramdisk(uint32_t wsector, char* buffer, size_t bufsize);
int read_sectors_to_ramdisk(uint32_t rsector, char* buffer, size_t bufsize);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // __RAMDISK_H__
