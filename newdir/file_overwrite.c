#include <stdio.h>  
#include <fcntl.h>  
#include <unistd.h>  

//#define BUFFER_SIZE 4096

int overwrite_file_at_offset(const char *file1, const char *file2, off_t offset) {  
    // 以读写模式打开目标文件
    int fd1 = open(file1, O_RDWR);  
    if (fd1 == -1) {  
        perror("Failed to open file1");  
        return -1;  
    } 

    // 以只读模式打开源文件
    int fd2 = open(file2, O_RDONLY);  
    if (fd2 == -1) {  
        perror("Failed to open file2");  
        close(fd1);  
        return -1;  
    } 

    //尝试将文件指针移动到目标文件的指定偏移处
    if (lseek(fd1, offset, SEEK_SET) == -1) {  
        perror("Failed to seek in file1");  
        // 如果移动失败，关闭源文件和目标文件
        close(fd1);  
        close(fd2);  
        return -1;  
    }  
    char buffer[1024];  //定义一个用于读写的缓冲区
    size_t bytesRead;   //每次从源文件读取的字节数
    while ((bytesRead = read(fd2, buffer, sizeof(buffer))) > 0) { // 循环读取源文件  
        if (write(fd1, buffer, bytesRead) != bytesRead) {  // 将读取的内容写入目标文件
            perror("Failed to write to file1");
            close(fd1);
            close(fd2);
            return -1;  
        }  
    }  
  if (bytesRead == -1) {  
        perror("Failed to read from file2");  
        close(fd1);  
        close(fd2);  
        return -1;  
    } 
    close(fd1);  
    close(fd2);  
    return 0; 
}
