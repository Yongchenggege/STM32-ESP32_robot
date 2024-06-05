using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Threading;


namespace MechanicalArmControl
{
    public partial class frmMain : Form
    {
        static SerialPort _serialPort;

        static bool _resume;

        Thread read_Thread = new Thread(Read);

        //Timer _timer ;

      //var timer = new Timer();
      //timer.Interval = 1000;
      //timer.Tick += new EventHandler(timer_Tick);
      //timer.Start();

        //string orderSting;
        //int orderNumber;

//十六进制指令	按键名称	方框格参数范围（可填执行次数 每200ms发一次指令）
//AA 01 BB	底座正转45度	范围1-8
//AA 02 BB	底座正转45度	范围1-8
//AA 03 BB	开爪45度	范围1-2
//AA 04 BB	收爪45度	范围1-2
//AA 05 BB	关节1正转45度	范围1-4
//AA 06 BB	关节1反转45度	范围1-4
//AA 07 BB	关节2正传45度	范围1-4
//AA 08 BB	关节2反传45度	范围1-4
//AA 09 BB	前运动	范围>=1
//AA 10 BB	后运动 	范围>=1
//AA 11 BB	左前运动	范围>=1
//AA 12 BB	右前运动	范围>=1
//AA 13 BB	停止	无
//AA 14 BB	物体颜色识别	无
//AA 15 BB	模式切换	无
//AA 16 BB	手动模式	无
//AA 17 BB	自动模式	无

//AA 01 BB	红色
//AA 02 BB	蓝色
//AA 03 BB	绿色
//AA 04 BB	没检测到

        private Byte[] cmdForward = { 0xaa, 0x09, 0xbb };
        private Byte[] cmdRetreat = { 0xaa, 0x0A, 0xbb };
        private Byte[] cmdLeft = { 0xaa, 0x0B, 0xbb };
        private Byte[] cmdRight = { 0xaa, 0x0C, 0xbb };
        private Byte[] cmdStop = { 0xaa, 0x0D, 0xbb };

        private Byte[] cmdBaseForwardRotate = { 0xaa, 0x01, 0xbb };
        private Byte[] cmdBaseReverse = { 0xaa, 0x02, 0xbb };
        private Byte[] cmdOpenClaw = { 0xaa, 0x03, 0xbb };
        private Byte[] cmdRetractClaw = { 0xaa, 0x04, 0xbb };

        private Byte[] cmdJoint1ForwardRotate = { 0xaa, 0x05, 0xbb };
        private Byte[] cmdJoint1Reverse = { 0xaa, 0x06, 0xbb };
        private Byte[] cmdJoint2ForwardRotate = { 0xaa, 0x07, 0xbb };
        private Byte[] cmdJoint2Reverse = { 0xaa, 0x08, 0xbb };

        //private Byte[] cmdForward = { 0xaa, 0x09, 0xbb };
        //private Byte[] cmdForward = { 0xaa, 0x09, 0xbb };
        //private Byte[] cmdForward = { 0xaa, 0x09, 0xbb };
        //private Byte[] cmdForward = { 0xaa, 0x09, 0xbb };
        //private Byte[] cmdForward = { 0xaa, 0x09, 0xbb };

        //private Byte[] 按下 = { 0xaa, 0x00, 0x00, 0xbb };

        //颜色
        private Byte myRed = 0x01;
        private Byte myBlue = 0x02;
        private Byte myGreen = 0x03;
        private Byte myNone = 0x04;

        public frmMain()
        {
            InitializeComponent();
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
            initData();
        }

        private void initData()
        {
            // Create a new SerialPort object with default settings.
            _serialPort = new SerialPort();

            initSerialPort();

            _resume = false;

            //Port name can be identified by checking the ports
            // section in Device Manager after connecting your device
            //serialPort1.PortName = "COM5";
            //Provide the name of port to which device is connected

            //default values of hardware[check with device specification document]
            //serialPort1.BaudRate = 9600;
            //serialPort1.Parity = Parity.None;
            //serialPort1.StopBits = StopBits.One;
            //serialPort1.Handshake = Handshake.None;

            //serialPort1.Open(); //opens the port
            //serialPort1.ReadTimeout = 200;
            //if (serialPort1.IsOpen)
            //{
            //    DispString = "";
            //    txtCardKeyDeactivate.Text = "";
            //}
            //serialPort1.DataReceived += new SerialDataReceivedEventHandler(serialPort1_DataReceived);

            // Allow the user to set the appropriate properties.
            //_serialPort.PortName = SetPortName(_serialPort.PortName);
            //_serialPort.BaudRate = SetPortBaudRate(_serialPort.BaudRate);
            //_serialPort.Parity = SetPortParity(_serialPort.Parity);
            //_serialPort.DataBits = SetPortDataBits(_serialPort.DataBits);
            //_serialPort.StopBits = SetPortStopBits(_serialPort.StopBits);
            //_serialPort.Handshake = SetPortHandshake(_serialPort.Handshake);

            //_serialPort.PortName = "COM1";
            //_serialPort.BaudRate = 115200;
            //_serialPort.Parity = Parity.None;
            //_serialPort.DataBits = 8;
            //_serialPort.StopBits = StopBits.One;
            //_serialPort.Handshake = Handshake.None;

            //// Set the read/write timeouts
            //_serialPort.ReadTimeout = 500;
            //_serialPort.WriteTimeout = 500;

            //_serialPort.Open();

        }

        private void initSerialPort()//初始化串口方法
        {
            //获取当前计算机的串口名称数组
            string[] ports = SerialPort.GetPortNames();
            if (ports.Length > 0)
            {
                cmbPortName.DataSource = ports;//向控件添加串口          
            }
            else
            {
                MessageBox.Show("未检测到串口");
            }
            //波特率设置
            string[] baunds = { "1200", "4800", "9600", "19200", "38400", "57600", "115200" };
            cmbBaudRate.DataSource = baunds;//向控件添加
            cmbBaudRate.SelectedIndex = 6;

            //数据位设置
            cmbDataBits.Items.AddRange(new string[] { "5", "6", "7", "8" });
            cmbDataBits.SelectedIndex = 3;

            //奇偶校验位设置
            cmbParity.DataSource = Enum.GetNames(typeof(Parity));//反射把枚举Parity中的东西全部搞出来

            //停止位设置
            cmbStopBits.DataSource = Enum.GetNames(typeof(StopBits));//反射把枚举StopBits中的东西全部搞出来
            cmbStopBits.SelectedIndex = 1;
        }

        public static void Read()
        {
            while (_resume)
            {
                try
                {
                    if (_serialPort.IsOpen)
                    {
                        // read the received message
                        while (_serialPort.BytesToRead > 0) // while there is data to read in the input buffer
                        {
                            //byte[] buffer = new byte[_serialPort.BytesToRead]; // create a byte array to hold the data
                            byte[] buffer = new byte[3]; // create a byte array to hold the data
                            _serialPort.Read(buffer, 0, buffer.Length); // reads the data into the array

                            //setColor(buffer[1].ToString());
                            Console.WriteLine(buffer[1].ToString()); // displays the data as ASCII text
                        }
                    }
                }

                catch (TimeoutException)
                {
                }
            }
        }

        public void receiveData()
        {
            try
            {
                if (_serialPort.IsOpen)
                {
                    // read the received message
                    if (_serialPort.BytesToRead > 0) // while there is data to read in the input buffer
                    {
                        byte[] buffer = new byte[_serialPort.BytesToRead]; // create a byte array to hold the data
                        //byte[] buffer = new byte[3]; // create a byte array to hold the data
                        _serialPort.Read(buffer, 0, buffer.Length); // reads the data into the array

                        for (int i = 0; i < buffer.Length; i++)
                        {
                            if (buffer[i] == 0xaa && i+2 <= buffer.Length)
                            {
                                if (buffer[i + 2] == 0xbb)
                                {
                                    setColor(buffer[i+1].ToString());
                                }
                            }
                            Console.WriteLine(buffer[i].ToString()); // displays the data as ASCII text
                        }
                    }
                }

                //for (int i = 1; i < 60; i++)
                //{
                //    int k;
                //    k = i % 69;
                //    setColor(k.ToString());

                //    Console.WriteLine(k.ToString());
                //    if (_resume == false)
                //    {
                //        i = 100;
                //    }
                //}

                if (_resume == true)
                {
                    timer1.Start();
                }

            }

            catch (TimeoutException)
            {
            }
        }

        private void getOrder(string controlOrder)
        {
            if (!_serialPort.IsOpen)
            {
                MessageBox.Show("请打开串行口.");
                return;
            }

            if (controlOrder == "Forward")
            {
                sendData(cmdForward);
            }
            else if (controlOrder == "Retreat")
            {
                sendData(cmdRetreat);
            }
            else if (controlOrder == "Left")
            {
                sendData(cmdLeft);
            }
            else if (controlOrder == "Right")
            {
                sendData(cmdRight);
            }
            else if (controlOrder == "Stop")
            {
                sendData(cmdStop);
            }
            else if (controlOrder == "BaseForwardRotate")
            {
                sendData(cmdBaseForwardRotate);
            }
            else if (controlOrder == "BaseReverse")
            {
                sendData(cmdBaseReverse);
            }
            else if (controlOrder == "OpenClaw")
            {
                sendData(cmdOpenClaw);
            }
            else if (controlOrder == "RetractClaw")
            {
                sendData(cmdRetractClaw);
            }
            else if (controlOrder == "Joint1Reverse")
            {
                sendData(cmdJoint1Reverse);
            }
            else if (controlOrder == "Joint1ForwardRotate")
            {
                sendData(cmdJoint1ForwardRotate);
            }
            else if (controlOrder == "Joint2Reverse")
            {
                sendData(cmdJoint2Reverse);
            }
            else if (controlOrder == "Joint2ForwardRotate")
            {
                sendData(cmdJoint2ForwardRotate);
            }
        }

        private void sendData(byte[] cmdData)
        {
            if (_serialPort.IsOpen)
            {
                //_serialPort.WriteLine(String.Format("{0},{1}", orderSting, orderNumber));

                //_serialPort.DiscardInBuffer();//清空输入缓存
                _serialPort.DiscardOutBuffer();//清空输出缓存
 
                _serialPort.Write(cmdData, 0, cmdData.Length);

                Console.WriteLine(String.Format("{0}", cmdData[1].ToString()));

            }
            else
            {
                MessageBox.Show("无法打开串口" + _serialPort.PortName);
            }

        }

        private void btForward_Click(object sender, EventArgs e)
        {
            getOrder("Forward");

        }

        private void btnOpen_Click(object sender, EventArgs e)
        {

            if (_serialPort.IsOpen) 
                _serialPort.Close();//如果打开就关闭

            if (!_serialPort.IsOpen)//如果串口是关闭的
            {
                try
                {
                    //从控件设置串口控件属性
                    _serialPort.PortName = cmbPortName.Text;
                    _serialPort.BaudRate = int.Parse(cmbBaudRate.Text);
                    _serialPort.DataBits = int.Parse(cmbDataBits.Text);
                    _serialPort.Parity = (Parity)Enum.Parse(typeof(Parity), cmbParity.Text);
                    _serialPort.StopBits = (StopBits)Enum.Parse(typeof(StopBits), cmbStopBits.Text);

                    //设置接收触发字节数
                    _serialPort.ReceivedBytesThreshold = 7;
                    _serialPort.Open();//打开串口
                    //_serialPort.DataReceived += _serialPort_DataReceived;

                    btnOpen.BackColor = Color.Lime;

                    MessageBox.Show("成功打开串口");

                    //if (!_resume)
                    //{
                    //    _resume = true;
                    //    read_Thread.Start();

                    //}

                }
                catch (Exception ee)
                {
                    MessageBox.Show(ee.Message);
                }
            }

            //if (btnOpen.Text == "打开")
            //{
            //    if (_serialPort.IsOpen) _serialPort.Close();//如果打开就关闭
            //    if (!_serialPort.IsOpen)//如果串口是关闭的
            //    {
            //        try
            //        {
            //            //从控件设置串口控件属性
            //            _serialPort.PortName = cmbPortName.Text;
            //            _serialPort.BaudRate = int.Parse(cmbBaudRate.Text);
            //            _serialPort.DataBits = int.Parse(cmbDataBits.Text);
            //            _serialPort.Parity = (Parity)Enum.Parse(typeof(Parity), cmbParity.Text);
            //            _serialPort.StopBits = (StopBits)Enum.Parse(typeof(StopBits), cmbStopBits.Text);

            //            //设置接收触发字节数
            //            _serialPort.ReceivedBytesThreshold = 7;
            //            _serialPort.Open();//打开串口
            //            //_serialPort.DataReceived += _serialPort_DataReceived;
            //            MessageBox.Show("成功打开串口");

            //            //开始轮循
            //            //测试与通讯发送("按下");

            //            btnOpen.Text = "关闭";
            //            btnOpen.BackColor = Color.Red;
            //        }
            //        catch (Exception ee)
            //        {
            //            MessageBox.Show(ee.Message);
            //        }
            //    }
            //}
            //else
            //{
            //    Environment.Exit(0);
            //    if (_serialPort.IsOpen) _serialPort.Close();//如果串口是卡开的就关闭
            //    btnOpen.Text = "打开";
            //    btnOpen.BackColor = Color.Lime;
            //}

        }

        private void btRetreat_Click(object sender, EventArgs e)
        {
            getOrder("Retreat");
        }

        private void btLeft_Click(object sender, EventArgs e)
        {
            getOrder("Left");
        }

        private void btRight_Click(object sender, EventArgs e)
        {
            getOrder("Right");
        }

        private void btBaseForwardRotate_Click(object sender, EventArgs e)
        {
            getOrder("BaseForwardRotate");
        }

        private void btBaseReverse_Click(object sender, EventArgs e)
        {
            getOrder("BaseReverse");

        }

        private void btOpenClaw_Click(object sender, EventArgs e)
        {
            getOrder("OpenClaw");

        }

        private void btRetractClaw_Click(object sender, EventArgs e)
        {
            getOrder("RetractClaw");

        }

        private void btJoint1Reverse_Click(object sender, EventArgs e)
        {
            getOrder("Joint1Reverse");
        }

        private void btJoint1ForwardRotate_Click(object sender, EventArgs e)
        {
            getOrder("Joint1ForwardRotate");
        }

        private void btJoint2Reverse_Click(object sender, EventArgs e)
        {
            getOrder("Joint2Reverse");
        }

        private void btJoint2ForwardRotate_Click(object sender, EventArgs e)
        {
            getOrder("Joint2ForwardRotate");
        }

        private void button1_Click(object sender, EventArgs e)
        {
            getOrder("Stop");

        }

        private void frmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
            try
            {


            }
            catch
            {

            }
        }

        public void setColor(string strColor)
        {
            if (myRed.ToString() == strColor)
            {
                if (pnlColor.BackColor != Color.Red)
                {
                    lblColor.Text = "红色";
                    lblColor.Refresh();
                    pnlColor.BackColor = Color.Red;
                    pnlColor.Refresh();
                    System.Threading.Thread.Sleep(1000);

                }
            }
            else if (myBlue.ToString() == strColor)
            {
                if (pnlColor.BackColor != Color.Blue)
                {
                    lblColor.Text = "蓝色";
                    lblColor.Refresh();
                    pnlColor.BackColor = Color.Blue;
                    pnlColor.Refresh();
                    System.Threading.Thread.Sleep(1000);
                }
            }
            else if (myGreen.ToString() == strColor)
            {
                if (pnlColor.BackColor != Color.Green)
                {
                    lblColor.Text = "绿色";
                    lblColor.Refresh();
                    pnlColor.BackColor = Color.Green;
                    pnlColor.Refresh();
                    System.Threading.Thread.Sleep(1000);
                }
            }
            else
            {
                if (pnlColor.BackColor != Color.Black)
                {
                    lblColor.Text = "未检测到颜色";
                    lblColor.Refresh();

                    pnlColor.BackColor = Color.Black;
                    pnlColor.Refresh();
                    System.Threading.Thread.Sleep(1000);
                }
            }

        }

        //private void button2_Click(object sender, EventArgs e)
        //{
        //    Read();
        //}

        private void port_DataReceived()
        {
            while (_serialPort.BytesToRead > 0) // while there is data to read in the input buffer
            {
                //byte[] buffer = new byte[_serialPort.BytesToRead]; // create a byte array to hold the data
                byte[] buffer = new byte[3]; // create a byte array to hold the data
                _serialPort.Read(buffer, 0, buffer.Length); // reads the data into the array
                Console.WriteLine(buffer[1].ToString()); // displays the data as ASCII text
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            timer1.Stop();
            receiveData();
        }

        private void btGetColor_Click(object sender, EventArgs e)
        {
            if (!_serialPort.IsOpen)
            {
                MessageBox.Show("请打开串行口.");
                return;
            }

            if (timer1.Enabled)
            {
                _resume = false;
                timer1.Stop();
                btGetColor.Text = "开始颜色检测";
                btGetColor.BackColor = Color.Green;
            }
            else
            {
                //清除串口的缓存，再接收数据
                if (_serialPort.IsOpen)
                {
                    _serialPort.DiscardInBuffer();
                }

                _resume = true;
                timer1.Start();
                btGetColor.Text = "停止颜色检测";
                btGetColor.BackColor = Color.Red;
            }
        }

    }
}
