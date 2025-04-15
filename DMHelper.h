// 文件: DMHelper.h
// 简介: 定义封装大漠插件的工具类
// 详细: 以对象方式使用大漠插件功能，提供初始化、资源路径设置、字库加载等常用接口

#pragma once
#include "dm.tlh"
#include <afxwin.h>

class CDMHelper
{
public:
	// 文件: DMHelper.h
	// 简介: 构造函数，创建大漠插件对象
	// 详细: 自动加载 dm.dll 并初始化大漠插件接口
	CDMHelper();

	// 文件: DMHelper.h
	// 简介: 析构函数
	// 详细: 释放大漠插件对象资源
	~CDMHelper();

	// 文件: DMHelper.h
	// 简介: 获取大漠插件接口指针
	// 详细: 返回当前对象中初始化好的 Idmsoft 接口指针
	Idmsoft* GetDm();

	// 文件: DMHelper.h
	// 简介: 设置大漠资源路径
	// 详细: 设置图片、字体资源的根路径，支持相对路径，如 ".\\Ocr"
	bool SetDmResourcePath(const CString& path);

	// 文件: DMHelper.h
	// 简介: 设置大漠字体库
	// 详细: 指定字库槽位及字体文件名，如 "font\\num.font"
	bool SetFontDict(int index, const CString& fontFile);

private:
	Idmsoft* m_pDm; // 大漠插件接口指针
};
