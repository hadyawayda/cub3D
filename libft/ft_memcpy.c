/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:10:03 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 20:10:03 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*a;
	char	*b;

	i = 0;
	a = (char *)dest;
	b = (char *)src;
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return ((void *)a);
}
