// �ļ�: DMHelper.cpp
// ���: ʵ�ִ�Į������̰߳�ȫ��װ
// ��ϸ: ʵ��ͨ����ע�᷽ʽ��̬���� dm.dll ����ȡ Idmsoft �ӿڶ����ṩ�̰߳�ȫ�ĵ�����ȡ���ͷŷ���

#include "pch.h"
#include "DMHelper.h"

Idmsoft* CDMHelper::m_pDm = nullptr;
CRITICAL_SECTION CDMHelper::m_cs;
bool CDMHelper::m_bInit = false;

// �ļ�: DMHelper.cpp
// ���: ��ʼ���߳�ͬ����Դ
// ��ϸ: ��ʼ�� Critical Section����֤���������̰߳�ȫ����ִ��һ��
void CDMHelper::Init()
{
	if (!m_bInit)
	{
		InitializeCriticalSection(&m_cs);
		m_bInit = true;
	}
}

// �ļ�: DMHelper.cpp
// ���: ��ȡ��Į�����������
// ��ϸ: ��̬���� dm.dll����ȡ DllGetClassObject ������ͨ�� COM �ӿڴ��� Idmsoft ʵ�����̰߳�ȫ
Idmsoft* CDMHelper::GetInstance()
{
	Init();
	EnterCriticalSection(&m_cs);

	if (m_pDm == nullptr)
	{
		typedef HRESULT(_stdcall* pfnGCO)(REFCLSID, REFIID, void**);
		pfnGCO fnGCO = nullptr;
		HINSTANCE hDll = LoadLibrary(_T("dm.dll"));
		if (hDll)
		{
			fnGCO = (pfnGCO)GetProcAddress(hDll, "DllGetClassObject");
			if (fnGCO)
			{
				IClassFactory* pcf = nullptr;
				HRESULT hr = fnGCO(__uuidof(dmsoft), IID_IClassFactory, (void**)&pcf);
				if (SUCCEEDED(hr) && pcf)
				{
					hr = pcf->CreateInstance(nullptr, __uuidof(Idmsoft), (void**)&m_pDm);
					pcf->Release();
				}
			}
		}
	}

	LeaveCriticalSection(&m_cs);
	return m_pDm;
}

// �ļ�: DMHelper.cpp
// ���: �ͷŴ�Į�������
// ��ϸ: ��ղ��ͷŴ�Į����� COM ʵ���������ڳ����˳�ʱ�����������̰߳�ȫ
void CDMHelper::ReleaseInstance()
{
	EnterCriticalSection(&m_cs);
	if (m_pDm)
	{
		m_pDm->Release();
		m_pDm = nullptr;
	}
	LeaveCriticalSection(&m_cs);
}
