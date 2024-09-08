#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <time.h>
#include "file_overwrite.h"  
#define MAX_STRINGS_LENGTH 20
int main(int argc, char *argv[]) {  
    printf("请选择功能：\n");
    printf("1.进行文件间数据替换：\n");
    printf("2.读位置从offset开始，长度为size的地址：\n");
    printf("3.读EC版本号\n");
    printf("4.重启\n");
    printf("5.关机\n");
    

    //检查命令行参数数量
    if (argc != 6) {
	//向标准错误输出报告错误信息
        fprintf(stderr, "Usage: %s <文件1> <替换文件> <替换起始位> <映射位置> <偏移量大小>\n", argv[0]);  
        return 1;  
    }  
    int a;
    scanf("%d",&a);
    const char *file1 = argv[1];  
    const char *file2 = argv[2];  
    //将字符串offset识别为16进制并转换成长整型数
    off_t offset = strtol(argv[3], NULL, 16); 
    //将字符串mem_offset识别为16进制并转换成长整型数
    off_t mem_offset=strtol(argv[4], NULL, 16);
    //将字符串mem_size别为16进制并转换成长整型数
    size_t mem_size=strtol(argv[5], NULL, 16);
    
    if(a>0 && a<6)
    {
        switch (a) {
        case 1:
        if (overwrite_file_at_offset(file1, file2, offset) != 0) {  
        fprintf(stderr, "Failed to overwrite file1 with file2 at offset\n");  
        return 1;  
    }  
            break;
        case 2:
             read_from_dev_mem(mem_offset,mem_size);
             break;
        case 3:
            Read_EcVsersion();
             break;
        case 4:
            Rebot();
             break;
        case 5:
            ShutDown();
             break;                 
        }
    }
    return 0;
}
