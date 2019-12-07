//
// Created by Akiva on 2019-11-29.
//

#ifndef DATACENTERSMANAGER_DATAMANAGEREXCEPTIONS_H
#define DATACENTERSMANAGER_DATAMANAGEREXCEPTIONS_H

#include <exception>

namespace DataManagerExceptions{
    class Exceptions : std::exception{};
    class ObjectUnfound : Exceptions{};
    class ObjectAlreadyExists : Exceptions{};
    class LinkedListExpired : Exceptions{};
}
#endif //DATACENTERSMANAGER_DATAMANAGEREXCEPTIONS_H
