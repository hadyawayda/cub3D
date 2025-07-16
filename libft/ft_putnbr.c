/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:10:40 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 20:10:40 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	nbr_len(int nb)
{
	int	length;

	length = 0;
	if (nb == -2147483648)
		return (11);
	if (nb == 0)
		length++;
	if (nb < 0)
	{
		nb = -nb;
		length++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		length++;
	}
	return (length);
}

int	ft_putnbr(int nb)
{
	int	length;

	length = nbr_len(nb);
	if (nb == -2147483648)
	{
		ft_putchar('-');
		ft_putchar('2');
		nb = 147483648;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		ft_putchar(nb + '0');
	}
	return (length);
}
