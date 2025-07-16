/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:12:23 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 20:12:23 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	nc;
	size_t			i;
	size_t			last_pos;

	i = 0;
	last_pos = (size_t) - 1;
	nc = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == nc)
		{
			last_pos = i;
		}
		i++;
	}
	if (nc == '\0')
	{
		return ((char *)&s[i]);
	}
	else if (last_pos == (size_t) - 1)
	{
		return (NULL);
	}
	return ((char *)&s[last_pos]);
}
