#include "device_node_identify.h"
#include <iostream>

namespace device
{

vector<string> GetHidrawDeviceList(string dirent_path)
{
    vector<string> res;
    DIR *dp = NULL;
    struct dirent *dirp = NULL;
    if (dirent_path.c_str() == NULL) {
        std::cout << "The input path is NULL!" << std::endl;
        return res;
    }

    int path_len = strlen(dirent_path.c_str());
    if (path_len == 0) {
        std::cout << "The length of path must longer than 0" << std::endl;
        return res;
    }

    if (dirent_path.c_str()[path_len-1] != '/') {
        std::cout << "The input path must end with '/'" << std::endl;
        return res; // 若目录没有以 ‘/’ 结尾 返回NULL；
    }   

    if ((dp = opendir(dirent_path.c_str())) == NULL) {
        std::cout << "Open dir failed!\n" << std::endl;
        return res; //目录打开失败，返回NULL
    } 

    while((dirp = readdir(dp)) != NULL) {
        if (strstr(dirp->d_name, "hidraw") != NULL) {
            string device_name(dirent_path);
            device_name += string(dirp->d_name);
            res.push_back(device_name);
        }
    }

    closedir(dp);
    return res;
}

int GetHidRawName(int fd, struct HidRawAllInfo *info)
{
    if (fd <= 0) {
        std::cout << "GetHidRawName: Input fd invaild!" << std::endl;
        return -1;
    }

    if (info == NULL) {
        std::cout << "GetHidRawName: Input info invaild!" << std::endl;
        return -1;
    }

    int res = ioctl(fd, HIDIOCGRAWNAME(256), info->hid_raw_name);
    if (res < 0) {
        perror("GetHidRawName: Ioctl error!\n");
        return res;
    }
        
    
    return res;
}

int GetHidRawPhy(int fd, struct HidRawAllInfo *info)
{
    if (fd <= 0) {
        std::cout << "GetHidRawPhy: Input fd invaild!" << std::endl;
        return -1;
    }

    if (info == NULL) {
        std::cout <<  "GetHidRawPhy: Input info invaild!" << std::endl;
        return -1;
    }

    int res = ioctl(fd, HIDIOCGRAWPHYS(256), info->hid_raw_phy);
    if (res < 0) {
        perror("GetHidRawPhy: Ioctl error!\n");
        return res;
    }
        

    return res;
}

int GetHidRawDevInfo(int fd, struct HidRawAllInfo *info)
{
    if (fd <= 0) {
        std::cout << "GetHidRawDevInfo: Input fd invaild!" << std::endl;
        return -1;
    }

    if (info == NULL) {
        std::cout << "GetHidRawDevInfo: Input info invaild!" << std::endl;
        return -1;
    }

    int res = ioctl(fd, HIDIOCGRAWINFO, &info->dev_info);
    if (res < 0) {
        perror("GetHidRawDevInfo: Ioctl error!\n");
        return res;
    }
        

    return res;
}

int GetHidRawDescSize(int fd, struct HidRawAllInfo *info)
{
    if (fd <= 0) {
        std::cout << "GetHidRawDescSize: Input fd invaild!" << std::endl;
        return -1;
    }

    if (info == NULL) {
        std::cout << "GetHidRawDescSize: Input info invaild!" << std::endl;
        return -1;
    }

    int res = ioctl(fd, HIDIOCGRDESCSIZE, &info->desc_size);
    if (res < 0) {
        perror("GetHidRawDescSize: Ioctl error!\n");
        return res;
    }
        

    return res;
}

int GetHidRawDescriptor(int fd, struct HidRawAllInfo *info)
{
    if (fd <= 0) {
        std::cout << "GetHidRawDescriptor: Input fd invaild!" << std::endl;
        return -1;
    }

    if (info == NULL) {
        std::cout << "GetHidRawDescriptor: Input info invaild!" << std::endl;
        return -1;
    }

    int res = ioctl(fd, HIDIOCGRDESC, &info->rpt_desc);
    if (res < 0) {
        perror("GetHidRawDescriptor: Ioctl error!\n");
        return res;
    }
        

    return res;
}

string GetDeviceNode(string device_dirent_path, 
                    string phy_info)
{
   vector<string> device_list;
   string node;
   if (phy_info.c_str() == NULL) {
       std::cout << "GetDeviceNode: Invalid input!" << std::endl;
       return string("");
   }
    device_list = GetHidrawDeviceList(device_dirent_path);
    if (device_list.size() == 0) {
        return string("");
    }

    for (unsigned int i = 0; i < device_list.size(); ++i) {
        int fd = ::open(device_list[i].c_str(), O_RDWR);
        if (fd < 0) {
            std::cout << "Open device failed!" << std::endl;
            return string("");
        }

        struct HidRawAllInfo info;
        if (GetHidRawDevInfo(fd, &info) < 0) {
            printf("Get device dev info failed!\n");
            return string("");
        }

        if (GetHidRawPhy(fd, &info) < 0) {
            printf("Get phy info failed!\n");
            return string("");
        }

        if (info.dev_info.product == CVT_DEF_HID_DEV_PID   //匹配触摸屏的pid和vid
                && info.dev_info.vendor == CVT_DEF_HID_DEV_VID
                && (strstr(info.hid_raw_phy, phy_info.c_str()) != NULL)) {

            node = device_list[i].c_str();
            return node;
        }
    }
    return string("");
}

}
