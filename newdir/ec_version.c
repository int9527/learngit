#include <stdint.h>  
#include <stdio.h>
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <fcntl.h>  
#include <unistd.h>  
#include <sys/mman.h>  
#include <sys/types.h>  
#include <sys/stat.h> 
  
int Read_EcVsersion() {  
    unsigned char *map_base;
  int fd;
  //以可读可写，同步写入模式打开/dev/mem
  fd = open ("/dev/mem", O_RDWR | O_SYNC);
  if (fd == -1)
    {
      printf ("open /dev/mem fail!\n");
      return (-1);
    }
    //使用mmap函数进行映射
  map_base =mmap (NULL, 1, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0x20000000);
  unsigned char *LPC_IO_381=(unsigned char*)(map_base + 0x381);
  unsigned char *LPC_IO_382=(unsigned char*)(map_base + 0x382);
  unsigned char *LPC_IO_383=(unsigned char*)(map_base + 0x383);
    // 往LPC IO 381写0x20  
    *LPC_IO_381 = 0x20;  
    // 往LPC IO 382写0x00  
    *LPC_IO_382 = 0x00;  
    // 从LPC IO 383读取值
    unsigned char value_read = *LPC_IO_383;  
    printf("%x",value_read);
    // 再次往LPC IO 381写0x20
    *LPC_IO_381 = 0x20;  
    // 往LPC IO 382写0x01 
    *LPC_IO_382 = 0x01;  
    // 从LPC IO 383再次读取，假设此时读取到0x71  
    value_read = *LPC_IO_383;  
    printf("%x",value_read);
    close (fd);
    munmap (map_base, 1);
    return 1;  
}
