CC=gcc  
#打开警告信息以及指定头文件搜索路径为当前文件夹
CFLAGS=-Wall -I.  
  
all: overwrite_files12  
  
overwrite_files12: main.o file_operations.o  
	$(CC) $(CFLAGS) -o overwrite_files12 main.o file_operations.o  
  
main.o: main.c file_operations.h  
	$(CC) $(CFLAGS) -c main.c  
  
file_operations.o: file_operations.c file_operations.h  
	$(CC) $(CFLAGS) -c file_operations.c 

clean:  
	rm -f *.o overwrite_files12
