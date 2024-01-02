
/*
* 自己添加Sever.cpp写函数实现，#include "Sever.h"
* 提醒：写完两个函数也不一定能成功运行，可能还有以下问题：
* 房间加入界面设计，服务器连接，延迟，战斗计算，玩家掉线判定和处理
* 玩家游戏退出重试处理
* 如果出现了这些问题，请你自己解决！
*/

#ifndef __SEVERMSG_H__
#define __SEVERMSG_H__

/* 在此处添加需要的头文件 */
#include "cocos2d.h"

class Sever : public cocos2d::Node
{
    /*
    * 参数：op - 操作类型，1为放置角色，2为移除角色
    *           玩家连接成功时应返回一个op为0信息（其他参数不用管）
    *       id - 要放置的角色id，如果op=1则忽略该参数的值
    *       row, col - 要放置或移除角色的行和列
    *                  ！！！注意发送或接收中其中一个环节要做对称操作
    *                  SendMsg中的参数是按照发送方的坐标，即0-2行
    *                  列可以不取对称，但行一定要取对称
    * init：该函数只调用一次，在里面添加所有初始化服务器的代码，初始化成功返回true
    * SendMsg：确保调用一次就能成功发送信息
    * GetMsg：这个函数会一直调用，如果对方发送了一个有效信息则返回true，否则返回false
    * connect：连接上了返回true，当未连接上时会重复调用
    */

public:
    virtual bool init();
    bool connect();
    void SendMsg(int op, int id, int row, int col);
    bool GetMsg(int& op, int& id, int& row, int& col);

    CREATE_FUNC(Sever) // 这行不用管
};

#endif // !__SEVERMSG_H__