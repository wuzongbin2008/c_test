#ifndef LIBEVENT_TEST_H_INCLUDED
#define LIBEVENT_TEST_H_INCLUDED

int libevent_server_test(int argc, char* argv[]);
int libevent_client_test(int argc, char*argv[]);
void release_sock_event(struct sock_ev* ev);
void on_write(int sock, short event, void* arg);
void on_read(int sock, short event, void* arg);
void on_accept(int sock, short event, void* arg);

#endif // LIBEVENT_TEST_H_INCLUDED
