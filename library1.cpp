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
    try {
        if (numOfServers <= 0 || DS == NULL || dataCenterID <= 0) return INVALID_INPUT;
        return (StatusType) ((DataCenterManager *) DS)->AddDataCenter(dataCenterID, numOfServers);
    }

    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
}

StatusType RemoveDataCenter(void *DS, int dataCenterID) {
    try {
        if (DS == NULL || dataCenterID <= 0) return INVALID_INPUT;
        return (StatusType) (((DataCenterManager *) DS)->RemoveDataCenter(dataCenterID));
    }

    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
}

StatusType RequestServer(void *DS, int dataCenterID, int serverID, int os, int *assignedID){
    try {
        if (assignedID == NULL || os > 1 || dataCenterID <= 0 || os < 0 || DS == NULL || serverID < 0)
            return INVALID_INPUT;
        return (StatusType) (((DataCenterManager *) DS)->RequestServer(dataCenterID, serverID, os, assignedID));
    }

    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
}

StatusType FreeServer(void *DS, int dataCenterID, int serverID){
    try {
        if (dataCenterID <= 0 || DS == NULL || serverID < 0) return INVALID_INPUT;
        return (StatusType) (((DataCenterManager *) DS)->FreeServer(dataCenterID, serverID));
    }

    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
}

StatusType GetDataCentersByOS(void *DS, int os, int **dataCenters, int* numOfDataCenters){
    try {
        if (dataCenters == NULL || DS == NULL || os < 0 || os > 1 || numOfDataCenters == NULL) return INVALID_INPUT;
        return static_cast<StatusType>(((DataCenterManager *) DS)->GetDataCentersByOs(os, dataCenters,
                                                                                      numOfDataCenters));
    }

    catch(const std::bad_alloc& ba){
        return ALLOCATION_ERROR;
    }
}

void Quit(void** DS){
    if (*DS == nullptr) return;
    delete (DataCenterManager *) DS;
    *DS = nullptr;
}
