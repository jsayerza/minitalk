/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsayerza <jsayerza@student.42barcelona.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:30:00 by jsayerza          #+#    #+#             */
/*   Updated: 2024/12/06 21:52:14 by jsayerza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <signal.h>

typedef struct s_mini
{
	int	pid_server;
	int	pid_client;
}	t_mini;

t_mini	*client_start(void);
t_mini	*server_start(void);
void	client_send(t_mini *talk, char *message);
void	server_receive(int signum);
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
void	ft_putstr(char *str);
void	ft_putnbr(int num);

#endif