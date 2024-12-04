/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:14:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/12/03 19:00:19 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
//#include "../libft/libft.h"

int	ft_printchar(int c)
{
	unsigned char	ch;

	ch = (unsigned char)c;
	if (write(1, &ch, 1) != -1)
		return (1);
	return (0);
}

int	ft_printstr(char const *str)
{
	size_t	i;

	if (str == NULL)
		return (write(1, "(null)", 6));
	else
	{
		i = 0;
		while (str[i])
			i++;
		return (write(1, str, i));
//		return (write(1, str, ft_strlen(str)));
	}
}

int	ft_print_unsigned(unsigned int n)
{
	int	size;

	size = 0;
	if (n == 0)
		size += ft_printchar('0');
	else
	{
		if (n / 10 != 0)
			ft_print_unsigned(n / 10);
		ft_printchar((n % 10) + '0');
		while (n > 0)
		{
			n /= 10;
			size++;
		}
	}
	return (size);
}

int	ft_print_number(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		size += ft_printchar('0');
	if (n == -2147483648)
	{
		size += ft_printstr("-2147483648");
		return (size);
	}
	if (n < 0)
	{
		size += ft_printchar('-');
		n = -n;
	}
	if (n > 0)
		size += ft_print_unsigned((unsigned int)n);
	return (size);
}
