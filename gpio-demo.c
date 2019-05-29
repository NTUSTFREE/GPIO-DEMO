/*HEADR FILE*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include "IPMI_App.h"
#include "Types.h"
#include "IPMIDefs.h"
#include "IPMI_AppDevice.h"
#include "IPMIConf.h"
#include "Util.h"
#include "hal_hw.h"
#include "AppDevice.h"
#include "OEMCmds.h"
#include "LEDMap.h"
#include "PDKHW.h"
#include "mmap.h"
#include "Util.h"
#include "EINTR_wrappers.h"
#include "gpio.h"

int main(){

	int cmd;
	int gpio_fd;
	int ioctl_ret;
	int gpio_number;
	gpio_ioctl_data gpio_arg;
	
	puts("Please enter command which you want to demo:\n0:Get GPIO dir\n1:Set GPIO dir as input\n2:Set GPIO dir as output\n3:Get GPIO data\n4:Set GPIO data to high\n5:Set GPIO data to low\n");
			
	scanf("%d %d", &cmd, &gpio_number);
	gpio_fd = sigwrap_open( GPIO_CTL_FILE, O_RDWR );
   	if( gpio_fd == -1 )
	printf("Couldn't open device node of gpio..\n");

	switch(cmd)
	{
		case 0:
				gpio_arg.PinNum = gpio_number;
				ioctl_ret = ioctl( gpio_fd, (unsigned long)GET_GPIO_DIRECTION, &gpio_arg );
				if(ioctl_ret==-1)printf("ioctl failed!!..\n");
				
				if(gpio_arg.data == 1)printf("GPIO direction is output\n");

				else if(gpio_arg.data == 0)printf("GPIO direction is input\n");

				else printf("Operation failed!\n");
					
				break;
		case 1:
					
				gpio_arg.PinNum = gpio_number;
				gpio_arg.data = 0;
					
				ioctl_ret = ioctl( gpio_fd, (unsigned long)SET_GPIO_DIRECTION, &gpio_arg );
				if(ioctl_ret==-1)printf("ioctl failed!!..\n");
				printf("Set GPIO direction as input..\n");
				break;
		case 2: 
				gpio_arg.PinNum = gpio_number;
				gpio_arg.data = 1;
					
				ioctl_ret = ioctl( gpio_fd, (unsigned long)SET_GPIO_DIRECTION, &gpio_arg );
				if(ioctl_ret==-1)printf("ioctl failed!!..\n");
				printf("Set GPIO direction as output..\n");
				break;
		case 3:
				gpio_arg.PinNum = gpio_number;
				ioctl_ret = ioctl( gpio_fd, (unsigned long)READ_GPIO, &gpio_arg );
				if(ioctl_ret==-1)printf("ioctl failed!!..\n");
					
				if(gpio_arg.data == 1)printf("GPIO data is high\n");

				else if(gpio_arg.data == 0)printf("GPIO data is low\n");

				else printf("Operation failed!\n");
					
				break;
		case 4: 
					
    				gpio_arg.PinNum = gpio_number;
    				gpio_arg.data = 1;

				ioctl_ret = ioctl( gpio_fd, (unsigned long)WRITE_GPIO, &gpio_arg );
				if(ioctl_ret==-1)printf("ioctl failed!!..\n");
				printf("Set GPIO data to high..\n");
				break;
		case 5:
				gpio_arg.PinNum = gpio_number;
    				gpio_arg.data = 0;

				ioctl_ret = ioctl( gpio_fd, (unsigned long)WRITE_GPIO, &gpio_arg );
				if(ioctl_ret==-1)printf("ioctl failed!!..\n");
				printf("Set GPIO data to high..\n");
				break;
		default:
				printf("Couldn't recognize this type of action\n");
				break;
			
		}
	(void)sigwrap_close( gpio_fd );
	return 0;
}
