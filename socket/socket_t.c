#include <sys/socket.h>

void getRemoteIp()
{
    struct sockaddr_in sa;
    int len = sizeof(sa);

    if (!getpeername(sockfd, (struct sockaddr *)&sa, &len))
    {
        printf( "对方IP：%s ", inet_ntoa(sa.sin_addr));
        printf( "对方PORT：%d ", ntohs(sa.sin_port));
    }
}
