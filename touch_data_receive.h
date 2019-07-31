/*
 * @Description: touch_data_receive模块头文件，此模块用于接受一个Hidraw数据报，共64字节
 * @Author: Ji Yongjie
 * @Date: 2019-07-12 19:29:51
 * @LastEditTime: 2019-07-23 10:05:35
 * @LastEditors: Please set LastEditors
 */

#ifndef C_TOUCHDATARECEIVE_H
#define C_TOUCHDATARECEIVE_H

#include <linux/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define TOUCH_DATA_REPORT_SIZE 64

//#pragma pack(1)
typedef struct
{
    uint8_t contact_id : 6; // 触控点ID
    uint8_t tip_switch : 1; // 1代表按下，0代表松开
    uint8_t reserved  : 1;  
    uint8_t x[2];  //x坐标 范围 0－0x4000
    uint8_t y[2];  //y坐标 范围 0－0x2580
} HidMtFingerReportElem;


//#pragma pack(1)
typedef struct
{
    uint8_t report_id; 
    HidMtFingerReportElem finger_rpt[10]; //最多支持10个手指
    uint8_t scan_time[4]; //时间戳
    uint8_t count;  // 触点数据统计
    uint8_t reserved[8];
} HidMtFingerReport;


#ifdef __cplusplus
extern "C" {
#endif
/**
 * @description: 用于接受一个hidraw数据包（64字节）,参数为打开的hidraw设备文件描述符，
 * 缓冲区指针，缓冲区大小。
 * 返回0代表成功，－1代表失败
 * @param {int, unsigned char*} 
 * @return: int
 */
int TouchDataReceive(int fd, 
                     unsigned char *buffer, 
                     int size);

int TouchDataSend(int fd, 
                  unsigned char* buffer, 
                int size);

#ifdef __cplusplus
}
#endif

#endif //C_TOUCHDATARECEIVE_H
