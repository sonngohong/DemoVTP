#include "TmpLock.h"

TmpLock::TmpLock()
{
    m_mutex.lock();
}

TmpLock::~TmpLock()
{
    m_mutex.unlock();
}
