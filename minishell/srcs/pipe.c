/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 17:49:34 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/23 17:52:03 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_in(t_mshell *mshell)
{
	dup2(mshell->fd[0], STDIN_FILENO);
	dup2(mshell->fd[1], STDOUT_FILENO);	
}