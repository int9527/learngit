#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <time.h>
#include "file_overwrite.h"  
#define MAX_STRINGS_LENGTH 20
#define MAX_LENGTH 100
int main() {  
    //int argc, char *argv[]
    char* argv[] = { "Blue","Yellow","Orange","Green","Red","black" };
    //检查命令行参数数量
    // if (argc != 6) {
	// //向标准错误输出报告错误信息
    //     fprintf(stderr, "Usage: %s <文件1> <替换文件> <替换起始位> <映射位置> <偏移量大小>\n", argv[0]);  
    //     return 1;  
    // }  
    printf("请选择功能：\n");
    printf("1.进行文件间数据替换：\n");
    printf("2.读位置从offset开始，长度为size的地址：\n");
    printf("3.读EC版本号\n");
    printf("4.读pci设备以及配置空间（x86环境下）\n");
    printf("5.重启\n");
    printf("6.关机\n");
    int a;
    scanf("%d",&a);
    if(a>0 && a<6)
    {
        
        switch (a) {
        case 1:
        	
        // 分配内存
            for (int i = 0; i < 4; i++) {
            argv[i] = (char*)malloc(MAX_LENGTH * sizeof(char));
            if (argv[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
             return 1;
                            }
            }

      // 从键盘输入数据
            printf("请输入：<文件1> <替换文件> <替换起始位> \n" );
            printf("每次输入后ENTER键确认 \n" );
            for (int i = 0; i < 4; i++) {
            fgets(argv[i], MAX_LENGTH, stdin);
            argv[i][strcspn(argv[i], "\n")] = '\0';  // 去除换行符
            } 
            const char *file1 = argv[1];  
            const char *file2 = argv[2];  
            //将字符串offset识别为16进制并转换成长整型数
            off_t offset = strtol(argv[3], NULL, 16); 
            if (overwrite_file_at_offset(file1, file2, offset) != 0) {  
            fprintf(stderr, "Failed to overwrite file1 with file2 at offset\n");  
            return 1;  
            }  
            for (int i = 0; i < 3; i++) {
            free(argv[i]);
             }
        break;
        case 2:
        // 分配内存
            for (int i = 0; i < 3; i++) {
            argv[i] = (char*)malloc(MAX_LENGTH * sizeof(char));
            if (argv[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
            }
          }

    // 从键盘输入数据
            printf("请输入：<映射位置> <偏移量大小> \n" );
            printf("每次输入后ENTER键确认 \n" );
            for (int i = 0; i < 3; i++) {
            // printf("Enter string %d: ", i);
            fgets(argv[i], MAX_LENGTH, stdin);
            argv[i][strcspn(argv[i], "\n")] = '\0';  // 去除换行符
            }
    //将字符串mem_offset识别为16进制并转换成长整型数
            off_t mem_offset=strtol(argv[1], NULL, 16);
    //将字符串mem_size别为16进制并转换成长整型数
            size_t mem_size=strtol(argv[2], NULL, 16);
            read_from_dev_mem(mem_offset,mem_size);

            // for (int i = 0; i < 3; i++) {
            // free(argv[i]);
            // }
        break;
        case 3:
            Read_EcVsersion();
             break;
         case 4:
            Readpci();
             break;
        case 5:
            Rebot();
             break;
        case 6:
            ShutDown();
             break;                 
        }
    }
    return 0;
}
