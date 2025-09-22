// operator.c
// PSEUDO-CODE!
// gcc operator.c -o operator
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5555);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sock, (struct sockaddr*)&addr, sizeof(addr));
    listen(sock, 1);

    printf("Waiting for client...\n");
    int client = accept(sock, NULL, NULL);
    char buf[256];
    while (fgets(buf, sizeof(buf), stdin)) {
        send(client, buf, strlen(buf), 0);
    }
    close(client);
    close(sock);
    return 0;
}
