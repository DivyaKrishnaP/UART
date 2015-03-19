UART_demo is an application through which read and write operations can be done from computer module to PC.


Hardware setup:
connect the serial port (UART_A/UART_B/UART_C) you want to test, through null modem aka cross-over cable to your PC's serial port or USB to 
serial adapter.


Compiling the application:
In the application directory, run make command preceding machine(module) name.
e.g: MACHINE=colibri-t20 make
Copy the exe to the module either through ethernet and USB.
Ethernet:
scp UART_demo root@10.18.0.162:/home/root
USB:
cp UART_demo /media/USB


Run the application:
Run the application with application name followed by uart device name.
e.g: ./uart_demo /dev/ttyHS3
Open serial terminal like minicom on the PC with command (sudo minicom -s) and configure it with the appropriate 
USB to serial adapter device name and set baud rate to 115200.


Output:
Output gives the option of read and write, choose an action to be done by giving 1 and 2 for read and write respectively. In read, the data 
transmitted from PC will be displayed at module's end and in write, the data written from module will be displayed in the serial terminal on 
PC.
