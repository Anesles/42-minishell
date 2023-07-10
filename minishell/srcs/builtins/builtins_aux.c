/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_aux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 14:13:20 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/07/07 15:25:13 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_exit(char	**str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (i >= 1)
			exit(1);
		if (str[i][0] == '-' || str[i][0] == '+')
			j = 1;
		else
			j = 0;
		while (str[i][j])
		{
			if (!ft_isdigit(str[i][j]))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	builtins_aux(t_cmds *cmds, t_mshell *mshell)
{
	int	var;

	if (!ft_strncmp("exit", cmds->words[0], 5))
	{
		if (valid_exit(&cmds->words[1]))
			return (2);
		if (cmds->words[1] == NULL)
			b_exit(0, mshell);
		var = ft_atoi(cmds->words[1]);
		b_exit(var, mshell);
	}
	else if (!ft_strncmp("env", cmds->words[0], 4))
		return (b_env(mshell));
	else if (!ft_strncmp("export", cmds->words[0], 7))
		return (b_export(cmds->words, mshell));
	else if (!ft_strncmp("unset", cmds->words[0], 6))
		return (b_unset(cmds->words, mshell));
	else
		executables(cmds->words, mshell);
	return (error_cmd_not_found(cmds));
}
