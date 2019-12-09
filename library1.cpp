//
// Created by Roy on 06/12/19.
//

//
// Created by Roy on 06/12/19.
//

#include"library1.h"
#include "DataCenterManager.h"

void *Init() {
    DataCenterManager *DS = new DataCenterManager ();
    return (void*)DS;
}

StatusType AddDataCenter(void *DS, int dataCenterID, int numOfServers) {
    if (numOfServers <= 0 || DS == NULL || dataCenterID <= 0) return INVALID_INPUT;
    return (StatusType)((DataCenterManager *)DS)-> AddDataCenter(dataCenterID, numOfServers);
}

StatusType RemoveDataCenter(void *DS, int dataCenterID) {
    if (DS == NULL || dataCenterID <= 0) return INVALID_INPUT;
    return (StatusType)(((DataCenterManager *) DS)->RemoveDataCenter(dataCenterID));
}

StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os, int *assignedID){
    if (assignedID == NULL || os > 1 || dataCenterID <= 0 || os < 0 || DS == NULL || serverID < 0) return INVALID_INPUT;
    return (StatusType) (((DataCenterManager *) DS)->RequestServer(dataCenterID, serverID, os, assignedID));
}

StatusType FreeServer(void *DS, int dataCenterID, int serverID){
    if (dataCenterID <= 0 || DS == NULL || serverID < 0) return INVALID_INPUT;
    return (StatusType)(((DataCenterManager *) DS)->FreeServer(dataCenterID, serverID));
}

StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters){
    if (dataCenters == NULL || DS == NULL || os < 0 || os > 1 || numOfDataCenters == NULL) return INVALID_INPUT;
    return static_cast<StatusType>(((DataCenterManager *) DS)->GetDataCentersByOs(os, dataCenters, numOfDataCenters));
}

void Quit(void** DS){
    if (*DS == nullptr) return;
    delete (DataCenterManager *) DS;
    *DS = nullptr;
}
