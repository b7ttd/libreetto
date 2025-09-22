// receiver.c
// pseudo code obviously not real, made by evil CHATGPT
// gcc receiver.c -o seat_client
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    inet_pton(AF_INET, "192.168.1.100", &addr.sin_addr); // operator IP

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect failed");
        return 1;
    }

    char buf[256];
    while (1) {
        int n = recv(sock, buf, sizeof(buf)-1, 0);
        if (n <= 0) break;
        buf[n] = '\0';
        printf("\033[2J\033[H"); // clear screen
        printf("%.*s\n", 16, buf); // first line
        if (n > 16) printf("%.*s\n", 16, buf+16); // second line
    }
    close(sock);
    return 0;
}
