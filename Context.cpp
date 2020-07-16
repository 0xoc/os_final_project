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

bool Context::started(int systemTime) const
{
    return systemTime >= _arrivalTime;
}

bool Context::ended() const
{
    return _elapesdTime >= _burstTime;
}

bool Context::isActive(int systemTime) const
{
    return started(systemTime) && !ended();
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
