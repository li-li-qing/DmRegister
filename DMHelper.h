// 文件: DMHelper.h
// 简介: 声明大漠插件封装类接口
// 详细: 提供线程安全的获取大漠对象实例方法，以及释放大漠对象的接口，供 MFC 项目调用

#pragma once
#include "dm.tlh"
#include <afxwin.h>

class CDMHelper
{
public:
	// 文件: DMHelper.h
	// 简介: 获取大漠插件单例对象
	// 详细: 返回线程安全的 Idmsoft 实例，首次调用时自动加载 dm.dll 并创建实例
	static Idmsoft* GetInstance();

	// 文件: DMHelper.h
	// 简介: 释放大漠插件对象
	// 详细: 释放 Idmsoft 指针资源，适用于程序退出或需重建对象时调用
	static void ReleaseInstance();

private:
	static Idmsoft* m_pDm;          // 大漠对象指针
	static CRITICAL_SECTION m_cs;  // 临界区，用于线程保护
	static bool m_bInit;            // 是否已初始化

	// 文件: DMHelper.h
	// 简介: 初始化内部状态
	// 详细: 初始化临界区，确保线程安全，仅在首次调用时执行一次
	static void Init();
};
