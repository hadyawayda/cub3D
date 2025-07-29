/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 18:05:27 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/29 18:05:27 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

long	get_time_ms(void)
{
	struct timeval tv;

	gettimeofday(&tv, 0);
	return (tv.tv_sec * 1000L + tv.tv_usec / 1000);
}
