/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalabrad <dalabrad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:42:08 by dalabrad          #+#    #+#             */
/*   Updated: 2025/03/05 11:23:09 by dalabrad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

int	ft_putstr(char *str)
{
	int	len;

	len = 0;
	while (*str)
	{
		len += ft_putchar(*str);
		str++;
	}
	return (len);
}

int	ft_putnbr(int n)
{
	int				len;
	unsigned int	nbr;

	len = 0;
	if (n < 0)
	{
		len += ft_putchar('-');
		nbr = -n;
	}
	else
		nbr = n;
	if (nbr > 9)
		len += ft_putnbr(nbr / 10);
	len += ft_putchar ('0' + nbr % 10);
	return (len);
}

int	ft_puthex(unsigned int n)
{
	int	len;

	len = 0;
	if (n < 10)
		len += ft_putchar('0' + n);
	else if (9 < n && n < 16)
		len += ft_putchar('a' + n - 10);
	else
	{
		len += ft_puthex(n / 16);
		len += ft_puthex(n % 16);
	}
	return (len);
}

char	*ft_strchr(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}

int	ft_print_arg(va_list args, const char fmt)
{
	int	len;

	len = 0;
	if (fmt == 's')
		len += ft_putstr(va_arg(args, char *));
	else if (fmt == 'd')
		len += ft_putnbr(va_arg(args, int));
	else if (fmt == 'x')
		len += ft_puthex(va_arg(args, unsigned int));
	else if (fmt == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *fmt_str, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, fmt_str);
	while (*fmt_str)
	{
		if (*fmt_str == '%' && ft_strchr("sdx%", *(fmt_str + 1))
			&& *(fmt_str + 1))
		{
			fmt_str++;
			len += ft_print_arg(args, *fmt_str);
		}
		else if (*fmt_str != '%')
			len += ft_putchar(*fmt_str);
		fmt_str++;
	}
	va_end(args);
	return (len);
}

/* int	main(int argc, char	**argv)
{
	int	n1, n2;
	int	printed_bytes;

	if (argc != 4)
		return (ft_putstr("Use ./a.out [string]" \
				" [positive_number] [negative_number]\n"));
	n1 = atoi(argv[2]);
	n2 = atoi(argv[3]);
	if (n1 < 0)
		return (ft_putstr("Introduce a positive number\n"));
	printed_bytes = printf("printf('%s')", argv[1]);
	printf("= %d\n", printed_bytes);
	printed_bytes = ft_printf("ft_printf('%s')", argv[1]);
	printf("= %d\n", printed_bytes - 3);
	printed_bytes = printf("printf('%x')", n1);
	printf("= %d\n", printed_bytes);
	printed_bytes = ft_printf("ft_printf('%x')", n1);
	printf("= %d\n", printed_bytes - 3);
	printed_bytes = printf("printf('%d')", n2);
	printf("= %d\n", printed_bytes);
	printed_bytes = ft_printf("ft_printf('%d')", n2);
	printf("= %d\n", printed_bytes - 3);
	printed_bytes = printf("printf('%%')");
	printf("= %d\n", printed_bytes);
	printed_bytes = ft_printf("ft_printf('%%')");
	printf("= %d\n", printed_bytes - 3);
	return (EXIT_SUCCESS);
} */