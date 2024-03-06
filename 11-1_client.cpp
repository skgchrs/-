#include <ezNetLib/UDPClient.h>
#include <string>
#include <chrono>
#include <thread>

int main(int argc, char* argv[])
{
    const std::string host = "127.0.0.1";
    const int port = 6000;
    std::string msg1 = "today";
    std::string msg2 = "now";

    eznetlib::UDPClient udpClient(host, port);
    
    udpClient.send(msg1);//"today"文字列送信
    std::this_thread::sleep_for(std::chrono::seconds(10));
    udpClient.send(msg2);//"now"文字列送信

    udpClient.release();
}