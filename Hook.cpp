
#include "hook.h"
#include <QDebug>

static HHOOK keyHook = nullptr;//钩子对象
static HHOOK mouseHook = nullptr;//钩子对象

static Hook* hook;//Qt界面中调用Hook类的对象
LRESULT CALLBACK keyProc(int nCode, WPARAM wParam, LPARAM lParam) {//钩子消息函数，系统消息队列信息会返回到该函数中
    tagMSLLHOOKSTRUCT* pkbhs = (tagMSLLHOOKSTRUCT*)lParam;//lParam用于判断按键类型
   // qDebug() << "wParamwParamwParamwParamwParamwParamwParamwParamwParam%d", wParam;
   // qDebug("\wParamwParamwParamwParamwParamwParamwParamwParamwParam [%d] \n", wParam);
    if (wParam == WM_MBUTTONDOWN) {//wParam用于判断事件类型，当前为按键按下事件
    //if(TRUE){
       // pkbhs-
       // if (GetAsyncKeyState(VK_MBUTTON)) {//按下Ctrl+1
       //     hook->sendSignal(Hook::CHANGE);//安装钩子的对象发出按键监听信号
       //}
       //if ( GetAsyncKeyState(VK_MBUTTON) & 0x8000 ) {//按下Ctrl+2
       //     hook->sendSignal(Hook::CHANGE);
       // }
       // if (pkbhs->vkCode == 0x04 && GetAsyncKeyState(VK_MBUTTON)) {//按下Ctrl+2
       //    hook->sendSignal(Hook::CHANGE);
       //}
       // if (GetAsyncKeyState(VK_MBUTTON)) {//按下Ctrl+2
          hook->sendSignal(Hook::CHANGE);
      //  }
       // if (pkbhs->vkCode == 0x04) {//按下Ctrl+2
       //     hook->sendSignal(Hook::CHANGE);
       // }
    }
    return CallNextHookEx(keyHook, nCode, wParam, lParam);//继续原有的事件队列
}

//LRESULT CALLBACK Mouseproc(int nCode, WPARAM wParam, LPARAM lParam)
//{
//
//    if (wParam == WM_MBUTTONDOWN)//中 右键
//    {
//        hook->sendSignal(Hook::CHANGE);
//
//      
//
//    }
//    return CallNextHookEx(mouseHook, nCode, wParam, lParam);
//}

Hook::Hook()
{

}

void Hook::installHook(Hook* h) {//安装钩子函数
    keyHook = SetWindowsHookEx(WH_MOUSE_LL, keyProc, nullptr, 0);
    hook = h;
}
void Hook::unInstallHook() {//删除钩子函数
    UnhookWindowsHookEx(keyHook);
    keyHook = nullptr;
}

void Hook::sendSignal(Type type) {//发送信号函数
    emit sendKeyType(type);
}
