# CPP免注册c++方法
下载以下文件,创建好MFC工程文件,然后把下载的文件拖到源目录里面

在你需要使用的文件中添加#include "DMHelper.h" 头文件


就可以直接使用里面的功能了
记得要登陆

// 自己封装的方便使用大漠插件的函数
CDMHelper DMHelper;

BOOL CArcheAgeLLQDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	// 初始化大漠对象
	Idmsoft* pdm = DMHelper.GetDm();
	if (pdm == nullptr)
	{
		AfxMessageBox(_T("大漠对象创建失败"));
		return FALSE;
	}

	long dmReg = pdm->Reg(_T("你的注册码"), _T("你的附加码"));
	if (dmReg != 1)
	{
		SetWindowTextA(m_hWnd, "创建失败");
	}
	else
	{
		SetWindowTextA(m_hWnd, pdm->Ver());
	}



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}