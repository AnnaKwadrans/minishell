/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 23:36:19 by akwadran          #+#    #+#             */
/*   Updated: 2024/12/28 20:09:47 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

int	ft_printf(char const *str, ...)
{
	va_list	ap;
	int		i;
	int		count;

	va_start(ap, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != '%')
			count += ft_putchar(str[i++]);
		else
		{
			count += get_format(str[i + 1], ap);
			i += 2;
		}
	}
	va_end(ap);
	return (count);
}

int	get_format(char format, va_list ap)
{
	int	count;

	count = 0;
	if (format == 'c')
		count = ft_putchar(va_arg(ap, int));
	else if (format == 's')
		count = ft_putstr(va_arg(ap, char *));
	else if (format == 'p')
		count += ft_pointer(va_arg(ap, void *));
	else if (format == 'd' || format == 'i')
		count = ft_putnbr(va_arg(ap, int));
	else if (format == 'u')
		count = ft_putnbr_unsigned(va_arg(ap, unsigned int));
	else if (format == 'x')
		count = ft_puthexa(va_arg(ap, unsigned int), "0123456789abcdef");
	else if (format == 'X')
		count = ft_puthexa(va_arg(ap, unsigned int), "0123456789ABCDEF");
	else if (format == '%')
		count = ft_putchar('%');
	return (count);
}
