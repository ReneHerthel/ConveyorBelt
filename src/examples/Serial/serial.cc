#include <hw/inout.h>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>



int main(int argc, char *argv[]) {
	char buff_in[20] = {0};
	char buff_out[20] = "Hallo Welt";

	int fd_ser1 = open("/dev/ser1", O_WRONLY);
	int fd_ser2 = open("/dev/ser2", O_RDONLY);

	struct termios ts_ser1;
	tcflush(fd_ser1, TCIOFLUSH); //Reset driver buffer (not the buffer we declared)
	tcgetattr(fd_ser1, &ts_ser1); //set all attributes predefined in serial to the terminos struct
	cfsetispeed(&ts_ser1, B115200); //input and output baud rate
	cfsetospeed(&ts_ser1, B115200);
	ts_ser1.c_cflag &= ~CSIZE; //reset the character size
	ts_ser1.c_cflag &= ~CSTOPB; //disable two stop bits
	ts_ser1.c_cflag &= ~PARENB;	//disable parity bit
	ts_ser1.c_cflag |= CS8;  	//8bit character
	ts_ser1.c_cflag |= CREAD; //enable receiver
	ts_ser1.c_cflag |= CLOCAL; //ignore module lines
	tcsetattr(fd_ser1, TCSANOW, &ts_ser1); //transfer the options to the serial file object, TCSANOW immediately

	struct termios ts_ser2;
	tcflush(fd_ser2, TCIOFLUSH);
	tcgetattr(fd_ser2, &ts_ser2);
	cfsetispeed(&ts_ser2, B115200);
	cfsetospeed(&ts_ser2, B115200);
	ts_ser2.c_cflag &= ~CSIZE;
	ts_ser2.c_cflag &= ~CSTOPB;
	ts_ser2.c_cflag &= ~PARENB;
	ts_ser2.c_cflag |= CS8;
	ts_ser2.c_cflag |= CREAD;
	ts_ser2.c_cflag |= CLOCAL;
	tcsetattr(fd_ser2, TCSANOW, &ts_ser2);

	if(fd_ser1 < 0 || fd_ser2 < 0){
		std::cout << "Serial Open Failed" << fd_ser1 << " " << fd_ser2 << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Trying Write" <<  " " <<  std::endl;
	int written = write(fd_ser1, &buff_out, 11);
	std::cout << "Written" <<  " " << written <<  std::endl;

	std::cout << "Trying Read" <<  " " <<  std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3));
	int received = read(fd_ser2, &buff_in, 11);
	std::cout << "Received" <<  " " << received << std::endl;

	if(written < 0 || received < 0){
			std::cout << "Write/Read failed" << written << " " << received << std::endl;
			return EXIT_FAILURE;
	}

	std::cout << written << " | " << received << std::endl;

	std::cout<<buff_in<<std::endl;

	close(fd_ser1);
	close(fd_ser2);
}
