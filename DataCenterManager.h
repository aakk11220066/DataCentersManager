//
// Created by Roy on 05/12/19.
//

#ifndef DATACENTERSMANAGER_DATACENTERMANAGER_H
#define DATACENTERSMANAGER_DATACENTERMANAGER_H

#include "Data Structures/AVLTree/AVLTree.h"
#include "DataCenter.h"
#include "AuxDataCenter.h"

class DataCenterManager {
private:
    AVLTree<DataCenter> data_centers_tree;
    AVLTree<AuxDataCenter> linux_tree;
    AVLTree<AuxDataCenter> windows_tree;
public:
    enum DataCenterManagerError {
        SUCCESS = 0, ERROR = -1, ALLOCATION_ERROR = -2, INVALID_INPUT = -3
    };

    DataCenterManager() = default;

    ~DataCenterManager() = default;

    DataCenterManagerError AddDataCenter(int DataCenterId, int numOfServers) {
        if ((DataCenterId <= 0) || (numOfServers <= 0)) return ERROR;
        try {
            DataCenter dc_temp(DataCenterId, numOfServers);
            data_centers_tree.insert(dc_temp);
            AuxDataCenter linux_aux_dc_temp(dc_temp, 0);
            linux_tree.insert(linux_aux_dc_temp);
            AuxDataCenter windows_aux_dc_temp(dc_temp, 1);
            windows_tree.insert(windows_aux_dc_temp);
            return SUCCESS;
        }
        catch (DataManagerExceptions::Exceptions &e) {
            return ERROR;
        }
    }

    DataCenterManagerError RemoveDataCenter(int DataCenterId) {
        if (DataCenterId <= 0) return ERROR;
        try {
            DataCenter dc_temp(DataCenterId);
            DataCenter &dc_to_delete = data_centers_tree.find(dc_temp);
            //if (dc_to_delete.linux_size) {
                AuxDataCenter linux_dc_temp(dc_to_delete, 0);
                linux_tree.remove(linux_dc_temp);
            //}
            //if (dc_to_delete.windows_size) {
                AuxDataCenter windows_dc_temp(dc_to_delete, 1);
                windows_tree.remove(windows_dc_temp);
            //}
            data_centers_tree.remove(dc_temp);
            return SUCCESS;
        }
        catch (DataManagerExceptions::Exceptions &e) {
            return ERROR;
        }
    }

    DataCenterManagerError RequestServer(int DataCenterID, int ServerID, int os, int *assignedID) {
        try {
            DataCenter dc_temp(DataCenterID);
            DataCenter &dc_to_alter = data_centers_tree.find(dc_temp);
            if (ServerID >= dc_to_alter.size) return INVALID_INPUT;
            AuxDataCenter linux_dc_before_change(dc_to_alter, 0);
            AuxDataCenter windows_dc_before_change(dc_to_alter, 1);
            int size = dc_to_alter.size;
            //for (int i = 0; i < size; i++) {
              //  printf("so sysyem is %d\n", (int)(dc_to_alter.servers[i].getSystem()));
            //}
            if (dc_to_alter.requestServer(os, ServerID, assignedID) != 0) return ERROR;
            AuxDataCenter linux_dc_after_change(dc_to_alter, 0);
            AuxDataCenter windows_dc_after_change(dc_to_alter, 1);
            UpdateTrees(linux_dc_before_change, windows_dc_before_change, linux_dc_after_change,
                        windows_dc_after_change, dc_to_alter.linux_size, dc_to_alter.windows_size);
            return SUCCESS;
        }
        catch (DataManagerExceptions::Exceptions &e) {
            return ERROR;
        }
    }

    DataCenterManagerError FreeServer(int DataCenterID, int ServerID) {
        try {
            DataCenter dc_temp(DataCenterID);
            DataCenter &dc_to_alter = data_centers_tree.find(dc_temp);
            if (ServerID >= dc_to_alter.size) return INVALID_INPUT;
            AuxDataCenter linux_dc_before_change(dc_to_alter, 0);
            AuxDataCenter windows_dc_before_change(dc_to_alter, 1);
            if (dc_to_alter.freeServer(ServerID)) return ERROR;
            AuxDataCenter linux_dc_after_change(dc_to_alter, 0);
            AuxDataCenter windows_dc_after_change(dc_to_alter, 1);
            UpdateTrees(linux_dc_before_change, windows_dc_before_change, linux_dc_after_change,
                        windows_dc_after_change, dc_to_alter.linux_size, dc_to_alter.windows_size);
            return SUCCESS;
//
        }
        catch (DataManagerExceptions::Exceptions &e) {
            return ERROR;
        }
    }

    void UpdateTrees(const AuxDataCenter &linux_dc_to_delete, const AuxDataCenter &windows_dc_to_delete,
                     const AuxDataCenter &linux_dc_to_add, const AuxDataCenter &windows_dc_to_add, int linux_size, int windows_size) {
        /*
        if (linux_dc_to_add.getServersNum()) linux_tree.remove(linux_dc_to_delete);
        if (linux_size) {
            linux_tree.insert(linux_dc_to_add);
        }

        if (windows_dc_to_add.getServersNum()) {
            windows_tree.remove(windows_dc_to_delete);
        }
        if (windows_size) {
            windows_tree.insert(windows_dc_to_add);
        }
         */
        linux_tree.remove(linux_dc_to_delete);
        linux_tree.insert(linux_dc_to_add);
        windows_tree.remove(windows_dc_to_delete);
        windows_tree.insert(windows_dc_to_add);

    }

    DataCenterManagerError GetDataCentersByOs(int os, int **dataCenters, int *numOfDataCenters) const {
        try {
            if ((os < 0) || (os > 1)) return ERROR;
            if ((dataCenters == nullptr) || (numOfDataCenters == nullptr)) return ERROR;
            if (!os) {
                Array<AuxDataCenter> list0 = linux_tree.getInOrder();
                if (!list0.getSize()) return ERROR;
                int size0 = (int) list0.getSize();
                *dataCenters = (int *) malloc(sizeof(int) * size0);
                //printf("size is %d\n", size0* sizeof(int));
                //printf("size0 is %d\n", size0);
                for (int i = 0; i < size0; i++) {
                    (*dataCenters)[i] = list0[i].getID();
                }
                *numOfDataCenters = size0;
            }
            if (os) {
                Array<AuxDataCenter> list1 = windows_tree.getInOrder();
                if (!list1.getSize()) return ERROR;
                int size1 = (int) list1.getSize();
                *dataCenters = (int *) malloc(sizeof(int *) * size1);
                for (int i = 0; i < size1; i++) {
                    (*dataCenters)[i] = list1[i].getID();
                }
                *numOfDataCenters = size1;
            }
            return SUCCESS;
        }
        catch (DataManagerExceptions::Exceptions &e) {
            return ERROR;
        }
    }

};


#endif //DATACENTERSMANAGER_DATACENTERMANAGER_H
