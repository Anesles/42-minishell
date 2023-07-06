/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:13:23 by brumarti          #+#    #+#             */
/*   Updated: 2023/07/06 18:39:11 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	sigint_handle_child(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	g_exit_status = 130;
}

void	sig_quit_child(int signum)
{
	(void)signum;
	write(1, "Quit\n", 5);
	g_exit_status = 131;
}

void	sig_continue(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_status = 130;
}

void	sig_fork(void)
{
	signal(SIGINT, &sigint_handle_child);
	signal(SIGQUIT, &sig_quit_child);
}

void	reset_signals(void)
{
	signal(SIGINT, &sig_continue);
	signal(SIGQUIT, SIG_IGN);
}