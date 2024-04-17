/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yowoo <yowoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:22:24 by yowoo             #+#    #+#             */
/*   Updated: 2024/04/17 11:23:12 by yowoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		rl_redisplay();
}

void	sigchecker(int sigint, int sigquit)
{
	if (sigint)
		signal(SIGINT, sighandler);
	if (sigquit)
		signal(SIGQUIT, sighandler);
}

void	catchsignal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL); //to hide ^C 
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	sigchecker(1, 1);
}
