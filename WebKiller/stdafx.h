// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define INIT_SEC 3600 // 1��Сʱ�������ʾ
#define REMINDING 600 // ����ʱ��
#define TICK_PATH "C:\\Windows\\tickclock.ini" // TICK�ļ�����λ��

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

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
