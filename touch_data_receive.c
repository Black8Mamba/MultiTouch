/*
 * @Description: touch_data_receive模块源文件，此模块用于接受一个Hidraw数据报，共64字节
 * @Author: Ji Yongjie
 * @Date: 2019-07-13 11:15:38
 * @LastEditTime: 2019-07-23 10:04:56
 * @LastEditors: Please set LastEditors
 */

#include "touch_data_receive.h"



/**
 * @description: 用于接受一个hidraw数据包（64字节）,参数为打开的hidraw设备文件描述符，
 * 缓冲区指针，缓冲区大小。
 * 返回0代表成功，－1代表失败
 * @param {int, unsigned char*} 
 * @return: int
 */
int TouchDataReceive(int fd, unsigned char* buffer, int size)
{
    if (size != TOUCH_DATA_REPORT_SIZE) {
        printf("TouchDataReceive: Input size is not equal to TOUCH_DATA_REPORT_SIZE\n");
        return -1;
    }//对输入参数有效性进行判断

    size_t n_left = size;
    ssize_t n_read = 0;

    unsigned char *ptr = buffer;

    while(n_left > 0) {
        if ((n_read = read(fd, ptr, n_left)) < 0) {
            if (errno == EINTR) //interrupt by signal
                n_read = 0;
            else 
                return -1;
        } else if (n_read == 0)
            break;

        n_left -= n_read;
        ptr  += n_read;
    }

    return size - n_left;
}

int TouchDataSend(int fd, unsigned char* buffer, int size)
{
    if (size != TOUCH_DATA_REPORT_SIZE) {
        printf("TouchDataReceive: Input size is not equal to TOUCH_DATA_REPORT_SIZE\n");
        return -1;
    }//对输入参数有效性进行判断

    size_t n_left = size;
    ssize_t n_write = 0;

    const unsigned char* ptr = buffer;
    while(n_left > 0) {
        if ((n_write = write(fd, ptr, n_left)) <= 0) {
            if (n_write < 0 && errno == EINTR)
                n_write = 0;
            else
                return -1;
        }
        n_left -= n_write;
        ptr     += n_write;
    }

    return size - n_left;    
}