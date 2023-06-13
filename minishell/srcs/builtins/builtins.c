/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:42:32 by mgraaf            #+#    #+#             */
/*   Updated: 2023/06/13 20:10:41 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_exit(int status)
{
	exit(status);
}

//dava erro sem o "[0]"
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
		printf("%s\n", mshell->envior[i]);
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

int	builtins(t_cmds *cmds, t_mshell *mshell)
{
	check_redirect(cmds);
	if (cmds->words)
	{
		if (!ft_strncmp("pwd", cmds->words[0], 3))
			return (b_pwd());
		else if (!ft_strncmp("echo", cmds->words[0], 4))
			return (b_echo(&cmds->words[1], cmds->count_words - 1));
		else if (!ft_strncmp("cd", cmds->words[0], 2))
			return (b_cd(cmds->words[1], mshell));
		else if (!ft_strncmp("exit", cmds->words[0], 4))
			b_exit(0);
		else if (!ft_strncmp("env", cmds->words[0], 3))
			return (b_env(mshell));
		else if (!ft_strncmp("export", cmds->words[0], 6))
			return (b_export(cmds->words[1], mshell));
		else if (!ft_strncmp("unset", cmds->words[0], 5))
			return (b_unset(cmds->words[1], mshell));
		else
			executables(cmds->words, mshell);
	}
	return (error_cmd_not_found(cmds->words[0]));
}
