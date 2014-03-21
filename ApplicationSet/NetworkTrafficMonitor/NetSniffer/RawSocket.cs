using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;

namespace NetSniffer
{
    class RawSocket
    {
        Socket _socket;
        public RawSocket()
        {

        }
        public void CreateAndBind(string ip)
        {
            _socket = new Socket(AddressFamily.InterNetwork, SocketType.Raw, ProtocolType.IP);
            _socket.Blocking = false; // 设置为非阻塞模式
            _socket.Bind(new IPEndPoint(IPAddress.Parse(ip), 0)); // 绑定套接字            
        }
        public bool SetOption()
        {
            _socket.SetSocketOption(SocketOptionLevel.IP, SocketOptionName.HeaderIncluded, 1); // 设置选项，包含IP头
            byte[] inValue = BitConverter.GetBytes(1);
            byte[] outValue = BitConverter.GetBytes(0);
            int code = _socket.IOControl(IOControlCode.ReceiveAll, inValue, outValue); // 可以接收所有包
            if (BitConverter.ToInt32(outValue, 0) != 0)
            {
                return false;
            }
            return true;
        }
    }
}
