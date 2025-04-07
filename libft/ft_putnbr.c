/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:59:55 by akwadran          #+#    #+#             */
/*   Updated: 2024/12/21 14:59:58 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

static int	calc_len(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	len++;
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str_n;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = calc_len(n);
	str_n = (char *)malloc(sizeof(char) * (len + 1));
	if (str_n == NULL)
		return (NULL);
	if (n < 0)
	{
		str_n[0] = '-';
		n = -n;
	}
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

int	ft_putnbr(int n)
{
	int		count;
	char	*n_str;

	n_str = ft_itoa(n);
	count = ft_putstr(n_str);
	free(n_str);
	return (count);
}
