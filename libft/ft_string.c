/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:40:21 by akwadran          #+#    #+#             */
/*   Updated: 2024/09/28 00:18:56 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n > 0)
	{
		*ptr = c;
		n--;
		ptr++;
	}
	return (s);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n > 0)
	{
		*ptr = 0;
		n--;
		ptr++;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr;

	dest_ptr = dest;
	src_ptr = src;
	if (dest_ptr == 0 && src_ptr == 0)
		return (dest);
	while (n > 0)
	{
		*dest_ptr = *src_ptr;
		n--;
		dest_ptr++;
		src_ptr++;
	}
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_ptr;
	const unsigned char	*src_ptr;

	if (dest == 0 && src == 0)
		return (dest);
	dest_ptr = dest;
	src_ptr = src;
	if (src > dest)
		ft_memcpy(dest, src, n);
	else if (src < dest)
	{
		while (n > 0)
		{
			*(dest_ptr + n - 1) = *(src_ptr + n - 1);
			n--;
		}
	}
	return (dest);
}
