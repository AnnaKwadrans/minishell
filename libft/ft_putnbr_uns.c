/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_uns.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 16:05:45 by akwadran          #+#    #+#             */
/*   Updated: 2024/12/14 16:19:42 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int	calc_len_uns(unsigned long long n)
{
	int	len;

	len = 0;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	len++;
	return (len);
}

char	*ft_itoa_uns(unsigned long long n)
{
	char	*str_n;
	int		len;

	len = calc_len_uns(n);
	str_n = (char *)malloc(sizeof(char) * (len + 1));
	if (str_n == NULL)
		return (NULL);
	str_n[len] = '\0';
	while (n > 9)
	{
		str_n[len - 1] = (n % 10) + '0';
		n = n / 10;
		len --;
	}
	str_n[--len] = n + '0';
	return (str_n);
}

int	ft_putnbr_unsigned(unsigned long long n)
{
	int		count;
	char	*n_str;

	n_str = ft_itoa_uns(n);
	count = ft_putstr(n_str);
	free(n_str);
	return (count);
}
