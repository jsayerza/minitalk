/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:40:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/12/07 10:10:17 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(pid_t server_pid, char c)
{
	int	ascii_val;
	int	i;

	ascii_val = (int)c;
	i = 0;
	while (i < ascii_val)
	{
//		ft_printf("i:%d ascii_val:%d c:%c\n", i, ascii_val, c);
		if (kill(server_pid, SIGUSR1) == -1)
		{
			ft_printf("Error: Unable to send SIGUSR1.\n");
			return ;
		}
		usleep(DELAY);
		i++;
	}
	if (kill(server_pid, SIGUSR2) == -1)
		ft_printf("Error: Unable to send SIGUSR2.\n");
}

int	main(int ac, char **av)
{
	char	*msg;
	pid_t	server_pid;

	if (ac == 3)
	{
		server_pid = ft_atoi(av[1]);
		if (!server_pid)
		{
			ft_printf("Error. Incorrect argument: server id.\n");
			return (1);
		}
		msg = av[2];
		if (msg[0] == 0)
		{
			ft_printf("Error. Incorrect argument: message.\n");
			return (1);
		}
		ft_printf("Message:%s\n", msg);
		while (*msg)
			send_char(server_pid, *msg++);
	}
	else
	{
		ft_printf("Error. Incorrect number of arguments.\n");
		ft_printf("Usage: ./client <PID> <message>");
	}
	return (0);
}
