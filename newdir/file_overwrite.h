#ifndef FILE_OVERWRITE_H  
#define FILE_OVERWRITE_H  
// 函数声明：将file2的内容复制到file1的指定offset处
#include <stdio.h>
int overwrite_file_at_offset(const char *file1, const char *file2, off_t offset);
// 函数声明：将起始地址为mem_offset，长度为mem_size的地址打印出来 
int read_from_dev_mem(off_t mem_offset,size_t mem_size);
int Read_EcVsersion( );
void Rebot();
void ShutDown();
int Readpci();
#endif
