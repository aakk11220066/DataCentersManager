//
// Created by Roy on 06/12/19.
//

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
    return (StatusType)((DataCenterManager *)DS)-> AddDataCenter(dataCenterID, numOfServers);
}

StatusType RemoveDataCenter(void *DS, int dataCenterID) {
    return (StatusType)(((DataCenterManager *) DS)->RemoveDataCenter(dataCenterID));
}

StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os, int *assignedID){
    return (StatusType)(((DataCenterManager *) DS)->RequestServer(dataCenterID, serverID, os, (int*) *assignedID));
}

StatusType FreeServer(void *DS, int dataCenterID, int serverID){
    return (StatusType)(((DataCenterManager *) DS)->FreeServer(dataCenterID, serverID));
}

StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters){
    return static_cast<StatusType>(((DataCenterManager *) DS)->GetDataCentersByOs(os, (int**) **dataCenters, (int*) *numOfDataCenters));
}

void Quit(void** DS){
    if (*DS == nullptr) return;
    delete (DataCenterManager *) DS;
    DS = nullptr;
}
