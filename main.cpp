#include <sys/ioctl.h> 
#include <fcntl.h> 
#include <iostream>
#include <unistd.h>
#include <linux/gpio.h>



int main(){
        int fd = open("/dev/gpiochip0",O_RDWR);
        if(fd < 0){
                std::cout<<"Unable to open file\n";
               return 0;
        }
        struct gpioline_info line_info;
        struct gpiochip_info info;
        int ioctl_response_value = ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &info);

        if (ioctl_response_value  < 0)

        {

                std::cout<<"Unable to get chip info from ioctl\n";
                close(fd);
                return 0;

        }

        struct gpiohandle_request request_object;
        request_object.flags = GPIOHANDLE_REQUEST_OUTPUT;
        request_object.lineoffsets[0] = 194; 
        request_object.lines = 1; 
         
        ioctl_response_value = ioctl(fd,GPIO_GET_LINEHANDLE_IOCTL,&request_object);
        if(ioctl_response_value < 0){
           std::cout<<"Unable to set GPIO pin\n";
           return 0; 
        }    

    
        struct gpiohandle_data data_object; 
        for(size_t i{}; i < 11; i++){
                i%2 == 0? data_object.values[0] = 3: data_object.values[0] = 0; 
                ioctl_response_value = ioctl(request_object.fd,GPIOHANDLE_SET_LINE_VALUES_IOCTL,&data_object);
                std::cout<<i%2<<std::endl;      
                if(ioctl_response_value < 0){
                   std::cout<<"Unable to output value to GPIO pin\n";
                   return 0; 
                }
                usleep(1000000);
        }
}
