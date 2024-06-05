namespace MechanicalArmControl
{
    partial class frmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label1 = new System.Windows.Forms.Label();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.panel2 = new System.Windows.Forms.Panel();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnOpen = new System.Windows.Forms.Button();
            this.button3 = new System.Windows.Forms.Button();
            this.button保存设置 = new System.Windows.Forms.Button();
            this.cmbStopBits = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.cmbParity = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.cmbDataBits = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.cmbBaudRate = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cmbPortName = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.panel3 = new System.Windows.Forms.Panel();
            this.label8 = new System.Windows.Forms.Label();
            this.lblColor = new System.Windows.Forms.Label();
            this.pnlColor = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.btJoint2ForwardRotate = new System.Windows.Forms.Button();
            this.btJoint2Reverse = new System.Windows.Forms.Button();
            this.btJoint1ForwardRotate = new System.Windows.Forms.Button();
            this.btJoint1Reverse = new System.Windows.Forms.Button();
            this.btRetractClaw = new System.Windows.Forms.Button();
            this.btOpenClaw = new System.Windows.Forms.Button();
            this.btBaseForwardRotate = new System.Windows.Forms.Button();
            this.btBaseReverse = new System.Windows.Forms.Button();
            this.btRight = new System.Windows.Forms.Button();
            this.btLeft = new System.Windows.Forms.Button();
            this.btRetreat = new System.Windows.Forms.Button();
            this.btForward = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.btGetColor = new System.Windows.Forms.Button();
            this.tableLayoutPanel1.SuspendLayout();
            this.panel1.SuspendLayout();
            this.tableLayoutPanel2.SuspendLayout();
            this.panel2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.panel1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 1);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 70F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(1218, 585);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.SystemColors.Window;
            this.panel1.Controls.Add(this.label1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(3, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(1212, 64);
            this.panel1.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 16.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(34, 19);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(155, 32);
            this.label1.TabIndex = 0;
            this.label1.Text = "机械臂控制";
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 2;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 350F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Controls.Add(this.panel2, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.panel3, 1, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 73);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(1212, 509);
            this.tableLayoutPanel2.TabIndex = 1;
            // 
            // panel2
            // 
            this.panel2.BackColor = System.Drawing.Color.LightCyan;
            this.panel2.Controls.Add(this.groupBox1);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(3, 3);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(344, 503);
            this.panel2.TabIndex = 0;
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Ivory;
            this.groupBox1.Controls.Add(this.btnOpen);
            this.groupBox1.Controls.Add(this.button3);
            this.groupBox1.Controls.Add(this.button保存设置);
            this.groupBox1.Controls.Add(this.cmbStopBits);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.cmbParity);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.cmbDataBits);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.cmbBaudRate);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.cmbPortName);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox1.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.Location = new System.Drawing.Point(0, 0);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(5, 6, 5, 6);
            this.groupBox1.Size = new System.Drawing.Size(344, 503);
            this.groupBox1.TabIndex = 2;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "串口设置";
            // 
            // btnOpen
            // 
            this.btnOpen.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            this.btnOpen.Location = new System.Drawing.Point(24, 354);
            this.btnOpen.Margin = new System.Windows.Forms.Padding(4);
            this.btnOpen.Name = "btnOpen";
            this.btnOpen.Size = new System.Drawing.Size(255, 54);
            this.btnOpen.TabIndex = 2;
            this.btnOpen.Text = "打开";
            this.btnOpen.UseVisualStyleBackColor = false;
            this.btnOpen.Click += new System.EventHandler(this.btnOpen_Click);
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(24, 354);
            this.button3.Margin = new System.Windows.Forms.Padding(4);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(135, 54);
            this.button3.TabIndex = 2;
            this.button3.Text = "保存设置";
            this.button3.UseVisualStyleBackColor = true;
            // 
            // button保存设置
            // 
            this.button保存设置.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.button保存设置.Location = new System.Drawing.Point(24, 429);
            this.button保存设置.Margin = new System.Windows.Forms.Padding(4);
            this.button保存设置.Name = "button保存设置";
            this.button保存设置.Size = new System.Drawing.Size(135, 54);
            this.button保存设置.TabIndex = 2;
            this.button保存设置.Text = "保存设置";
            this.button保存设置.UseVisualStyleBackColor = false;
            this.button保存设置.Visible = false;
            // 
            // cmbStopBits
            // 
            this.cmbStopBits.BackColor = System.Drawing.Color.White;
            this.cmbStopBits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbStopBits.FormattingEnabled = true;
            this.cmbStopBits.Location = new System.Drawing.Point(119, 284);
            this.cmbStopBits.Margin = new System.Windows.Forms.Padding(4);
            this.cmbStopBits.Name = "cmbStopBits";
            this.cmbStopBits.Size = new System.Drawing.Size(160, 28);
            this.cmbStopBits.TabIndex = 1;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label5.Location = new System.Drawing.Point(13, 294);
            this.label5.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(72, 20);
            this.label5.TabIndex = 0;
            this.label5.Text = "停止位";
            // 
            // cmbParity
            // 
            this.cmbParity.BackColor = System.Drawing.Color.White;
            this.cmbParity.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbParity.FormattingEnabled = true;
            this.cmbParity.Location = new System.Drawing.Point(119, 214);
            this.cmbParity.Margin = new System.Windows.Forms.Padding(4);
            this.cmbParity.Name = "cmbParity";
            this.cmbParity.Size = new System.Drawing.Size(160, 28);
            this.cmbParity.TabIndex = 1;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label4.Location = new System.Drawing.Point(13, 225);
            this.label4.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(72, 20);
            this.label4.TabIndex = 0;
            this.label4.Text = "校验位";
            // 
            // cmbDataBits
            // 
            this.cmbDataBits.BackColor = System.Drawing.Color.White;
            this.cmbDataBits.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbDataBits.FormattingEnabled = true;
            this.cmbDataBits.Location = new System.Drawing.Point(119, 156);
            this.cmbDataBits.Margin = new System.Windows.Forms.Padding(4);
            this.cmbDataBits.Name = "cmbDataBits";
            this.cmbDataBits.Size = new System.Drawing.Size(160, 28);
            this.cmbDataBits.TabIndex = 1;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label3.Location = new System.Drawing.Point(13, 160);
            this.label3.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(72, 20);
            this.label3.TabIndex = 0;
            this.label3.Text = "数据位";
            // 
            // cmbBaudRate
            // 
            this.cmbBaudRate.BackColor = System.Drawing.Color.White;
            this.cmbBaudRate.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbBaudRate.FormattingEnabled = true;
            this.cmbBaudRate.Location = new System.Drawing.Point(119, 97);
            this.cmbBaudRate.Margin = new System.Windows.Forms.Padding(4);
            this.cmbBaudRate.Name = "cmbBaudRate";
            this.cmbBaudRate.Size = new System.Drawing.Size(160, 28);
            this.cmbBaudRate.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label2.Location = new System.Drawing.Point(13, 101);
            this.label2.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(72, 20);
            this.label2.TabIndex = 0;
            this.label2.Text = "波特率";
            // 
            // cmbPortName
            // 
            this.cmbPortName.AccessibleRole = System.Windows.Forms.AccessibleRole.None;
            this.cmbPortName.BackColor = System.Drawing.Color.White;
            this.cmbPortName.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.cmbPortName.FormattingEnabled = true;
            this.cmbPortName.Location = new System.Drawing.Point(119, 42);
            this.cmbPortName.Margin = new System.Windows.Forms.Padding(4);
            this.cmbPortName.Name = "cmbPortName";
            this.cmbPortName.Size = new System.Drawing.Size(160, 28);
            this.cmbPortName.TabIndex = 1;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("SimSun", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label6.Location = new System.Drawing.Point(13, 45);
            this.label6.Margin = new System.Windows.Forms.Padding(5, 0, 5, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(72, 20);
            this.label6.TabIndex = 0;
            this.label6.Text = "端口号";
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.btGetColor);
            this.panel3.Controls.Add(this.label8);
            this.panel3.Controls.Add(this.lblColor);
            this.panel3.Controls.Add(this.pnlColor);
            this.panel3.Controls.Add(this.button1);
            this.panel3.Controls.Add(this.btJoint2ForwardRotate);
            this.panel3.Controls.Add(this.btJoint2Reverse);
            this.panel3.Controls.Add(this.btJoint1ForwardRotate);
            this.panel3.Controls.Add(this.btJoint1Reverse);
            this.panel3.Controls.Add(this.btRetractClaw);
            this.panel3.Controls.Add(this.btOpenClaw);
            this.panel3.Controls.Add(this.btBaseForwardRotate);
            this.panel3.Controls.Add(this.btBaseReverse);
            this.panel3.Controls.Add(this.btRight);
            this.panel3.Controls.Add(this.btLeft);
            this.panel3.Controls.Add(this.btRetreat);
            this.panel3.Controls.Add(this.btForward);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(353, 3);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(856, 503);
            this.panel3.TabIndex = 1;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(570, 94);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(92, 17);
            this.label8.TabIndex = 15;
            this.label8.Text = "检测到的颜色";
            // 
            // lblColor
            // 
            this.lblColor.Location = new System.Drawing.Point(570, 117);
            this.lblColor.Name = "lblColor";
            this.lblColor.Size = new System.Drawing.Size(201, 23);
            this.lblColor.TabIndex = 14;
            this.lblColor.Text = "...";
            // 
            // pnlColor
            // 
            this.pnlColor.BackColor = System.Drawing.Color.Black;
            this.pnlColor.Location = new System.Drawing.Point(570, 148);
            this.pnlColor.Name = "pnlColor";
            this.pnlColor.Size = new System.Drawing.Size(201, 294);
            this.pnlColor.TabIndex = 13;
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.LightCyan;
            this.button1.Location = new System.Drawing.Point(215, 151);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(108, 39);
            this.button1.TabIndex = 12;
            this.button1.Text = "停止";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // btJoint2ForwardRotate
            // 
            this.btJoint2ForwardRotate.Location = new System.Drawing.Point(354, 355);
            this.btJoint2ForwardRotate.Name = "btJoint2ForwardRotate";
            this.btJoint2ForwardRotate.Size = new System.Drawing.Size(108, 39);
            this.btJoint2ForwardRotate.TabIndex = 11;
            this.btJoint2ForwardRotate.Text = "关节2正转";
            this.btJoint2ForwardRotate.UseVisualStyleBackColor = true;
            this.btJoint2ForwardRotate.Click += new System.EventHandler(this.btJoint2ForwardRotate_Click);
            // 
            // btJoint2Reverse
            // 
            this.btJoint2Reverse.Location = new System.Drawing.Point(70, 355);
            this.btJoint2Reverse.Name = "btJoint2Reverse";
            this.btJoint2Reverse.Size = new System.Drawing.Size(108, 39);
            this.btJoint2Reverse.TabIndex = 10;
            this.btJoint2Reverse.Text = "关节2反转";
            this.btJoint2Reverse.UseVisualStyleBackColor = true;
            this.btJoint2Reverse.Click += new System.EventHandler(this.btJoint2Reverse_Click);
            // 
            // btJoint1ForwardRotate
            // 
            this.btJoint1ForwardRotate.Location = new System.Drawing.Point(354, 305);
            this.btJoint1ForwardRotate.Name = "btJoint1ForwardRotate";
            this.btJoint1ForwardRotate.Size = new System.Drawing.Size(108, 39);
            this.btJoint1ForwardRotate.TabIndex = 9;
            this.btJoint1ForwardRotate.Text = "关节1正转";
            this.btJoint1ForwardRotate.UseVisualStyleBackColor = true;
            this.btJoint1ForwardRotate.Click += new System.EventHandler(this.btJoint1ForwardRotate_Click);
            // 
            // btJoint1Reverse
            // 
            this.btJoint1Reverse.Location = new System.Drawing.Point(70, 305);
            this.btJoint1Reverse.Name = "btJoint1Reverse";
            this.btJoint1Reverse.Size = new System.Drawing.Size(108, 39);
            this.btJoint1Reverse.TabIndex = 8;
            this.btJoint1Reverse.Text = "关节1反转";
            this.btJoint1Reverse.UseVisualStyleBackColor = true;
            this.btJoint1Reverse.Click += new System.EventHandler(this.btJoint1Reverse_Click);
            // 
            // btRetractClaw
            // 
            this.btRetractClaw.Location = new System.Drawing.Point(354, 403);
            this.btRetractClaw.Name = "btRetractClaw";
            this.btRetractClaw.Size = new System.Drawing.Size(108, 39);
            this.btRetractClaw.TabIndex = 7;
            this.btRetractClaw.Text = "收爪";
            this.btRetractClaw.UseVisualStyleBackColor = true;
            this.btRetractClaw.Click += new System.EventHandler(this.btRetractClaw_Click);
            // 
            // btOpenClaw
            // 
            this.btOpenClaw.Location = new System.Drawing.Point(70, 403);
            this.btOpenClaw.Name = "btOpenClaw";
            this.btOpenClaw.Size = new System.Drawing.Size(108, 39);
            this.btOpenClaw.TabIndex = 6;
            this.btOpenClaw.Text = "开爪";
            this.btOpenClaw.UseVisualStyleBackColor = true;
            this.btOpenClaw.Click += new System.EventHandler(this.btOpenClaw_Click);
            // 
            // btBaseForwardRotate
            // 
            this.btBaseForwardRotate.Location = new System.Drawing.Point(354, 257);
            this.btBaseForwardRotate.Name = "btBaseForwardRotate";
            this.btBaseForwardRotate.Size = new System.Drawing.Size(108, 39);
            this.btBaseForwardRotate.TabIndex = 5;
            this.btBaseForwardRotate.Text = "底座正转";
            this.btBaseForwardRotate.UseVisualStyleBackColor = true;
            this.btBaseForwardRotate.Click += new System.EventHandler(this.btBaseForwardRotate_Click);
            // 
            // btBaseReverse
            // 
            this.btBaseReverse.Location = new System.Drawing.Point(70, 257);
            this.btBaseReverse.Name = "btBaseReverse";
            this.btBaseReverse.Size = new System.Drawing.Size(108, 39);
            this.btBaseReverse.TabIndex = 4;
            this.btBaseReverse.Text = "底座反转";
            this.btBaseReverse.UseVisualStyleBackColor = true;
            this.btBaseReverse.Click += new System.EventHandler(this.btBaseReverse_Click);
            // 
            // btRight
            // 
            this.btRight.Location = new System.Drawing.Point(354, 148);
            this.btRight.Name = "btRight";
            this.btRight.Size = new System.Drawing.Size(108, 39);
            this.btRight.TabIndex = 3;
            this.btRight.Text = "向右";
            this.btRight.UseVisualStyleBackColor = true;
            this.btRight.Click += new System.EventHandler(this.btRight_Click);
            // 
            // btLeft
            // 
            this.btLeft.Location = new System.Drawing.Point(70, 148);
            this.btLeft.Name = "btLeft";
            this.btLeft.Size = new System.Drawing.Size(108, 39);
            this.btLeft.TabIndex = 2;
            this.btLeft.Text = "向左";
            this.btLeft.UseVisualStyleBackColor = true;
            this.btLeft.Click += new System.EventHandler(this.btLeft_Click);
            // 
            // btRetreat
            // 
            this.btRetreat.Location = new System.Drawing.Point(215, 197);
            this.btRetreat.Name = "btRetreat";
            this.btRetreat.Size = new System.Drawing.Size(108, 39);
            this.btRetreat.TabIndex = 1;
            this.btRetreat.Text = "后退";
            this.btRetreat.UseVisualStyleBackColor = true;
            this.btRetreat.Click += new System.EventHandler(this.btRetreat_Click);
            // 
            // btForward
            // 
            this.btForward.BackColor = System.Drawing.Color.LightCyan;
            this.btForward.Location = new System.Drawing.Point(215, 101);
            this.btForward.Name = "btForward";
            this.btForward.Size = new System.Drawing.Size(108, 39);
            this.btForward.TabIndex = 0;
            this.btForward.Text = "前进";
            this.btForward.UseVisualStyleBackColor = false;
            this.btForward.Click += new System.EventHandler(this.btForward_Click);
            // 
            // timer1
            // 
            this.timer1.Interval = 1000;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // btGetColor
            // 
            this.btGetColor.Location = new System.Drawing.Point(570, 45);
            this.btGetColor.Name = "btGetColor";
            this.btGetColor.Size = new System.Drawing.Size(201, 39);
            this.btGetColor.TabIndex = 17;
            this.btGetColor.Text = "开始颜色检测";
            this.btGetColor.UseVisualStyleBackColor = true;
            this.btGetColor.Click += new System.EventHandler(this.btGetColor_Click);
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1218, 585);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "frmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Arm Control";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.frmMain_FormClosed);
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.panel2.ResumeLayout(false);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Button btRight;
        private System.Windows.Forms.Button btLeft;
        private System.Windows.Forms.Button btRetreat;
        private System.Windows.Forms.Button btForward;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnOpen;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.Button button保存设置;
        private System.Windows.Forms.ComboBox cmbStopBits;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox cmbParity;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox cmbDataBits;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox cmbBaudRate;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cmbPortName;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button btBaseForwardRotate;
        private System.Windows.Forms.Button btBaseReverse;
        private System.Windows.Forms.Button btRetractClaw;
        private System.Windows.Forms.Button btOpenClaw;
        private System.Windows.Forms.Button btJoint2ForwardRotate;
        private System.Windows.Forms.Button btJoint2Reverse;
        private System.Windows.Forms.Button btJoint1ForwardRotate;
        private System.Windows.Forms.Button btJoint1Reverse;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Panel pnlColor;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label lblColor;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button btGetColor;
    }
}

