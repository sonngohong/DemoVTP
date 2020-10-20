#include "KeyHandle.h"
#include <windows.h>
#include "TmpLock.h"
#include <QDebug>

#define     SLEEP_TIME  500 // sleep time = 500 milliseconds

KeyHandle::KeyHandle()
    : m_action(NO_ACTION)
{

}

KeyHandle::~KeyHandle()
{
    if (m_thread.joinable())
    {
        m_thread.join();
    }
}

void KeyHandle::leftClick()
{
//    INPUT    Input={0};
//    // left up
//    Input.type      = INPUT_MOUSE;
//    Input.mi.dwFlags  = MOUSEEVENTF_LEFTUP;
//    ::SendInput(1,&Input,sizeof(INPUT));

//    // left down
//    ::ZeroMemory(&Input,sizeof(INPUT));
//    Input.type      = INPUT_MOUSE;
//    Input.mi.dwFlags  = MOUSEEVENTF_LEFTDOWN;
//    ::SendInput(1,&Input,sizeof(INPUT));
}

void KeyHandle::start()
{
    TmpLock lock;
    m_action = START;
    if (START != m_action && !m_thread.joinable())
    {
        m_thread = std::thread(&KeyHandle::workThread,this);
    }
}

void KeyHandle::pause()
{
    TmpLock lock;
    m_action = PAUSE;
}

void KeyHandle::stop()
{
    TmpLock lock;
    m_action = STOP;
}

void KeyHandle::workThread()
{
    while (true)
    {
        if (PAUSE == m_action)
        {
            Sleep(SLEEP_TIME);
            continue;
        }
        if (STOP == m_action)
        {
            break;
        }
//        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
//        {
//            leftClick();
//            qDebug() << "Clicked";
//        }
        Sleep(SLEEP_TIME);
    }
}
