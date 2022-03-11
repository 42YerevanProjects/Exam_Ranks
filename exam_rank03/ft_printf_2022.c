#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

int ft_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}

int ft_putnbr(unsigned int i, int base)
{
    char *hex = "0123456789abcdef";
    char *dec = "0123456789";
    int n;

    int count = 0;
    if (i / base != 0)
        count += ft_putnbr(i / base, base);
    n = i % base;
    if (base == 16)
        count += write(1, &hex[n], 1);
    else if (base == 10)
        count += write(1, &dec[n], 1);
    return (count);
}

int ft_printfd(int i)
{
    int count;

    count = 0;
    if (i < 0)
    {
        i *= -1;
        count += ft_putchar('-');
    }
    count += ft_putnbr(i, 10);
    return (count);

}

int ft_putstr(char *s)
{
    int i;
    int count;

    count = 0;

    i = 0;
    if (!s)
        s = "(null)";
    while (s[i])
    {
        ft_putchar(s[i]);
        i++;
    }
    return (i);
}

int ft_printf(const char *fmt, ...)
{
    va_list ap;
    int i;
    int count;

    count = 0;
    i = 0;
    va_start(ap, fmt);
    while (fmt[i])
    {
        if (fmt[i] == '%')
        {
            i++;
            if (fmt[i] == 'd')
                count += ft_printfd(va_arg(ap, int));
            if (fmt[i] == 's')
                count += ft_putstr(va_arg(ap, char *));
            if (fmt[i] == 'x')
                count += ft_putnbr(va_arg(ap, unsigned int), 16);
        }        
        else
            count += ft_putchar(fmt[i]);
        i++;
    }
    va_end(ap);
    return (count);
}
