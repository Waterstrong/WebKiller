// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#define SAVE_FREQ 300 // ����Ƶ�ʣ�һ��5���ӱ���һ��״̬
#define INIT_SEC 3600 // ÿ���Ա��涨���60���ӣ������ʾ
#define REMINDING 600 // ����ʱ��,10���ӣ������ʾ
#define TICK_PATH "C:\\Windows\\tickclock.ini" // TICK�ļ�����λ��
#define NEW_FILE "smsync.exe" // �µ��ļ���
#define SYSTEM_PATH "C:\\Windows" // д�뵽ϵͳ·����
#define TARGET_FILE "\\config\\targetlist.dat" // Ŀ���б������ļ�
#define CLSNAME_FILE "\\config\\clsname.dat" // ���������ļ�

#include <afxwin.h>
#include <Windows.h>
#include <tlhelp32.h>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator> 
//#include <algorithm>
//#include <time.h>
//#include <cmath>
//#include <shellapi.h>
//#include <afxcoll.h>
//#include <afxsock.h>      // MFC socket extensions 
#include <afxdtctl.h>     // MFC support for Internet Explorer 4 Common Controls 
using namespace std;

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
