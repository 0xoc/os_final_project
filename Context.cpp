#include "Context.h"

int Context::getPid() const
{
    return _pid;
}

int Context::getArrivalTime() const
{
    return _arrivalTime;
}

int Context::getBurstTime() const
{
    return _burstTime;
}

int Context::getElapsedTime() const
{
    return _elapesdTime;
}

int Context::getLastShare() const
{
    return _lastShare;
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

void Context::run(int timeQ, int systemTime)
{
    _elapesdTime += timeQ;
    _lastShare = timeQ + systemTime;
}
