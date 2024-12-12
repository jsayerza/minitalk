/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:40:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/12/10 12:17:58 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_receiver = 0;
static int	g_byte_index = 0;

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	i = 0;

	(void)context;
	(void)info;
	g_receiver = 1;
	if (signum == SIGUSR2)
		i++;
	else if (signum == SIGUSR1)
	{
		ft_printf("Bytes sent    : %d\n", g_byte_index);
		ft_printf("Bytes received: %d\n", i / 8);
	}
}

int	char_to_bin(char c, int server_pid)
{
	int	itr;
	int	bit_index;

	bit_index = 7;
	while (bit_index >= 0)
	{
		if ((c >> bit_index) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		itr = 0;
		while (g_receiver == 0)
		{
			if (itr == WAIT_RESPONSE)
			{
				perror("No response from server");
				exit(EXIT_FAILURE);
			}
			itr++;
			usleep(DELAY);
		}
		g_receiver = 0;
		bit_index--;
	}
	return (0);
}

static int	client(char *msg, int server_pid)
{
	struct sigaction	sa;
	sigset_t			set;

	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	sigprocmask(SIG_UNBLOCK, &set, NULL);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("Error setting up signal handlers");
		exit(EXIT_FAILURE);
	}
	while (msg[g_byte_index] != 0)
	{
		char_to_bin(msg[g_byte_index], server_pid);
		g_byte_index++;
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
