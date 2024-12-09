/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:35:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/12/06 21:46:52 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handler(int signum)
{
	static int	signal_count = 0;
	char		c;

//	ft_printf("signum:%d sig_count:%d\n", signum, signal_count);
//	c = 0;
    if (signum == SIGUSR1)
		signal_count++;
    else if (signum == SIGUSR2)
	{
		c = (char)signal_count;
		if (signal_count > 0)
			write(1, &c, 1);
		signal_count = 0;
	}
}


int	main(void)
{
	struct sigaction	action;

	ft_printf("Server PID: %d\n", getpid());

	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;

//	sigaction(SIGUSR1, &action, NULL);
//	sigaction(SIGUSR2, &action, NULL);
	if (sigaction(SIGUSR1, &action, NULL) == -1 
		|| sigaction(SIGUSR2, &action, NULL) == -1)
	{
		ft_printf("Error setting up signal handlers.\n");
		return (1);
	}
	while (1)
	{
		pause();
	}
	return (0);
}
