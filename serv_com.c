#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib, "Ws2_32.lib")
#define CHUNK_SIZE 1024

char *get(char *serv,int port,char *url) {
  WSADATA wsaData;
  SOCKET sock = INVALID_SOCKET;
  struct sockaddr_in server_addr;
  char *response = NULL;
  size_t response_size = 0;

  // Initialize Winsock
  if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
      return '\0';
  }
  // Create socket
  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock == INVALID_SOCKET) {
      WSACleanup();
      return '\0';
  }
  // Setup server address - localhost:3000
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  server_addr.sin_addr.s_addr = inet_addr(serv);  // localhost
  // Connect to server
  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
      closesocket(sock);
      WSACleanup();
      return '\0';
  }
  // Send HTTP GET request for /names
  char *http_request = malloc(512);
  snprintf(http_request,512,        
    "GET /%s HTTP/1.1\r\n"
    "Host: localhost\r\n"
    "Connection: close\r\n"
    "\r\n",url);
  int sent = send(sock, http_request, (int)strlen(http_request), 0);
  if (sent == SOCKET_ERROR) {
      closesocket(sock);
      WSACleanup();
      return '\0';
  }
  // Receive response dynamically
  char buffer[CHUNK_SIZE];
  int bytes_received;
  while ((bytes_received = recv(sock, buffer, CHUNK_SIZE, 0)) > 0) {
    char *new_response = realloc(response, response_size + bytes_received + 1);
    if (!new_response) {
        free(response);
        closesocket(sock);
        WSACleanup();
        return '\0';
    }
    response = new_response;
    memcpy(response + response_size, buffer, bytes_received);
    response_size += bytes_received;
    response[response_size] = '\0';
  }
  if (bytes_received != SOCKET_ERROR) {
    char *body = strstr(response, "\r\n\r\n");
    free(response);
    closesocket(sock);
    WSACleanup();
    if (body != NULL) {
      body += 4; // Skip the "\r\n\r\n"
      return body;
    } 
    else {
      return '\0';
    }
  }
  free(response);
  closesocket(sock);
  WSACleanup();
  return '\0';
}

char *post(){
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    struct sockaddr_in server_addr;
    char *response = NULL;
    size_t response_size = 0;
    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return '\0';
    }

    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        WSACleanup();
        return '\0';
    }

    // Setup server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        printf("Connect failed\n");
        closesocket(sock);
        WSACleanup();
        return '\0';
    }

    // JSON data to send
    const char *json_data = "{\"name\":\"John\"}";
    char http_request[1024];

    // Build HTTP POST request
    snprintf(http_request, sizeof(http_request),
        "POST /names HTTP/1.1\r\n"
        "Host: localhost\r\n"
        "Content-Type: application/json\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n"
        "%s",
        (int)strlen(json_data), json_data);

    // Send request
    int sent = send(sock, http_request, (int)strlen(http_request), 0);
    if (sent == SOCKET_ERROR) {
        printf("Send failed\n");
        closesocket(sock);
        WSACleanup();
        return '\0';
    }

    // Receive response dynamically
    char buffer[CHUNK_SIZE];
    int bytes_received;
    while ((bytes_received = recv(sock, buffer, CHUNK_SIZE, 0)) > 0) {
        char *new_response = realloc(response, response_size + bytes_received + 1);
        if (!new_response) {
            printf("Memory allocation failed\n");
            free(response);
            closesocket(sock);
            WSACleanup();
            return '\0';
        }
        response = new_response;
        memcpy(response + response_size, buffer, bytes_received);
        response_size += bytes_received;
        response[response_size] = '\0';
    }

  if (bytes_received != SOCKET_ERROR) {
    char *body = strstr(response, "\r\n\r\n");
    free(response);
    closesocket(sock);
    WSACleanup();
    if (body != NULL) {
      body += 4; // Skip the "\r\n\r\n"
      return body;
    } 
    else {
      return '\0';
    }
  }
  free(response);
  closesocket(sock);
  WSACleanup();
  return '\0';
}



int main(){
  printf("%s",post());
}