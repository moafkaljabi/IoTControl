#include <iostream>
#include <vector>

std::vector<int> serverSockets;  // [1,2,3]

int main(){

    for(int i =0; i < 10; i++) {
        std::cout << i << std::endl;
        serverSockets.push_back(i);
        std::cout << serverSockets[i] << std::endl;
    }

    return 0;
}