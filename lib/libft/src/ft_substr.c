/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:12:36 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 20:12:36 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		i;
	size_t		j;
	char		*substr;

	i = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start > i)
		len = 0;
	else if (len > i - start)
		len = i - start;
	substr = (char *) malloc ((sizeof(char) * (len + 1)));
	if (!substr)
		return (NULL);
	j = 0;
	while (j < len)
	{
		substr[j] = s[start];
		j++;
		start++;
	}
	substr[j] = '\0';
	return (substr);
}
