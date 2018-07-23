#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include "system.h"
#include "packet.h"
//#include "winsock.h"

BYTE  buffer[1024];    //分配一段内存区
#define INVALID_SOCKET -1
int sock;

int InitSocket(int iport)
{
        struct sockaddr_in addr;

        //WSADATA Data;
        int err;

        sock=INVALID_SOCKET;
        //err = WSAStartup(MAKEWORD(1,1), &Data);
        //if (err!=0) return sock;

        sock=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (sock != INVALID_SOCKET)
        {
                addr.sin_family=AF_INET;
                addr.sin_port=htons((WORD)iport);
                addr.sin_addr.s_addr=htonl(INADDR_ANY);

                if (bind(sock, (struct sockaddr*)(&addr), sizeof(struct sockaddr_in)) < 0)
                {
                        close(sock);
                        sock= INVALID_SOCKET;
                }
        }
        return sock;
}

int CloseSocket(SOCKET s)
{
        if (s!=INVALID_SOCKET) close(s);
        //WSACleanup();
        return 0;
}

int SocketWrite(SOCKET s, BYTE* buffer, DWORD size, char* ip, WORD port)
{
        struct sockaddr_in addr;
        if (s!=INVALID_SOCKET)
        {
                addr.sin_family=AF_INET;
                addr.sin_port=htons(port);
                addr.sin_addr.s_addr=inet_addr(ip);
                return sendto(s, (const char*)buffer, size, 0, (struct sockaddr*)(&addr), sizeof(struct sockaddr_in));
        }
        return 0;
}

int SocketRead(SOCKET s, BYTE* buffer, DWORD size, char* ip, WORD* port)
{
        fd_set readfds;
        struct timeval timeout;
        int dwSize, fromlen;
        struct sockaddr_in addr;

        if (s!=INVALID_SOCKET)
        {
                #if 0
                readfds.fd_count=0;
                if (readfds.fd_count<FD_SETSIZE)
                {
                        readfds.fd_array[readfds.fd_count]=s;
                        readfds.fd_count++;
                }
                #endif
                FD_ZERO(&readfds);
                FD_SET(s, &readfds);
                timeout.tv_sec=0;
                timeout.tv_usec=100000;
                if (select(s + 1, &readfds, NULL, NULL, &timeout))
                {
                        if (FD_ISSET(s, &readfds))
                        {
                                fromlen=sizeof(struct sockaddr_in);
                                dwSize=recvfrom(s, (char*)buffer, size, 0, (struct sockaddr*)(&addr),
                                (socklen_t *)&fromlen);
                                if (dwSize > 0)
                                {
                                        *port=htons(addr.sin_port);
                                        strcpy(ip, inet_ntoa(addr.sin_addr));
                                        return dwSize;
                                }
                        }
                }
        }
        return 0;
}
