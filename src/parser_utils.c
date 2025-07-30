/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:41:04 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/30 21:16:19 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*read_fd_to_str(int fd)
{
	char	buf[1024];
	int		r;
	char	*out;
	char	*tmp;

	out = ft_strdup("");
	while (1)
	{
		r = read(fd, buf, 1023);
		if (r <= 0)
			break ;
		buf[r] = '\0';
		tmp = ft_strjoin(out, buf);
		free(out);
		if (!tmp)
			return (NULL);
		out = tmp;
	}
	if (*out == '\0')
		return (free(out), NULL);
	return (out);
}

char	*ft_file_to_str(char *path)
{
	int		fd;
	char	*result;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	result = read_fd_to_str(fd);
	close(fd);
	return (result);
}

void	ft_split_free(char **arr)
{
	size_t	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

bool	valid_cell(char ch)
{
	return (ch == '0' || ch == '1' || ch == ' ' || ch == DOOR_CLOSED
		|| ch == SPRITE_CHAR || ch == 'N' || ch == 'S' || ch == 'E'
		|| ch == 'W');
}

/*
**  After scanning all lines, ensure each texture path and both colors were set.
*/
bool	check_required_elements(t_cub *c)
{
	if (!c->tex[0].img.ptr || !c->tex[1].img.ptr || !c->tex[2].img.ptr
		|| !c->tex[3].img.ptr || c->floor_col == -1 || c->ceil_col == -1)
		return (c->err = "Missing element.", false);
	return (true);
}
