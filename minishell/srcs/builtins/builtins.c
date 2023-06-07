/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:42:32 by mgraaf            #+#    #+#             */
/*   Updated: 2023/06/07 11:42:35 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_echo(char **words, int max_words)
{
	int	i;
	int	mode;

	mode = 0;
	if (!words[0])
	{
		ft_printf("\n");
		return (0);
	}
	i = 0;
	if (!ft_strncmp(words[i], "-n", 2))
	{
		mode = 1;
		i++;
	}
	else
		i = 0;
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
	return (0);
}

int	b_cd(char *direct)
{
	int	error;

	error = chdir((const char *)direct);
	if (error != 0)
		perror("cd failed");
	return(0);
}

void	b_exit(int status)
{
	exit(status);
}

int	b_pwd(void)
{
	char	str[256];

	getcwd(str, sizeof(str));
	printf("%s\n", str);
	return(0);
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
	return(0);
}

int	b_export(char *new_variable, t_mshell *mshell)
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
	return (0);
}

int	b_unset(char *variable, t_mshell *mshell)
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
	return (0);
}

int	builtins(t_cmds *cmds, t_mshell *mshell)
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
	if (cmds->words)
	{
		if (!ft_strncmp("pwd", cmds->words[0], 3))
			return (b_pwd());
		else if (!ft_strncmp("echo", cmds->words[0], 4))
			return (b_echo(&cmds->words[1], cmds->count_words - 1));
		else if (!ft_strncmp("cd", cmds->words[0], 2))
			return(b_cd(cmds->words[1]));
		else if (!ft_strncmp("exit", cmds->words[0], 4))
			b_exit(0);
		else if (!ft_strncmp("env", cmds->words[0], 3))
			return(b_env(mshell));
		else if (!ft_strncmp("export", cmds->words[0], 6))
			return(b_export(cmds->words[1], mshell));
		else if (!ft_strncmp("unset", cmds->words[0], 5))
			return(b_unset(cmds->words[1], mshell));
		else
			executables(cmds->words, mshell);
	}
	error_cmd_not_found(cmds->words[0]);
	return(EXIT_FAILURE);
}
