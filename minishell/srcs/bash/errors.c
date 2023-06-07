/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:13:36 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/06/07 14:59:29 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int  g_exit_status;

void    error_cmd_not_found(char *cmd)
{
    ft_putstr_fd("Command '", STDERR_FILENO);
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd("' not found\n", STDERR_FILENO);
    b_exit(127);
}

int    error_cd(char *cmd)
{
    ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
    ft_putstr_fd(cmd, STDERR_FILENO);
    ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
    return (1);
}
//void    ()