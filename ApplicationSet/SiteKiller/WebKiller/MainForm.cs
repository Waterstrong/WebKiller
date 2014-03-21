using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace WebKiller
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }
        string[] _proNames;
        MyProcess _pro = new MyProcess();
        private void MainForm_Load(object sender, EventArgs e)
        {
            try
            {
                this.Visible = false;
                string strRead;
                char[] seperator = { ' ' };
                strRead = File.ReadAllText("list.dat");
                _proNames = strRead.Split(seperator, StringSplitOptions.RemoveEmptyEntries);
                timer_check.Start();
            }
            catch (System.Exception ex)
            {
                MessageBox.Show("未找到指定文件。");
                Application.Exit();
            }
            
        }

        private void timer_check_Tick(object sender, EventArgs e)
        {
            foreach (string name in _proNames)
            {
                _pro.ProcessName = name;
                _pro.Terminate();
            }
        }
    }
}
