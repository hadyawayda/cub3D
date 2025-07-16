/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:41:04 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 19:41:04 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Helpers that did not fit elsewhere
   (ft_file_to_str and ft_split_free). */

char	*ft_file_to_str(char *path)
{
	int		fd;
	char	buf[1024];
	int		r;
	char	*tmp;
	char	*out;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	out = ft_strdup("");
	while ((r = read(fd, buf, 1023)) > 0)
	{
		buf[r] = 0;
		tmp = ft_strjoin(out, buf);
		free(out);
		out = tmp;
	}
	close(fd);
	return (out && *out ? out : NULL);
}

void	ft_split_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}
