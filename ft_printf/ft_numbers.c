/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numbers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yude-oli <yude-oli@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 10:40:53 by yude-oli          #+#    #+#             */
/*   Updated: 2023/11/01 12:05:49 by yude-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_intnumber(int nbr, int *len)
{
	if (nbr == INT_MIN)
	{
		write(1, "-2147483648", 11);
		(*len += 11);
		return ;
	}
	if (nbr < 0)
	{
		ft_putchar_len('-', len);
		ft_intnumber(nbr * -1, len);
	}
	else
	{
		if (nbr > 9)
			ft_intnumber(nbr / 10, len);
		ft_putchar_len(nbr % 10 + '0', len);
	}
}

void	ft_pointer(size_t pointer, int *len)
{
	char	string[25];
	int		i;
	char	*base_char;

	base_char = "0123456789abcdef";
	i = 0;
	if (pointer == 0)
	{
		write (1, "(nil)", 5);
		(*len) += 5;
		return ;
	}
	write (1, "0x", 2);
	(*len) += 2;
	while (pointer != 0)
	{
		string[i] = base_char[pointer % 16];
		pointer = pointer / 16;
		i++;
	}
	while (i--)
	{
		ft_putchar_len(string[i], len);
	}
}

void	ft_hexa_in_lower_or_upper(unsigned int x, int *len, char deftype_x)
{
	char	string[25];
	char	*base_char;
	int		i;

	i = 0;
	if (deftype_x == 'X')
		base_char = "0123456789ABCDEF";
	else
		base_char = "0123456789abcdef";
	if (x == 0)
	{
		ft_putchar_len('0', len);
	}
	while (x != 0)
	{
		string[i] = base_char [x % 16];
		x = x / 16;
		i++;
	}
	while (i--)
		ft_putchar_len(string[i], len);
}

void	ft_unsigned_int(unsigned int u, int *len)
{
	if (u >= 10)
		ft_unsigned_int(u / 10, len);
	ft_putchar_len(u % 10 + '0', len);
}
