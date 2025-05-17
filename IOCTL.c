#include <stdio.h>
   #include <stdlib.h>
   #include <unistd.h>
   #include <fcntl.h>
   #include <sys/ioctl.h>
   #include <linux/kd.h>

   int main() {
       int fd;
       int res;
       unsigned char leds;

       fd = open("/dev/tty0", O_RDONLY);  // Note: "O_RDONLY" (letter 'O', not zero)
       if (fd == -1) {
           perror("open /dev/tty0");
           exit(EXIT_FAILURE);
       }

       res = ioctl(fd, KDGETLED, &leds);
       if (res == -1) {
           perror("ioctl KDGETLED");
           close(fd);
           exit(EXIT_FAILURE);
       }

       printf("Current keyboard LEDs: 0x%x\n", leds);
       printf("(1=ScrollLock, 2=NumLock, 4=CapsLock)\n");

       printf("Toggling Scroll Lock LED...\n");
       leds ^= LED_SCR;

       res = ioctl(fd, KDSETLED, leds);
       if (res == -1) {
           perror("ioctl KDSETLED");
           close(fd);
           exit(EXIT_FAILURE);
       }

       close(fd);
       printf("Done. Check your keyboard LEDs.\n");
       return 0;
   }