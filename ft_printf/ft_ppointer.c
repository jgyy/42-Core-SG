/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ppointer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateow <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 18:56:45 by ateow             #+#    #+#             */
/*   Updated: 2023/09/15 18:56:46 by ateow            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ppointer(unsigned long nbr)
{
	ft_pchar('0');
	ft_pchar('x');
	return (ft_phexapointer(nbr) + 2);
}

int	ft_phexapointer(unsigned long nbr)
{
	char	*hex;
	int		count;

	hex = "0123456789abcdef";
	count = 0;
	if (nbr < 16)
	{
		ft_pchar(hex[nbr]);
		count++;
	}
	else
	{
		count += ft_phexapointer(nbr / 16);
		count += ft_phexapointer(nbr % 16);
	}
	return (count);
}
