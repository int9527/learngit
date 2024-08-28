#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <time.h>
#include "file_overwrite.h"  
int main(int argc, char *argv[]) {  
    //检查命令行参数数量
    if (argc != 6) {
	  //向标准错误输出报告错误信息
        fprintf(stderr, "Usage: %s <文件1> <替换文件> <替换起始位> <映射位置> <偏移量大小>\n", argv[0]);  
        return 1;  
    }  
    const char *file1 = argv[1];  
    const char *file2 = argv[2];  
      //将字符串offset转换成长整型数
    off_t offset = strtol(argv[3], NULL, 16); 
    if (overwrite_file_at_offset(file1, file2, offset) != 0) {  
        fprintf(stderr, "Failed to overwrite file1 with file2 at offset\n");  
        return 1;  
    }  
    off_t mem_offset=strtol(argv[4], NULL, 16);;
    size_t mem_size=strtol(argv[5], NULL, 16);;
    read_from_dev_mem(mem_offset,mem_size);
    return 0;
}
