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
    AuxDataCenter()= default;
    //added line 16 to solve not enough parameters provided for the constructor
    AuxDataCenter(const DataCenter &dc, int os){
        id = dc.id;
        if (os == 0) (servers_num =dc.linux_size);
        if (os == 1) (servers_num=dc.windows_size);
    }
    int getID() const {return id;}
    int getServersNum() const {return servers_num;}
    bool operator> (const AuxDataCenter &aux_dc) const {
        if (servers_num < aux_dc.servers_num) return true;
        if (servers_num > aux_dc.servers_num) return false;
        if (servers_num == aux_dc.servers_num){
            return id > aux_dc.id;
        }
        return false;
        //line 27 added to avoid clion message
    }
    bool operator==(const AuxDataCenter &aux_dc) const {
        return ((aux_dc.id == id))&&(aux_dc.servers_num == servers_num);
    }
};
#endif //UNTITLED_AUXDATACENTER_H
