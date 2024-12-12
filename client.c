/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:40:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/12/10 12:17:58 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	char_to_bin(char c, int server_pid)
{
	int	bit_index;

	bit_index = 7;
	while (bit_index >= 0)
	{
		if ((c >> bit_index) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(DELAY);
		bit_index--;
	}
	return (0);
}

static int	client(char *msg, int server_pid)
{
	int	byte_index;

	byte_index = 0;
	while (msg[byte_index] != 0)
	{
		char_to_bin(msg[byte_index], server_pid);
		byte_index++;
	}
	char_to_bin('\0', server_pid);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[])
{
	int	server_pid;

	if (argc != 3)
	{
		ft_printf("Usage: %s <PID> <message>\n", argv[0]);
		return (EXIT_FAILURE);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		perror("Error: Invalid PID.");
		return (EXIT_FAILURE);
	}
	client(argv[2], server_pid);
	return (EXIT_SUCCESS);
}
