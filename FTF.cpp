#include "client.hpp"
#include "server.hpp"

void srv_start()
{
    p2pserver server;
    server.Start(10088);
}

int main ()
{
    std::thread thr(srv_start);
    thr.detach();
    PClient client;
    client.Start(10088);
    return ;
}
