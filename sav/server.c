/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:35:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/12/07 10:11:04 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*void	signal_handler(int signum)
{
	static int	signal_count = 0;

    if (signum == SIGUSR1)
//		printf("sig_count:%d signum:%d  --> 0\n", signum, signal_count);
		printf("0");
    else if (signum == SIGUSR2)
//		printf("sig_count:%d signum:%d  --> 1\n", signum, signal_count);
		printf("1");
	else
//		printf("sig_count:%d signum:%d  --> ?\n", signum, signal_count);
		printf("?");
	signal_count++;
	if (signal_count == 8)
	{
		printf("\n");
		signal_count = 0;
	}
}*/

void	signal_handler(int signum)
{
	static unsigned char	c = 0;
	static int				bit_count = 0;

	if (signum == SIGUSR2)
		c |= (1 << (7 - bit_count)); // Set the corresponding bit to 1
	else if (signum == SIGUSR1)
		c &= ~(1 << (7 - bit_count)); // Ensure the bit is 0

	bit_count++;
	if (bit_count == 8) // When a full character is received
	{
		if (c == '\0') // End of message
			ft_printf("\n");
		else
			write(1, &c, 1);
		c = 0;
		bit_count = 0;
	}
}


int	main(void)
{
	struct sigaction	action;

	printf("Server PID: %d\n", getpid());

	action.sa_handler = signal_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = SA_RESTART;

	if (sigaction(SIGUSR1, &action, NULL) == -1 
		|| sigaction(SIGUSR2, &action, NULL) == -1)
	{
		perror("Error setting up signal handlers");
		return (EXIT_FAILURE);
	}
	while (1)
		pause();
	return (EXIT_SUCCESS);
}
