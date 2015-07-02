#ifndef CENTER_H
#define CENTER_H

#include "messagestruct.h"


class center
{
private:
	int haverun;
	pthread_t tid1,tid2,tid3,tid4,tid5;
public:
	center();
	~center();

	bool run();

	//����Ǳ�����ñ����еĺ�����Ϊ�̺߳�������Ӧ��Ϊstatic
	static void* takeoutjsin(void* lp);//�߳�2��stackjsonmessageinȡ����Ϣ����struct1��struct2
	static void* dispose1(void* lp);//�߳�3����struct1->jsonmessageout
	static void* dispose2(void* lp);//�߳�4����struct2

	static void* sendjsonout(void* lp);//�߳�6����jsonmessageout


	static std::queue<sockerjson> jsonmessagein;//�߳�1��ȡ������
	static std::queue<messagestruct> struct1;//�߳�2�Ľ��
	static std::queue<messagestruct> struct2;//�߳�2�Ľ����struct2������������ǿ��ݴ���������Ϣ����Ӻ���

	//�߳�4����struct2���Ƿ�ֱ�ӷ��ͻ��ݴ�
	static std::queue<jsonout_ip> jsonmessageout;//�߳�5��struct1��Ϊjson��ʽ
	//�߳�6����jsonmessageout

};

#endif

/*
��Ϣ����
0 �ͻ�����������ˢ��
1 ע��
2 ��¼
3 �˳�
4 ���ҵ���qq��Ϣ
5 ��ȡqq�����б�

6 ����qq��Ϣ
7 �������qq����
8 �ظ���Ӻ���

//--------------------
110 ���ͻ���ʧ����ʾ��Ϣ
111ע��ɹ�
112����qq������Ϣ
113qq�����б�
114��Ӻ�������
115 qq��Ϣ

200 �ÿͻ���ȥ����ˢ��
//--------------------

�������ݿ����Ϣ
classid 1 ��Ӻ���
classid 2 qq��Ϣ
״̬ 0Ϊ���� 1����ok
*/

//char recvBuf[1001]; ���յ����ݱ��޶���Ŷ

/*
�����߳�1,������Ϣ��������Ϣ����jsonmessagein--queue.
�����߳�2,ȡ��jsonmessagein�е���Ϣ-��������Ϊmessagestruct->���䵽struct1��struct2
�����߳�3������ע�ᣬ��¼���˳����鿴qq������Ϣ
�����߳�4������qq��Ϣ�ͺ������
�����߳�5������json��ʽ����Ϣ���ͻ���
*/