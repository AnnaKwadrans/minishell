/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:00:35 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/12 18:01:22 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	update_pwd_var(t_data *data)
{
	t_vars	*pwd;
	char	path[PATH_MAX];

	if (getcwd(path, PATH_MAX) == NULL)
		return (perror("getcwd failed"));
	pwd = search_var(data, "PWD");
	free(pwd->value);
	pwd->value = ft_strdup(path);
	return ;
}

int	ft_cd(t_data *data, char **args)
{
	t_vars	*home_var;
	char	*home_path;

	if (array_size(args) > 2)
	{
		ft_putendl_fd("too many arguments", 2);
		return (1);
	}
	else if (array_size(args) == 1 || ft_strncmp(args[1], "~", 1) == 0)
	{
		home_var = search_var(data, "HOME");
		if (chdir(home_var->value) == -1)
			return (perror("chdir failed"), 1);
	}
	else
	{
		if (chdir(args[1]) == -1)
			return (perror("chdir failed"), 1);
	}
	update_pwd_var(data);
	return (0);
}
