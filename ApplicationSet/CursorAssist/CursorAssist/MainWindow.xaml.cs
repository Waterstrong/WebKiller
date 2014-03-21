﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Threading;
using System.Windows.Media.Animation;
using System.Configuration;

namespace CursorAssist
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private DispatcherTimer _tmr = new DispatcherTimer();
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            this.Title = "鼠标助手";
            double interval = 0.1;
            try
            {
                interval = Convert.ToDouble(ConfigurationManager.AppSettings["interval"]);
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
            // 计时器
            _tmr.Interval = TimeSpan.FromSeconds(interval);
            _tmr.Tick += TimerOnTick;

        }

        private void btn_click_Click(object sender, RoutedEventArgs e)
        {
            _tmr.Start();
            btn_click.Content = "正在点击...";
        }

        private void TimerOnTick(object sender, EventArgs args)
        {
            double x = this.Left + Canvas.GetLeft(label_arrow) + label_arrow.Width / 2;
            double y = this.Top - 10;
            Common.Mouse.MoveTo(new Point(x, y));
            Common.Mouse.Click(MouseButton.Left);
        }

        private void Window_MouseEnter(object sender, MouseEventArgs e)
        {
            _tmr.Stop();
            btn_click.Content = "开始点击";
        }

        private void btn_exit_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void Canvas_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            this.DragMove();
        }
    }
}
