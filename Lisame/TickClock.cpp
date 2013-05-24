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
	// 获取当前时间
	//time_t now = time(NULL);
	//tm fmt;
	//localtime_s(&fmt, &now);
	SYSTEMTIME st = {0};
	GetLocalTime(&st);
	if (st.wYear == year && st.wMonth == month && st.wDay == day)
	{
		return 0; // 停留在当下
	}
	else // 未来或过去
	{
		int monCur = st.wYear*12+st.wMonth; // 实际的总月数
		int monTic = year*12+month; // 获取的的总月数
		if (monCur ==  monTic)
		{
			if (st.wDay > day)
			{
				return 1;// 表示已经到了未来了
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
			return -1;// 回到了过去
		}
	}
}