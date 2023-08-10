#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

struct sockaddr_in serverAddr;
serverAddr.sin_family = AF_INET;
serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
serverAddr.sin_port = htons(9999);

bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

listen(serverSocket, 5);

while(1) {
  int clientSocket = accept(serverSocket, NULL, NULL);

  pthread_t thread;
  pthread_create(&thread, NULL, handleClient, (void*)&clientSocket);
}
