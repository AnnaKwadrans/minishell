/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akwadran <akwadran@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:21:58 by akwadran          #+#    #+#             */
/*   Updated: 2024/12/28 20:30:45 by akwadran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include "ft_printf.h"

int		ft_printf(char const *str, ...);
int		get_format(char format, va_list ap);

int		ft_putstr(char *s);
int		ft_putchar(char c);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);

char	*ft_itoa(int n);
int		ft_putnbr(int n);
char	*ft_itoa_uns(unsigned long long n);
int		ft_putnbr_unsigned(unsigned long long n);
char	*ft_itoa_hexa(unsigned long long n, char *base);
int		ft_puthexa(unsigned long long n, char *base);
int		ft_pointer(void *ptr);

#endif