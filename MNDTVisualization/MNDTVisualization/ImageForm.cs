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
    public partial class ImageForm : Form
    {
        public ImageForm()
        {
            InitializeComponent();
        }

        public ImageForm(Bitmap image, string title)
        {
            InitializeComponent();
            this.Text = title;
            pic_image.Image = image;
        }
    }
}
