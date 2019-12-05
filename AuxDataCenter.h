//
// Created by Roy on 01/12/19.
//

#ifndef UNTITLED_AUXDATACENTER_H
#define UNTITLED_AUXDATACENTER_H

#include "DataCenter.h"

class AuxDataCenter{
private:
    int id;
    int servers_num;

public:
    explicit AuxDataCenter(const DataCenter &dc, int os){
        id = dc.id;
        if (os == 0) (servers_num =dc.linux_size);
        if (os == 1) (servers_num=dc.windows_size);
    }
    int getID() {return id;}
    bool operator> (const AuxDataCenter &aux_dc){
        if (servers_num < aux_dc.servers_num) return true;
        if (servers_num >= aux_dc.servers_num) return false;
        if (servers_num == aux_dc.servers_num){
            return id < aux_dc.id;
        }
        return true;
        //line 27 added to avoid clion message
    }
    bool operator==(const AuxDataCenter &aux_dc){
        return ((aux_dc.id == id))&&(aux_dc.servers_num == servers_num);
    }
};
#endif //UNTITLED_AUXDATACENTER_H
