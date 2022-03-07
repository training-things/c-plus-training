#include <iostream>
#include <unistd.h>
#include <unordered_map>
// #include <sys/socket.h>

#include <errno.h>
#include <fcntl.h>
#include <poll.h>

#include <arpa/inet.h>

int checkConnectDone(int fd, sockaddr_in saddr)
{
    int rc = connect(fd, (const struct sockaddr *)&saddr, sizeof(saddr));
    if (rc == 0)
    {
        return 1;
    }
    switch (errno)
    {
    case EISCONN:
    case EALREADY:
    case EINPROGRESS:
    case EWOULDBLOCK:
        return 1;
    default:
        return -1;
    }
}

int waitReady(int fd, long msec, sockaddr_in saddr)
{
    struct pollfd wfd[1];

    wfd[0].fd = fd;
    wfd[0].events = POLLOUT;

    if (errno == EINPROGRESS)
    {
        int res;

        if ((res = poll(wfd, 1, msec)) == -1) // poll(2)
        {
            return -3;
        }
        else if (res == 0) // errno = ETIMEDOUT;
        {

            return -2;
        }

        if (checkConnectDone(fd, saddr) < 0)
        {
            return -4;
        }

        return 1;
    }

    return -1;
}

int setBlocking(int fd, int blocking)
{
    int flags;
    /* Set the socket nonblocking.
     * Note that fcntl(2) for F_GETFL and F_SETFL can't be
     * interrupted by a signal. */
    if ((flags = fcntl(fd, F_GETFL)) == -1)
    {
        return -1;
    }
    if (blocking)
        flags &= ~O_NONBLOCK;
    else
        flags |= O_NONBLOCK;

    if (fcntl(fd, F_SETFL, flags) == -1)
    {
        return -1;
    }

    return 1;
}

int main(int argc, char **argv)
{
    unsigned int j, isunix = 0;
    const char *hostname = (argc > 1) ? argv[1] : "127.0.0.1";

    int blocking = 0;

    if (argc > 2)
    {
        if (*argv[2] == 'u' || *argv[2] == 'U')
        {
            isunix = 1;
            /* in this case, host is the path to the unix socket */
            printf("Will connect to unix socket @%s\n", hostname);
        }
    }

    if (argc > 3)
    {
        blocking = 1;
    }

    int port = (argc > 2) ? atoi(argv[2]) : 6379;

    printf("hostname:port %s:%d\n", hostname, port);

    printf("this0\n");

    std::unordered_map<std::string, std::string> pairs;

    auto sync_port = pairs["sync_port"].c_str();

    printf("pairs.sync_port.c_str:%s, sync_port=%d\n", sync_port, atoi(sync_port));

    auto sin_port = htons(port);

    printf("sin_port=%d\n", sin_port);

    auto sin_port1 = htons(atoi(sync_port));
    printf("sin_port1=%d\n", sin_port1);

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in master_addr;
    memset(&master_addr, 0, sizeof(struct sockaddr_in));

    master_addr.sin_family = AF_INET;
    master_addr.sin_port = sin_port;

    printf("this1 sock_fd=%d\n", sock_fd);

    if (inet_pton(AF_INET, hostname, &master_addr.sin_addr) <= 0)
    {
        printf("demote error: parse master ip failed\n");
        return false;
    }

    printf("master_addr.sin_addr.s_addr: %d\n", master_addr.sin_addr.s_addr);

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 1 * 1000;
    // SO_SNDTIMEO
    setsockopt(sock_fd, SOL_SOCKET, SO_SNDTIMEO, (const char *)&tv, sizeof tv);
    setsockopt(sock_fd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof tv);

    printf("this2\n");

    if (blocking)
    {
        setBlocking(sock_fd, 0);
    }

    if (connect(sock_fd, (struct sockaddr *)&master_addr, sizeof(master_addr)) <
        0)
    {

        printf("connect error: %s\n", strerror(errno));

        int wait = waitReady(sock_fd, 3000, master_addr);
        printf("wait:%d\n", wait);

        if (wait != 1)
        {
            printf("demote error: connect to master failed\n");
            return false;
        }
    }

    if (blocking)
    {
        setBlocking(sock_fd, 1);
    }

    printf("connected\n");
}
