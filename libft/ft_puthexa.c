/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:59:11 by akwadran          #+#    #+#             */
/*   Updated: 2024/12/28 20:32:11 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int	calc_len_hexa(unsigned long long n)
{
	int	len;

	len = 0;
	while (n > 15)
	{
		n /= 16;
		len++;
	}
	len++;
	return (len);
}

char	*ft_itoa_hexa(unsigned long long n, char *base)
{
	char	*str_n;
	int		len;

	len = calc_len_hexa(n);
	str_n = (char *)malloc(sizeof(char) * (len + 1));
	if (str_n == NULL)
		return (NULL);
	str_n[len] = '\0';
	while (n > 15)
	{
		str_n[len - 1] = (base[n % 16]);
		n = n / 16;
		len --;
	}
	str_n[--len] = base[n];
	return (str_n);
}

int	ft_puthexa(unsigned long long n, char *base)
{
	int		count;
	char	*n_str;

	count = 0;
	n_str = ft_itoa_hexa(n, base);
	count += ft_putstr(n_str);
	free(n_str);
	return (count);
}

int	ft_pointer(void *ptr)
{
	int					count;
	unsigned long long	n;

	if (ptr == NULL)
		return (ft_putstr("(nil)"));
	n = (unsigned long long)ptr;
	count = ft_putstr("0x");
	count += ft_puthexa(n, "0123456789abcdef");
	return (count);
}
