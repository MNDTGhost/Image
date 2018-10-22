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
    }
}
