#ifndef UART_DEMO_H_
#define UART_DEMO_H_

#include <termios.h>
#include <fcntl.h>

//Switch cases
#define READ 1
#define WRITE 2
#define EXIT 3

void serialSetup(int fileDescriptor)
{
    struct termios options;
    // Set serial port to blocking mode.
    fcntl(fileDescriptor, F_SETFL, 0);
    // Get the current options for the port.
    tcgetattr(fileDescriptor, &options);
    // Set the tx and rx baud rates to 115,200.
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);
    // Enable the receiver and set local mode.
    options.c_cflag |= (CLOCAL | CREAD);
    // 8 data bits, no parity, one stop bit.
    // 8N1
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    // No hardware flow control.
    options.c_cflag &= ~CRTSCTS;
    // No software flow control.
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    // Raw input mode. No line buffering.
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    // Raw output mode.
    options.c_oflag &= ~OPOST;
    // Flush the input buffer
    tcflush(fileDescriptor, TCIFLUSH);
    // Set the new options for the port.
    tcsetattr(fileDescriptor, TCSANOW, &options);
}

char *serialRead(int fileDescriptor, char *receivedMessage)
{
    char rxBuf = '\0';
    int count = 0;
    // Read serial port one char at a time
    // until a newline is received.
    printf("Reading..\n");
    while (rxBuf != 0xa)
    {
	read(fileDescriptor, &rxBuf, 1);
        if (rxBuf != 0xa)	//checking  for line feed
        {
		receivedMessage[count] = rxBuf;
        	count++;
        }
    }
    receivedMessage[count] = '\0';

    return receivedMessage;
}

int serialWrite(int fileDescriptor, char *message)
{
	strncat(message, "\r\n", 4);
    if(write(fileDescriptor, message, strlen(message)) < 0)
    {
    	perror("Message send failed !");
    	return -1;
    }
    return 0;
}


char *proc_info(char *detail)
{

	FILE *f = fopen ("/proc/cpuinfo", "r");

	char *a = malloc (256);
	char *b = malloc (128);
	char *c = malloc (128);

	while (!feof (f))
	{
		fgets (a, 512, f);

		if (strlen (a) == 1) continue;

		sscanf (a, "%[^\t:] : %[^\t\n]", b, c);

		if(strstr(b, detail))
		{
			return c;
		}
	}

	fclose (f);
	free(a);
	free(b);
	free(c);
	return "Unknown module";
}

#endif /* UART_DEMO_H_ */
