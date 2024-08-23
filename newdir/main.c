#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include "file_operations.h"  
  
int main(int argc, char *argv[]) {  
    //检查命令行参数数量
    if (argc != 4) {
	  //向标准错误输出报告错误信息
        fprintf(stderr, "Usage: %s <file1> <file2> <offset>\n", argv[0]);  
        return 1;  
    }  
    // 以二进制读写模式打开目标文件
    FILE *file1 = fopen(argv[1], "r+b");  
    if (!file1) {  
        perror("Failed to open file1");  
        return 1;  
    }  
    // 以二进制读模式打开源文件
    FILE *file2 = fopen(argv[2], "rb");  
    if (!file2) {  
        perror("Failed to open file2");  
        fclose(file1);  
        return 1;  
    }  

    //将file2中的字符串转换成长整型数
    long offset = strtol(argv[3], NULL, 16);  

    //尝试将文件指针移动到目标文件的指定偏移处
    if (fseek(file1, offset, SEEK_SET) != 0) {  
        perror("Failed to seek in file1");  
        // 如果移动失败，关闭源文件和目标文件
        fclose(file1);  
        fclose(file2);  
        return 1;  
    }  
  
    if (!overwrite_file_at_offset(file1, file2)) {// 如果写入失败，关闭所有文件  
        fprintf(stderr, "Failed to overwrite file1\n");  
        fclose(file1);  
        fclose(file2);  
        return 1;  
    }  
  
    fclose(file1);  // 关闭目标文件 
    fclose(file2);  // 关闭源文件 
    return 0;  
}
