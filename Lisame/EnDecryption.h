#pragma once
class EnDecryption
{
private:
	string distance;    //加密和解密的跨度，如减distance和加distance
	string cryptograph; //密文
	string realPwd;     //明文
public:
	EnDecryption(void);
	~EnDecryption(void);
public:
	/// <summary>
	/// 获取或设置用户密码,即明文
	/// </summary>
	string GetRealPwd();
	// 设置明文
	void SetRealPwd(string value)
	{
		realPwd = value;
	}

	/// <summary>
	/// 设置真正存储在文件中的加密密码,即密文
	/// </summary>
	string GetCryptograph();
	// 设置密文
	void SetCryptograph(string value);
};

