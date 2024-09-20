#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define PCI_CONFIG_SPACE_SIZE 0xfffffff
#define PCI_BASE_ADDRESS 0x40000000 // 假设的PCI设备起始地址
#define MAX_BUS 256
#define MAX_DEVICE 32
#define MAX_FUNCTION 8
int Readpci() {
    int fd = open("/dev/mem", O_RDWR | O_SYNC);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    // 映射PCI设备的配置空间
    void *pci_mem = mmap(NULL, PCI_CONFIG_SPACE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, PCI_BASE_ADDRESS);
    if (pci_mem == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return 1;
    }
int bus, device, func,reg;
for (bus = 0; bus < MAX_BUS; bus++)
        for (device = 0; device < MAX_DEVICE; device++)
            for(func=0;func < MAX_FUNCTION;func++)
            {

                    unsigned char *address = (unsigned char *) (pci_mem +((bus << 20) | (device << 15)));
                // 读取设备的Vendor ID和Device ID
                    uint16_t vendor_id = *((uint16_t *)(address + 0x00));
                    uint16_t device_id = *((uint16_t *)(address + 0x02));
                    //判断是否存在设备 
                    if ((vendor_id != 0xffff) && (vendor_id != 0)){
                        printf("\n%02x:%02x:%02x\n", bus, device, func);
                        printf("Vendor ID: 0x%04x, Device ID: 0x%04x\n", vendor_id, device_id);
                        //打印设备配置空间
                        for (int reg = 0; reg < 16; reg++) {
                        uint32_t data = *((uint32_t *)(address + (reg * 4)));
                        printf("0x%02x: 0x%08x\n", reg * 4, data);
                    }
                    } 
            }
    // 解除映射
    munmap(pci_mem, PCI_CONFIG_SPACE_SIZE);
    close(fd);
    return 0;
}
