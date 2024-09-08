CC=gcc  
#打开警告信息以及指定头文件搜索路径为当前文件夹
CFLAGS=-Wall -I.  
  
all: run_files12  
#run_files12依赖于main.o和file_operations.o这两个对象文件
run_files12: main.o file_overwrite.o file_mmap.o ec_version.o ec_rebot.o ec_shutdown.o
#编译生成run_files12 
	$(CC) $(CFLAGS) -o run_files12 main.o file_overwrite.o file_mmap.o ec_version.o ec_rebot.o ec_shutdown.o
  
main.o: main.c file_overwrite.h 
	$(CC) $(CFLAGS) -c main.c  
  
file_overwrite.o: file_overwrite.c file_overwrite.h 
	$(CC) $(CFLAGS) -c file_overwrite.c 

file_mmap.o: file_mmap.c file_overwrite.h 
	$(CC) $(CFLAGS) -c file_mmap.c

ec_version.o:ec_version.c file_overwrite.h
	$(CC) $(CFLAGS) -c ec_version.c

ec_rebot.o:ec_rebot.c file_overwrite.h
	$(CC) $(CFLAGS) -c ec_rebot.c

ec_shutdown.o:ec_shutdown.c file_overwrite.h
	$(CC) $(CFLAGS) -c ec_shutdown.c

clean:  
# 删除所有.o对象和run_files12可执行文件
	rm -f *.o
