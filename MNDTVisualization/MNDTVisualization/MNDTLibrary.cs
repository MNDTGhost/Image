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
        unsafe private static extern void mndtChangeColor(IntPtr src, IntPtr pur, int width, int height, int type);

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
        unsafe private static extern void mndtAdjustmentHSV(IntPtr src, IntPtr pur, int width, int height, int H, int S, int V);

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
        unsafe private static extern void mndtAdjustmentYCbCr(IntPtr src, IntPtr pur, int width, int height, int H, int S, int V);

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

    }
}
