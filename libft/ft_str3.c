/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:49:55 by akwadran          #+#    #+#             */
/*   Updated: 2024/10/14 17:54:12 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	unsigned int	i;

	ptr = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
