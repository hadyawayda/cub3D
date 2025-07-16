/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:11:22 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 20:11:22 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	nc;
	size_t			i;

	i = 0;
	nc = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == nc)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (nc == '\0')
	{
		return ((char *)&s[i]);
	}
	return (NULL);
}
