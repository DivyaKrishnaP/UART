#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#include "uart_demo.h"



int main(int argc, char **argv)
{
    int fd = 0;
    char dev[15];
    char *message = NULL;
    char *detail = "Hardware", *module_name;
    char receivedMessage[255];
    int firstChoice = 0;

    module_name = proc_info(detail);

	if(argc < 2)
	{
		printf("Usage:%s <uart device name> . e.g: uart_demo /dev/ttyHS3\n",argv[0]);
		exit(-1);
	}
	sprintf(dev,"%s",argv[1]);



    if(strstr(module_name, "Colibri T20"))
    {
    	printf("%s detected\n", module_name);
    	
    }
    else if(strstr(module_name, "Colibri T30"))
    {
    	printf("%s detected\n", module_name);
    	
    }
    else if(strstr(module_name, "Colibri VF50"))
    {
    	printf("%s detected\n", module_name);
    	
    }
    else if(strstr(module_name, "Colibri VF61"))
    {
    	printf("%s detected\n", module_name);
    	
    }
    else if(strstr(module_name, "Apalis T30"))
    {
    	printf("%s detected\n", module_name);
    	
    }
    else
    {
    	printf("unknown module\n");
    	return -1;

    }

    // Open the serial port.
    fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd >= 0)
    {
        // Successfully opened the serial port.
        // Configure the port.
        serialSetup(fd);
    }
    else
    {
        // Failed to open the serial port
        perror("Cannot open serial port device file");
    }

   while(1)
    {
        printf("\n*****************************************\n");
        printf("\t  Toradex UART Demo\n");
        printf("*****************************************\n");
        printf("[1] Read\n[2] Write\n[3] Exit\n");
        printf("Enter your choice:");
        scanf("%d", &firstChoice);

        if ((firstChoice > EXIT))
        {
            printf("Please enter your choice between 1-3.. Press Enter to exit\n");
            getchar();
            return -1;
        }

        switch (firstChoice)
        {
            case READ:

            	serialRead(fd, receivedMessage);
            	printf("Message recived is: %s\n", receivedMessage);

                break;

            case WRITE:

            	message = (char*)malloc(128);

            	printf("\nEnter the Message: "); scanf(" %[^\n]", message);

            	if((serialWrite(fd, message)) < 0) { break; }
            	else { printf("Message sent\n"); }

                break;

            case EXIT:
                // Close the serial port.
                close(fd);
            	free(message);
                break;
        }
    }
    return 0;
}

       

