using System;
using System.Collections.Generic;
using System.Text;

namespace FreeWeb
{
	class EnDecryption
	{
		private string distance;    //加密和解密的跨度，如减distance和加distance
        private string cryptograph; //密文
		private string realPwd;     //明文

        /// <summary>
        /// 构造函数，初始化
        /// </summary>
        public EnDecryption()
		{
			distance = ""; 
			cryptograph = "";   
			realPwd = "";      
		}

        /// <summary>
        /// 获取或设置用户密码,即明文
        /// </summary>
		public string RealPwd
		{
			get
			{
				this.realPwd = "";
				int nRealStrLength = cryptograph.Length;
				string pwd = cryptograph.Substring(0, nRealStrLength / 2);
				string dis = cryptograph.Substring(nRealStrLength / 2);
				for (int i = 0; i < nRealStrLength / 2; i++ )
				{
					char ch = (char)(pwd[i] + dis[i] - 48);
					this.realPwd += ch;
				}
				return this.realPwd;
			}
            set
            {
                realPwd = value;
            }
        }

        /// <summary>
		/// 设置真正存储在文件中的加密密码,即密文
		/// </summary>
		public string Cryptograph
		{
			get
			{
				string strReal = "";
                int nPwdLength = this.realPwd.Length;
				Random rand = new Random();
                distance = "";
				for (int i = 0; i < nPwdLength; i++)
				{
					int nRandNumber = rand.Next(9);
                    char ch = (char)(this.realPwd[i] - nRandNumber);
					strReal += ch;
					distance += (char)(nRandNumber + 48);
				}
				strReal += distance;
				return strReal;
			}
			set
			{
				cryptograph = value;
				int nRealStrLength = cryptograph.Length;
				realPwd = cryptograph.Substring(0, nRealStrLength / 2);
				distance = cryptograph.Substring(nRealStrLength / 2);
			}
		}
	}
}
