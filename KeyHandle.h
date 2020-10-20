#ifndef KEYHANDLE_H
#define KEYHANDLE_H

#include <thread>

using namespace std;

enum ACTION_STATE
{
    NO_ACTION = -1,
    START = 1,
    PAUSE = 2,
    STOP = 3,
};

class KeyHandle
{
private:
    ACTION_STATE    m_action;
    thread          m_thread;
    void          workThread();

public:
    KeyHandle();
    ~KeyHandle();
    void leftClick();
    void start();
    void pause();
    void stop();
};

#endif // KEYHANDLE_H
