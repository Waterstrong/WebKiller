// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define INIT_SEC 3600 // 1个小时，以秒表示
#define REMINDING 600 // 提醒时间
#define TICK_PATH "C:\\Windows\\tickclock.ini" // TICK文件保存位置

#include <afxwin.h>
#include <Windows.h>
#include <tlhelp32.h>  
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator> 
#include <algorithm>
#include <time.h>
#include <cmath>
//#include <shellapi.h>
#include <afxcoll.h>
#include <afxsock.h>      // MFC socket extensions 
#include <afxdtctl.h>     // MFC support for Internet Explorer 4 Common Controls 
using namespace std;

// TODO: 在此处引用程序需要的其他头文件
