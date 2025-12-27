#include "include/enet.h"
#include <iostream>


int main(){

    enet_initialize();
    ENetAddress address;
    ENetHost *client;
    ENetPeer *peer;

    enet_address_set_host(&address,"34.122.23.53");
    address.port = 3344;
    client = enet_host_create(NULL,32,2,0,0);

    peer = enet_host_connect(client,&address,1,0);

    ENetEvent event;
    if(enet_host_service(client,&event,5000)>0 && event.type == ENET_EVENT_TYPE_CONNECT){
        printf("Connected success\n");
    }
    else{
        printf("Connection unsuccessful\n");
    }
    while(enet_host_service(client,&event,5000)>0){
        switch (event.type)
        {
        case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
            printf("Connection timeout\n");
            break;
        case ENET_EVENT_TYPE_DISCONNECT:
        printf("Connection disconnected\n");
            break;
        case ENET_EVENT_TYPE_RECEIVE:{
            printf("Packet received at lenght: %zu\n",event.packet->dataLength);
            printf("Message: %s\n", event.packet->data);

            enet_packet_destroy(event.packet);
            break;
        }
        default:
            printf("Event defaulted\n");
            break;
        }
    }
    enet_host_destroy(client);
    enet_deinitialize();
    return 0;
}
