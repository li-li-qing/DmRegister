// 文件: DMHelper.cpp
// 简介: 实现大漠插件的线程安全封装
// 详细: 实现通过免注册方式动态加载 dm.dll 并获取 Idmsoft 接口对象，提供线程安全的单例获取及释放方法

#include "pch.h"
#include "DMHelper.h"

Idmsoft* CDMHelper::m_pDm = nullptr;
CRITICAL_SECTION CDMHelper::m_cs;
bool CDMHelper::m_bInit = false;

// 文件: DMHelper.cpp
// 简介: 初始化线程同步资源
// 详细: 初始化 Critical Section，保证后续访问线程安全，仅执行一次
void CDMHelper::Init()
{
	if (!m_bInit)
	{
		InitializeCriticalSection(&m_cs);
		m_bInit = true;
	}
}

// 文件: DMHelper.cpp
// 简介: 获取大漠插件单例对象
// 详细: 动态加载 dm.dll，获取 DllGetClassObject 函数，通过 COM 接口创建 Idmsoft 实例，线程安全
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

// 文件: DMHelper.cpp
// 简介: 释放大漠插件对象
// 详细: 清空并释放大漠插件的 COM 实例，适用于程序退出时的清理工作，线程安全
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
