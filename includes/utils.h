/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marykman <marykman@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 17:29:35 by marykman          #+#    #+#             */
/*   Updated: 2024/09/02 17:55:22 by marykman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define BASE_DECI	"0123456789"

# include <stddef.h>

size_t	ft_strlen(const char *str);
int		ft_isspace(int c);
int		ft_index(const char *s, char c);
long	ft_strtol(const char *str, char **endptr, const char *base);

#endif
