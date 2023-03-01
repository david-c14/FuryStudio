using Avalonia.Data.Converters;
using System;

namespace carbon14.FuryStudio.AvaloniaUI.Converters
{
    public class BooleanToStringValueConverter : IValueConverter
    {
        public object Convert(object? value, Type targetType, object? parameter, System.Globalization.CultureInfo culture)
        {
            if (System.Convert.ToString(value)?.Equals(System.Convert.ToString(parameter)) == true)
            {
                return true;
            }
            return false;
        }

        public object? ConvertBack(object? value, Type targetType, object? parameter, System.Globalization.CultureInfo culture)
        {
            if (System.Convert.ToBoolean(value))
            {
                return parameter;
            }
            return null;
        }
    }
}
