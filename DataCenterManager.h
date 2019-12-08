//
// Created by Roy on 05/12/19.
//

#ifndef DATACENTERSMANAGER_DATACENTERMANAGER_H
#define DATACENTERSMANAGER_DATACENTERMANAGER_H

#include "Data Structures/AVLTree/AVLTree.h"
#include "DataCenter.h"
#include "AuxDataCenter.h"

class DataCenterManager{
private:
    AVLTree<DataCenter> data_centers_tree;
    AVLTree<AuxDataCenter> linux_tree;
    AVLTree<AuxDataCenter> windows_tree;
public:
    enum DataCenterManagerError{SUCCESS = 0, ERROR = -1};
    DataCenterManager() = default;
    ~DataCenterManager() = default;
    DataCenterManagerError AddDataCenter(int DataCenterId, int numOfServers){
        if ((DataCenterId <= 0) || (numOfServers <=0)) return ERROR;
        try {
            DataCenter dc_temp(DataCenterId, numOfServers);
            data_centers_tree.insert(dc_temp);
            AuxDataCenter aux_dc_temp(dc_temp, 0);
            linux_tree.insert(aux_dc_temp);
            return SUCCESS;
        }
        catch (DataManagerExceptions::Exceptions& e)
        {
            return ERROR;
        }
    }
    DataCenterManagerError RemoveDataCenter(int DataCenterId){
        if (DataCenterId <=0) return ERROR;
        try{
            DataCenter dc_temp(DataCenterId);
            DataCenter dc_to_delete = data_centers_tree.find(dc_temp);
            if (!dc_to_delete.linux_size) {
                AuxDataCenter linux_dc_temp(dc_to_delete, 0);
                linux_tree.remove(linux_dc_temp);
            }
            if (!dc_to_delete.windows_size) {
                AuxDataCenter windows_dc_temp(dc_to_delete, 1);
                windows_tree.remove(windows_dc_temp);
            }
            data_centers_tree.remove(dc_temp);
            return SUCCESS;
        }
        catch(DataManagerExceptions::Exceptions& e){
            return ERROR;
        }
    }

    DataCenterManagerError RequestServer(int DataCenterID, int ServerID, int os, int *assignedID){
        try {
            DataCenter dc_temp(DataCenterID);
            DataCenter& dc_to_alter = data_centers_tree.find(dc_temp);
            //DataCenter dc_before_change = dc_to_alter;
            if (dc_to_alter.requestServer(os, ServerID, assignedID) != 0) return ERROR;
            printf("hjghjgh\n");
            //UpdateTrees(dc_before_change, dc_to_alter);
            return SUCCESS;
        }
        catch(DataManagerExceptions::Exceptions& e){
            return ERROR;
        }
    }

    DataCenterManagerError FreeServer(int DataCenterID, int ServerID){
        try{
            DataCenter dc_temp(DataCenterID);
            DataCenter dc_to_alter = data_centers_tree.find(dc_temp);
            if (!dc_to_alter.freeServer(ServerID)) return ERROR;
            DataCenter dc_before_change = dc_to_alter;
            UpdateTrees(dc_before_change, dc_to_alter);
            return SUCCESS;

        }
        catch(DataManagerExceptions::Exceptions& e){
            return ERROR;
        }
    }

    void UpdateTrees(const DataCenter& dc_to_delete, const DataCenter& dc_to_add){
        AuxDataCenter linux_dc_to_delete(dc_to_delete, 0);
        if (dc_to_delete.linux_size) linux_tree.remove(linux_dc_to_delete);
        if (dc_to_add.linux_size){
            AuxDataCenter linux_dc_to_add(dc_to_add, 0);
            linux_tree.insert(linux_dc_to_add);
        }
        AuxDataCenter windows_dc_to_delete(dc_to_delete, 1);
        if (dc_to_delete.windows_size) windows_tree.remove(windows_dc_to_delete);
        if (dc_to_add.windows_size){
            AuxDataCenter windows_dc_to_add(dc_to_add, 0);
            windows_tree.insert(windows_dc_to_add);
        }
    }

    DataCenterManagerError GetDataCentersByOs(int os, int **dataCenters, int *numOfDataCenters) const {
        try {
            if ((os < 0) || (os > 1)) return ERROR;
            if ((dataCenters == nullptr) || (numOfDataCenters == nullptr)) return ERROR;
            if (!os) {
                Array<AuxDataCenter> list0 = linux_tree.getInOrder();
                if (!list0.getSize()) return ERROR;
                int size0 = (int) list0.getSize();
                *dataCenters = (int*)malloc(sizeof(int)*size0);
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
        catch(DataManagerExceptions::Exceptions& e){
            return ERROR;
        }
    }

};


#endif //DATACENTERSMANAGER_DATACENTERMANAGER_H
