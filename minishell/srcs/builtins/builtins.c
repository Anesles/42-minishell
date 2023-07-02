/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:42:32 by mgraaf            #+#    #+#             */
/*   Updated: 2023/06/14 17:43:56 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_exit(int status, t_mshell *mshell)
{
	int	i;

	i = -1;
	while (mshell->envior[++i])
		free(mshell->envior[i]);
	free(mshell->envior[i]);
	free(mshell->envior);
	exit(status);
}

int	b_pwd(void)
{
	char	str[256];

	getcwd(str, sizeof(str));
	if (!str[0])
		return (EXIT_FAILURE);
	printf("%s\n", str);
	return (EXIT_SUCCESS);
}

int	b_env(t_mshell *mshell)
{
	int	i;

	i = 0;
	while (mshell->envior[i])
	{
		ft_printf("%s\n", mshell->envior[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

void	check_redirect(t_cmds *cmds)
{
	if (cmds->token != NULL)
	{
		if (!ft_strncmp(cmds->token, ">>", 2))
			token_more(cmds, 1);
		else if (!ft_strncmp(cmds->token, "<<", 2))
			token_less(cmds, 1);
		else if (!ft_strncmp(cmds->token, ">", 1))
			token_more(cmds, 0);
		else if (!ft_strncmp(cmds->token, "<", 1))
			token_less(cmds, 0);
	}
}

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

int	builtins(t_cmds *cmds, t_mshell *mshell)
{
	int	var;
	
	check_redirect(cmds);
	if (cmds->words)
	{
		if (!ft_strncmp("pwd", cmds->words[0], 3))
			return (b_pwd());
		else if (!ft_strncmp("echo", cmds->words[0], 4))
			return (b_echo(&cmds->words[1], cmds->count_words - 1));
		else if (!ft_strncmp("cd", cmds->words[0], 2))
		{
			if (cmds->words[2] != NULL)
				return (EXIT_FAILURE);
			return (b_cd(cmds->words[1], mshell));
		}
		else if (!ft_strncmp("exit", cmds->words[0], 4))
		{
			if (valid_exit(&cmds->words[1]))
				return (2);
			if (cmds->words[1] == NULL)
				b_exit(0, mshell);
			var = ft_atoi(cmds->words[1]);
			b_exit(var, mshell);
		}
		else if (!ft_strncmp("env", cmds->words[0], 3))
			return (b_env(mshell));
		else if (!ft_strncmp("export", cmds->words[0], 6))
			return (b_export(cmds->words, mshell));
		else if (!ft_strncmp("unset", cmds->words[0], 5))
			return (b_unset(cmds->words[1], mshell));
		else
			executables(cmds->words, mshell);
	}
	return (error_cmd_not_found(cmds->words[0]));
}
