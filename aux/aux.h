/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 18:06:32 by akwadran          #+#    #+#             */
/*   Updated: 2025/07/12 18:07:37 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AUX_H
# define AUX_H

# include "../data.h"
# include "../libft/libft.h"
# include "../parser/parser.h"

// 👇 Forward declaration
typedef struct s_cmd	t_cmd;
typedef struct s_data	t_data;

// ARRAY FUNCTIONS

size_t	array_size(char **array);
void	print_array(char **array);
void	free_array(char **array);
char	**join_arrays(char **array, char **add);

#endif
