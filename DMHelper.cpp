// 文件: DMHelper.cpp
// 简介: 实现大漠插件封装类
// 详细: 初始化 dm.dll，提供资源路径和字库设置封装

#include "pch.h"
#include "DMHelper.h"

// 文件: DMHelper.cpp
// 简介: 构造函数
// 详细: 加载 dm.dll 并创建 Idmsoft 对象
CDMHelper::CDMHelper()
{
	m_pDm = nullptr;

	typedef HRESULT(_stdcall* pfnGCO)(REFCLSID, REFIID, void**);
	pfnGCO fnGCO = nullptr;
	HINSTANCE hDll = LoadLibrary(_T("dm.dll"));
	if (hDll)
	{
		fnGCO = (pfnGCO)GetProcAddress(hDll, "DllGetClassObject");
		if (fnGCO)
		{
			IClassFactory* pcf = nullptr;
			if (SUCCEEDED(fnGCO(__uuidof(dmsoft), IID_IClassFactory, (void**)&pcf)) && pcf)
			{
				pcf->CreateInstance(nullptr, __uuidof(Idmsoft), (void**)&m_pDm);
				pcf->Release();
			}
		}
	}
}

// 文件: DMHelper.cpp
// 简介: 析构函数
// 详细: 释放 Idmsoft 对象，防止资源泄漏
CDMHelper::~CDMHelper()
{
	if (m_pDm)
	{
		m_pDm->Release();
		m_pDm = nullptr;
	}
}

// 文件: DMHelper.cpp
// 简介: 获取大漠插件接口指针
// 详细: 返回 m_pDm 指针，可用于调用大漠所有原始函数
Idmsoft* CDMHelper::GetDm()
{
	return m_pDm;
}

// 文件: DMHelper.cpp
// 简介: 设置资源路径
// 详细: 设置大漠查图、识字所使用的基础目录，如 .\\Ocr
bool CDMHelper::SetDmResourcePath(const CString& path)
{
	// 设置大漠路径
	return m_pDm && m_pDm->SetPath((LPCTSTR)path) == 1;
}


// 文件: DMHelper.cpp
// 简介: 设置大漠插件字库（自动创建 .txt 字库）
// 详细: 如果指定 .txt 字库文件不存在，则自动创建一个空的文本文件并设置到指定槽位
bool CDMHelper::SetFontDict(int index, const CString& fontFile)
{
	// 设置字库到指定槽位
	return m_pDm && m_pDm->SetDict(index, (LPCTSTR)fontFile) == 1;
}

