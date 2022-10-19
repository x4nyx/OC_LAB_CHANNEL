#include <iostream>
#include <thread>
#include "buffered_channel.h"

void threadFunc(BufferedChannel<int> &channel) {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    channel.send(51);
    channel.close();
}

int main() {
    BufferedChannel<int> channel(10);
    for (int i = 0; i < 10; i++) {
        channel.send(i);
    }
    std::thread thr(threadFunc, std::ref(channel));
    for (int i = 0; i < 12; i++) {
        std::pair<int, bool> value = channel.recv();
        std::cout << value.first << std::endl;
    }
    thr.join();

    return 0;
}