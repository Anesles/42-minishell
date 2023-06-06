/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:13:36 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/06/06 14:13:37 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    error_cmd_not_found(char *cmd)
{
    ft_putstr_fd("Command '", STDERR_FILENO);
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd("' not found\n", STDERR_FILENO);
//    g_exit_status = 127;
}

//void    ()