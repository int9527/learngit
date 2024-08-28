CC=gcc  
#打开警告信息以及指定头文件搜索路径为当前文件夹
CFLAGS=-Wall -I.  
  
all: overwrite_files12  
#overwrite_files12依赖于main.o和file_operations.o这两个对象文件
overwrite_files12: main.o file_overwrite.o file_mmap.o
#编译生成overwrite_files12 
	$(CC) $(CFLAGS) -o overwrite_files12 main.o file_overwrite.o file_mmap.o
  
main.o: main.c file_overwrite.h 
	$(CC) $(CFLAGS) -c main.c  
  
file_overwrite.o: file_overwrite.c file_overwrite.h 
	$(CC) $(CFLAGS) -c file_overwrite.c 

file_mmap.o: file_mmap.c file_overwrite.h 
	$(CC) $(CFLAGS) -c file_mmap.c

clean:  
# 删除所有.o对象和overwrite_files可执行文件
	rm -f *.o
