using Avalonia.Data.Converters;
using Avalonia.Media.Imaging;
using System;
using System.IO;

namespace carbon14.FuryStudio.AvaloniaUI.Converters
{
    public class BitmapAssetValueConverter: IValueConverter
    {
        public static BitmapAssetValueConverter Instance = new BitmapAssetValueConverter();

        public object? Convert(object? value, Type targetType, object? parameter, System.Globalization.CultureInfo culture)
        {
            if (value == null)
            {
                return null;
            }
            if (value is Stream stream && targetType.IsAssignableFrom(typeof(Bitmap)))
            {
                return new Bitmap(stream);
            }
            throw new NotSupportedException();
        }

        public object? ConvertBack(object? value, Type targetType, object? parameter, System.Globalization.CultureInfo culture)
        {
            throw new NotSupportedException();
        }
    }
}
