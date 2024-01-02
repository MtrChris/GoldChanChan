
/*
* �Լ����Sever.cppд����ʵ�֣�#include "Sever.h"
* ���ѣ�д����������Ҳ��һ���ܳɹ����У����ܻ����������⣺
* ������������ƣ����������ӣ��ӳ٣�ս�����㣬��ҵ����ж��ʹ���
* �����Ϸ�˳����Դ���
* �����������Щ���⣬�����Լ������
*/

#ifndef __SEVERMSG_H__
#define __SEVERMSG_H__

/* �ڴ˴������Ҫ��ͷ�ļ� */
#include "cocos2d.h"

class Sever : public cocos2d::Node
{
    /*
    * ������op - �������ͣ�1Ϊ���ý�ɫ��2Ϊ�Ƴ���ɫ
    *           ������ӳɹ�ʱӦ����һ��opΪ0��Ϣ�������������ùܣ�
    *       id - Ҫ���õĽ�ɫid�����op=1����Ըò�����ֵ
    *       row, col - Ҫ���û��Ƴ���ɫ���к���
    *                  ������ע�ⷢ�ͻ����������һ������Ҫ���ԳƲ���
    *                  SendMsg�еĲ����ǰ��շ��ͷ������꣬��0-2��
    *                  �п��Բ�ȡ�Գƣ�����һ��Ҫȡ�Գ�
    * init���ú���ֻ����һ�Σ�������������г�ʼ���������Ĵ��룬��ʼ���ɹ�����true
    * SendMsg��ȷ������һ�ξ��ܳɹ�������Ϣ
    * GetMsg�����������һֱ���ã�����Է�������һ����Ч��Ϣ�򷵻�true�����򷵻�false
    * connect���������˷���true����δ������ʱ���ظ�����
    */

public:
    virtual bool init();
    bool connect();
    void SendMsg(int op, int id, int row, int col);
    bool GetMsg(int& op, int& id, int& row, int& col);

    CREATE_FUNC(Sever) // ���в��ù�
};

#endif // !__SEVERMSG_H__