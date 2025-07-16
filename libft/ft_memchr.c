/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:09:54 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 20:09:54 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*a;
	size_t				i;
	unsigned char		b;

	i = 0;
	a = (const unsigned char *)s;
	b = (unsigned char )c;
	while (i < n)
	{
		if (a[i] == b)
			return ((void *)(a + i));
		i++;
	}
	return (NULL);
}
