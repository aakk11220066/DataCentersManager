//
// Created by Akiva on 2019-11-29.
//

#ifndef DATACENTERSMANAGER_DATAMANAGEREXCEPTIONS_H
#define DATACENTERSMANAGER_DATAMANAGEREXCEPTIONS_H

#include <exception>

/**
 * Exceptions class for DataCenterManager
 */
namespace DataManagerExceptions{
    class Exceptions : public std::exception {
    };

    class ObjectUnfound : public Exceptions {
    };

    class ObjectAlreadyExists : public Exceptions {
    };

    class LinkedListExpired : public Exceptions {
    };
}
#endif //DATACENTERSMANAGER_DATAMANAGEREXCEPTIONS_H
