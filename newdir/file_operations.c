#include <stdio.h>  

  
// 声明在 file_operations.h 中  
int overwrite_file_at_offset(FILE *dest, FILE *src) {  
    char buffer[1024];  //定义一个用于读写的缓冲区
    size_t bytesRead;   //每次从源文件读取的字节数
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) { // 循环读取源文件  
        if (fwrite(buffer, 1, bytesRead, dest) != bytesRead) {  // 将读取的内容写入目标文件
            return 0;  
        }  
    }  
  
    return 1;  
}
