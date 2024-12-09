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

void	send_signals(int pid, char *message)
{
	int				letter;
	int				i;

	letter = 0;
	while (message[letter])
	{
		i = -1;
		while (++i < 8)
		{
			if (((unsigned char)(message[letter] >> (7 - i)) & 1) == 0)
				kill(pid, SIGUSR1);
			else if (((unsigned char)(message[letter] >> (7 - i)) & 1) == 1)
				kill(pid, SIGUSR2);
			usleep(50);
		}
	letter++;
	}
	i = 0;
	while (i++ < 8)
	{
		kill(pid, SIGUSR1);
		usleep(50);
	}
}

int	main(int argc, char **argv)
{
	char				*message;
	int					server_id;

	if (argc == 3)
	{
		server_id = ft_atoi(argv[1]);
		if (!server_id)
		{
			ft_printf("[ERROR]. Wrong arg");
			return (0);
		}
		message = argv[2];
		if (message[0] == 0)
		{
			ft_printf("Tu n'as envoyé aucun texte ! Ecris qqch pls :)");
			return (0);
		}
		send_signals(server_id, message);
	}
	else
	{
		ft_printf("[ERROR]. Too much or too few arguments.\n Make sure ");
		ft_printf("you enter arguments as follow: ./client <PID> <MESSAGE>");
	}
	return (0);
}