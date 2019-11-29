//
// Created by User on 2019-11-29.
//

#ifndef DATACENTERSMANAGER_DATAMANAGEREXCEPTIONS_H
#define DATACENTERSMANAGER_DATAMANAGEREXCEPTIONS_H

#include <exception>

namespace DataManagerExceptions{
    class Exceptions : std::exception{};
    class ObjectUnfound : Exceptions{};
    class ObjectAlreadyExists : Exceptions{};
}
#endif //DATACENTERSMANAGER_DATAMANAGEREXCEPTIONS_H
