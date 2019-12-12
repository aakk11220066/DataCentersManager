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

    //ctor
    AuxDataCenter()= default;

    //ctor with parameters
    AuxDataCenter(const DataCenter &dc, int os){
        id = dc.id;
        if (os == 0) (servers_num =dc.linux_size);
        if (os == 1) (servers_num=dc.windows_size);
    }

    //get class id data member
    int getID() const {return id;}

    //operator> operates reversely, mostly like operator<.
    //it operates in such manner such that the tree's Inorder would print the AuxDataCenters
    //according to the assignment's criteria (instead of implementing reversed Inorder function).
    bool operator> (const AuxDataCenter &aux_dc) const {
        if (servers_num < aux_dc.servers_num) return true;
        if (servers_num > aux_dc.servers_num) return false;
        if (servers_num == aux_dc.servers_num){
            return id > aux_dc.id;
        }
        return false;
    }

    //operator==
    bool operator==(const AuxDataCenter &aux_dc) const {
        return ((aux_dc.id == id))&&(aux_dc.servers_num == servers_num);
    }
};
#endif //UNTITLED_AUXDATACENTER_H
