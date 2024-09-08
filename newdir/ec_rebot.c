#include <stdio.h>  
#include <stdint.h>  
#include <fcntl.h>  
#include <unistd.h>  
#include <stdint.h>  
#include <stdlib.h>  
#include <string.h>  
#include <fcntl.h>   
#include <sys/mman.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#define EC_OBF 0x01
#define EC_IBF 0x02
int Rebot( ){	
    int fd;
  //以可读可写，同步写入模式打开/dev/mem
  fd = open ("/dev/mem", O_RDWR | O_SYNC);
  if (fd == -1)
    {
      printf ("open /dev/mem fail!\n");
      return (-1);
    }
    //使用mmap函数进行映射
    unsigned char *map_base;
    map_base =mmap (NULL,1, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x20000000);
    //对62 66IO进行映射
    unsigned char *LPC_IO_62=(volatile unsigned char*)(map_base + 0x62);
    unsigned char *LPC_IO_66=(volatile unsigned char*)(map_base + 0x66);
    //确认输入缓冲区为空，并向66端口输入0x81，说明要写EC RAM
    while ((*LPC_IO_66 & EC_IBF));
    *LPC_IO_66=0x81;
    //确认输入缓冲区为空，并向62端口输入要修改的地址0x0A
    while ((*LPC_IO_66 & EC_IBF));
    *LPC_IO_62=0x0A;
    //确认输入缓冲区为空，修改0x0A地址的值为0x08（重启）
    while ((*LPC_IO_66 & EC_IBF));
    //usleep(10000);
    *LPC_IO_62=0x08;
    return 1;
}
