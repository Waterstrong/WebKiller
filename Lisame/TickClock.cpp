#include "StdAfx.h"
#include "TickClock.h"


TickClock::TickClock(void)
{
	year = 1900;
	month = 1;
	day = 1;
	hour = 0;
	minute = 0;
	second = 0;
	clockSec = 0;
	path = TICK_PATH;
}


TickClock::~TickClock(void)
{
}

int TickClock::TimeLine()
{
	// ��ȡ��ǰʱ��
	//time_t now = time(NULL);
	//tm fmt;
	//localtime_s(&fmt, &now);
	SYSTEMTIME st = {0};
	GetLocalTime(&st);
	if (st.wYear == year && st.wMonth == month && st.wDay == day)
	{
		return 0; // ͣ���ڵ���
	}
	else // δ�����ȥ
	{
		int monCur = st.wYear*12+st.wMonth; // ʵ�ʵ�������
		int monTic = year*12+month; // ��ȡ�ĵ�������
		if (monCur ==  monTic)
		{
			if (st.wDay > day)
			{
				return 1;// ��ʾ�Ѿ�����δ����
			}
			else
			{
				return -1;
			}
		}
		else if (monCur > monTic)
		{
			return 1;
		}
		else
		{
			return -1;// �ص��˹�ȥ
		}
	}
}