/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 10:14:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/12/01 10:51:48 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printformat(va_list args, const char format)
{
	if (format == '%')
		return (write(1, "%", 1));
	else if (format == 'c')
		return (ft_printchar(va_arg(args, int)));
	else if (format == 's')
		return (ft_printstr(va_arg(args, char *)));
	else if (format == 'd')
		return (ft_print_number(va_arg(args, int)));
	return (0);
}

int	ft_printf(char const *str, ...)
{
	int		i;
	int		count;
	va_list	args;

	va_start(args, str);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_printformat(args, str[i]);
		}
		else
			count += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
