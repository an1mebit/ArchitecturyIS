#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>


int main() {
  int sock;
  struct sockaddr_in addr;
  sock = socket(AF_INET, SOCK_DGRAM, 0);

  addr.sin_family = AF_INET;
  addr.sin_port = htons(3425);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  int code;
  std::string response, x, y;
  char message[10];
  while (true) {
          std::cout << "Enter command"<< std::endl;
          std::cout << "Command list: " << std::endl <<
              "go to positi on-0, clean-1, manual-control-2, go to start position-3, turn off-4" << std::endl;
          std::cin >> code; 
          while (code < 0 && code > 4) {
              std::cout << "Wrong command" << std::endl;
              std::cin >> code;
          }
          switch (code) {
              case 0:
                  std::cout << "Enter direction X and Y" << std::endl;
                  std::cin >> x >> y;
                  break;
          }
    response = std::to_string(code) + " " + x + " " + y;
    strcpy(message, response.c_str());
    sendto(sock, message, sizeof(message), 0, (struct sockaddr *)&addr, sizeof(addr));
  }
  close(sock);
  return 0;
}
