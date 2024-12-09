/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:40:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/12/06 21:50:11 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_mini	*client_initiate(void)
{
	t_mini	*talk;

	talk = malloc(sizeof(t_mini));
	if (!talk)
	{
		ft_putstr("ERROR! malloc fail\n");
		exit(EXIT_FAILURE);
	}
	talk->pid_server = 0;
	talk->pid_client = 0;
	return (talk);
}

void	client_send(t_mini *talk, char *message)
{
	int	bit_displacement;
	int	i;
	int	signal;

	printf("msg:%s\n", message);
	i = -1;
	while (++i <= ft_strlen(message))
	{
		printf("\nmessage[%d]:%c\n", i, message[i]);
		bit_displacement = -1;
		signal = 0;
		while (++bit_displacement < 8)
		{
			if ((message[i] >> bit_displacement) & 1)
			{
				signal = SIGUSR2;
			}
			else
				signal = SIGUSR1;
			printf("%d", signal == SIGUSR1? 0: 1);
			kill(talk->pid_server, signal);
			usleep(200);
		}
	}
	printf("\n");
	return ;
}

int	main(int nword, char *arguments[])
{
	t_mini	*talk;

	talk = NULL;
	if (nword != 3)
	{
		ft_putstr("ERROR!, Usage: ./client <server PID> <message>\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		talk = client_initiate();
		talk->pid_server = ft_atoi(arguments[1]);
		if (talk->pid_server <= 0)
		{
			ft_putstr("ERROR!, Incorrect PID\n");
			free(talk);
			exit(EXIT_FAILURE);
		}
		client_send(talk, arguments[2]);
	}
	free(talk);
	return (EXIT_SUCCESS);
}