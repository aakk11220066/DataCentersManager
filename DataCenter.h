//
// Created by Roy on 28/11/19.
//

#ifndef UNTITLED_DATACENTER_H
#define UNTITLED_DATACENTER_H

#include <iostream>
#include "linkedList.h"
#include "Data Structures/Array.h"

class ServerDetails {
private:
    int system;
    bool is_taken;
    Node *position;

public:
    explicit ServerDetails(Node *p = nullptr) : position(p) {
        system = 0;
        is_taken = false;
    }
    int getSystem()const {return system;}
    bool getIsTaken()const {return is_taken;}
    Node* getPosition()const{return position;}
    void setSystem(int given_system){
        system=given_system;

    }
    void setIsTaken(bool given_is_taken){is_taken=given_is_taken;}
    void setPosition(Node *p) { position = p; }
};

class DataCenter {
public:
    int id;
    int size;
    int linux_size;
    int windows_size;
    DoubleLinkedList linux_servers;
    DoubleLinkedList windows_servers;
    Array<ServerDetails> servers;
    enum DataCenterError{SUCCESS = 0, FAILURE = -1, ALLOCATION_ERROR = -2, INVALID_INPUT = -3};

    //copy ctor
    DataCenter(const DataCenter &original) = default;

    //operator=
    DataCenter &operator=(const DataCenter &original) = default;

    virtual ~DataCenter() = default;

    /**
     * constructor
     * initializes a double linked list with a given size of elements.
     * initializes an array of the same size
     * @param given_id
     * @param servers_num
     */
    explicit DataCenter(int given_id, int servers_num = 0) : id(given_id), size(servers_num), linux_size(servers_num),
                                                windows_size(0), servers(Array<ServerDetails>(size)) {
        for (int i = 0; i < size; i++) {
            Node *temp = new Node(i);
            linux_servers.beginningInsert(temp);
            servers[i].setPosition(temp);
            servers[i].setSystem(0);
            //printf("system is %d\n", servers[i].getSystem());
        }
    }

    void printPosition() {
        for (int i = 0; i < size; i++) {
            std::cout << servers[i].getPosition() << "," << servers[i].getSystem() << ", " << servers[i].getIsTaken() << ", \n";
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

    /**
     * operator==
     * opeator>
     * @param dc
     * @return
     */
    bool operator==(const DataCenter &dc) const{return (id==dc.id); }
    bool operator>(const DataCenter &dc)const {return (id > dc.id); }

    /**
     * marking an untaken server as taken and returning its number.
     * in case the given server is taken, call requestTakenServer, else call requestNonTakenServer.
     *
     * @param os
     * @param given_server
     * @param assigned_server
     * @return
     */
    DataCenterError requestServer(int os, int given_server, int *assigned_server);


    void requestNonTakenServer(int os, int given_server);

    int requestTakenServer(int os);

    /**
     *
     * @param given_server
     * @return
     */
    DataCenterError freeServer(int given_server);

    bool hasFreeServer(){ return (linux_servers.getSize() + windows_servers.getSize());}

};

DataCenter::DataCenterError DataCenter::requestServer(int os, int given_server, int *assigned_server) {
    printf("system is %d, taken is %d\n",servers[given_server].getSystem(), int(servers[given_server].getIsTaken()));
    int flag = 0;
    if (!hasFreeServer()) return FAILURE;
    if (assigned_server == nullptr) return FAILURE;
    if ((os > 1) || (os < 0)) return INVALID_INPUT;
    if ((given_server >= size) || (given_server < 0)) return INVALID_INPUT;
    printf("system is %d, taken is %d\n",servers[given_server].getSystem(), int(servers[given_server].getIsTaken()));
    if (!servers[given_server].getIsTaken()) {
        DataCenter::requestNonTakenServer(os, given_server);
        *assigned_server = given_server;
        flag = 1;
    }
    if (flag == 0)
    {
        *assigned_server = DataCenter::requestTakenServer(os);
    }
    return SUCCESS;
}

int DataCenter::requestTakenServer(int os) {
    int inserted_id = -1, flag =0;
    if (((os == 0) && linux_servers.getSize())|| ((os == 1) && !windows_servers.getSize())) {
        //printf("size = %d, tail = %d, end\n", linux_servers.getSize(), linux_servers.getTail());
        inserted_id = linux_servers.getTail()->getData();
        linux_servers.deleteNode(linux_servers.getTail());
        //printf("size = %d, tail = %d, end\n", linux_servers.getSize(), linux_servers.getTail());
        flag = 1;
    }
    if (((os == 1)&& windows_servers.getSize()) || (((os == 0) && !linux_servers.getSize()) && (flag == 0))) {
        inserted_id = windows_servers.getTail()->getData();
        windows_servers.deleteNode(windows_servers.getTail());
    }
    if (linux_size!= size && windows_size!= size) {
        if ((os == 1) && !windows_servers.getTail()) {
            linux_size--;
            windows_size++;
        }
        if ((os == 0) && !linux_servers.getTail()) {
            linux_size++;
            windows_size--;
        }
    }
    servers[inserted_id].setIsTaken(true);
    servers[inserted_id].setSystem(os);
    servers[inserted_id].setPosition(nullptr);
    return inserted_id;
}

void DataCenter::requestNonTakenServer(int os, int given_server) {
    if (!servers[given_server].getSystem()) {
        linux_servers.deleteNode(servers[given_server].getPosition());
        if (servers[given_server].getSystem() != os) {
            linux_size--;
            windows_size++;
        }
    }
    if (servers[given_server].getSystem()) {
        windows_servers.deleteNode(servers[given_server].getPosition());
        if (servers[given_server].getSystem() != os) {
            linux_size++;
            windows_size--;
        }
    }
    servers[given_server].setSystem(os);
    servers[given_server].setIsTaken(true);
    servers[given_server].setPosition(nullptr);
}

DataCenter::DataCenterError DataCenter::freeServer(int given_server){
    if ((given_server < 0)||(given_server >= size)) return INVALID_INPUT;
    if (!servers[given_server].getIsTaken()) return FAILURE;
    servers[given_server].setIsTaken(false);
    Node* temp = new Node(given_server);
    servers[given_server].setPosition(temp);
    if (servers[given_server].getSystem() ==0) linux_servers.beginningInsert(temp);
    if (servers[given_server].getSystem() ==1) windows_servers.beginningInsert(temp);
    //printf("head is %d, tail is %d\n", windows_servers.head->m_data, windows_servers.tail->m_data);
    return SUCCESS;
    }





#endif //UNTITLED_DATACENTER_H
