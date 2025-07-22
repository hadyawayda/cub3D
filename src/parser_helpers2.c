/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helpers2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 15:46:26 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/22 15:46:26 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**  Return true if 's' ends in ".xpm"
*/
bool	has_xpm_ext(char *s)
{
	size_t	len;

	if (!s)
		return (false);
	len = ft_strlen(s);
	if (len < 5)
		return (false);
	return (ft_strcmp(s + len - 4, ".xpm") == 0);
}
