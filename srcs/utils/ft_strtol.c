/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:27:03 by marykman          #+#    #+#             */
/*   Updated: 2024/09/02 17:36:15 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static long	set_endptr(const char *str, char **endptr, long n)
{
	if (endptr)
		*endptr = (char *)str;
	return (n);
}

int	check_base(const char *base)
{
	int	base_len;

	if (!base)
		return (0);
	base_len = -1;
	while (base[++base_len])
		if (base[base_len] == '+' || base[base_len] == '-'
			|| ft_isspace(base[base_len])
			|| ft_index(base + base_len + 1, base[base_len]) >= 0)
			return (0);
	return (base_len);
}

/**
 * @brief Function that mimic the strtol function from libc.
 *  Small difference in the base argument wich takes the base string directly
 * instead of the base value.
 * @param str String to be converted
 * @param endptr Stores the address of the first invalid character
 * @param base Used to convert the number
 * @return The converted number as a long
 */
long	ft_strtol(const char *str, char **endptr, const char *base)
{
	unsigned long	n;
	char			sign;
	int				base_len;

	base_len = check_base(base);
	if (base_len <= 1)
		return (set_endptr(str, endptr, 0));
	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	n = 0;
	while (ft_index(base, *str) >= 0)
		n = n * base_len + ft_index(base, *str++);
	return (set_endptr(str, endptr, n * sign));
}
