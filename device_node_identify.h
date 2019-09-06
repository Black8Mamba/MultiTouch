/*
 * @Description: In User Settings Edit
 * @Author: Yongjie
 * @Date: 2019-09-06 14:42:29
 * @LastEditTime: 2019-09-06 16:53:09
 * @LastEditors: Please set LastEditors
 */
#ifndef DEVICE_NODE_IDENTIFY_
#define DEVICE_NODE_IDENTIFY_

#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include <dirent.h>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <linux/hidraw.h>
#include <sys/ioctl.h>
#include <linux/input.h>


using std::vector;
using std::string;


#define CVT_DEF_HID_DEV_PID     0x11    //目标设备PID
#define CVT_DEF_HID_DEV_VID     0x222a  //目标设备VID

namespace device
{


struct HidRawAllInfo
{
    int desc_size; //报表描述符大小
    struct hidraw_report_descriptor rpt_desc; //报表描述符
    struct hidraw_devinfo dev_info;  //设备原生信息
    char hid_raw_name[256]; //名字
    char hid_raw_phy[256];  //物理信息
};

int GetHidRawName(int fd, 
                    struct HidRawAllInfo *);

int GetHidRawPhy(int fd, 
                    struct HidRawAllInfo *);

int GetHidRawDevInfo(int fd, 
                    struct HidRawAllInfo *);

int GetHidRawDescSize(int fd, 
                    struct HidRawAllInfo *);

int GetHidRawDescriptor(int fd, 
                    struct HidRawAllInfo *);                                                                                

vector<string> GetHidrawDeviceList(string dirent_path);   

string GetDeviceNode(string device_dirent_path, 
                    string phy_info);
}
#endif
