#include <sys/io.h>     
#include <stdio.h>      
#include <unistd.h>      
// 定义PCIe设备信息限制
#define MAX_BUS 256
#define MAX_DEVICE 32
#define MAX_FUNCTION 8
// 定义CONFIG_ADDRESS和CONFIG_DATA的地址
#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA 0xCFC

#define BASE_ADDR 0x80000000 // 基地址定义

typedef unsigned int WORD;  // 定义WORD为4字节的无符号整数

int Readpci()
{
    WORD bus, device, func, reg; // 定义总线、设备、功能和寄存器变量
    WORD data, address;          // 定义数据和地址变量
    int ret = 0;                 // 用于存储函数调用返回值

    // 设置I/O权限级别为高
    ret = iopl(3);
    if (ret < 0)
    {
        perror("iopl set to high level error\n"); // 输出错误信息
        return -1; // 设置权限失败，返回-1
    }
    // 遍历所有可能的总线、设备、功能和寄存器
    for (bus = 0; bus < MAX_BUS; bus++)
        for (device = 0; device < MAX_DEVICE; device++)
            for (func = 0; func < MAX_FUNCTION; func++)
            {
                for (reg = 0; reg < 16; reg++)
                {
                    address = BASE_ADDR | (bus << 16) | (device << 11) | (func << 8);
                    // 将地址写入CONFIG_ADDRESS
                    outl(address, CONFIG_ADDRESS); 
                    // 从CONFIG_DATA读取数据
                    data = inl(CONFIG_DATA);       
                    if ((data != 0xffffffff) && (data != 0))
                    {
                        printf("\n%02x:%02x:%02x\n", bus, device, func);
                        for (reg = 0; reg < 16; reg++)
                        {
                            if (reg % 4 == 0)
                            {
                                printf("%02x:", reg * 4); // 打印寄存器地址
                            }
                            address = BASE_ADDR | (bus << 16) | (device << 11) | (func << 8) | (reg << 2);
                            // 将地址写入CONFIG_ADDRESS
                            outl(address, CONFIG_ADDRESS); 
                            // 从CONFIG_DATA读取数据
                            data = inl(CONFIG_DATA);       
                            // 打印数据的每个字节
                            printf("%02x ", (unsigned char)(data >> 0));
                            printf("%02x ", (unsigned char)(data >> 8));
                            printf("%02x ", (unsigned char)(data >> 16));
                            printf("%02x ", (unsigned char)(data >> 24));
                            if (reg % 4 == 3)
                                printf("\n");
                        }
                    }
                }
            }

    // 恢复I/O权限级别
    iopl(0);
    if (ret < 0)
    {
        // 输出错误信息
        perror("iopl set to low level error\n"); 
        return -1; // 恢复权限失败，返回-1
    }

    return 0; 
}
