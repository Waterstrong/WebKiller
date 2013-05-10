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

        private void Generating_Load(object sender, EventArgs e)
        {

        }

        private void btn_ok_Click(object sender, EventArgs e)
        {
            string type;
            switch(cbb_type.SelectedIndex)
            {
                case 1:
                    type = "ONEHOUR";
                    break;
                case 2:
                    type = "TWOHOUR";
                    break;
                default:
                    MessageBox.Show("请选择类型!", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                    cbb_type.SelectedIndex = 0;
                    cbb_type.Focus();
                    return;
            }
            if (txt_pwd.Text != "yyhua")
            {
                MessageBox.Show("密码输入有误!", "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                txt_pwd.Focus();
                return;
            }
            DateTime dt = DateTime.Now;
            string str = txt_pwd.Text + "#" + string.Format("{0:HH:mm:ss#yyyy-MM-dd}", dt) + "#" + type;
            EnDecryption ende = new EnDecryption();
            ende.RealPwd = str;
            str = ende.Cryptograph;
            string filePath = "D:\\key" + string.Format("{0:yyyyMMddHHmmss}", dt) + ".gen";
            try
            {
                File.WriteAllText(filePath, str);
                rtb_key.Text += dt.ToString() + " 成功生成验证钥并保存到<" + filePath + ">中：\r\n";
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "提示", MessageBoxButtons.OK, MessageBoxIcon.Information);
                rtb_key.Text += dt.ToString() + " 成功生成验证钥但未保存到<" + filePath + ">中：\r\n";
            }
            rtb_key.Text += "类型：" + cbb_type.Text + "\r\n";
            rtb_key.Text += "验证钥：" + str + "\r\n\r\n";
        }
    }
}
