project(robot)

set(HEADERS "../common/SocketExchanger.h" "../Common/socketExchanger.cpp" "src/generator.h" "src/generator.cpp")

add_executable(Client "src/main.cpp" "${HEADERS}")