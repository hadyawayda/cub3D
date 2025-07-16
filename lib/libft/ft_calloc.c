/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:08:33 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 20:08:33 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	s_zero(void *s, size_t n)
{
	while (n--)
		*(unsigned char *)s++ = 0;
}

void	*ft_calloc(size_t nbr, size_t s)
{
	void	*ptr;

	if (nbr && s && nbr > (2147483648 / s))
		return (NULL);
	ptr = malloc(nbr * s);
	if (!ptr)
		return (NULL);
	else
		s_zero(ptr, nbr * s);
	return (ptr);
}
