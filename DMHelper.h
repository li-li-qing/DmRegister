// �ļ�: DMHelper.h
// ���: ������Į�����װ��ӿ�
// ��ϸ: �ṩ�̰߳�ȫ�Ļ�ȡ��Į����ʵ���������Լ��ͷŴ�Į����Ľӿڣ��� MFC ��Ŀ����

#pragma once
#include "dm.tlh"
#include <afxwin.h>

class CDMHelper
{
public:
	// �ļ�: DMHelper.h
	// ���: ��ȡ��Į�����������
	// ��ϸ: �����̰߳�ȫ�� Idmsoft ʵ�����״ε���ʱ�Զ����� dm.dll ������ʵ��
	static Idmsoft* GetInstance();

	// �ļ�: DMHelper.h
	// ���: �ͷŴ�Į�������
	// ��ϸ: �ͷ� Idmsoft ָ����Դ�������ڳ����˳������ؽ�����ʱ����
	static void ReleaseInstance();

private:
	static Idmsoft* m_pDm;          // ��Į����ָ��
	static CRITICAL_SECTION m_cs;  // �ٽ����������̱߳���
	static bool m_bInit;            // �Ƿ��ѳ�ʼ��

	// �ļ�: DMHelper.h
	// ���: ��ʼ���ڲ�״̬
	// ��ϸ: ��ʼ���ٽ�����ȷ���̰߳�ȫ�������״ε���ʱִ��һ��
	static void Init();
};
