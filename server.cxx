
#include "include/enet.h"
#include <iostream>


//para diri mag memory leak, handle ctrl c kun mag terminate
#include <csignal>
bool running = true;
void signalHandler(int signum) {
    running = false;
}


int main(){
    std::signal(SIGINT, signalHandler);

    
    enet_initialize();
    ENetAddress address;
    ENetHost * server;

    address.host = ENET_HOST_ANY;
    address.port = 3344;

    server = enet_host_create(&address,32,2,0,0);


    ENetEvent event;

    char msg [128] = "Hi from server\n";
    const char *msg2 = "676767";
    ENetPacket *packet;

    printf("Host_service..starting\n");



    while(running){
        if(enet_host_service(server,&event,1000)>0){

            char ip[32];
            enet_address_get_host_ip(&event.peer->address, ip, sizeof(ip));
            switch(event.type){
                case ENET_EVENT_TYPE_CONNECT:
                    

                    printf("A connection is made by %s at port %u\n",ip,
                        event.peer->address.port);
                    
                    
                    packet = enet_packet_create(msg,strlen(msg)+1,ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(event.peer,0,packet);
                    
                    packet = enet_packet_create(msg2,strlen(msg2)+1,ENET_PACKET_FLAG_RELIABLE);
                    enet_peer_send(event.peer,0,packet);
                    break;
                case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
                    printf("Connection timeout\n");
                    break;
                case ENET_EVENT_TYPE_DISCONNECT:{
                    printf("Client disconneted %s",ip);
                    break;
                }
                default:
                    printf("Event defaulted\n");
                    break;
            }
        }
    }
    
    printf("Host destoryed and enet deinitialized");
    enet_host_destroy(server);
    enet_deinitialize();
    return 0;
}
