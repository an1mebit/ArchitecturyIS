#include <iostream>
#include <sstream>
#include <string>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/mount.h>
#include <sys/stat.h>

#include <platform/platform.h>
#include <kos_net.h>

#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

#define server_addr "localhost"
#define ANSI_COLOR_RED   "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define MAX_PENDING_CONNECTIONS 10

//состояния робота
enum State {
    MANUAL_CONTROL,
    WAIT_COMMAND_STATE, 
    MOVE_TO_POSITION_STATE, 
    ERROR_STATE, 
    CLEANING_STATE, 
    MOVE_TO_START_STATE, 
    OFF_STATE, 
    };

//структура для хранения позиции робота
struct Position {
    int x;
    int y;
};

static void printErrorMessage(const char *message) {
    printf(ANSI_COLOR_RED);
    perror(message);
    printf(ANSI_COLOR_RESET);
}

class CommandStrategy {
public:
    virtual std::string getCommand() = 0;
    virtual int init() = 0;
};

class CommandNetwork : public CommandStrategy {
private:
    int sock;
    int bytes_read;
    struct sockaddr_in stSockAddr;
    char buf [10];

public:
    int init() override {
        int serverSocketFD = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


        if (-1 == serverSocketFD)
        {
            printErrorMessage("Can not create socket");
            return EXIT_FAILURE;
        }

        memset(&stSockAddr, 0, sizeof(stSockAddr));

        stSockAddr.sin_family = AF_INET;
        stSockAddr.sin_port = htons(3425);
        stSockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

        struct addrinfo hints;
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;

        struct addrinfo *resultHints = NULL;
        int res = getaddrinfo(server_addr, NULL, &hints, &resultHints);
        if (res != 0)
        {
            perror("cannot get address info");
            close(serverSocketFD);
            return EXIT_FAILURE;
        }

        struct sockaddr_in* in_addr = (struct sockaddr_in *)resultHints->ai_addr;
        memcpy(&stSockAddr.sin_addr.s_addr, &in_addr->sin_addr.s_addr, sizeof(in_addr_t));
        freeaddrinfo(resultHints);

        res = -1;
        for (int i = 0; res == -1 && i < 10; i++)
        {
            sleep(1);
            res = connect(serverSocketFD, (struct sockaddr *)&stSockAddr, sizeof(stSockAddr));
        }

        if (-1 == bind(serverSocketFD, (struct sockaddr *)&stSockAddr, sizeof(stSockAddr)))
        {
            printErrorMessage("Error bind failed");
            close(serverSocketFD);
            return EXIT_FAILURE;
        }

        if (-1 == listen(serverSocketFD, MAX_PENDING_CONNECTIONS))
        {
            printErrorMessage("Error listen failed");
            close(serverSocketFD);
            return EXIT_FAILURE;
        }

        return 0;
    }

    std::string getCommand() override {
        std::cout << "Waiting for a command" << std::endl;
        std::string response;


        bytes_read = recvfrom(sock, buf, sizeof (buf), 0, NULL, NULL);
        buf[bytes_read + 1] = '\0';
        response = buf;

        return response;
    }
};

class CommandConsole : public CommandStrategy {
public:
    int init() override {
        return 0;
    };
    
    std::string getCommand() override {
        int code = -1;
        std::string response, x, y;
        std::cout << "Enter command"<< std::endl;
        std::cout << "Command list: " << std::endl <<
            "go to position-0, clean-1, manual-control-2, go to start position-3, turn off-4" << std::endl;
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
        return response;
    };
};

class Robot {
private:
    State state;
    CommandStrategy *cmd;
    Position *rob_pos;

    int ManualControl() {
        std::cout << "Manual mode: ON" << std::endl;
        std::cout << "Manual mode: OFF" << std::endl;
        return EXIT_SUCCESS;
    };

    int GoToPosition(int x_target, int y_target) {
        this->rob_pos->x = x_target;
        this->rob_pos->y = y_target;
        std::cout << "Robot position: (" << this->rob_pos->x << ";" << this->rob_pos->y << ")" << std::endl;
        return EXIT_SUCCESS;
    };

    int Error(int error_code) {
        std::cout << "Error %d" << error_code << std::endl;
        return EXIT_SUCCESS;
    };

    int CLeaning() {
        std::cout << "Graffiti is cleaned up" << std::endl;
        return EXIT_SUCCESS;
    };

public:
    Robot(CommandStrategy* source, Position* pos):state(WAIT_COMMAND_STATE), cmd(source), rob_pos(pos) {
        cmd->init();
    };

    ~Robot() {
        delete cmd;
        delete rob_pos;
    };

    State getState () {
        return state;
    };
            
    void processEvent (std::string command) {
        std::istringstream stream_command(command);
        int code;
        stream_command >> code;

        switch (state) {
            case WAIT_COMMAND_STATE:
                switch (code) {
                    case 0:
                        state = MOVE_TO_POSITION_STATE;
                        break;
                    case 1:
                        state = CLEANING_STATE;
                        break;
                    case 2:
                        state = MANUAL_CONTROL;
                        break;
                    case 3:
                        state = MOVE_TO_START_STATE;
                        break;
                    case 4:
                        state = OFF_STATE;
                        break;
                }
                break;

            case MOVE_TO_POSITION_STATE:
                int x_target, y_target;
                stream_command >> x_target;
                stream_command >> y_target;
                this->GoToPosition(x_target, y_target);

                state = WAIT_COMMAND_STATE;
                break;

            case ERROR_STATE:
                this->Error(-1);

                state = MOVE_TO_START_STATE;
                break;

            case CLEANING_STATE:
                this->CLeaning();

                state = MOVE_TO_START_STATE;
                break;

            case MOVE_TO_START_STATE:
                if (rob_pos->x != 0 || rob_pos->y != 0) {
                    this->GoToPosition(0, 0);
                }

                state = WAIT_COMMAND_STATE;
                break;

            case MANUAL_CONTROL:
                this->ManualControl();

                state = MOVE_TO_START_STATE;
                break;
        }
    };

    std::string getEvent () {
        return cmd->getCommand();
    };
};

int main (void) {
    Robot* cleaner;
    std::cout << "Choose method of control (c = соnsole  or n = network): ";
    char meth = 'n';
    if (meth == 'c') {
        cleaner = new Robot(new CommandConsole, new Position);
    } 
    else if (meth == 'n') {
        cleaner = new Robot(new CommandNetwork, new Position);
    }
    std::string command;
    while (cleaner->getState() != OFF_STATE) {
        if (cleaner->getState() == WAIT_COMMAND_STATE)
            command = cleaner->getEvent();
        cleaner->processEvent (command);
    }
    return 0;
}
