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

t_mini	*server_initiate(void)
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

void	print_bits(unsigned char octet)
{
	unsigned char	bit;
	int				i;

	bit = 0;
	i = 8;
	while (i--)
	{
		bit = ((octet >> i) & 1) + '0';
		write(1, &bit, 1);
	}
}

void	server_recieve(int signum)
{
	static int	bit_displacement = 0;
	static char	letter = 0;
	int			boolean;

	boolean = 0;
	if (signum == SIGUSR2)
		boolean = 1;
	letter += ((boolean & 1) << bit_displacement++);
	print_bits((unsigned char )letter);
	printf("signum: %d boolean:%d bit_displacement:%d\n", \
		signum, boolean, bit_displacement);
	if (bit_displacement == 8)
	{
		printf("letter:%c\n", letter);
		print_bits((unsigned char )letter);
		printf("\n");
		write(1, &letter, 1);
//		if (!letter)
			write(1, "\n", 1);
		bit_displacement = 0;
		letter = 0;
	}
	return ;
}

void	server_loop(t_mini *talk)
{
	while (1)
	{
		if ((signal(SIGUSR1, server_recieve) == SIG_ERR)
			|| (signal(SIGUSR2, server_recieve) == SIG_ERR))
		{
			ft_putstr("ERROR!, Signal error x_x!\n");
			free(talk);
			exit(EXIT_FAILURE);
		}
		sleep(5);
	}
	return ;
}

int	main(int nword, char *arguments[])
{
	t_mini	*talk;

	(void)arguments;
	talk = NULL;
	if (nword != 1)
	{
		ft_putstr("ERROR!, Usage: ./server\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		talk = server_initiate();
		talk->pid_server = getpid();
		ft_putstr("Server PID: ");
		ft_putnbr(talk->pid_server);
		write(1, "\n", 1);
		server_loop(talk);
	}
	free(talk);
	return (EXIT_SUCCESS);
}