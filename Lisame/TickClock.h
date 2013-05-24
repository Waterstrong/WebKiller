#pragma once
class TickClock
{
protected:
	int year; // 年月日
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int clockSec; // 计时器，以秒为单位
	string path; // 文件路径
public:
	TickClock(void);
	~TickClock(void);
	int &Year()
	{
		return year;
	}
	int &Month()
	{
		return month;
	}
	int &Day()
	{
		return day;
	}
	int &Hour()
	{
		return hour;
	}
	int &Minute()
	{
		return minute;
	}
	int &Second()
	{
		return second;
	}
	int &ClockSec()
	{
		return clockSec;
	}
	// 新的一天需要更新日期和时间
	void UpdateDateTime()
	{
		// 修改为当前时间
		SYSTEMTIME st = {0};
		GetLocalTime(&st);
		year = st.wYear;
		month = st.wMonth;
		day = st.wDay;
		hour = st.wHour;
		minute = st.wMinute;
		second = st.wSecond;
	}
	// 保存Tick状态
	bool WriteToFile()
	{
		ofstream output;
		output.open(path, ios::out);
		if (!output)
		{
			return false;
		}
		output<<year<<"-"<<month<<"-"<<day<<" "
			<<hour<<":"<<minute<<":"<<second<<" "
			<<clockSec<<endl;
		output.close();
		return true;
	}
	// 读取Tick状态
	bool ReadFromFile()
	{
		ifstream input;
		input.open(path, ios::in);
		if (!input)
		{
			return false;
		}
		char ch;
		input>>year>>ch>>month>>ch>>day
			>>hour>>ch>>minute>>ch>>second
			>>clockSec;
		if (input.fail())
		{
			return false;
		}
		input.close();
		return true;
	}
	// 判断时间线 1未来，0现在，-1过去
	int TimeLine();

};