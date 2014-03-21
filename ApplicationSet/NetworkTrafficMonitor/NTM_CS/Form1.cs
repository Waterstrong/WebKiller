﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net.Sockets;

namespace NTM_CS
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void CreateAndBindSocket(string ip)
        {
            Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Raw, ProtocolType.IP);
            socket.Blocking = false;
            //socket.Bind();
        }


        
// socket = new Socket(endPoint.Address.AddressFamily, SocketType.Raw, endPoint.Address.IsIPv6LinkLocal ? ProtocolType.IPv6 : ProtocolType.IP);   //在发送时，您的应用程序必须提供完整的 IP 标头。所接收的数据报在返回时会保持其 IP 标头和选项不变。
// socket.Blocking = false;    //置socket非阻塞状态
// socket.Bind(this.endPoint = endPoint);    //绑定套接字
// 
// //设置套接字选项时必须使套接字包含IP包头，否则无法填充IPHeader结构，也无法获得数据包信息
// socket.SetSocketOption(endPoint.Address.IsIPv6LinkLocal ? SocketOptionLevel.IPv6 : SocketOptionLevel.IP, SocketOptionName.HeaderIncluded, 1);
// byte[] inCode = new byte[4] { 1, 0, 0, 0 }, outCode = new byte[4];
// 
// //因为，在windows中我们不能用Receive函数来接收raw socket上的数据，这是因为，所有的IP包都是先递交给系统核心，然后再传输到用户程序，当发送一个raws socket包的时候（比如syn），核心并不知道，也没有这个数据被发送或者连接建立的记录，因此，当远端主机回应的时候，系统核心就把这些包都全部丢掉，从而到不了应用程序上。所以，就不能简单地使用接收函数来接收这些数据报。要达到接收数据的目的，就必须采用嗅探，接收所有通过的数据包，然后进行筛选，留下符合我们需要的。
// //低级别操作模式,接受所有的数据包，这一步是关键，必须把socket设成raw和IP Level才可用IOControlCode.ReceiveAll
// int code = socket.IOControl(IOControlCode.ReceiveAll, inCode, outCode);
// if((code = showjim.sys.bitConverter.toInt31(outCode)) == 0)
// {
//     this.getPacket = getPacket;
//     //返回了一个异步操作的接口，并在此接口的生成函数BeginReceive中声明了异步回调函数CallReceive，并把接收到的网络数据流传给receive_buf_bytes，这样就可用一个带有异步操作的接口参数的异步回调函数不断地接收数据包
//     buffer = new byte[bufferBytes];
//     socket.BeginReceive(buffer, 0, bufferBytes, SocketFlags.None, new AsyncCallback(callReceive), this);
// }
// 
// private void callReceive(IAsyncResult asyncResult)
// {
//     int length = socket.EndReceive(asyncResult);
//     //处理buffer
// }


