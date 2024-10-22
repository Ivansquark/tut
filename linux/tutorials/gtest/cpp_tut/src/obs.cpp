#include "obs.h"

void (*SubManager::fptr[10])() = {nullptr};
void (*SubManVirt::fPtr[10])() = {nullptr};
ObjVirt* ObsVirt::virtClasses[2] = {nullptr};
