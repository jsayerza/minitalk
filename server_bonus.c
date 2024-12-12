/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:35:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/12/10 12:40:06 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	bin_to_char(int signum, char *c)
{
	if (signum == SIGUSR1)
		*c = (*c << 1) | 1;
	else if (signum == SIGUSR2)
		*c <<= 1;
}

void	signal_handler(int signum, siginfo_t *info, void *context)
{
	static int	client_pid = 0;
	static int	i = 0;
	static char	c = 0;

	(void)context;
	if (client_pid == 0)
		client_pid = info->si_pid;
	bin_to_char(signum, &c);
	if (++i == 8)
	{
		i = 0;
		if (c == 0)
		{
			kill(client_pid, SIGUSR1);
			client_pid = 0;
			return ;
		}
		write(1, &c, 1);
		c = 0;
	}
	kill(client_pid, SIGUSR2);
}

void	handle_exit(int signum)
{
	(void)signum;
	write(1, "\nExiting server...\n", 19);
	fclose(stdout);
	exit(EXIT_SUCCESS);
}

static int	server(void)
{
	struct sigaction	sa;
	struct sigaction	exit_action;

	ft_printf("Server PID: %d\n", getpid());
	exit_action.sa_handler = handle_exit;
	sigemptyset(&exit_action.sa_mask);
	exit_action.sa_flags = 0;
	sigaction(SIGINT, &exit_action, NULL);
	sigaction(SIGTERM, &exit_action, NULL);
	sa.sa_sigaction = signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1
		|| sigaction(SIGUSR2, &sa, NULL) == -1)
	{
		perror("Error setting up signal handlers");
		exit(EXIT_FAILURE);
	}
	while (1)
		pause();
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	(void)av;
	if (ac != 1)
	{
		perror("ERROR!, Usage: ./server");
		exit(EXIT_FAILURE);
	}
	else
		server();
	return (EXIT_SUCCESS);
}
