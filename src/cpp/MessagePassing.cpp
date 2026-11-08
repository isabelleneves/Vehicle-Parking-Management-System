#include <iostream>
#include <queue>
#include <string>

class MessageQueue {

private:
    std::queue<std::string> messages;

public:
    void sendMessage(const std::string& message) {
        messages.push(message);

        std::cout << "Producer sent: "
                  << message << std::endl;
    }

    void receiveMessage() {
        if (!messages.empty()) {
            std::string message = messages.front();
            messages.pop();

            std::cout << "Consumer received: "
                      << message << std::endl;
        }
    }
};

int main() {

    MessageQueue parkingMessages;

    std::cout << "MESSAGE PASSING TEST" << std::endl;
    std::cout << "--------------------" << std::endl;

    // Producer sends vehicle information
    parkingMessages.sendMessage("ABC123 - Motorcycle");
    parkingMessages.sendMessage("DEF456 - Car");
    parkingMessages.sendMessage("GHI789 - Bus");

    std::cout << std::endl;

    // Consumer receives vehicle information
    parkingMessages.receiveMessage();
    parkingMessages.receiveMessage();
    parkingMessages.receiveMessage();

    return 0;
}
