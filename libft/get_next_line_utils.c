/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:30:15 by akwadran          #+#    #+#             */
/*   Updated: 2025/02/12 20:39:31 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

char	*ft_strjoin_gnl(char *s1, const char *s2)
{
	char	*ptr;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(sizeof(char) * (len + 1));
	if (s1 == NULL || s2 == NULL || ptr == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] && i < len)
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j] && i < len)
	{
		ptr[i] = s2[j];
		i++;
		j++;
	}
	ptr[i] = '\0';
	free(s1);
	return (ptr);
}

char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
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
