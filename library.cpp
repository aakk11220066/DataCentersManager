//
// Created by Roy on 06/12/19.
//

#include"library.h"
#include "DataCenterManager.h"
void *Init() {
    DataCenterManager *DS = new DataCenterManager ();
    return (void*)DS;
}
StatusType AddDataCenter(void *DS, int dataCenterID, int numOfServers) {
    return static_cast<StatusType>(((DataCenterManager *) DS)->AddDataCenter(dataCenterID, numOfServers));
}

StatusType RemoveDataCenter(void *DS, int dataCenterID) {
    return static_cast<StatusType>(((DataCenterManager *) DS)->RemoveDataCenter(dataCenterID));
}

StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os, int *assignedID){
    return static_cast<StatusType>(((DataCenterManager *) DS)->RequestServer(dataCenterID, serverID, assignedID));
}

StatusType FreeServer(void *DS, int dataCenterID, int serverID){
    return static_cast<StatusType>(((DataCenterManager *) DS)->FreeServer(dataCenterID, serverID));
}

StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters){
    return static_cast<StatusType>(((DataCenterManager *) DS)->GetDataCentersByOs(os, (int**) **dataCenters, (int*) *numOfDataCenters));
}

void Quit(void** DS){
    if (*DS == nullptr) return;
    delete (DataCenterManager *) DS;
    DS = nullptr;
}