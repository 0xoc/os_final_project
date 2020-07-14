#include "Context.h"

int Context::getPid()
{
    return 0;
}

int Context::getArrivalTime()
{
    return _arrivalTime;
}

int Context::getBurstTime()
{
    return _burstTime;
}

void Context::setPid(int pid)
{
    _pid = pid;
}

void Context::setArrivalTile(int arrivalTime)
{
    _arrivalTime = arrivalTime;
}

void Context::setBurstTime(int burstTime)
{
    _burstTime = burstTime;
}
