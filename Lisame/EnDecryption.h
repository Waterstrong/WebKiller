#pragma once
class EnDecryption
{
private:
	string distance;    //���ܺͽ��ܵĿ�ȣ����distance�ͼ�distance
	string cryptograph; //����
	string realPwd;     //����
public:
	EnDecryption(void);
	~EnDecryption(void);
public:
	/// <summary>
	/// ��ȡ�������û�����,������
	/// </summary>
	string GetRealPwd();
	// ��������
	void SetRealPwd(string value)
	{
		realPwd = value;
	}

	/// <summary>
	/// ���������洢���ļ��еļ�������,������
	/// </summary>
	string GetCryptograph();
	// ��������
	void SetCryptograph(string value);
};

