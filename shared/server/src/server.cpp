#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#define EXAMPLE_PORT 1103
#define MAX_PENDING_CONNECTIONS 10

int main(int argc, const char *argv[])
{
  for (;;)
  {
    struct sockaddr_in stSockAddr;

    int serverSocketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(-1 == serverSocketFD)
    {
      perror("can not create socket");
      return EXIT_FAIL_URE;
    }

    memset(&stSockAddr, 0, sizeof(stSockAddr));
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(EXAMPLE_PORT);
    stSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(-1 == bind(serverSocketFD,(struct sockaddr *)&stSockAddr, sizeof(stSockAddr)))
    {
      perror("error bind failed");
      close(serverSocketFD);
      return EXIT_FAILURE;
    }

    if(-1 == listen(serverSocketFD, MAX_PENDING_CONNECTIONS))
    {
      perror("error listen failed");
      close(serverSocketFD);
      return EXIT_FAILURE;
    }

    {
      fd_set readset;

      FD_ZERO(&readset);
      FD_SET(serverSocketFD, &readset);

      if (select(serverSocketFD + 1, &readset, NULL, NULL, NULL) == 1)
      {
        int ConnectFD = accept(serverSocketFD, NULL, NULL);
        if (ConnectFD == -1)
        {
          perror("error accept failed");
          close(serverSocketFD);
          return EXIT_FAILURE;
        }
        char buf[1024];

        if (-1 == recv(ConnectFD, buf, sizeof(buf), 0))
        {
          perror("recv failed");
          close(ConnectFD);
          close(serverSocketFD);
          return EXIT_FAILURE;
        }
        else
        {
          fprintf(stdout, "Server received: %s", buf);
        }

      if (-1 == shutdown(ConnectFD, SHUT_RDWR))
      {
        perror("can not shutdown socket");
        close(ConnectFD);
        close(serverSocketFD);
        return EXIT_FAILURE;
      }
      close(ConnectFD);
      }
      else
      {
        close(serverSocketFD);
        return EXIT_FAILURE;
      }
    }
    fflush(stdout);

    shutdown(serverSocketFD, SHUT_RDWR);
    close(serverSocketFD);
    return EXIT_SUCCESS;
  }
}