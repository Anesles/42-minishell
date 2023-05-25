/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:42:32 by mgraaf            #+#    #+#             */
/*   Updated: 2023/05/25 01:27:34 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_env(char	*name, char	*variable);

void	b_pwd(void)
{
	char	str[256];//buff size pode ser qualquer um, usei este como exemplo
	getcwd(str, sizeof(str));
	printf("%s\n", str);
}

void	b_echo(char **array, int max, t_mshell *mshell)
{
	int		i;
	int		status;
	char	*str;
	char	trim[1];

	trim[0] = 34;
	i = -1;
	status = 0;
	if (!ft_strncmp(array[0], "-n", 2))
	{
		status = 1;
		i++;
	}
	while (++i < max)
	{
		str = ft_strtrim(array[i], trim);
		if (mshell->current_cmd == mshell->n_cmds - 1)
		{
			ft_putstr_fd(str, STDOUT_FILENO);
			if (i != max - 1)
				write(STDOUT_FILENO, " ", 1);
		}
		else
		{
			ft_putstr_fd(array[i], mshell->fd[0]);
			if (i != max - 1)
				write(mshell->fd[0], " ", 1);
		}
		free(str);
	}
	if (status == 0)
	{
		if (mshell->current_cmd == mshell->n_cmds - 1)
			write(STDOUT_FILENO, "\n", 1);
		else
			write(mshell->fd[0], "\n", 1);
	}
}

void	b_cd(char *direct)
{
	int	error;

	error = chdir((const char *)direct);
	if (error != 0)
		perror("cd failed");
}

void	b_exit(int status)
{
	exit(status);
}

void	b_env(void)
{
	int	i;

	i = 0;
	while (__environ[i] != NULL)
	{
		printf("%s\n", __environ[i]);
		i++;
	}
}

char	*new_env(char	*name, char	*variable)
{
	char	*new;
	int		tam_name;
	int		tam_var;
	int		i;
	int 	j;

	tam_name = 0;
	tam_var = 0;
	tam_name = ft_strlen(name);
	tam_var = ft_strlen(variable);
	new = malloc(sizeof(char) * (tam_name + tam_var + 2));
	if (!new)
		return (0);
	i = -1;
	while (++i < tam_name)
		new[i] = name[i];
	if (variable == NULL)
		return (NULL);
	new[i] = '=';
	i++;
	j = 0;
	while (j < tam_var)
	{
		new[i] = variable[j];
		j++;
		i++;
	}
	new[i] = '\0';
	return (new);
}

void b_export(char *new)
{
	int		i;
	char	**new_environ;
	char	**new_var;
	int		status;

	new_var = ft_split(new, '=');
	status = 0;
	i = 0;
	while (__environ[i] != NULL)
	{
		if (!ft_strncmp(__environ[i], new_var[0], ft_strlen(new_var[0])))
			status = 1;
		i++;
	}
	if ((new_var[1] != NULL))
	{
		if (status == 0)
			new_environ = malloc(sizeof(char *) * i + 2);
		else
			new_environ = malloc(sizeof(char *) * i + 1);
		i = -1;
		while (__environ[++i] != NULL)
		{
			if (!ft_strncmp(__environ[i], new_var[0], ft_strlen(new_var[0])))
			{
				new_environ[i] = new_env(new_var[0], new_var[1]);
			}
			else
				new_environ[i] = __environ[i];
		}
		if (status == 0)
			new_environ[i] = ft_strdup(new);
		new_environ[i + 1] = NULL;
		__environ = new_environ;
	}
}

void	b_unset(char *variable)
{
	int		count;
	int		track;
	char	**new_environ;

	count = 0;
	while (__environ[count] != NULL)
		count++;
	new_environ = (char **)malloc(sizeof(char *) * count);
	count = 0;
	track = 0;
	while (__environ[count] != NULL)
	{
		if (ft_strncmp(variable, __environ[count], ft_strlen(variable)) != 0)
		{
			new_environ[track] = __environ[count];
			track++;
		}
		count++;
	}
	new_environ[track] = NULL;
	__environ = new_environ;
}

void	b_get(char *word)
{
	printf("%s\n", getenv(word));
}

void	builtins(t_cmds *cmds, t_mshell *mshell)
{
/* 	static void	*builtins[7][2] = {
	{"echo", b_echo}, DONE
	{"cd", b_cd}, TODO
	{"pwd", b_pwd}, DONE
	{"export", b_export}, TODO
	{"unset", b_unset}, TODO
	{"env", b_env}, TODO
	{"exit", b_exit} TODO
	}; */
	if (cmds->words)
	{
		if (!ft_strncmp("pwd", cmds->words[0], 3))
			b_pwd();
		//else if (!ft_strncmp("echo", cmds->words[0], 4))
			//b_echo(&cmds->words[1], count_words - 1, mshell);//transormar i input nos argv[1] ate acabarem	
		else if (!ft_strncmp("cd", cmds->words[0], 2))
			b_cd(cmds->words[1]);
		else if (!ft_strncmp("exit", cmds->words[0], 4))
			b_exit(0);
		else if (!ft_strncmp("env", cmds->words[0], 3))
			b_env();
		else if (!ft_strncmp("export", cmds->words[0], 6))
			b_export(cmds->words[1]);
		else if (!ft_strncmp("unset", cmds->words[0], 5))
			b_unset(cmds->words[1]);
		else
			executables(cmds->words, mshell);
	}
}