#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <fcntl.h>  
#include <unistd.h>  
#include <sys/mman.h>  
#include <sys/types.h>  
#include <sys/stat.h> 
// 实现read_from_dev_mem函数  
int read_from_dev_mem(off_t mem_offset,size_t mem_size) {  
    unsigned char *map_base;
  //FILE *f;
  //int n;
  int fd;
 
  fd = open ("/dev/mem", O_RDWR | O_SYNC);
  if (fd == -1)
    {
      printf ("open /dev/mem fail!\n");
      return (-1);
    }
 
  map_base =mmap (NULL, mem_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, mem_offset);
  if (map_base == 0)
    {
      printf ("NULL pointer!\n");
    }
  else
    {
      printf ("map Successfull!\n");
    }

  unsigned long addr;
  unsigned char content;
 
  int i = 0;
  for (; i < 0xf; ++i)
    {
      addr = (unsigned long) (map_base + i);
      content = map_base[i];
      printf ("address: 0x%lx   value: 0x%x\t\t", addr,(unsigned int) content);
 
      map_base[i] = (unsigned char) i;
      content = map_base[i];
      printf ("address: 0x%lx   value: 0x%x\t\t", addr,(unsigned int) content);
 
      map_base[i] = (unsigned char) i;
      content = map_base[i];
      printf ("address: 0x%lx   new value: 0x%x\n", addr,(unsigned int) content);
    } 
  close (fd);
  munmap (map_base, 0xff);
  return 1;
}