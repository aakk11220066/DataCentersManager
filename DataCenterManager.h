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

    //ctor
    DataCenterManager() = default;

    //dtor
    ~DataCenterManager() = default;

    /**
     * In case the conditions are met:
     * First, the function creates a temporary datCenter and add it to dataCenters tree.
     * Then, the function updates both AuxDataCenters trees based on DataCenter's values.
     *
     * @param DataCenterId
     * @param numOfServers
     * @return
     */
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

    /**
     * In case the conditions are met, the function does the following:
     * First it creates a dummy dataCenter with correct ID in O(1).
     * Secondly, the tree finds the DataCenter with matched ID.
     * Thirdly, the found DataCenter is removed from all 3 trees.
     * @param DataCenterId
     * @return
     */
    DataCenterManagerError RemoveDataCenter(int DataCenterId) {
        if (DataCenterId <= 0) return ERROR;
        try {
            DataCenter dc_temp(DataCenterId);
            DataCenter &dc_to_delete = data_centers_tree.find(dc_temp);
            AuxDataCenter linux_dc_temp(dc_to_delete, 0);
            linux_tree.remove(linux_dc_temp);
            AuxDataCenter windows_dc_temp(dc_to_delete, 1);
            windows_tree.remove(windows_dc_temp);
            data_centers_tree.remove(dc_temp);
            return SUCCESS;
        }
        catch (DataManagerExceptions::Exceptions &e) {
            return ERROR;
        }
    }

    /**
     * if conditions for the functions are met, it operates as the following:
     * First, AuxDataCenters are created for both OS. These store the pre-changed DataCenter values.
     * Secondly, RequestServer operates according to assignment's criteria (DataCenter.h
     * covers its functionality more thoroughly).
     * Thirdly, function creates 2 AuxDataCenters with post-changed DataCenter values and
     * at last updates the 2 AuxDataCenters avl trees accordingly (using UpdateTrees function).
     * @param DataCenterID
     * @param ServerID
     * @param os
     * @param assignedID
     * @return
     */
    DataCenterManagerError RequestServer(int DataCenterID, int ServerID, int os, int *assignedID) {
        try {
            DataCenter dc_temp(DataCenterID);
            DataCenter &dc_to_alter = data_centers_tree.find(dc_temp);
            if (ServerID >= dc_to_alter.size) return INVALID_INPUT;
            AuxDataCenter linux_dc_before_change(dc_to_alter, 0);
            AuxDataCenter windows_dc_before_change(dc_to_alter, 1);
            auto res = (DataCenterManagerError) dc_to_alter.requestServer(os, ServerID, assignedID);
            if (res != 0) return res;
            AuxDataCenter linux_dc_after_change(dc_to_alter, 0);
            AuxDataCenter windows_dc_after_change(dc_to_alter, 1);
            UpdateTrees(linux_dc_before_change, windows_dc_before_change, linux_dc_after_change,
                        windows_dc_after_change);
            return SUCCESS;
        }
        catch (DataManagerExceptions::Exceptions &e) {
            return ERROR;
        }
    }

/**
     * if conditions for the functions are met, it operates as the following:
     * First, AuxDataCenters are created for both OS. These store the pre-changed DataCenter values.
     * Secondly, FreeServer operates according to assignment's criteria (DataCenter.h
     * covers its functionality more thoroughly).
     * Thirdly, function creates 2 AuxDataCenters with post-changed DataCenter values and
     * at last updates the 2 AuxDataCenters avl trees accordingly (using UpdateTrees function).
     * @param DataCenterID
     * @param ServerID
     * @param os
     * @param assignedID
     * @return
     */
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
                        windows_dc_after_change);
            return SUCCESS;
        }
        catch (DataManagerExceptions::Exceptions &e) {
            return ERROR;
        }
    }

    /**
     * function removes AuxDataCenter from a tree and then enter a new one, done for each tree respectively.
     * @param linux_dc_to_delete
     * @param windows_dc_to_delete
     * @param linux_dc_to_add
     * @param windows_dc_to_add
     */
    void UpdateTrees(const AuxDataCenter &linux_dc_to_delete, const AuxDataCenter &windows_dc_to_delete,
                     const AuxDataCenter &linux_dc_to_add, const AuxDataCenter &windows_dc_to_add){
        linux_tree.remove(linux_dc_to_delete);
        linux_tree.insert(linux_dc_to_add);
        windows_tree.remove(windows_dc_to_delete);
        windows_tree.insert(windows_dc_to_add);

    }

    /**
     * In case conditions are met, the function operates as follows:
     * it creates an array with the DataCenterIDs (of the given OS) in the correct order.
     * @param os
     * @param dataCenters
     * @param numOfDataCenters
     * @return
     */
    DataCenterManagerError GetDataCentersByOs(int os, int **dataCenters, int *numOfDataCenters) const {
        try {
            if ((os < 0) || (os > 1)) return ERROR;
            if ((dataCenters == nullptr) || (numOfDataCenters == nullptr)) return ERROR;
            if (!os) {
                Array<AuxDataCenter> list0 = linux_tree.getInOrder();
                if (!list0.getSize()) return ERROR;
                int size0 = (int) list0.getSize();
                *dataCenters = (int *) malloc(sizeof(int) * size0);
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
