#pragma once
class TickClock
{
protected:
	int year; // ������
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int clockSec; // ��ʱ��������Ϊ��λ
	string path; // �ļ�·��
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
	// �µ�һ����Ҫ�������ں�ʱ��
	void UpdateDateTime()
	{
		// �޸�Ϊ��ǰʱ��
		SYSTEMTIME st = {0};
		GetLocalTime(&st);
		year = st.wYear;
		month = st.wMonth;
		day = st.wDay;
		hour = st.wHour;
		minute = st.wMinute;
		second = st.wSecond;
	}
	// ����Tick״̬
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
	// ��ȡTick״̬
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
	// �ж�ʱ���� 1δ����0���ڣ�-1��ȥ
	int TimeLine();

};