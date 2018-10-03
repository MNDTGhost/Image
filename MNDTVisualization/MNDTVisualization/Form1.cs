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
    public partial class Form1 : Form
    {
        MNDTLibrary _lib = new MNDTLibrary();
        private static string FILE_NAME = @"C:\Users\Ghost\Desktop\Lenna.jpg";
        private Bitmap _fileImage = new Bitmap(FILE_NAME);
        private Bitmap _nowImage = new Bitmap(FILE_NAME);

        public Form1()
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
            if(numericObj != null)
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

    }
}
