//
// Created by Roy on 28/11/19.
//

#ifndef UNTITLED_DATACENTER_H
#define UNTITLED_DATACENTER_H

#include <iostream>
#include "linkedList.h"

class ServerDetails {
public:
    int system;
    bool is_taken;
    Node *position;

    ServerDetails(Node *p = nullptr) : position(p) {
        system = 0;
        is_taken = false;
    }

    void SetPosition(Node *p) { position = p; }
};

class DataCenter {
public:
    int id;
    int size;
    int linux_size;
    int windows_size;
    DoubleLinkedList linux_servers;
    DoubleLinkedList windows_servers;
    ServerDetails *servers;

    DataCenter(int given_id, int servers_num) : id(given_id), size(servers_num), linux_size(servers_num),
                                                windows_size(0) {
        servers = new ServerDetails[size];
        for (int i = 0; i < size; i++) {
            Node *temp = new Node(i);
            linux_servers.beginningInsert(temp);
            servers[i].SetPosition(temp);
        }
    }

    ~DataCenter() {
        delete[] servers;
    }

    void printPosition() {
        for (int i = 0; i < size; i++) {
            std::cout << servers[i].position << "," << servers[i].system << ", " << servers[i].is_taken << ", \n";
        }
    }

    void printServers() {
        std::cout << "this linux: ";
        linux_servers.print();
        //printf("head is %d, tail is %d\n", linux_servers.head->m_data, linux_servers.tail->m_data);
        std::cout << "this windows: ";
        windows_servers.print();
        //printf("head is %d, tail is %d\n", windows_servers.head->m_data, windows_servers.tail->m_data);
        std::cout << "total linux = " << linux_size << "   total windows = " << windows_size << std::endl;

    }

    void requestServer(int os, int given_server, int *assigned_server);

    void requestNonTakenServer(int os, int given_server);

    int requestTakenServer(int os, int given_server);

    void freeServer(int given_server);

    bool hasFreeServer(){ return (linux_servers.size + windows_servers.size);}

};

void DataCenter::requestServer(int os, int given_server, int *assigned_server) {
    if ((os > 1) || (os < 0)) return;
    if ((given_server >= size) || (given_server < 0)) return;
    if (!servers[given_server].is_taken) {
        DataCenter::requestNonTakenServer(os, given_server);
        *assigned_server = given_server;
    } else {
        *assigned_server = DataCenter::requestTakenServer(os, given_server);
    }
}

int DataCenter::requestTakenServer(int os, int given_server) {
    int inserted_id = -1;
    if (((os == 0) && linux_servers.tail)|| ((os == 1) && !windows_servers.tail)) {
        inserted_id = linux_servers.tail->m_data;
        linux_servers.deleteNode(linux_servers.tail);
    }
    if (((os == 1)&& windows_servers.tail) || ((os == 0) && !linux_servers.tail)) {
        inserted_id = windows_servers.tail->m_data;
        windows_servers.deleteNode(windows_servers.tail);
    }
    if ((os == 1) && !windows_servers.tail) {
        linux_size--;
        windows_size++;
    }
    if ((os == 0) && !linux_servers.tail) {
        linux_size++;
        windows_size--;
    }
    servers[inserted_id].is_taken = true;
    servers[inserted_id].system = os;
    servers[inserted_id].position = nullptr;
    return inserted_id;
}

void DataCenter::requestNonTakenServer(int os, int given_server) {
    if (!servers[given_server].system) {
        linux_servers.deleteNode(servers[given_server].position);
        if (servers[given_server].system != os) {
            linux_size--;
            windows_size++;
        }
    }
    if (servers[given_server].system) {
        windows_servers.deleteNode(servers[given_server].position);
        if (servers[given_server].system != os) {
            linux_size++;
            windows_size--;
        }
    }
    servers[given_server].system = os;
    servers[given_server].is_taken = true;
    servers[given_server].position = nullptr;
}

void DataCenter::freeServer(int given_server){
    if ((given_server < 0)||(given_server >= size)) return;
    if (!servers[given_server].is_taken) return;
    servers[given_server].is_taken = false;
    Node* temp = new Node(given_server);
    servers[given_server].position = temp;
    if (servers[given_server].system ==0) linux_servers.beginningInsert(temp);
    if (servers[given_server].system ==1) windows_servers.beginningInsert(temp);
    //printf("head is %d, tail is %d\n", windows_servers.head->m_data, windows_servers.tail->m_data);
}



#endif //UNTITLED_DATACENTER_H
