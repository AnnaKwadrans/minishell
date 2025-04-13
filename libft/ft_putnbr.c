/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:59:55 by akwadran          #+#    #+#             */
/*   Updated: 2025/04/13 21:50:03 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int		count;
	char	*n_str;

	n_str = ft_itoa(n);
	count = ft_putstr(n_str);
	free(n_str);
	return (count);
}
