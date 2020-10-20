#ifndef TMPLOCK_H
#define TMPLOCK_H
#include <mutex>

class TmpLock
{
    std::mutex  m_mutex;
public:
    explicit TmpLock();
    virtual ~TmpLock();
};

#endif // TMPLOCK_H
