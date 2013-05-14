using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace GenKey
{
    public partial class Generating : Form
    {
        public Generating()
        {
            InitializeComponent();
        }
        private const string identity = "yyhua";

        private void btn_ok_Click(object sender, EventArgs e)
        {
            string type;
            switch(cbb_type.SelectedIndex)
            {
                case 0:
                    type = "TENTEST";
                    break;
                case 1:
                    type = "HALFHOUR";
                    break;
                case 2:
                    type = "ONEHOUR";
                    break;
                case 3:
                    type = "TWOHOUR";
                    break;
                case 4:
                    type = "THREEHOUR";
                    break;
                default:
                    MessageBox.Show("请选择类型!", "提示", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    cbb_type.Focus();
                    return;
            }
            if (txt_pwd.Text != identity)
            {
                MessageBox.Show("请输入有正确有效的密码!", "提示", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                txt_pwd.Focus();
                return;
            }
            FolderBrowserDialog foldDialog = new FolderBrowserDialog();
            foldDialog.RootFolder = Environment.SpecialFolder.DesktopDirectory;
            foldDialog.ShowNewFolderButton = true;
            foldDialog.Description = "选择要保存到的文件夹";
            if (foldDialog.ShowDialog() != DialogResult.OK)
            {
                return;
            }

            DateTime dt = DateTime.Now;
            string str = txt_pwd.Text + "#" + string.Format("{0:HH:mm:ss#yyyy-MM-dd}", dt) + "#" + type + "#" + string.Format("{0:HH:mm:ss}", dt);
            EnDecryption ende = new EnDecryption();
            ende.RealPwd = str;
            str = ende.Cryptograph;

            string filePath = foldDialog.SelectedPath + "\\key" + string.Format("{0:yyyyMMddHHmmss}", dt) + ".gen";
            try
            {
                File.WriteAllText(filePath, str);
                rtb_key.Text += dt.ToString() + " 成功生成验证钥并保存到<" + filePath + ">中：\r\n";
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "提示", MessageBoxButtons.OK, MessageBoxIcon.Error);
                rtb_key.Text += dt.ToString() + " 成功生成验证钥但未保存到<" + filePath + ">中：\r\n";
            }
            rtb_key.Text += "类型：" + cbb_type.Text + "\r\n";
            rtb_key.Text += "验证钥：" + str + "\r\n\r\n";
        }
    }
}
