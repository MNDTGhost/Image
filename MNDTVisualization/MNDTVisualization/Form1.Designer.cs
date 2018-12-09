namespace MNDTVisualization
{
    partial class MNDT
    {
        /// <summary>
        /// 設計工具所需的變數。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清除任何使用中的資源。
        /// </summary>
        /// <param name="disposing">如果應該處置 Managed 資源則為 true，否則為 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 設計工具產生的程式碼

        /// <summary>
        /// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
        /// 這個方法的內容。
        /// </summary>
        private void InitializeComponent()
        {
            this.pic_src = new System.Windows.Forms.PictureBox();
            this.pic_pur = new System.Windows.Forms.PictureBox();
            this.btn_RGB2Gray8 = new System.Windows.Forms.Button();
            this.btn_BGR2HSV = new System.Windows.Forms.Button();
            this.btn_HSV2BGR = new System.Windows.Forms.Button();
            this.pic_now = new System.Windows.Forms.PictureBox();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.btn_YCbCr2BGR = new System.Windows.Forms.Button();
            this.btn_BGR2YCbCr = new System.Windows.Forms.Button();
            this.tabPage5 = new System.Windows.Forms.TabPage();
            this.btn_bilateral = new System.Windows.Forms.Button();
            this.btn_median_blur = new System.Windows.Forms.Button();
            this.btn_gauss_blur = new System.Windows.Forms.Button();
            this.btn_blur = new System.Windows.Forms.Button();
            this.tabPage6 = new System.Windows.Forms.TabPage();
            this.btn_meanshift = new System.Windows.Forms.Button();
            this.btn_channel = new System.Windows.Forms.Button();
            this.btn_back_projection = new System.Windows.Forms.Button();
            this.btn_hisogram_equalization = new System.Windows.Forms.Button();
            this.btn_histogram = new System.Windows.Forms.Button();
            this.tabPage7 = new System.Windows.Forms.TabPage();
            this.btn_threshold = new System.Windows.Forms.Button();
            this.tabPage8 = new System.Windows.Forms.TabPage();
            this.btn_affine = new System.Windows.Forms.Button();
            this.btn_pyramid_up = new System.Windows.Forms.Button();
            this.btn_pyramid_down = new System.Windows.Forms.Button();
            this.btn_linear = new System.Windows.Forms.Button();
            this.btn_nearest = new System.Windows.Forms.Button();
            this.btn_vertical = new System.Windows.Forms.Button();
            this.btn_horizontal = new System.Windows.Forms.Button();
            this.tabPage9 = new System.Windows.Forms.TabPage();
            this.btn_hough_circle = new System.Windows.Forms.Button();
            this.btn_hough_lines = new System.Windows.Forms.Button();
            this.btn_sobel_edge = new System.Windows.Forms.Button();
            this.btn_24bit_sobel = new System.Windows.Forms.Button();
            this.tabPage10 = new System.Windows.Forms.TabPage();
            this.btn_histogram_lbp = new System.Windows.Forms.Button();
            this.btn_semb_lbp = new System.Windows.Forms.Button();
            this.btn_mb_lbp = new System.Windows.Forms.Button();
            this.btn_equivalent_lbp = new System.Windows.Forms.Button();
            this.btn_invariant_lbp = new System.Windows.Forms.Button();
            this.btn_circular_lbp = new System.Windows.Forms.Button();
            this.btn_original_lbp = new System.Windows.Forms.Button();
            this.tabPage11 = new System.Windows.Forms.TabPage();
            this.btn_hog_cell_view = new System.Windows.Forms.Button();
            this.btn_hog_block_view = new System.Windows.Forms.Button();
            this.btn_gradient_hog = new System.Windows.Forms.Button();
            this.btn_gamma = new System.Windows.Forms.Button();
            this.tabPage4 = new System.Windows.Forms.TabPage();
            this.btn_test = new System.Windows.Forms.Button();
            this.btn_padding = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.lab_combination = new System.Windows.Forms.Label();
            this.btn_now_pic_init = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.track_hsv_v = new System.Windows.Forms.TrackBar();
            this.numeric_hsv_v = new System.Windows.Forms.NumericUpDown();
            this.numeric_hsv_s = new System.Windows.Forms.NumericUpDown();
            this.numeric_hsv_h = new System.Windows.Forms.NumericUpDown();
            this.label9 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.lab_hsv_h = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.track_hsv_s = new System.Windows.Forms.TrackBar();
            this.label8 = new System.Windows.Forms.Label();
            this.track_hsv_h = new System.Windows.Forms.TrackBar();
            this.label5 = new System.Windows.Forms.Label();
            this.pic_app = new System.Windows.Forms.PictureBox();
            this.label7 = new System.Windows.Forms.Label();
            this.btn_app_pic_init = new System.Windows.Forms.Button();
            this.tabControl2 = new System.Windows.Forms.TabControl();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.tabPage3 = new System.Windows.Forms.TabPage();
            this.numeric_ycbcr_cr = new System.Windows.Forms.NumericUpDown();
            this.label11 = new System.Windows.Forms.Label();
            this.numeric_ycbcr_cb = new System.Windows.Forms.NumericUpDown();
            this.track_ycbcr_cr = new System.Windows.Forms.TrackBar();
            this.numeric_ycbcr_y = new System.Windows.Forms.NumericUpDown();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.track_ycbcr_y = new System.Windows.Forms.TrackBar();
            this.label14 = new System.Windows.Forms.Label();
            this.track_ycbcr_cb = new System.Windows.Forms.TrackBar();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.tabPage12 = new System.Windows.Forms.TabPage();
            this.btn_segment = new System.Windows.Forms.Button();
            this.btn_selective_search = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pic_src)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_pur)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_now)).BeginInit();
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage5.SuspendLayout();
            this.tabPage6.SuspendLayout();
            this.tabPage7.SuspendLayout();
            this.tabPage8.SuspendLayout();
            this.tabPage9.SuspendLayout();
            this.tabPage10.SuspendLayout();
            this.tabPage11.SuspendLayout();
            this.tabPage4.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.track_hsv_v)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_hsv_v)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_hsv_s)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_hsv_h)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.track_hsv_s)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.track_hsv_h)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_app)).BeginInit();
            this.tabControl2.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.tabPage3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_ycbcr_cr)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_ycbcr_cb)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.track_ycbcr_cr)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_ycbcr_y)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.track_ycbcr_y)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.track_ycbcr_cb)).BeginInit();
            this.tabPage12.SuspendLayout();
            this.SuspendLayout();
            // 
            // pic_src
            // 
            this.pic_src.Location = new System.Drawing.Point(12, 124);
            this.pic_src.Name = "pic_src";
            this.pic_src.Size = new System.Drawing.Size(300, 300);
            this.pic_src.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pic_src.TabIndex = 0;
            this.pic_src.TabStop = false;
            // 
            // pic_pur
            // 
            this.pic_pur.Location = new System.Drawing.Point(12, 457);
            this.pic_pur.Name = "pic_pur";
            this.pic_pur.Size = new System.Drawing.Size(300, 300);
            this.pic_pur.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pic_pur.TabIndex = 1;
            this.pic_pur.TabStop = false;
            // 
            // btn_RGB2Gray8
            // 
            this.btn_RGB2Gray8.Location = new System.Drawing.Point(6, 6);
            this.btn_RGB2Gray8.Name = "btn_RGB2Gray8";
            this.btn_RGB2Gray8.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_RGB2Gray8.Size = new System.Drawing.Size(100, 44);
            this.btn_RGB2Gray8.TabIndex = 2;
            this.btn_RGB2Gray8.Text = "8bit灰階";
            this.btn_RGB2Gray8.UseVisualStyleBackColor = true;
            this.btn_RGB2Gray8.Click += new System.EventHandler(this.btn_RGB2Gray8_Click);
            // 
            // btn_BGR2HSV
            // 
            this.btn_BGR2HSV.Location = new System.Drawing.Point(112, 6);
            this.btn_BGR2HSV.Name = "btn_BGR2HSV";
            this.btn_BGR2HSV.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_BGR2HSV.Size = new System.Drawing.Size(100, 44);
            this.btn_BGR2HSV.TabIndex = 3;
            this.btn_BGR2HSV.Text = "BGR->HSV";
            this.btn_BGR2HSV.UseVisualStyleBackColor = true;
            this.btn_BGR2HSV.Click += new System.EventHandler(this.btn_BGR2HSV_Click);
            // 
            // btn_HSV2BGR
            // 
            this.btn_HSV2BGR.Location = new System.Drawing.Point(218, 6);
            this.btn_HSV2BGR.Name = "btn_HSV2BGR";
            this.btn_HSV2BGR.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_HSV2BGR.Size = new System.Drawing.Size(100, 44);
            this.btn_HSV2BGR.TabIndex = 4;
            this.btn_HSV2BGR.Text = "HSV->BGR";
            this.btn_HSV2BGR.UseVisualStyleBackColor = true;
            this.btn_HSV2BGR.Click += new System.EventHandler(this.btn_HSV2BGR_Click);
            // 
            // pic_now
            // 
            this.pic_now.Location = new System.Drawing.Point(350, 124);
            this.pic_now.Name = "pic_now";
            this.pic_now.Size = new System.Drawing.Size(300, 300);
            this.pic_now.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pic_now.TabIndex = 5;
            this.pic_now.TabStop = false;
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage5);
            this.tabControl1.Controls.Add(this.tabPage6);
            this.tabControl1.Controls.Add(this.tabPage7);
            this.tabControl1.Controls.Add(this.tabPage8);
            this.tabControl1.Controls.Add(this.tabPage9);
            this.tabControl1.Controls.Add(this.tabPage10);
            this.tabControl1.Controls.Add(this.tabPage11);
            this.tabControl1.Controls.Add(this.tabPage12);
            this.tabControl1.Controls.Add(this.tabPage4);
            this.tabControl1.Location = new System.Drawing.Point(12, 12);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(987, 100);
            this.tabControl1.TabIndex = 6;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.btn_YCbCr2BGR);
            this.tabPage1.Controls.Add(this.btn_BGR2YCbCr);
            this.tabPage1.Controls.Add(this.btn_RGB2Gray8);
            this.tabPage1.Controls.Add(this.btn_BGR2HSV);
            this.tabPage1.Controls.Add(this.btn_HSV2BGR);
            this.tabPage1.Location = new System.Drawing.Point(4, 25);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(979, 71);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "色彩空間轉換";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // btn_YCbCr2BGR
            // 
            this.btn_YCbCr2BGR.Location = new System.Drawing.Point(460, 6);
            this.btn_YCbCr2BGR.Name = "btn_YCbCr2BGR";
            this.btn_YCbCr2BGR.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_YCbCr2BGR.Size = new System.Drawing.Size(130, 44);
            this.btn_YCbCr2BGR.TabIndex = 6;
            this.btn_YCbCr2BGR.Text = "YCbCr->BGR";
            this.btn_YCbCr2BGR.UseVisualStyleBackColor = true;
            this.btn_YCbCr2BGR.Click += new System.EventHandler(this.btn_YCbCr2BGR_Click);
            // 
            // btn_BGR2YCbCr
            // 
            this.btn_BGR2YCbCr.Location = new System.Drawing.Point(324, 6);
            this.btn_BGR2YCbCr.Name = "btn_BGR2YCbCr";
            this.btn_BGR2YCbCr.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_BGR2YCbCr.Size = new System.Drawing.Size(130, 44);
            this.btn_BGR2YCbCr.TabIndex = 5;
            this.btn_BGR2YCbCr.Text = "BGR->YCbCr";
            this.btn_BGR2YCbCr.UseVisualStyleBackColor = true;
            this.btn_BGR2YCbCr.Click += new System.EventHandler(this.btn_BGR2YCbCr_Click);
            // 
            // tabPage5
            // 
            this.tabPage5.Controls.Add(this.btn_bilateral);
            this.tabPage5.Controls.Add(this.btn_median_blur);
            this.tabPage5.Controls.Add(this.btn_gauss_blur);
            this.tabPage5.Controls.Add(this.btn_blur);
            this.tabPage5.Location = new System.Drawing.Point(4, 25);
            this.tabPage5.Name = "tabPage5";
            this.tabPage5.Size = new System.Drawing.Size(979, 71);
            this.tabPage5.TabIndex = 2;
            this.tabPage5.Text = "平滑處理";
            this.tabPage5.UseVisualStyleBackColor = true;
            // 
            // btn_bilateral
            // 
            this.btn_bilateral.Location = new System.Drawing.Point(324, 6);
            this.btn_bilateral.Name = "btn_bilateral";
            this.btn_bilateral.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_bilateral.Size = new System.Drawing.Size(100, 44);
            this.btn_bilateral.TabIndex = 7;
            this.btn_bilateral.Text = "雙邊濾波";
            this.btn_bilateral.UseVisualStyleBackColor = true;
            this.btn_bilateral.Click += new System.EventHandler(this.btn_bilateral_Click);
            // 
            // btn_median_blur
            // 
            this.btn_median_blur.Location = new System.Drawing.Point(218, 6);
            this.btn_median_blur.Name = "btn_median_blur";
            this.btn_median_blur.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_median_blur.Size = new System.Drawing.Size(100, 44);
            this.btn_median_blur.TabIndex = 6;
            this.btn_median_blur.Text = "中值濾波";
            this.btn_median_blur.UseVisualStyleBackColor = true;
            this.btn_median_blur.Click += new System.EventHandler(this.btn_median_blur_Click);
            // 
            // btn_gauss_blur
            // 
            this.btn_gauss_blur.Location = new System.Drawing.Point(112, 6);
            this.btn_gauss_blur.Name = "btn_gauss_blur";
            this.btn_gauss_blur.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_gauss_blur.Size = new System.Drawing.Size(100, 44);
            this.btn_gauss_blur.TabIndex = 5;
            this.btn_gauss_blur.Text = "高斯平滑";
            this.btn_gauss_blur.UseVisualStyleBackColor = true;
            this.btn_gauss_blur.Click += new System.EventHandler(this.btn_gauss_blur_Click);
            // 
            // btn_blur
            // 
            this.btn_blur.Location = new System.Drawing.Point(6, 6);
            this.btn_blur.Name = "btn_blur";
            this.btn_blur.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_blur.Size = new System.Drawing.Size(100, 44);
            this.btn_blur.TabIndex = 4;
            this.btn_blur.Text = "平滑";
            this.btn_blur.UseVisualStyleBackColor = true;
            this.btn_blur.Click += new System.EventHandler(this.btn_blur_Click);
            // 
            // tabPage6
            // 
            this.tabPage6.Controls.Add(this.btn_meanshift);
            this.tabPage6.Controls.Add(this.btn_channel);
            this.tabPage6.Controls.Add(this.btn_back_projection);
            this.tabPage6.Controls.Add(this.btn_hisogram_equalization);
            this.tabPage6.Controls.Add(this.btn_histogram);
            this.tabPage6.Location = new System.Drawing.Point(4, 25);
            this.tabPage6.Name = "tabPage6";
            this.tabPage6.Size = new System.Drawing.Size(979, 71);
            this.tabPage6.TabIndex = 3;
            this.tabPage6.Text = "直方圖";
            this.tabPage6.UseVisualStyleBackColor = true;
            // 
            // btn_meanshift
            // 
            this.btn_meanshift.Location = new System.Drawing.Point(430, 6);
            this.btn_meanshift.Name = "btn_meanshift";
            this.btn_meanshift.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_meanshift.Size = new System.Drawing.Size(100, 44);
            this.btn_meanshift.TabIndex = 12;
            this.btn_meanshift.Text = "均值飄移";
            this.btn_meanshift.UseVisualStyleBackColor = true;
            this.btn_meanshift.Click += new System.EventHandler(this.btn_meanshift_Click);
            // 
            // btn_channel
            // 
            this.btn_channel.Location = new System.Drawing.Point(218, 6);
            this.btn_channel.Name = "btn_channel";
            this.btn_channel.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_channel.Size = new System.Drawing.Size(100, 44);
            this.btn_channel.TabIndex = 11;
            this.btn_channel.Text = "單個色彩圖像";
            this.btn_channel.UseVisualStyleBackColor = true;
            this.btn_channel.Click += new System.EventHandler(this.btn_channel_Click);
            // 
            // btn_back_projection
            // 
            this.btn_back_projection.Location = new System.Drawing.Point(324, 6);
            this.btn_back_projection.Name = "btn_back_projection";
            this.btn_back_projection.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_back_projection.Size = new System.Drawing.Size(100, 44);
            this.btn_back_projection.TabIndex = 10;
            this.btn_back_projection.Text = "直方圖反投影";
            this.btn_back_projection.UseVisualStyleBackColor = true;
            this.btn_back_projection.Click += new System.EventHandler(this.btn_back_projection_Click);
            // 
            // btn_hisogram_equalization
            // 
            this.btn_hisogram_equalization.Location = new System.Drawing.Point(112, 6);
            this.btn_hisogram_equalization.Name = "btn_hisogram_equalization";
            this.btn_hisogram_equalization.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_hisogram_equalization.Size = new System.Drawing.Size(100, 44);
            this.btn_hisogram_equalization.TabIndex = 9;
            this.btn_hisogram_equalization.Text = "直方圖等化";
            this.btn_hisogram_equalization.UseVisualStyleBackColor = true;
            this.btn_hisogram_equalization.Click += new System.EventHandler(this.btn_hisogram_equalization_Click);
            // 
            // btn_histogram
            // 
            this.btn_histogram.Location = new System.Drawing.Point(6, 6);
            this.btn_histogram.Name = "btn_histogram";
            this.btn_histogram.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_histogram.Size = new System.Drawing.Size(100, 44);
            this.btn_histogram.TabIndex = 8;
            this.btn_histogram.Text = "直方圖";
            this.btn_histogram.UseVisualStyleBackColor = true;
            this.btn_histogram.Click += new System.EventHandler(this.btn_histogram_Click);
            // 
            // tabPage7
            // 
            this.tabPage7.Controls.Add(this.btn_threshold);
            this.tabPage7.Location = new System.Drawing.Point(4, 25);
            this.tabPage7.Name = "tabPage7";
            this.tabPage7.Size = new System.Drawing.Size(979, 71);
            this.tabPage7.TabIndex = 4;
            this.tabPage7.Text = "二值化";
            this.tabPage7.UseVisualStyleBackColor = true;
            // 
            // btn_threshold
            // 
            this.btn_threshold.Location = new System.Drawing.Point(6, 6);
            this.btn_threshold.Name = "btn_threshold";
            this.btn_threshold.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_threshold.Size = new System.Drawing.Size(100, 44);
            this.btn_threshold.TabIndex = 11;
            this.btn_threshold.Text = "二值化";
            this.btn_threshold.UseVisualStyleBackColor = true;
            this.btn_threshold.Click += new System.EventHandler(this.btn_threshold_Click);
            // 
            // tabPage8
            // 
            this.tabPage8.Controls.Add(this.btn_affine);
            this.tabPage8.Controls.Add(this.btn_pyramid_up);
            this.tabPage8.Controls.Add(this.btn_pyramid_down);
            this.tabPage8.Controls.Add(this.btn_linear);
            this.tabPage8.Controls.Add(this.btn_nearest);
            this.tabPage8.Controls.Add(this.btn_vertical);
            this.tabPage8.Controls.Add(this.btn_horizontal);
            this.tabPage8.Location = new System.Drawing.Point(4, 25);
            this.tabPage8.Name = "tabPage8";
            this.tabPage8.Size = new System.Drawing.Size(979, 71);
            this.tabPage8.TabIndex = 5;
            this.tabPage8.Text = "幾何變化";
            this.tabPage8.UseVisualStyleBackColor = true;
            // 
            // btn_affine
            // 
            this.btn_affine.Location = new System.Drawing.Point(642, 6);
            this.btn_affine.Name = "btn_affine";
            this.btn_affine.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_affine.Size = new System.Drawing.Size(100, 44);
            this.btn_affine.TabIndex = 18;
            this.btn_affine.Text = "仿射轉換";
            this.btn_affine.UseVisualStyleBackColor = true;
            this.btn_affine.Click += new System.EventHandler(this.btn_affine_Click);
            // 
            // btn_pyramid_up
            // 
            this.btn_pyramid_up.Location = new System.Drawing.Point(536, 6);
            this.btn_pyramid_up.Name = "btn_pyramid_up";
            this.btn_pyramid_up.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_pyramid_up.Size = new System.Drawing.Size(100, 44);
            this.btn_pyramid_up.TabIndex = 17;
            this.btn_pyramid_up.Text = "金字塔放大";
            this.btn_pyramid_up.UseVisualStyleBackColor = true;
            this.btn_pyramid_up.Click += new System.EventHandler(this.btn_pyramid_up_Click);
            // 
            // btn_pyramid_down
            // 
            this.btn_pyramid_down.Location = new System.Drawing.Point(430, 6);
            this.btn_pyramid_down.Name = "btn_pyramid_down";
            this.btn_pyramid_down.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_pyramid_down.Size = new System.Drawing.Size(100, 44);
            this.btn_pyramid_down.TabIndex = 16;
            this.btn_pyramid_down.Text = "金字塔縮小";
            this.btn_pyramid_down.UseVisualStyleBackColor = true;
            this.btn_pyramid_down.Click += new System.EventHandler(this.btn_pyramid_down_Click);
            // 
            // btn_linear
            // 
            this.btn_linear.Location = new System.Drawing.Point(324, 6);
            this.btn_linear.Name = "btn_linear";
            this.btn_linear.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_linear.Size = new System.Drawing.Size(100, 44);
            this.btn_linear.TabIndex = 15;
            this.btn_linear.Text = "雙線插值";
            this.btn_linear.UseVisualStyleBackColor = true;
            this.btn_linear.Click += new System.EventHandler(this.btn_linear_Click);
            // 
            // btn_nearest
            // 
            this.btn_nearest.Location = new System.Drawing.Point(218, 6);
            this.btn_nearest.Name = "btn_nearest";
            this.btn_nearest.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_nearest.Size = new System.Drawing.Size(100, 44);
            this.btn_nearest.TabIndex = 14;
            this.btn_nearest.Text = "鄰近內插";
            this.btn_nearest.UseVisualStyleBackColor = true;
            this.btn_nearest.Click += new System.EventHandler(this.btn_nearest_Click);
            // 
            // btn_vertical
            // 
            this.btn_vertical.Location = new System.Drawing.Point(112, 6);
            this.btn_vertical.Name = "btn_vertical";
            this.btn_vertical.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_vertical.Size = new System.Drawing.Size(100, 44);
            this.btn_vertical.TabIndex = 13;
            this.btn_vertical.Text = "垂直轉換";
            this.btn_vertical.UseVisualStyleBackColor = true;
            this.btn_vertical.Click += new System.EventHandler(this.btn_vertical_Click);
            // 
            // btn_horizontal
            // 
            this.btn_horizontal.Location = new System.Drawing.Point(6, 6);
            this.btn_horizontal.Name = "btn_horizontal";
            this.btn_horizontal.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_horizontal.Size = new System.Drawing.Size(100, 44);
            this.btn_horizontal.TabIndex = 12;
            this.btn_horizontal.Text = "水平轉換";
            this.btn_horizontal.UseVisualStyleBackColor = true;
            this.btn_horizontal.Click += new System.EventHandler(this.btn_horizontal_Click);
            // 
            // tabPage9
            // 
            this.tabPage9.Controls.Add(this.btn_hough_circle);
            this.tabPage9.Controls.Add(this.btn_hough_lines);
            this.tabPage9.Controls.Add(this.btn_sobel_edge);
            this.tabPage9.Controls.Add(this.btn_24bit_sobel);
            this.tabPage9.Location = new System.Drawing.Point(4, 25);
            this.tabPage9.Name = "tabPage9";
            this.tabPage9.Size = new System.Drawing.Size(979, 71);
            this.tabPage9.TabIndex = 6;
            this.tabPage9.Text = "邊緣偵測";
            this.tabPage9.UseVisualStyleBackColor = true;
            // 
            // btn_hough_circle
            // 
            this.btn_hough_circle.Location = new System.Drawing.Point(324, 6);
            this.btn_hough_circle.Name = "btn_hough_circle";
            this.btn_hough_circle.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_hough_circle.Size = new System.Drawing.Size(100, 44);
            this.btn_hough_circle.TabIndex = 6;
            this.btn_hough_circle.Text = "霍夫找圓";
            this.btn_hough_circle.UseVisualStyleBackColor = true;
            this.btn_hough_circle.Click += new System.EventHandler(this.btn_hough_circle_Click);
            // 
            // btn_hough_lines
            // 
            this.btn_hough_lines.Location = new System.Drawing.Point(218, 6);
            this.btn_hough_lines.Name = "btn_hough_lines";
            this.btn_hough_lines.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_hough_lines.Size = new System.Drawing.Size(100, 44);
            this.btn_hough_lines.TabIndex = 5;
            this.btn_hough_lines.Text = "霍夫找線";
            this.btn_hough_lines.UseVisualStyleBackColor = true;
            this.btn_hough_lines.Click += new System.EventHandler(this.btn_hough_lines_Click);
            // 
            // btn_sobel_edge
            // 
            this.btn_sobel_edge.Location = new System.Drawing.Point(112, 6);
            this.btn_sobel_edge.Name = "btn_sobel_edge";
            this.btn_sobel_edge.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_sobel_edge.Size = new System.Drawing.Size(100, 44);
            this.btn_sobel_edge.TabIndex = 4;
            this.btn_sobel_edge.Text = "邊緣檢測";
            this.btn_sobel_edge.UseVisualStyleBackColor = true;
            this.btn_sobel_edge.Click += new System.EventHandler(this.btn_sobel_edge_Click);
            // 
            // btn_24bit_sobel
            // 
            this.btn_24bit_sobel.Location = new System.Drawing.Point(6, 6);
            this.btn_24bit_sobel.Name = "btn_24bit_sobel";
            this.btn_24bit_sobel.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_24bit_sobel.Size = new System.Drawing.Size(100, 44);
            this.btn_24bit_sobel.TabIndex = 3;
            this.btn_24bit_sobel.Text = "24BitSobel";
            this.btn_24bit_sobel.UseVisualStyleBackColor = true;
            this.btn_24bit_sobel.Click += new System.EventHandler(this.btn_24bit_sobel_Click);
            // 
            // tabPage10
            // 
            this.tabPage10.Controls.Add(this.btn_histogram_lbp);
            this.tabPage10.Controls.Add(this.btn_semb_lbp);
            this.tabPage10.Controls.Add(this.btn_mb_lbp);
            this.tabPage10.Controls.Add(this.btn_equivalent_lbp);
            this.tabPage10.Controls.Add(this.btn_invariant_lbp);
            this.tabPage10.Controls.Add(this.btn_circular_lbp);
            this.tabPage10.Controls.Add(this.btn_original_lbp);
            this.tabPage10.Location = new System.Drawing.Point(4, 25);
            this.tabPage10.Name = "tabPage10";
            this.tabPage10.Size = new System.Drawing.Size(979, 71);
            this.tabPage10.TabIndex = 7;
            this.tabPage10.Text = "LBP";
            this.tabPage10.UseVisualStyleBackColor = true;
            // 
            // btn_histogram_lbp
            // 
            this.btn_histogram_lbp.Location = new System.Drawing.Point(640, 6);
            this.btn_histogram_lbp.Name = "btn_histogram_lbp";
            this.btn_histogram_lbp.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_histogram_lbp.Size = new System.Drawing.Size(100, 44);
            this.btn_histogram_lbp.TabIndex = 10;
            this.btn_histogram_lbp.Text = "直方圖特徵";
            this.btn_histogram_lbp.UseVisualStyleBackColor = true;
            this.btn_histogram_lbp.Click += new System.EventHandler(this.btn_histogram_lbp_Click);
            // 
            // btn_semb_lbp
            // 
            this.btn_semb_lbp.Location = new System.Drawing.Point(536, 6);
            this.btn_semb_lbp.Name = "btn_semb_lbp";
            this.btn_semb_lbp.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_semb_lbp.Size = new System.Drawing.Size(100, 44);
            this.btn_semb_lbp.TabIndex = 9;
            this.btn_semb_lbp.Text = "等價多尺度";
            this.btn_semb_lbp.UseVisualStyleBackColor = true;
            this.btn_semb_lbp.Click += new System.EventHandler(this.btn_semb_lbp_Click);
            // 
            // btn_mb_lbp
            // 
            this.btn_mb_lbp.Location = new System.Drawing.Point(430, 6);
            this.btn_mb_lbp.Name = "btn_mb_lbp";
            this.btn_mb_lbp.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_mb_lbp.Size = new System.Drawing.Size(100, 44);
            this.btn_mb_lbp.TabIndex = 8;
            this.btn_mb_lbp.Text = "多尺度";
            this.btn_mb_lbp.UseVisualStyleBackColor = true;
            this.btn_mb_lbp.Click += new System.EventHandler(this.btn_mb_lbp_Click);
            // 
            // btn_equivalent_lbp
            // 
            this.btn_equivalent_lbp.Location = new System.Drawing.Point(324, 6);
            this.btn_equivalent_lbp.Name = "btn_equivalent_lbp";
            this.btn_equivalent_lbp.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_equivalent_lbp.Size = new System.Drawing.Size(100, 44);
            this.btn_equivalent_lbp.TabIndex = 7;
            this.btn_equivalent_lbp.Text = "等價";
            this.btn_equivalent_lbp.UseVisualStyleBackColor = true;
            this.btn_equivalent_lbp.Click += new System.EventHandler(this.btn_equivalent_lbp_Click);
            // 
            // btn_invariant_lbp
            // 
            this.btn_invariant_lbp.Location = new System.Drawing.Point(218, 6);
            this.btn_invariant_lbp.Name = "btn_invariant_lbp";
            this.btn_invariant_lbp.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_invariant_lbp.Size = new System.Drawing.Size(100, 44);
            this.btn_invariant_lbp.TabIndex = 6;
            this.btn_invariant_lbp.Text = "旋轉不變";
            this.btn_invariant_lbp.UseVisualStyleBackColor = true;
            this.btn_invariant_lbp.Click += new System.EventHandler(this.btn_invariant_lbp_Click);
            // 
            // btn_circular_lbp
            // 
            this.btn_circular_lbp.Location = new System.Drawing.Point(112, 6);
            this.btn_circular_lbp.Name = "btn_circular_lbp";
            this.btn_circular_lbp.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_circular_lbp.Size = new System.Drawing.Size(100, 44);
            this.btn_circular_lbp.TabIndex = 5;
            this.btn_circular_lbp.Text = "圓形";
            this.btn_circular_lbp.UseVisualStyleBackColor = true;
            this.btn_circular_lbp.Click += new System.EventHandler(this.btn_circular_lbp_Click);
            // 
            // btn_original_lbp
            // 
            this.btn_original_lbp.Location = new System.Drawing.Point(6, 6);
            this.btn_original_lbp.Name = "btn_original_lbp";
            this.btn_original_lbp.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_original_lbp.Size = new System.Drawing.Size(100, 44);
            this.btn_original_lbp.TabIndex = 4;
            this.btn_original_lbp.Text = "原始";
            this.btn_original_lbp.UseVisualStyleBackColor = true;
            this.btn_original_lbp.Click += new System.EventHandler(this.btn_original_lbp_Click);
            // 
            // tabPage11
            // 
            this.tabPage11.Controls.Add(this.btn_hog_cell_view);
            this.tabPage11.Controls.Add(this.btn_hog_block_view);
            this.tabPage11.Controls.Add(this.btn_gradient_hog);
            this.tabPage11.Controls.Add(this.btn_gamma);
            this.tabPage11.Location = new System.Drawing.Point(4, 25);
            this.tabPage11.Name = "tabPage11";
            this.tabPage11.Size = new System.Drawing.Size(979, 71);
            this.tabPage11.TabIndex = 8;
            this.tabPage11.Text = "HOG";
            this.tabPage11.UseVisualStyleBackColor = true;
            // 
            // btn_hog_cell_view
            // 
            this.btn_hog_cell_view.Location = new System.Drawing.Point(218, 6);
            this.btn_hog_cell_view.Name = "btn_hog_cell_view";
            this.btn_hog_cell_view.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_hog_cell_view.Size = new System.Drawing.Size(100, 44);
            this.btn_hog_cell_view.TabIndex = 6;
            this.btn_hog_cell_view.Text = "Cell可視化";
            this.btn_hog_cell_view.UseVisualStyleBackColor = true;
            this.btn_hog_cell_view.Click += new System.EventHandler(this.btn_hog_cell_view_Click);
            // 
            // btn_hog_block_view
            // 
            this.btn_hog_block_view.Location = new System.Drawing.Point(324, 6);
            this.btn_hog_block_view.Name = "btn_hog_block_view";
            this.btn_hog_block_view.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_hog_block_view.Size = new System.Drawing.Size(100, 44);
            this.btn_hog_block_view.TabIndex = 5;
            this.btn_hog_block_view.Text = "Block可視化";
            this.btn_hog_block_view.UseVisualStyleBackColor = true;
            this.btn_hog_block_view.Click += new System.EventHandler(this.btn_hog_block_view_Click);
            // 
            // btn_gradient_hog
            // 
            this.btn_gradient_hog.Location = new System.Drawing.Point(112, 6);
            this.btn_gradient_hog.Name = "btn_gradient_hog";
            this.btn_gradient_hog.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_gradient_hog.Size = new System.Drawing.Size(100, 44);
            this.btn_gradient_hog.TabIndex = 4;
            this.btn_gradient_hog.Text = "梯度";
            this.btn_gradient_hog.UseVisualStyleBackColor = true;
            this.btn_gradient_hog.Click += new System.EventHandler(this.btn_gradient_hog_Click);
            // 
            // btn_gamma
            // 
            this.btn_gamma.Location = new System.Drawing.Point(6, 6);
            this.btn_gamma.Name = "btn_gamma";
            this.btn_gamma.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_gamma.Size = new System.Drawing.Size(100, 44);
            this.btn_gamma.TabIndex = 3;
            this.btn_gamma.Text = "Gamma";
            this.btn_gamma.UseVisualStyleBackColor = true;
            this.btn_gamma.Click += new System.EventHandler(this.btn_gamma_Click);
            // 
            // tabPage4
            // 
            this.tabPage4.Controls.Add(this.btn_test);
            this.tabPage4.Controls.Add(this.btn_padding);
            this.tabPage4.Location = new System.Drawing.Point(4, 25);
            this.tabPage4.Name = "tabPage4";
            this.tabPage4.Size = new System.Drawing.Size(979, 71);
            this.tabPage4.TabIndex = 1;
            this.tabPage4.Text = "測試";
            this.tabPage4.UseVisualStyleBackColor = true;
            // 
            // btn_test
            // 
            this.btn_test.Location = new System.Drawing.Point(112, 6);
            this.btn_test.Name = "btn_test";
            this.btn_test.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_test.Size = new System.Drawing.Size(100, 44);
            this.btn_test.TabIndex = 4;
            this.btn_test.Text = "測試";
            this.btn_test.UseVisualStyleBackColor = true;
            this.btn_test.Click += new System.EventHandler(this.btn_test_Click);
            // 
            // btn_padding
            // 
            this.btn_padding.Location = new System.Drawing.Point(6, 6);
            this.btn_padding.Name = "btn_padding";
            this.btn_padding.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_padding.Size = new System.Drawing.Size(100, 44);
            this.btn_padding.TabIndex = 3;
            this.btn_padding.Text = "填充";
            this.btn_padding.UseVisualStyleBackColor = true;
            this.btn_padding.Click += new System.EventHandler(this.btn_padding_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(133, 427);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(37, 15);
            this.label1.TabIndex = 7;
            this.label1.Text = "原圖";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(133, 760);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(82, 15);
            this.label2.TabIndex = 8;
            this.label2.Text = "原圖處理後";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(490, 427);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(37, 15);
            this.label3.TabIndex = 9;
            this.label3.Text = "組合";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(662, 124);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(82, 15);
            this.label4.TabIndex = 10;
            this.label4.Text = "現在組合：";
            // 
            // lab_combination
            // 
            this.lab_combination.AutoSize = true;
            this.lab_combination.Location = new System.Drawing.Point(3, 0);
            this.lab_combination.Name = "lab_combination";
            this.lab_combination.Size = new System.Drawing.Size(0, 15);
            this.lab_combination.TabIndex = 11;
            // 
            // btn_now_pic_init
            // 
            this.btn_now_pic_init.Location = new System.Drawing.Point(659, 380);
            this.btn_now_pic_init.Name = "btn_now_pic_init";
            this.btn_now_pic_init.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_now_pic_init.Size = new System.Drawing.Size(158, 44);
            this.btn_now_pic_init.TabIndex = 12;
            this.btn_now_pic_init.Text = "組合初始化";
            this.btn_now_pic_init.UseVisualStyleBackColor = true;
            this.btn_now_pic_init.Click += new System.EventHandler(this.btn_now_pic_init_Click);
            // 
            // panel1
            // 
            this.panel1.AutoScroll = true;
            this.panel1.Controls.Add(this.lab_combination);
            this.panel1.Location = new System.Drawing.Point(659, 142);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(158, 232);
            this.panel1.TabIndex = 13;
            // 
            // track_hsv_v
            // 
            this.track_hsv_v.Location = new System.Drawing.Point(63, 130);
            this.track_hsv_v.Maximum = 100;
            this.track_hsv_v.Name = "track_hsv_v";
            this.track_hsv_v.Size = new System.Drawing.Size(176, 56);
            this.track_hsv_v.TabIndex = 14;
            this.track_hsv_v.Value = 50;
            this.track_hsv_v.Scroll += new System.EventHandler(this.track_hsv_Scroll);
            // 
            // numeric_hsv_v
            // 
            this.numeric_hsv_v.Location = new System.Drawing.Point(245, 128);
            this.numeric_hsv_v.Name = "numeric_hsv_v";
            this.numeric_hsv_v.Size = new System.Drawing.Size(59, 25);
            this.numeric_hsv_v.TabIndex = 30;
            this.numeric_hsv_v.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numeric_hsv_v.ValueChanged += new System.EventHandler(this.numeric_hsv_ValueChanged);
            // 
            // numeric_hsv_s
            // 
            this.numeric_hsv_s.Location = new System.Drawing.Point(245, 68);
            this.numeric_hsv_s.Name = "numeric_hsv_s";
            this.numeric_hsv_s.Size = new System.Drawing.Size(59, 25);
            this.numeric_hsv_s.TabIndex = 29;
            this.numeric_hsv_s.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numeric_hsv_s.ValueChanged += new System.EventHandler(this.numeric_hsv_ValueChanged);
            // 
            // numeric_hsv_h
            // 
            this.numeric_hsv_h.Location = new System.Drawing.Point(245, 8);
            this.numeric_hsv_h.Name = "numeric_hsv_h";
            this.numeric_hsv_h.Size = new System.Drawing.Size(59, 25);
            this.numeric_hsv_h.TabIndex = 28;
            this.numeric_hsv_h.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numeric_hsv_h.ValueChanged += new System.EventHandler(this.numeric_hsv_ValueChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(310, 130);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(19, 15);
            this.label9.TabIndex = 24;
            this.label9.Text = "%";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(310, 70);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(19, 15);
            this.label6.TabIndex = 23;
            this.label6.Text = "%";
            // 
            // lab_hsv_h
            // 
            this.lab_hsv_h.AutoSize = true;
            this.lab_hsv_h.Location = new System.Drawing.Point(310, 10);
            this.lab_hsv_h.Name = "lab_hsv_h";
            this.lab_hsv_h.Size = new System.Drawing.Size(19, 15);
            this.lab_hsv_h.TabIndex = 22;
            this.lab_hsv_h.Text = "%";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(5, 70);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(52, 15);
            this.label10.TabIndex = 21;
            this.label10.Text = "飽和度";
            // 
            // track_hsv_s
            // 
            this.track_hsv_s.Location = new System.Drawing.Point(63, 68);
            this.track_hsv_s.Maximum = 100;
            this.track_hsv_s.Name = "track_hsv_s";
            this.track_hsv_s.Size = new System.Drawing.Size(176, 56);
            this.track_hsv_s.TabIndex = 20;
            this.track_hsv_s.Value = 50;
            this.track_hsv_s.Scroll += new System.EventHandler(this.track_hsv_Scroll);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(20, 10);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(37, 15);
            this.label8.TabIndex = 18;
            this.label8.Text = "色相";
            // 
            // track_hsv_h
            // 
            this.track_hsv_h.Location = new System.Drawing.Point(63, 6);
            this.track_hsv_h.Maximum = 100;
            this.track_hsv_h.Name = "track_hsv_h";
            this.track_hsv_h.Size = new System.Drawing.Size(176, 56);
            this.track_hsv_h.TabIndex = 17;
            this.track_hsv_h.Value = 50;
            this.track_hsv_h.Scroll += new System.EventHandler(this.track_hsv_Scroll);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(20, 130);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(37, 15);
            this.label5.TabIndex = 15;
            this.label5.Text = "明度";
            // 
            // pic_app
            // 
            this.pic_app.Location = new System.Drawing.Point(350, 457);
            this.pic_app.Name = "pic_app";
            this.pic_app.Size = new System.Drawing.Size(300, 300);
            this.pic_app.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.pic_app.TabIndex = 16;
            this.pic_app.TabStop = false;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(475, 760);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(37, 15);
            this.label7.TabIndex = 17;
            this.label7.Text = "應用";
            // 
            // btn_app_pic_init
            // 
            this.btn_app_pic_init.Location = new System.Drawing.Point(659, 713);
            this.btn_app_pic_init.Name = "btn_app_pic_init";
            this.btn_app_pic_init.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_app_pic_init.Size = new System.Drawing.Size(158, 44);
            this.btn_app_pic_init.TabIndex = 18;
            this.btn_app_pic_init.Text = "應用初始化";
            this.btn_app_pic_init.UseVisualStyleBackColor = true;
            this.btn_app_pic_init.Click += new System.EventHandler(this.btn_app_pic_init_Click);
            // 
            // tabControl2
            // 
            this.tabControl2.Controls.Add(this.tabPage2);
            this.tabControl2.Controls.Add(this.tabPage3);
            this.tabControl2.Location = new System.Drawing.Point(656, 457);
            this.tabControl2.Name = "tabControl2";
            this.tabControl2.SelectedIndex = 0;
            this.tabControl2.Size = new System.Drawing.Size(347, 250);
            this.tabControl2.TabIndex = 19;
            // 
            // tabPage2
            // 
            this.tabPage2.BackColor = System.Drawing.Color.White;
            this.tabPage2.Controls.Add(this.numeric_hsv_v);
            this.tabPage2.Controls.Add(this.label8);
            this.tabPage2.Controls.Add(this.numeric_hsv_s);
            this.tabPage2.Controls.Add(this.track_hsv_v);
            this.tabPage2.Controls.Add(this.numeric_hsv_h);
            this.tabPage2.Controls.Add(this.label5);
            this.tabPage2.Controls.Add(this.label9);
            this.tabPage2.Controls.Add(this.track_hsv_h);
            this.tabPage2.Controls.Add(this.label6);
            this.tabPage2.Controls.Add(this.track_hsv_s);
            this.tabPage2.Controls.Add(this.lab_hsv_h);
            this.tabPage2.Controls.Add(this.label10);
            this.tabPage2.Location = new System.Drawing.Point(4, 25);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(339, 221);
            this.tabPage2.TabIndex = 0;
            this.tabPage2.Text = "HSV";
            // 
            // tabPage3
            // 
            this.tabPage3.Controls.Add(this.numeric_ycbcr_cr);
            this.tabPage3.Controls.Add(this.label11);
            this.tabPage3.Controls.Add(this.numeric_ycbcr_cb);
            this.tabPage3.Controls.Add(this.track_ycbcr_cr);
            this.tabPage3.Controls.Add(this.numeric_ycbcr_y);
            this.tabPage3.Controls.Add(this.label12);
            this.tabPage3.Controls.Add(this.label13);
            this.tabPage3.Controls.Add(this.track_ycbcr_y);
            this.tabPage3.Controls.Add(this.label14);
            this.tabPage3.Controls.Add(this.track_ycbcr_cb);
            this.tabPage3.Controls.Add(this.label15);
            this.tabPage3.Controls.Add(this.label16);
            this.tabPage3.Location = new System.Drawing.Point(4, 25);
            this.tabPage3.Name = "tabPage3";
            this.tabPage3.Size = new System.Drawing.Size(339, 221);
            this.tabPage3.TabIndex = 1;
            this.tabPage3.Text = "YCbCr";
            this.tabPage3.UseVisualStyleBackColor = true;
            // 
            // numeric_ycbcr_cr
            // 
            this.numeric_ycbcr_cr.Location = new System.Drawing.Point(245, 128);
            this.numeric_ycbcr_cr.Name = "numeric_ycbcr_cr";
            this.numeric_ycbcr_cr.Size = new System.Drawing.Size(59, 25);
            this.numeric_ycbcr_cr.TabIndex = 42;
            this.numeric_ycbcr_cr.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numeric_ycbcr_cr.ValueChanged += new System.EventHandler(this.numeric_ycbcr_ValueChanged);
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(20, 10);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(37, 15);
            this.label11.TabIndex = 34;
            this.label11.Text = "光度";
            // 
            // numeric_ycbcr_cb
            // 
            this.numeric_ycbcr_cb.Location = new System.Drawing.Point(245, 68);
            this.numeric_ycbcr_cb.Name = "numeric_ycbcr_cb";
            this.numeric_ycbcr_cb.Size = new System.Drawing.Size(59, 25);
            this.numeric_ycbcr_cb.TabIndex = 41;
            this.numeric_ycbcr_cb.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numeric_ycbcr_cb.ValueChanged += new System.EventHandler(this.numeric_ycbcr_ValueChanged);
            // 
            // track_ycbcr_cr
            // 
            this.track_ycbcr_cr.BackColor = System.Drawing.Color.White;
            this.track_ycbcr_cr.Location = new System.Drawing.Point(63, 130);
            this.track_ycbcr_cr.Maximum = 100;
            this.track_ycbcr_cr.Name = "track_ycbcr_cr";
            this.track_ycbcr_cr.Size = new System.Drawing.Size(176, 56);
            this.track_ycbcr_cr.TabIndex = 31;
            this.track_ycbcr_cr.Value = 50;
            this.track_ycbcr_cr.Scroll += new System.EventHandler(this.track_ycbcr_Scroll);
            // 
            // numeric_ycbcr_y
            // 
            this.numeric_ycbcr_y.Location = new System.Drawing.Point(245, 8);
            this.numeric_ycbcr_y.Name = "numeric_ycbcr_y";
            this.numeric_ycbcr_y.Size = new System.Drawing.Size(59, 25);
            this.numeric_ycbcr_y.TabIndex = 40;
            this.numeric_ycbcr_y.Value = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numeric_ycbcr_y.ValueChanged += new System.EventHandler(this.numeric_ycbcr_ValueChanged);
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(20, 130);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(37, 15);
            this.label12.TabIndex = 32;
            this.label12.Text = "紅綠";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(310, 130);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(19, 15);
            this.label13.TabIndex = 39;
            this.label13.Text = "%";
            // 
            // track_ycbcr_y
            // 
            this.track_ycbcr_y.BackColor = System.Drawing.Color.White;
            this.track_ycbcr_y.Location = new System.Drawing.Point(63, 6);
            this.track_ycbcr_y.Maximum = 100;
            this.track_ycbcr_y.Name = "track_ycbcr_y";
            this.track_ycbcr_y.Size = new System.Drawing.Size(176, 56);
            this.track_ycbcr_y.TabIndex = 33;
            this.track_ycbcr_y.Value = 50;
            this.track_ycbcr_y.Scroll += new System.EventHandler(this.track_ycbcr_Scroll);
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(310, 70);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(19, 15);
            this.label14.TabIndex = 38;
            this.label14.Text = "%";
            // 
            // track_ycbcr_cb
            // 
            this.track_ycbcr_cb.BackColor = System.Drawing.Color.White;
            this.track_ycbcr_cb.Location = new System.Drawing.Point(63, 68);
            this.track_ycbcr_cb.Maximum = 100;
            this.track_ycbcr_cb.Name = "track_ycbcr_cb";
            this.track_ycbcr_cb.Size = new System.Drawing.Size(176, 56);
            this.track_ycbcr_cb.TabIndex = 35;
            this.track_ycbcr_cb.Value = 50;
            this.track_ycbcr_cb.Scroll += new System.EventHandler(this.track_ycbcr_Scroll);
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(310, 10);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(19, 15);
            this.label15.TabIndex = 37;
            this.label15.Text = "%";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(20, 70);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(37, 15);
            this.label16.TabIndex = 36;
            this.label16.Text = "藍綠";
            // 
            // tabPage12
            // 
            this.tabPage12.Controls.Add(this.btn_selective_search);
            this.tabPage12.Controls.Add(this.btn_segment);
            this.tabPage12.Location = new System.Drawing.Point(4, 25);
            this.tabPage12.Name = "tabPage12";
            this.tabPage12.Size = new System.Drawing.Size(979, 71);
            this.tabPage12.TabIndex = 9;
            this.tabPage12.Text = " 圖片分割";
            this.tabPage12.UseVisualStyleBackColor = true;
            // 
            // btn_segment
            // 
            this.btn_segment.Location = new System.Drawing.Point(6, 6);
            this.btn_segment.Name = "btn_segment";
            this.btn_segment.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_segment.Size = new System.Drawing.Size(100, 44);
            this.btn_segment.TabIndex = 3;
            this.btn_segment.Text = "圖片分割";
            this.btn_segment.UseVisualStyleBackColor = true;
            this.btn_segment.Click += new System.EventHandler(this.btn_segment_Click);
            // 
            // btn_selective_search
            // 
            this.btn_selective_search.Location = new System.Drawing.Point(112, 6);
            this.btn_selective_search.Name = "btn_selective_search";
            this.btn_selective_search.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.btn_selective_search.Size = new System.Drawing.Size(100, 44);
            this.btn_selective_search.TabIndex = 4;
            this.btn_selective_search.Text = "圖片合併";
            this.btn_selective_search.UseVisualStyleBackColor = true;
            this.btn_selective_search.Click += new System.EventHandler(this.btn_selective_search_Click);
            // 
            // MNDT
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1014, 833);
            this.Controls.Add(this.tabControl2);
            this.Controls.Add(this.btn_app_pic_init);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.pic_app);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.btn_now_pic_init);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.pic_now);
            this.Controls.Add(this.pic_pur);
            this.Controls.Add(this.pic_src);
            this.Name = "MNDT";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pic_src)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_pur)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_now)).EndInit();
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage5.ResumeLayout(false);
            this.tabPage6.ResumeLayout(false);
            this.tabPage7.ResumeLayout(false);
            this.tabPage8.ResumeLayout(false);
            this.tabPage9.ResumeLayout(false);
            this.tabPage10.ResumeLayout(false);
            this.tabPage11.ResumeLayout(false);
            this.tabPage4.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.track_hsv_v)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_hsv_v)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_hsv_s)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_hsv_h)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.track_hsv_s)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.track_hsv_h)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pic_app)).EndInit();
            this.tabControl2.ResumeLayout(false);
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            this.tabPage3.ResumeLayout(false);
            this.tabPage3.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_ycbcr_cr)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_ycbcr_cb)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.track_ycbcr_cr)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_ycbcr_y)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.track_ycbcr_y)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.track_ycbcr_cb)).EndInit();
            this.tabPage12.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pic_src;
        private System.Windows.Forms.PictureBox pic_pur;
        private System.Windows.Forms.Button btn_RGB2Gray8;
        private System.Windows.Forms.Button btn_BGR2HSV;
        private System.Windows.Forms.Button btn_HSV2BGR;
        private System.Windows.Forms.PictureBox pic_now;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label lab_combination;
        private System.Windows.Forms.Button btn_now_pic_init;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.TrackBar track_hsv_v;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.PictureBox pic_app;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button btn_app_pic_init;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TrackBar track_hsv_s;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TrackBar track_hsv_h;
        private System.Windows.Forms.Button btn_BGR2YCbCr;
        private System.Windows.Forms.Button btn_YCbCr2BGR;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label lab_hsv_h;
        private System.Windows.Forms.NumericUpDown numeric_hsv_v;
        private System.Windows.Forms.NumericUpDown numeric_hsv_s;
        private System.Windows.Forms.NumericUpDown numeric_hsv_h;
        private System.Windows.Forms.TabControl tabControl2;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.TabPage tabPage3;
        private System.Windows.Forms.NumericUpDown numeric_ycbcr_cr;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.NumericUpDown numeric_ycbcr_cb;
        private System.Windows.Forms.TrackBar track_ycbcr_cr;
        private System.Windows.Forms.NumericUpDown numeric_ycbcr_y;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.TrackBar track_ycbcr_y;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.TrackBar track_ycbcr_cb;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.TabPage tabPage4;
        private System.Windows.Forms.Button btn_padding;
        private System.Windows.Forms.TabPage tabPage5;
        private System.Windows.Forms.Button btn_blur;
        private System.Windows.Forms.Button btn_gauss_blur;
        private System.Windows.Forms.Button btn_median_blur;
        private System.Windows.Forms.Button btn_bilateral;
        private System.Windows.Forms.TabPage tabPage6;
        private System.Windows.Forms.Button btn_histogram;
        private System.Windows.Forms.Button btn_hisogram_equalization;
        private System.Windows.Forms.Button btn_back_projection;
        private System.Windows.Forms.Button btn_channel;
        private System.Windows.Forms.TabPage tabPage7;
        private System.Windows.Forms.Button btn_threshold;
        private System.Windows.Forms.Button btn_meanshift;
        private System.Windows.Forms.TabPage tabPage8;
        private System.Windows.Forms.Button btn_horizontal;
        private System.Windows.Forms.Button btn_vertical;
        private System.Windows.Forms.Button btn_nearest;
        private System.Windows.Forms.Button btn_linear;
        private System.Windows.Forms.Button btn_pyramid_up;
        private System.Windows.Forms.Button btn_pyramid_down;
        private System.Windows.Forms.Button btn_affine;
        private System.Windows.Forms.Button btn_test;
        private System.Windows.Forms.TabPage tabPage9;
        private System.Windows.Forms.Button btn_24bit_sobel;
        private System.Windows.Forms.Button btn_sobel_edge;
        private System.Windows.Forms.TabPage tabPage10;
        private System.Windows.Forms.Button btn_original_lbp;
        private System.Windows.Forms.Button btn_circular_lbp;
        private System.Windows.Forms.Button btn_invariant_lbp;
        private System.Windows.Forms.Button btn_semb_lbp;
        private System.Windows.Forms.Button btn_mb_lbp;
        private System.Windows.Forms.Button btn_equivalent_lbp;
        private System.Windows.Forms.Button btn_histogram_lbp;
        private System.Windows.Forms.TabPage tabPage11;
        private System.Windows.Forms.Button btn_gamma;
        private System.Windows.Forms.Button btn_gradient_hog;
        private System.Windows.Forms.Button btn_hog_block_view;
        private System.Windows.Forms.Button btn_hog_cell_view;
        private System.Windows.Forms.Button btn_hough_lines;
        private System.Windows.Forms.Button btn_hough_circle;
        private System.Windows.Forms.TabPage tabPage12;
        private System.Windows.Forms.Button btn_segment;
        private System.Windows.Forms.Button btn_selective_search;
    }
}

