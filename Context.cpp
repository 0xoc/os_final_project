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
    if (_lastShare == 0)
        return _arrivalTime;
    return _lastShare;
}

int Context::getRemainingTime() const
{
    return _burstTime - _elapesdTime;
}

int Context::getLastShareStartTime() const
{
    return _lastShareStartTime;
}

int Context::getLastShareTimeQuantom() const
{
    return _lastShareTimeQuantom;
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

    _lastShareTimeQuantom = timeQ;
    _lastShareStartTime = systemTime;
}
