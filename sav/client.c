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

static void	send_signs(pid_t server_pid, char *msg)
{
	unsigned char	c;
	int				bit;
	int				i;

	i = 0;
	while (msg[i])
	{
		c = (unsigned char)msg[i];
		printf("\nmsg:%s c:%c -->", msg, c);
		bit = 8;
		while (bit--)
		{
			if ((c >> bit) & 1)
			{
				printf("|");
				if (kill(server_pid, SIGUSR2) == -1)
				{
					perror("Error sending SIGUSR2");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				printf("o|");
				if (kill(server_pid, SIGUSR1) == -1)
				{
					perror("Error sending SIGUSR1");
					exit(EXIT_FAILURE);				}
			}
			usleep(DELAY);
		}
		i++;
	}
	printf("\n");
	bit = 8;
	while (bit--)
	{
		printf("o");
		if (kill(server_pid, SIGUSR1) == -1)
		{
			perror("Error sending SIGUSR1");
			exit(EXIT_FAILURE);
		}
		usleep(DELAY);
	}
	printf("\n");
}

int	main(int ac, char **av)
{
//	char	*msg;
	pid_t	server_pid;

	if (ac != 3)
	{
		ft_printf("Usage: %s <PID> <message>\n", av[0]);
		return (EXIT_FAILURE);
	}

	server_pid = ft_atoi(av[1]);
	if (server_pid <= 0)
	{
		ft_printf("Error: Invalid PID.\n");
		return (EXIT_FAILURE);
	}

	send_signs(server_pid, av[2]);
	return (EXIT_SUCCESS);

/*	if (ac == 3)
	{
		server_pid = ft_atoi(av[1]);
		if (!server_pid)
		{
			printf("Error. Incorrect argument: server id.\n");
			return (1);
		}
		msg = av[2];
		if (msg[0] == 0)
		{
			printf("Error. Incorrect argument: message.\n");
			return (1);
		}
		printf("Message:%s\n", msg);
		send_signs(server_pid, msg);
	}
	else
	{
		printf("Error. Incorrect number of arguments.\n");
		printf("Usage: ./client <PID> <message>");
	}
	return (0);*/
}
