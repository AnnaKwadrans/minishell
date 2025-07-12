/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:54:34 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/12 17:55:01 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX) == NULL)
	{
		perror("getcwd failed");
		return (1);
	}
	printf("%s\n", path);
	return (0);
}
