/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:42:32 by mgraaf            #+#    #+#             */
/*   Updated: 2023/05/25 16:21:57 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_echo(char **words, int max_words)
{
	int	i;
	int	mode;

	i = 0;
	mode = 0;
	if (!ft_strncmp(words[i], "-n", 2))
	{
		mode = 1;
		i++;
	}
	while (words[i])
	{
		if (i == max_words - 1)
		{
			if (mode == 0)
				printf("%s\n", words[i]);
			else
				printf("%s", words[i]);
		}
		else
			printf("%s ", words[i]);
		i++;
	}
}

void	b_cd(char *direct)
{
	int	error;

	error = chdir((const char *)direct);
	if (error != 0)
		perror("cd failed");
}

void	b_pwd(void)
{
	char	str[256];
	getcwd(str, sizeof(str));
	printf("%s\n", str);
}

void	b_exit(int status)
{
	exit(status);
}

void	b_env(t_mshell *mshell)
{
	int	i;

	i = 0;
	while (mshell->envior[i])
	{
		printf("%s\n", mshell->envior[i]);
		i++;
	}
}

void b_export(char *new_variable, t_mshell *mshell)
{
	int		count;
	int		i;
	int		mode;
	char	**new_env;

	count = 0;
	mode = 0;
	while (mshell->envior[count])
	{
		if (!ft_strncmp(new_variable, mshell->envior[count], find_char(new_variable, '=')))
			mode = 1;
		count++;
	}
	if (mode == 1)
		count--;
	new_env = (char **)malloc(sizeof(char *) * (count + 2));
	i = 0;
	while (mshell->envior[i])
	{
		if (!ft_strncmp(new_variable, mshell->envior[i], find_char(new_variable, '=')))
			new_env[i] = ft_strdup(new_variable);
		else
			new_env[i] = ft_strdup(mshell->envior[i]);
		i++;
	}
	if (mode == 0)
	{
		new_env[i] = ft_strdup(new_variable);
		new_env[i + 1] = NULL;
	}
	else
		new_env[i] = NULL;
	free(mshell->envior);
	mshell->envior = new_env;
}

void	b_unset(char *variable, t_mshell *mshell)
{
	int		count;
	int		track;
	char	**new_environ;

	count = 0;
	while (mshell->envior[count] != NULL)
		count++;
	new_environ = (char **)malloc(sizeof(char *) * count);
	count = 0;
	track = 0;
	while (mshell->envior[count] != NULL)
	{
		if (ft_strncmp(variable, mshell->envior[count], ft_strlen(variable)))
		{
			new_environ[track] = ft_strdup(mshell->envior[count]);
			track++;
		}
		count++;
	}
	new_environ[track] = NULL;
	mshell->envior = new_environ;
}

void	builtins(t_cmds *cmds, t_mshell *mshell)
{	
	if (cmds->words)
	{
		if (!ft_strncmp("pwd", cmds->words[0], 3))
			b_pwd();
		else if (!ft_strncmp("echo", cmds->words[0], 4))
			b_echo(&cmds->words[1], cmds->count_words - 1);
		else if (!ft_strncmp("cd", cmds->words[0], 2))
			b_cd(cmds->words[1]);
		else if (!ft_strncmp("exit", cmds->words[0], 4))
			b_exit(0);
		else if (!ft_strncmp("env", cmds->words[0], 3))
			b_env(mshell);
		else if (!ft_strncmp("export", cmds->words[0], 6))
			b_export(cmds->words[1], mshell);
		else if (!ft_strncmp("unset", cmds->words[0], 5))
			b_unset(cmds->words[1], mshell);
		else
			executables(cmds->words, mshell);
	}
}