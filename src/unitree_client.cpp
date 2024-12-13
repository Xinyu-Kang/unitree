#include <unitree/robot/go2/sport/sport_client.hpp>
#include <iostream>
#include <thread>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace unitree::robot::go2;

// 处理从电脑接收到的指令
void handleCommand(const std::string &command, SportClient &sport_client) {
    if (command == "sit") {
        sport_client.Sit();  // 调用 SDK 的坐下接口
    } else if (command == "stand_up") {
        sport_client.StandUp();  // 调用站起来接口
    } else if (command == "move_forward") {
        sport_client.Move(0.5, 0, 0);  // 向前走，设置 vx=0.5
    } else if (command == "move_backward") {
        sport_client.Move(-0.5, 0, 0);  // 向后走，设置 vx=-0.5
    }
}

int main() {
    // 初始化机械狗控制接口
    SportClient sport_client;
    sport_client.Init();

    // 设置网络通信
    io_context io;
    ip::tcp::acceptor acceptor(io, ip::tcp::endpoint(ip::tcp::v4(), 8888));
    ip::tcp::socket socket(io);

    std::cout << "Waiting for connection..." << std::endl;
    acceptor.accept(socket);
    std::cout << "Connected to controller!" << std::endl;

    char buffer[1024];
    while (true) {
        std::size_t length = socket.read_some(buffer(buffer));
        std::string command(buffer, length);
        handleCommand(command, sport_client);
    }

    return 0;
}
