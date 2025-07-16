/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:11:14 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 20:11:14 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	ft_strcasecmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (ft_tolower(s1[i]) == ft_tolower(s2[i]) && s1[i] != '\0')
		i++;
	return (ft_tolower(s1[i]) - ft_tolower(s2[i]));
}
