using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace MNDTVisualization
{
    public enum ColerType : int
    {
        BGR2GRAY_8BIT = 0,
        BGR2HSV = 1,
        HSV2BGR = 2,
        BGR2YCbCr = 3,
        YCbCr2BGR = 4
    }

    public enum BlurType : int
    {
        BLUR = 0,
        GAUSS_BLUR = 1
    }

    public enum RotatType : int
    {
        HORIZONTAL = 0,
        VERTICAL = 1
    }

    public enum ResizeType : int
    {
        NEAREST = 0,
        LINEAR = 1
    }

    class MNDTLibrary
    {
        private const string DLL_PATH = @"D:\Visual Studio 2013 Project\Projects\MNDTLibrary\x64\Debug\MNDTLibrary.dll";
        private ColorPalette _colorPalette = null;

        public MNDTLibrary()
        {
            using (Bitmap bitmap = new Bitmap(1, 1, PixelFormat.Format8bppIndexed))
            {
                _colorPalette = bitmap.Palette;
            }

            for (int i = 0; i < 256; i++)
            {
                _colorPalette.Entries[i] = Color.FromArgb(i, i, i);
            }
        }

        [DllImport(DLL_PATH)]
        private static extern void mndtWrite(string msg);

        public void Write(string msg)
        {

            mndtWrite(msg);
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtChangeColor(IntPtr src, IntPtr pur
            , int width, int height
            , int type);

        public Bitmap Change8BitColor(Bitmap srcImage, ColerType type)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtChangeColor(srcPtr, purPtr, srcImage.Width, srcImage.Height, (int)type);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        public Bitmap ChangeColor(Bitmap srcImage, ColerType type)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format24bppRgb);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtChangeColor(srcPtr, purPtr, srcImage.Width, srcImage.Height, (int)type);
            }

            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtAdjustmentHSV(IntPtr src, IntPtr pur
            , int width, int height
            , int H, int S, int V);

        public Bitmap AdjustmentHSV(Bitmap srcImage, int H, int S, int V)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format24bppRgb);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtAdjustmentHSV(srcPtr, purPtr, srcImage.Width, srcImage.Height, H, S, V);
            }

            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtAdjustmentYCbCr(IntPtr src, IntPtr pur
            , int width, int height
            , int H, int S, int V);

        public Bitmap AdjustmentYCbCr(Bitmap srcImage, int Y, int Cb, int Cr)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format24bppRgb);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtAdjustmentYCbCr(srcPtr, purPtr, srcImage.Width, srcImage.Height, Y, Cb, Cr);
            }

            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtImagePadding8bit(IntPtr src, IntPtr pur
            , int width, int height
            , int pad);

        public Bitmap ImagePadding8bit(Bitmap srcImage, int pad)
        {
            Bitmap purImage = new Bitmap(srcImage.Width + pad * 2, srcImage.Height + pad * 2, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtImagePadding8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , pad);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtImagePadding24bit(IntPtr src, IntPtr pur
            , int width, int height
            , int pad);

        public Bitmap ImagePadding24bit(Bitmap srcImage, int pad)
        {
            Bitmap purImage = new Bitmap(srcImage.Width + pad * 2, srcImage.Height + pad * 2, PixelFormat.Format24bppRgb);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtImagePadding24bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , pad);
            }

            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtBlur8bit(IntPtr src, IntPtr pur
            , int width, int height
            , int size);

        public Bitmap Blur8bit(Bitmap srcImage, int blockSize)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtBlur8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , blockSize);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtBlurGauss8bit(IntPtr src, IntPtr pur
            , int width, int height
            , int size
            , float sigma);

        public Bitmap BlurGauss8bit(Bitmap srcImage, int gaussSize, float sigma)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtBlurGauss8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , gaussSize
                    , sigma);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtBlurGauss24bit(IntPtr src, IntPtr pur
            , int width, int height
            , int size
            , float sigma);

        public Bitmap BlurGauss24bit(Bitmap srcImage, int gaussSize, float sigma)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format24bppRgb);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtBlurGauss24bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , gaussSize
                    , sigma);
            }

            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtMedianBlur8bit(IntPtr src, IntPtr pur
            , int width, int height
            , int size);

        public Bitmap MedianBlur8bit(Bitmap srcImage, int blockSize)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtMedianBlur8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , blockSize);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtBilateralBlur8bit(IntPtr src, IntPtr pur
            , int width, int height
            , float spaceSigma, float colorSigma
            , int size);

        public Bitmap BilateralBlur8bit(Bitmap srcImage, float spaceSigma, float colorSigma, int blockSize)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtBilateralBlur8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , spaceSigma, colorSigma
                    , blockSize);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtHistogram8bit(IntPtr src, IntPtr pur
            , int width, int height);

        public Bitmap Histogram8bit(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(256, 256, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(new Rectangle(0, 0, 256, 256), ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtHistogram8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtHistogramEqualization8bit(IntPtr src, IntPtr pur
            , int width, int height);

        public Bitmap HistogramEqualization8bit(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtHistogramEqualization8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtCompareHistogram(IntPtr src, IntPtr pur
            , int width, int height);

        public Bitmap CompareHistogram(Bitmap srcImage, Bitmap purImage)
        {
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtCompareHistogram(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtChannel(IntPtr src, IntPtr pur
            , int width, int height
            , int channel);

        public Bitmap Channel(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtChannel(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , 1);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }


        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtSetHistogram8bit(IntPtr src, int[] histogram
            , int hisWidth, int hisHeight
            , byte minRange, byte maxRange
            , byte bin);

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtSetNormalizedHistogram8bit(int[] histogram
            , byte bin
            , byte maxRange);

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtBackProjection(IntPtr src, IntPtr pur
            , int srcWidth, int srcHeight
            , int[] histogram
            , byte minRange, byte maxRange
            , byte bin);

        public Bitmap BackProjection(Bitmap srcImage, Bitmap hisImage, byte bin)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            Rectangle hisSize = new Rectangle(0, 0, hisImage.Width, hisImage.Height);
            BitmapData hisData = hisImage.LockBits(hisSize, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                IntPtr hisPtr = hisData.Scan0;

                int[] histogram = new int[bin];

                mndtSetHistogram8bit(hisPtr, histogram
                   , hisImage.Width, hisImage.Height
                   , 0, bin
                   , bin);

                mndtSetNormalizedHistogram8bit(histogram, bin, bin);

                mndtBackProjection(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , histogram
                    , 0, bin
                    , bin);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);
            hisImage.UnlockBits(hisData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtThreshold8bit(IntPtr src, IntPtr pur
            , int width, int height
            , int threshold);

        public Bitmap Threshold8bit(Bitmap srcImage, int threshold)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtThreshold8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , threshold);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }


        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtMeanShift(IntPtr src, IntPtr pur
            , int width, int height
            , int[] rectPoint
            , int times
            , double threshold);

        public Bitmap MeanShift(Bitmap srcImage, int[] rectPoint, int times, double threshold)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtMeanShift(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , rectPoint
                    , times
                    , threshold);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtRotate8bit(IntPtr src, IntPtr pur
            , int width, int height
            , int type);

        public Bitmap Rotate8bit(Bitmap srcImage, RotatType type)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;

                mndtRotate8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , (int)type);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtResize8bit(IntPtr src, IntPtr pur
            , int width, int height
            , int reWidth, int reHeight
            , int type);

        public Bitmap Resize8bit(Bitmap srcImage, int reWidth, int reHeight, ResizeType type)
        {
            Bitmap purImage = new Bitmap(reWidth, reHeight, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(new Rectangle(0, 0, reWidth, reHeight), ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;

                mndtResize8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , reWidth, reHeight
                    , (int)type);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);
            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtPyramidDown8bit(IntPtr src, IntPtr pur
            , int width, int height);

        public Bitmap PyramidDown8bit(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width >> 1, srcImage.Height >> 1, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(new Rectangle(0, 0, srcImage.Width >> 1, srcImage.Height >> 1), ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;

                mndtPyramidDown8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtPyramidUp8bit(IntPtr src, IntPtr pur
            , int width, int height);

        public Bitmap PyramidUp8bit(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width << 1, srcImage.Height << 1, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(new Rectangle(0, 0, srcImage.Width << 1, srcImage.Height << 1), ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;

                mndtPyramidUp8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtSetAffineTransform(float[,] affine
            , float[] baseX, float[] baseY
            , int row, int col);


        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtAffine8bit(IntPtr src, IntPtr pur
            , int width, int height
            , float[] baseX, float[] baseY);

        public Bitmap Affine8bit(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(new Rectangle(0, 0, srcImage.Width, srcImage.Height), ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                float[,] affine = new float[3, 5];
                float[] baseX = new float[3];
                float[] baseY = new float[3];
                //[0] = x, [1] = y, [2] = b's base, [3] = change x, [4] = change y
                affine[0, 0] = 0;
                affine[0, 1] = 0;
                affine[0, 2] = 1;
                affine[0, 3] = 0;
                affine[0, 4] = srcImage.Height * 0.3f;

                affine[1, 0] = srcImage.Width - 1;
                affine[1, 1] = 0;
                affine[1, 2] = 1;
                affine[1, 3] = srcImage.Width * 0.8f;
                affine[1, 4] = 0;

                affine[2, 0] = 0;
                affine[2, 1] = srcImage.Height - 1;
                affine[2, 2] = 1;
                affine[2, 3] = srcImage.Width * 0.1f;
                affine[2, 4] = srcImage.Height * 0.9f;

                mndtSetAffineTransform(affine
                    , baseX, baseY
                    , 3, 5);

                mndtAffine8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , baseX, baseY);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtSobelEdge8bit(IntPtr src, IntPtr pur
            , int width, int height);

        public Bitmap SobelEdge8bit(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;

                mndtSobelEdge8bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtSobel24bit(IntPtr src, IntPtr pur
            , int width, int height
            , bool dx, bool dy);

        public Bitmap Sobel24bit(Bitmap srcImage
            , bool dx, bool dy)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format24bppRgb);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;

                mndtSobel24bit(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , dx, dy);

            }

            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtSegmentImage(IntPtr src, IntPtr pur
            , int width, int height
            , float sigma, float threshold, int minSize
            , int* numCss);

        public Bitmap SegmentImage(Bitmap srcImage
            , float sigma, float threshold, int minSize)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format24bppRgb);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            BitmapData purData = purImage.LockBits(new Rectangle(0, 0, srcImage.Width, srcImage.Height), ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
            int num = 0;
            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                int* numCss = &num;
                mndtSegmentImage(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , sigma, threshold, minSize
                    , numCss);

            }

            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtSelectiveSearch(IntPtr src, IntPtr pur
            , int width, int height
            , float sigma, float threshold, int minSize
            , int* numCss);

        public Bitmap SelectiveSearch(Bitmap srcImage
            , float sigma, float threshold, int minSize)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format24bppRgb);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format24bppRgb);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);
            int num = 0;
            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                int* numCss = &num;
                mndtSelectiveSearch(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , sigma, threshold, minSize
                    , numCss);

            }

            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtOriginalLBP(IntPtr src, IntPtr pur
            , int width, int height);

        public Bitmap OriginalLBP(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtOriginalLBP(srcPtr, purPtr, srcImage.Width, srcImage.Height);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtCircularLBP(IntPtr src, IntPtr pur
            , int width, int height);

        public Bitmap CircularLBP(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtCircularLBP(srcPtr, purPtr, srcImage.Width, srcImage.Height);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtInvariantLBP(IntPtr src, IntPtr pur
            , int width, int height);

        public Bitmap InvariantLBP(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtInvariantLBP(srcPtr, purPtr, srcImage.Width, srcImage.Height);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtEquivalentLBP(IntPtr src, IntPtr pur
            , int width, int height);

        public Bitmap EquivalentLBP(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtEquivalentLBP(srcPtr, purPtr, srcImage.Width, srcImage.Height);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtMultiScaleBlockLBP(IntPtr src, IntPtr pur
            , int width, int height);

        public Bitmap MultiScaleBlockLBP(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtMultiScaleBlockLBP(srcPtr, purPtr, srcImage.Width, srcImage.Height);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtSEMultiScaleBlockLBP(IntPtr src, IntPtr pur
            , int width, int height);

        public Bitmap SEMultiScaleBlockLBP(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtSEMultiScaleBlockLBP(srcPtr, purPtr, srcImage.Width, srcImage.Height);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtLBPHistogram(IntPtr src, IntPtr pur
           , int width, int height
           , int gridX, int gridY
           , int bin);

        public Bitmap LBPHistogram(Bitmap srcImage, int gridX, int gridY, int bin)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtLBPHistogram(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , gridX, gridY
                    , bin);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtGamma(IntPtr src, IntPtr pur
           , int width, int height
           , double gamma);

        public Bitmap Gamma(Bitmap srcImage, double gamma)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtGamma(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , gamma);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtHOGGradient(IntPtr src, IntPtr pur
           , int width, int height);

        public Bitmap HOGGradient(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtHOGGradient(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtHOGCellHistogram(IntPtr src, IntPtr pur
          , int width, int height
          , int cellX, int cellY);

        public Bitmap HOGCellHistogram(Bitmap srcImage)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtHOGCellHistogram(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , 8, 8);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtHOGBlockView(IntPtr src, IntPtr pur
              , int width, int height
              , int cellX, int cellY
              , int blockX, int blockY);

        public Bitmap HOGBlockView(Bitmap srcImage, int cellX, int cellY, int blockX, int blockY)
        {
            int purWidth = Convert.ToInt32(Math.Ceiling((double)srcImage.Width / cellX)) * cellX;
            int purHeight = Convert.ToInt32(Math.Ceiling((double)srcImage.Height / cellY)) * cellY;
            Bitmap purImage = new Bitmap(purWidth, purHeight, PixelFormat.Format8bppIndexed);
            Rectangle purSize = new Rectangle(0, 0, purWidth, purHeight);
            BitmapData purData = purImage.LockBits(purSize, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtHOGBlockView(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , cellX, cellY
                    , blockX, blockY);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtHOGCellView(IntPtr src, IntPtr pur
              , int width, int height
              , int cellX, int cellY);

        public Bitmap HOGCellView(Bitmap srcImage, int cellX, int cellY)
        {
            int purWidth = Convert.ToInt32(Math.Ceiling((double)srcImage.Width / cellX)) * cellX;
            int purHeight = Convert.ToInt32(Math.Ceiling((double)srcImage.Height / cellY)) * cellY;
            Bitmap purImage = new Bitmap(purWidth, purHeight, PixelFormat.Format8bppIndexed);
            Rectangle purSize = new Rectangle(0, 0, purWidth, purHeight);
            BitmapData purData = purImage.LockBits(purSize, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);

            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtHOGCellView(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , cellX, cellY);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtHoughLines(IntPtr src, IntPtr pur
             , int width, int height
             , float rho, float theta, int threshold);

        public Bitmap HoughLines(Bitmap srcImage, float rho, float theta, int threshold)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);
            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtHoughLines(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , rho, theta, threshold);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }

        [DllImport(DLL_PATH)]
        unsafe private static extern void mndtHoughCircles(IntPtr src, IntPtr pur
             , int width, int height
             , float minRadius, float maxRadius, int threshold);

        public Bitmap HoughCircles(Bitmap srcImage, float minRadius, float maxRadius, int threshold)
        {
            Bitmap purImage = new Bitmap(srcImage.Width, srcImage.Height, PixelFormat.Format8bppIndexed);
            Rectangle size = new Rectangle(0, 0, srcImage.Width, srcImage.Height);
            BitmapData srcData = srcImage.LockBits(size, ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
            BitmapData purData = purImage.LockBits(size, ImageLockMode.ReadWrite, PixelFormat.Format8bppIndexed);
            unsafe
            {
                IntPtr srcPtr = srcData.Scan0;
                IntPtr purPtr = purData.Scan0;
                mndtHoughCircles(srcPtr, purPtr
                    , srcImage.Width, srcImage.Height
                    , minRadius, maxRadius, threshold);
            }

            purImage.Palette = _colorPalette;
            srcImage.UnlockBits(srcData);
            purImage.UnlockBits(purData);

            return purImage;
        }
    }
}
