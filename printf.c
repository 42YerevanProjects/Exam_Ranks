#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

int	count;
int	width;
int	dot;

static void ft_putchar(char c)
{
	write (1, &c, 1);
	count += 1;
}

static void ft_putstr(char *str, int len)
{
	while (*str && len > 0)
	{
		ft_putchar(*str);
		str++;
		len--;
	}
}

static int ft_strlen(char *str)
{
	int len;

	len = 0;
	while (*str++ != '\0')
		len++;
	return (len);
}

static char *ft_itoa(unsigned long nbr, int base)
{
	unsigned long	temp_nbr;
	int 			len;

	char *str = NULL;
	temp_nbr = nbr;
	len = 0;
	if (nbr == 0)
		len++;
	while (temp_nbr > 0)
	{
		temp_nbr /= base;
		len++;
	}
	str = malloc(len + 1);
	str[len] = '\0';
	while (len > 0)
	{
		str[len -1] = nbr % base;
		if (nbr % base > 9)
			str[len - 1] += 'a' - 10;
		else
			str[len] += '0';
		nbr /= base;
		len--;
	}
	return (str);
}

static void ft_printf_x(unsigned long nbr)
{
	char	*str;
	int		len;

	str = ft_itoa(nbr, 16);
	len = ft_strlen(str);
	if (dot != -1 && dot > len)
		len = dot;
	while (width > len)
	{
		ft_putchar(' ');
		width--;
	}
	while (len > ft_strlen(str))
	{
		ft_putchar('0');
		len--;
	}
	ft_putstr(str, ft_strlen(str));
	free(str);
}

static void ft_printf_d(long nbr)
{
	char	*str;
	int		minus;
	int		len;

	minus = 0;
	if (nbr < 0)
	{
		minus = 1;
		nbr *= -1;
	}
	str = ft_itoa(nbr, 10);
	len = ft_strlen(str);

	if (dot != -1 && dot > len)
		len = dot;
	if (minus == 1 && width > 0)
		width--;
	while (width > len)
	{
		ft_putchar(' ');
		width--;
	}
	if (minus == 1)
		ft_putchar('-');
	while (len > ft_strlen(str))
	{
		ft_putchar('0');
		len--;
	}
	ft_putstr(str, ft_strlen(str));
	free(str);
}

static void ft_printf_s(char *str)
{
	int len;

	len = ft_strlen(str);
	if (dot != -1 && dot < len)
		len = dot;
	while (width > len)
	{
		ft_putchar(' ');
		width--;
	}
	ft_putstr(str, len);
}

int ft_printf(const char *str, ...)
{
	int		i;
	va_list	ap;

	count = 0;
	i = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i +1] != '\0')
		{
			i++;
			width = 0;
			dot = -1;
			while (str[i] >= '0' && str[i] <= '9')
			{
				width = width * 10 + (str[i] - '0');
				i++;
			}
			if (str[i] == '.')
			{
				dot = 0;
				i++;
				while (str[i] >= '0' && str[i] <= '9')
				{
					dot = dot * 10 + (str[i] - '0');
					i++;
				}
			}
			if (str[i] == 's')
				ft_printf_s(va_arg(ap, char *));
			else if (str[i] == 'd')
				ft_printf_d(va_arg(ap, int));
			else if(str[i] == 'x')
				ft_printf_x(va_arg(ap, unsigned int));
			else
				ft_putchar(str[i]);
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	va_end(ap);
	return (count);
}

int main(void)
{
	printf("%d\n", ft_printf("%.5s", "Hello Bro"));
}
