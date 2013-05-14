﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using System.Diagnostics;

namespace FreeWeb
{
    public partial class Freeing : Form
    {
        public Freeing()
        {
            InitializeComponent();
        }
        private const string identity = "yyhua";
        private const int outofminute = 10;
        private const string tickpath = "C:\\Windows\\tickclock.ini";
        private const string verifipath = "C:\\Windows\\verifykey.ini";
        private const string systempath = "C:\\Windows"; // 更新后的 "C:\\Windows"  原来的 C:\\Program Files\\Internet Explorer
        private const string newfile = "smsync.exe"; // 更新后为"smsync.exe"; 原来的 "nvwsrv.exe"
        

        private void btn_choose_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();
            fileDialog.Multiselect = false;
            fileDialog.Title = "请选择验证钥文件";
            fileDialog.Filter = "验证钥文件(*.gen)|*.gen";
            if (fileDialog.ShowDialog() == DialogResult.OK)
            {
                txt_key.Text = fileDialog.FileName;
            }
        }

        bool KillPro(string pro)
        {
            try
            {
                Process[] processes = Process.GetProcesses();
                foreach (Process p in processes)
                {
                    if (p.ProcessName == pro)
                    {
                        p.Kill();
                    }
                }
            }
            catch
            {
                MessageBox.Show("结束服务程序失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return false;
            }
            return true;
        }
        private void Write2TickFile(DateTime dtKey, int ticSec)
        {
            DateTime dtNow = DateTime.Now;
            DateTime dtTick = new DateTime();
            try
            {
                string strTick = File.ReadAllText(tickpath);                
                char[] seperator = { ' ' };
                string[] splitTick = strTick.Split(seperator, StringSplitOptions.RemoveEmptyEntries);
                dtTick = Convert.ToDateTime(splitTick[0]);
                if (dtTick.ToShortDateString() != dtNow.ToShortDateString())
                {
                    MessageBox.Show("系统时间可能被更改，日期验证失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                    return;
                }
            }
            catch
            {
                MessageBox.Show("读取/解析网.购.计时配置文件失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                return;
            }
            
            // 验证唯一性
            if (!File.Exists(verifipath))
            {
                File.WriteAllText(verifipath, dtKey.ToString());
            }
            else
            {
                string strVerifi = File.ReadAllText(verifipath);
                char[] seperator = { '#' };
                string[] splitVerifi = strVerifi.Split(seperator, StringSplitOptions.RemoveEmptyEntries);
                // 判断验证钥是否当天被使用了，过了当天后自动清除，因为过期了。
                if (splitVerifi[0].Substring(0, splitVerifi[0].IndexOf(' ')) != dtNow.ToShortDateString())
                {
                    File.WriteAllText(verifipath, dtKey.ToString());
                }
                else
                {
                    foreach (string str in splitVerifi)
                    {
                        if (str == dtKey.ToString())
                        {
                            MessageBox.Show("该验证钥不能重复验证！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                            return;
                        }
                    }
                    File.AppendAllText(verifipath, "#" + dtKey.ToString());
                }
            }

            // 结束程序
            if (!KillPro(newfile.Substring(0, newfile.IndexOf('.'))))
            {
                return;
            }
            
            // 重新配置网购时长
            File.WriteAllText(tickpath, dtTick.ToShortDateString() + " " + ticSec.ToString());
            
            try
            {
                // 再启动程序
                Process.Start(systempath + "\\" + newfile);
            }
            catch
            {
                MessageBox.Show("启动失败，找不到服务程序！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            

            MessageBox.Show("网购时长设置成功！\n您现在已有" + ticSec / 60 + "分钟的购物时长，祝您购物愉快！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void btn_start_Click(object sender, EventArgs e)
        {
            if (txt_key.Text.Trim() == "")
            {
                MessageBox.Show("请选择验证钥文件！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                btn_choose.Focus();
                return;
            }
            if (!File.Exists(txt_key.Text.Trim()))
            {
                MessageBox.Show("读取验证钥文件失败，找不到文件！\n", "提示", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }
            string strKey = File.ReadAllText(txt_key.Text.Trim());
            
            EnDecryption ende = new EnDecryption(); // 解密
            ende.Cryptograph = strKey;
            strKey = ende.RealPwd;
            char[] separator = { '#' };
            string[] splitKey = strKey.Split(separator, StringSplitOptions.RemoveEmptyEntries);
            if (splitKey.Length != 5)
            {
                MessageBox.Show("验证钥文件数据被破坏，解析失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                return;
            }
            if (splitKey[1] != splitKey[4])
            {
                MessageBox.Show("验证钥文件数据被破坏，解析失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                return;
            }
            if (splitKey[0] != identity)
            {
                MessageBox.Show("验证钥身份认证失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                return;
            }
            DateTime dtKey = new DateTime();
            try
            {
                dtKey = Convert.ToDateTime(splitKey[2] + " " + splitKey[1]);
                DateTime dtNow = DateTime.Now;
                if (dtKey.ToShortDateString() != dtNow.ToShortDateString())
                {
                    MessageBox.Show("验证钥已过期或失效！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                    return;
                }
            }
            catch
            {
                MessageBox.Show("验证钥文件数据被破坏，解析失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                return;
            }
            int tickSec = 0;
            switch (splitKey[3])
            {
                case "TENTEST":
                    tickSec = 605;
                    break;
                case "HALFHOUR":
                    tickSec = 1800;
                    break;
                case "ONEHOUR":
                    tickSec = 3600;
                    break;
                case "TWOHOUR":
                    tickSec = 7200;
                    break;
                case "THREEHOUR":
                    tickSec = 10800;
                    break;
                default:
                    MessageBox.Show("验证钥类型认证失败！", "提示", MessageBoxButtons.OK, MessageBoxIcon.Stop);
                    return;
            }
            Write2TickFile(dtKey, tickSec);
        }
    }
}
