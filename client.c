/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:40:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/12/03 18:38:42 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int ac, char **av)
{
	char	*msg;
	int		serverid;

	if (ac == 3)
	{
		serverid = ft_atoi(av[1]);
		if (!serverid)
		{
			ft_printf("Error. Incorrect argument: server id.\n");
			return (9);
		}
		msg = av[2];
		if (msg[0] == 0)
		{
			ft_printf("Error. Incorrect argument: message.\n");
			return (9);
		}
		ft_printf("Message:%s\n", msg);
	}
	else
	{
		ft_printf("Error. Incorrect number of arguments.\n");
		ft_printf("Usage: ./client <PID> <message>");
	}
	return (0);
}
