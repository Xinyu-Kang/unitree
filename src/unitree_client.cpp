#include <unitree/robot/b2/sport/sport_client.hpp>
#include <unitree/robot/channel/channel_factory.hpp>
#include <unitree/robot/channel/channel_subscriber.hpp>
#include <iostream>
#include <string>

using namespace unitree::robot;
using namespace unitree::robot::b2;

// Handle incoming robot commands
void handleCommand(const std::string &command, SportClient &sport_client) {
    if (command == "sit") {
        sport_client.Sit();  // Call SDK's sit function
        std::cout << "Command: Sit executed.\n";
    } else if (command == "stand_up") {
        sport_client.StandUp();  // Call stand-up function
        std::cout << "Command: Stand Up executed.\n";
    } else if (command == "move_forward") {
        sport_client.Move(0.5, 0, 0);  // Move forward with vx=0.5
        std::cout << "Command: Move Forward executed.\n";
    } else if (command == "move_backward") {
        sport_client.Move(-0.5, 0, 0);  // Move backward with vx=-0.5
        std::cout << "Command: Move Backward executed.\n";
    } else {
        std::cerr << "Unknown command: " << command << std::endl;
    }
}

int main() {
    try {
        // Initialize DDS communication
        ChannelFactory::Instance()->Init(0);  // Automatically selects network interface
        std::cout << "DDS communication initialized.\n";

        // Initialize SportClient for robot control
        SportClient sport_client;
        sport_client.Init();
        std::cout << "SportClient initialized.\n";

        // Create a subscriber for receiving commands
        ChannelSubscriber<std::string> commandSubscriber("robot_command_channel");
        commandSubscriber.InitChannel([&](const void *message) {
            std::string command = *static_cast<const std::string *>(message);
            handleCommand(command, sport_client);
        });

        std::cout << "Waiting for commands...\n";

        // Keep the program running to process incoming commands
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
