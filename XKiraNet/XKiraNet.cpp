#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <ctime>
#include <random>
#include <windows.h>
#include <regex>
#include <string>

using namespace std;

std::string botnetb64encryted = "NjYuMjI4LjMzLjE5Nw==";

void setConsoleColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void sendPayload(int packetSize) {
    int progress = 0;
    while (progress < packetSize) {
        int chunk = rand() % 100 + 1;
        progress += chunk;
        if (progress > packetSize) progress = packetSize;
        this_thread::sleep_for(chrono::milliseconds(50));
    }
}

void randomizeHeaders() {
    static const string headers[] = {
        "User-Agent: Mozilla/5.0", "Accept-Encoding: gzip, deflate",
        "Connection: keep-alive", "Content-Type: application/x-www-form-urlencoded",
        "Cache-Control: no-cache", "Accept-Language: en-US,en;q=0.9"
    };
    int headerCount = rand() % 3 + 2;
    for (int i = 0; i < headerCount; ++i) {
        cout << headers[rand() % 6] << endl;
    }
}

bool isValidIP(const string& ip) {
    regex ipPattern(R"((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?))");
    return regex_match(ip, ipPattern);
}

bool pingIP(const string& ip) {
    string command = "ping -n 1 " + ip + " >nul 2>&1";
    return system(command.c_str()) == 0;
}

void simulatePacketSending(const string& ip, int port, int duration) {
    int packetsSent = 0;
    auto startTime = chrono::steady_clock::now();
    auto endTime = startTime + chrono::seconds(duration);

    setConsoleColor(2);

    while (chrono::steady_clock::now() < endTime) {
        int packetSize = rand() % 1436 + 64;

        setConsoleColor(9);
        cout << "[INFO] Establishing connection to " << ip << " on port " << port << "..." << endl;
        randomizeHeaders();

        setConsoleColor(10);
        cout << "[INFO] Sending data packet of size: " << packetSize << " bytes." << endl;
        sendPayload(packetSize);

        setConsoleColor(2);
        cout << "[INFO] Packet sent successfully." << endl;

        packetsSent++;
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    setConsoleColor(12);
    cout << "\nOperation completed. Total packets sent: " << packetsSent << endl;
}

void displayBanner() {
    setConsoleColor(11);

    cout << R"(

        ********** XKIRANET TOOL **********
)" << endl;

    setConsoleColor(7);
}

int main() {
    string targetIP;
    int targetPort;
    int attackDuration;

    displayBanner();

    setConsoleColor(14);
    cout << "Enter target IP address: ";
    cin >> targetIP;

    while (!isValidIP(targetIP)) {
        cout << "Invalid IP address format. Please enter a valid IP: ";
        cin >> targetIP;
    }

    if (!pingIP(targetIP)) {
        cout << "The IP address " << targetIP << " is not responding to pings. Exiting." << endl;
        return 1;
    }

    cout << "Enter target port: ";
    cin >> targetPort;

    cout << "Enter attack duration (in seconds): ";
    cin >> attackDuration;

    setConsoleColor(13);
    cout << "\nLaunching attack on " << targetIP << " at port " << targetPort << "...\n" << endl;

    srand(static_cast<unsigned int>(time(0)));
    simulatePacketSending(targetIP, targetPort, attackDuration);

    setConsoleColor(7);
    cout << "\nClosing connection." << endl;

    return 0;
}
