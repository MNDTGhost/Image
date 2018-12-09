using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace MNDTVisualization
{
    public partial class MNDT : Form
    {
        MNDTLibrary _lib = new MNDTLibrary();
        private static string FILE_NAME = @"C:\Users\Ghost\Desktop\Lenna2.jpg";
        private Bitmap _fileImage = new Bitmap(FILE_NAME);
        private Bitmap _nowImage = new Bitmap(FILE_NAME);

        public MNDT()
        {
            InitializeComponent();
            pic_src.Image = _fileImage;
            pic_pur.Image = _fileImage;
            pic_now.Image = _fileImage;
            pic_app.Image = _fileImage;
        }

        private void SetCombinationImage(Bitmap bitmap, string actionName)
        {
            lab_combination.Text += actionName + " ->\r\n";
            _nowImage = bitmap;
            pic_now.Image = _nowImage;
        }

        private void btn_now_pic_init_Click(object sender, EventArgs e)
        {
            lab_combination.Text = "";
            _nowImage = _fileImage;
            pic_now.Image = _nowImage;
        }

        private void UpdateHSVAppPic()
        {
            int H = (track_hsv_h.Value - 50) * 2;
            int S = (track_hsv_s.Value - 50) * 2;
            int V = (track_hsv_v.Value - 50) * 2;
            pic_app.Image = _lib.AdjustmentHSV(_fileImage, H, S, V);
        }

        private void UpdateYCbCrAppPic()
        {
            int Y = (track_ycbcr_y.Value - 50) * 2;
            int Cb = (track_ycbcr_cb.Value - 50) * 2;
            int Cr = (track_ycbcr_cr.Value - 50) * 2;
            pic_app.Image = _lib.AdjustmentYCbCr(_fileImage, Y, Cb, Cr);
        }

        private void btn_app_pic_init_Click(object sender, EventArgs e)
        {
            // HSV
            track_hsv_h.Value = 50;
            track_hsv_s.Value = 50;
            track_hsv_v.Value = 50;
            pic_app.Image = _fileImage;

            // YCbCr
            track_ycbcr_y.Value = 50;
            track_ycbcr_cb.Value = 50;
            track_ycbcr_cr.Value = 50;
            pic_app.Image = _fileImage;
        }

        private void btn_RGB2Gray8_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.Change8BitColor(_nowImage, ColerType.BGR2GRAY_8BIT);
            SetCombinationImage(bitmap, "8bit灰階");

            pic_pur.Image = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
        }

        private void btn_BGR2HSV_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.ChangeColor(_nowImage, ColerType.BGR2HSV);
            SetCombinationImage(bitmap, "BGR2HSV");

            pic_pur.Image = _lib.ChangeColor(_fileImage, ColerType.BGR2HSV);
        }

        private void btn_HSV2BGR_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.ChangeColor(_nowImage, ColerType.HSV2BGR);
            SetCombinationImage(bitmap, "HSV2BGR");

            pic_pur.Image = _lib.ChangeColor(_fileImage, ColerType.HSV2BGR);
        }

        private void track_hsv_Scroll(object sender, EventArgs e)
        {

            string numericName = ((TrackBar)sender).Name.Replace("track", "numeric");
            NumericUpDown numericObj = Controls.Find(numericName, true).FirstOrDefault() as NumericUpDown;
            if (numericObj != null)
            {
                numericObj.Value = ((TrackBar)sender).Value;
            }
            UpdateHSVAppPic();
        }

        private void numeric_hsv_ValueChanged(object sender, EventArgs e)
        {
            string trackName = ((NumericUpDown)sender).Name.Replace("numeric", "track");
            TrackBar trackObj = Controls.Find(trackName, true).FirstOrDefault() as TrackBar;
            if (trackObj != null)
            {
                trackObj.Value = Convert.ToInt32(((NumericUpDown)sender).Value);
            }
            UpdateHSVAppPic();
        }

        private void btn_BGR2YCbCr_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.ChangeColor(_nowImage, ColerType.BGR2YCbCr);
            SetCombinationImage(bitmap, "BGR2YCbCr");

            pic_pur.Image = _lib.ChangeColor(_fileImage, ColerType.BGR2YCbCr);
        }

        private void btn_YCbCr2BGR_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.ChangeColor(_nowImage, ColerType.YCbCr2BGR);
            SetCombinationImage(bitmap, "YCbCr2BGR");

            pic_pur.Image = _lib.ChangeColor(_fileImage, ColerType.YCbCr2BGR);
        }

        private void track_ycbcr_Scroll(object sender, EventArgs e)
        {

            string numericName = ((TrackBar)sender).Name.Replace("track", "numeric");
            NumericUpDown numericObj = Controls.Find(numericName, true).FirstOrDefault() as NumericUpDown;

            if (numericObj != null)
            {
                numericObj.Value = ((TrackBar)sender).Value;
            }
            UpdateYCbCrAppPic();
        }

        private void numeric_ycbcr_ValueChanged(object sender, EventArgs e)
        {
            string trackName = ((NumericUpDown)sender).Name.Replace("numeric", "track");
            TrackBar trackObj = Controls.Find(trackName, true).FirstOrDefault() as TrackBar;

            if (trackObj != null)
            {
                trackObj.Value = Convert.ToInt32(((NumericUpDown)sender).Value);
            }
            UpdateYCbCrAppPic();
        }

        private void btn_padding_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.ImagePadding8bit(_nowImage, 30);
            SetCombinationImage(bitmap, "Padding");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.ImagePadding8bit(bitmap, 10);
        }

        private void btn_blur_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.Blur8bit(_nowImage, 2);
            SetCombinationImage(bitmap, "Blur");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.Blur8bit(bitmap, 3);
        }

        private void btn_gauss_blur_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.BlurGauss8bit(_nowImage, 3, 1);
            SetCombinationImage(bitmap, "GaussBlur");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.BlurGauss8bit(bitmap, 3, 1);
        }

        private void btn_median_blur_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.MedianBlur8bit(_nowImage, 5);
            SetCombinationImage(bitmap, "MedianBlur");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.MedianBlur8bit(bitmap, 5);
        }

        private void btn_bilateral_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.BilateralBlur8bit(_nowImage, 30, 30, 21);
            SetCombinationImage(bitmap, "BilateralBlur");


            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.BilateralBlur8bit(bitmap, 30, 30, 21);
        }

        private void btn_histogram_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.Histogram8bit(_nowImage);
            SetCombinationImage(bitmap, "Histogram");


            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.Histogram8bit(bitmap);
        }

        private void btn_hisogram_equalization_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.HistogramEqualization8bit(_nowImage);
            SetCombinationImage(bitmap, "HistogramEqualization");


            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.HistogramEqualization8bit(bitmap);
        }

        private void btn_back_projection_Click(object sender, EventArgs e)
        {
            string hisPath = @"C:\Users\Ghost\Desktop\Lenn.jpg";
            Bitmap hisImage = new Bitmap(hisPath);

            new ImageForm(hisImage, "HistogramImage").Show();

            hisImage = _lib.ChangeColor(hisImage, ColerType.BGR2HSV);
            hisImage = _lib.Channel(hisImage);

            new ImageForm(hisImage, "HistogramImageHChannel").Show();

            Bitmap bitmap = _lib.BackProjection(_nowImage, hisImage, 180);
            SetCombinationImage(bitmap, "BackProject");
        }

        private void btn_channel_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.Channel(_nowImage);
            SetCombinationImage(bitmap, "Channel");

            pic_pur.Image = _lib.Channel(_fileImage);
        }

        private void btn_threshold_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.Threshold8bit(_nowImage, 65);
            SetCombinationImage(bitmap, "Threshold");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.Threshold8bit(bitmap, 65);
        }

        private void btn_meanshift_Click(object sender, EventArgs e)
        {
            int[] rectPoint = { 196, 195, 80, 102 };
            Bitmap bitmap = _lib.MeanShift(_nowImage, rectPoint, 30, 0.01);
            SetCombinationImage(bitmap, "MeanShift");

        }

        private void btn_horizontal_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.Rotate8bit(_nowImage, RotatType.HORIZONTAL);
            SetCombinationImage(bitmap, "Horizontal");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.Rotate8bit(bitmap, RotatType.HORIZONTAL);
        }

        private void btn_vertical_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.Rotate8bit(_nowImage, RotatType.VERTICAL);
            SetCombinationImage(bitmap, "Vertical");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.Rotate8bit(bitmap, RotatType.VERTICAL);
        }

        private void btn_nearest_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.Resize8bit(_nowImage, 200, 300, ResizeType.NEAREST);
            SetCombinationImage(bitmap, "Nearest");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.Resize8bit(bitmap, 200, 300, ResizeType.NEAREST);
        }

        private void btn_linear_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.Resize8bit(_nowImage, 200, 300, ResizeType.LINEAR);
            SetCombinationImage(bitmap, "Linear");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.Resize8bit(bitmap, 200, 300, ResizeType.LINEAR);

        }

        private void btn_pyramid_down_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.PyramidDown8bit(_nowImage);
            SetCombinationImage(bitmap, "PyramidDown");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.PyramidDown8bit(bitmap);
        }

        private void btn_pyramid_up_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.PyramidUp8bit(_nowImage);
            SetCombinationImage(bitmap, "PyramidUp");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.PyramidUp8bit(bitmap);
        }

        private void btn_affine_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.Affine8bit(_nowImage);
            SetCombinationImage(bitmap, "Affine");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.Affine8bit(bitmap);
        }

        private void btn_test_Click(object sender, EventArgs e)
        {
            //float sigma = 0.7f;
            //float threshold = 100f;
            //int minSize = 100;
            //// pic_pur.Image = _lib.SelectiveSearch(_fileImage, sigma, threshold, minSize);
            ////pic_pur.Image = _lib.SegmentImage(_fileImage, sigma, threshold, minSize);
            //_lib.HOGCellHistogram(_fileImage);
        }

        private void btn_24bit_sobel_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.Sobel24bit(_nowImage, true, false);
            SetCombinationImage(bitmap, "24bitSobel");

            new ImageForm(_lib.Sobel24bit(_fileImage, true, false), "24bitSobel dx").Show();
            new ImageForm(_lib.Sobel24bit(_fileImage, false, true), "24bitSobel dy").Show();

            pic_pur.Image = _lib.Sobel24bit(_fileImage, true, false);
        }

        private void btn_sobel_edge_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.SobelEdge8bit(_nowImage);
            SetCombinationImage(bitmap, "SobelEdge");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.SobelEdge8bit(bitmap);
        }

        private void btn_original_lbp_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.OriginalLBP(_nowImage);
            SetCombinationImage(bitmap, "OriginalLBP");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.OriginalLBP(bitmap);
        }

        private void btn_circular_lbp_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.CircularLBP(_nowImage);
            SetCombinationImage(bitmap, "CircularLBP");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.CircularLBP(bitmap);
        }

        private void btn_invariant_lbp_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.InvariantLBP(_nowImage);
            SetCombinationImage(bitmap, "InvariantLBP");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            bitmap = _lib.InvariantLBP(bitmap);
            pic_pur.Image = bitmap;
            new ImageForm(bitmap, "InvariantLBP").Show();
        }

        private void btn_equivalent_lbp_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.EquivalentLBP(_nowImage);
            SetCombinationImage(bitmap, "EquivalentLBP");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            bitmap = _lib.EquivalentLBP(bitmap);
            pic_pur.Image = bitmap;
            new ImageForm(bitmap, "EquivalentLBP").Show();
        }

        private void btn_mb_lbp_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.MultiScaleBlockLBP(_nowImage);
            SetCombinationImage(bitmap, "MultiScaleBlockLBP");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.MultiScaleBlockLBP(bitmap);
        }

        private void btn_semb_lbp_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.SEMultiScaleBlockLBP(_nowImage);
            SetCombinationImage(bitmap, "SEMultiScaleBlockLBP");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.SEMultiScaleBlockLBP(bitmap);
        }

        private void btn_histogram_lbp_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.LBPHistogram(_nowImage, 8, 8, 60);
            SetCombinationImage(bitmap, "LBPHistogram");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.LBPHistogram(bitmap, 8, 8, 256);
        }

        private void btn_gamma_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.Gamma(_nowImage, 1.5);
            SetCombinationImage(bitmap, "Gamma");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.Gamma(bitmap, 1.5);
        }

        private void btn_gradient_hog_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.HOGGradient(_nowImage);
            SetCombinationImage(bitmap, "HOGGradient");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.HOGGradient(bitmap);
        }

        private void btn_hog_block_view_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.HOGBlockView(_nowImage, 16, 16, 2, 2);
            SetCombinationImage(bitmap, "HOGBlockView");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.HOGBlockView(bitmap, 16, 16, 2, 2);
        }

        private void btn_hog_cell_view_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = _lib.HOGCellView(_nowImage, 16, 16);
            SetCombinationImage(bitmap, "HOGCellView");

            bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            pic_pur.Image = _lib.HOGCellView(bitmap, 16, 16);
        }

        private void btn_hough_lines_Click(object sender, EventArgs e)
        {
            //Bitmap bitmap = _lib.HoughLines(_nowImage, 1.0f, (float)(Math.PI / 180), 50);
            //SetCombinationImage(bitmap, "HoughLines");

            Bitmap bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            bitmap = _lib.SobelEdge8bit(bitmap);
            bitmap = _lib.Threshold8bit(bitmap, 65);
            bitmap = _lib.HoughLines(bitmap, 0.7f, (float)(Math.PI / 180.0), 120);
            pic_pur.Image = bitmap;
            new ImageForm(bitmap, "HoughLines").Show();
        }

        private void btn_hough_circle_Click(object sender, EventArgs e)
        {
            //Bitmap bitmap = _lib.HoughCircles(_nowImage, 30, 70, 30);
            //SetCombinationImage(bitmap, "HoughCircles");

            Bitmap bitmap = _lib.Change8BitColor(_fileImage, ColerType.BGR2GRAY_8BIT);
            //bitmap = _lib.SobelEdge8bit(bitmap);
            //bitmap = _lib.Threshold8bit(bitmap, 10);
            bitmap = _lib.HoughCircles(bitmap, 30, 70, 30);
            pic_pur.Image = bitmap;
            new ImageForm(bitmap, "HoughCircles").Show();
        }

        private void btn_segment_Click(object sender, EventArgs e)
        {
            float sigma = 0.7f;
            float threshold = 100f;
            int minSize = 100;
            pic_pur.Image = _lib.SegmentImage(_fileImage, sigma, threshold, minSize);
        }

        private void btn_selective_search_Click(object sender, EventArgs e)
        {
            float sigma = 0.7f;
            float threshold = 100f;
            int minSize = 100;
            pic_pur.Image = _lib.SelectiveSearch(_fileImage, sigma, threshold, minSize);
        }
    }
}
