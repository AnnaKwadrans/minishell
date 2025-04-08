/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 22:29:12 by akwadran          #+#    #+#             */
/*   Updated: 2024/10/14 21:25:48 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	substr_len;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		substr_len = 0;
	else if (ft_strlen(s) - start < len)
		substr_len = ft_strlen(s) - start;
	else
		substr_len = len;
	ptr = malloc((sizeof(char) * (substr_len + 1)));
	if (ptr == NULL)
		return (NULL);
	else
	{
		if (start >= ft_strlen(s))
			ft_strlcpy(ptr, "", substr_len + 1);
		else
			ft_strlcpy(ptr, s + start, substr_len + 1);
		return (ptr);
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	else
	{
		ft_strlcpy(ptr, s1, ft_strlen(s1) + 1);
		ft_strlcat(ptr, s2, len + 1);
		return (ptr);
	}
}

static int	is_set(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*ptr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	if (!(*s1))
		return (ft_strdup(""));
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && is_set(s1[i], set))
		i++;
	while (is_set(s1[j], set) && j >= i)
		j--;
	ptr = (char *)malloc(sizeof(char) * (j - i + 2));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1 + i, j - i + 2);
	return (ptr);
}
