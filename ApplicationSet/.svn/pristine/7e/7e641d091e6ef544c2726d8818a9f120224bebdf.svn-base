/*********************************************************
 * 文件名称：GIProcess
 * 文件功能描述：实现GI进程控制
 * 
 * 创建标识：Waterstrong 20120513
 * 
 * 修改标识：
 * 修改描述：
*********************************************************/
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Windows.Forms;

namespace WebKiller
{
    class MyProcess
    {
        private void ShowError(string error)
        {
            MessageBox.Show(error + "\n" + filePath, "GI控制面板", MessageBoxButtons.OK, MessageBoxIcon.Warning);
        }
        protected string processName;
        public string ProcessName
        {
            get { return processName; }
            set { processName = value; }
        }
        protected string filePath;
        public string FilePath
        {
            get { return filePath; }
            set { filePath = value; }
        }
        /// <summary>
        /// 实现进程操作
        /// </summary>
        /// <param name="proName">进程名</param>
        /// <param name="filePath">文件路径</param>
        public MyProcess(string proName, string filePath)
        {
            this.processName = proName;
            this.filePath = filePath;
        }
        public MyProcess(string proName)
        {
            this.processName = proName;
        }
        public MyProcess()
        {
        }
        public bool Create()
        {
            try
            {
                Process.Start(filePath);
                return true;
            }
            catch (System.Exception ex)
            {
                ShowError(ex.Message);
                return false;
            }
        }
        public bool Exist()
        {
            try
            {
                Process[] myProcesses = Process.GetProcesses();
                foreach (Process myProcess in myProcesses)
                {
                    MessageBox.Show(myProcess.ProcessName);
                    if (processName == myProcess.ProcessName)
                    {
                        return true;
                    }
                }
                return false;
            }
            catch (System.Exception ex)
            {
                ShowError(ex.Message);
                return false;
            }
        }
        public void Terminate()
        {
            try
            {
                Process[] myProcesses = Process.GetProcesses();
                foreach (Process myProcess in myProcesses)
                {
                    if (processName == myProcess.ProcessName)
                    {
                        myProcess.Kill();//关掉已启动的进程
                    }
                }
            }
            catch (System.Exception ex)
            {
                ShowError(ex.Message);
            }
        }
        
    }
}
