/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:49:34 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/31 17:14:39 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_pipe(t_mshell *mshell)
{
	if (mshell->current_cmd == mshell->n_cmds - 1)
	{
		dup2(mshell->fd[0], STDIN_FILENO);
		close(mshell->fd[0]);
		close(mshell->fd[1]);
	}
	else
	{
		dup2(mshell->fd[1], STDOUT_FILENO);
		close(mshell->fd[0]);
		close(mshell->fd[1]);
	}
}

void	reset_pipes(t_mshell *mshell)
{
	dup2(mshell->save_fd[0], STDIN_FILENO);
	dup2(mshell->save_fd[1], STDOUT_FILENO);
}