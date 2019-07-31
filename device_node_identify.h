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


#define PID 0x11
#define VID 0x222a

namespace device
{


struct HidRawAllInfo
{
    int desc_size; //报表描述符大小
    struct hidraw_report_descriptor rpt_desc; //报表描述服
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
