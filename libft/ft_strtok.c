/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:12:27 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 20:12:27 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok_r(char *str, const char *delim, char **next)
{
	char	*token;

	token = ft_strnstr(str, delim, ft_strlen(str));
	if (token)
	{
		*token = '\0';
		*next = token + ft_strlen(delim);
	}
	else
	{
		*next = NULL;
	}
	return (token);
}

char	*ft_strtok(char *str, const char *delim)
{
	char	*token;

	token = ft_strtok_r(str, delim, &str);
	return (token);
}
