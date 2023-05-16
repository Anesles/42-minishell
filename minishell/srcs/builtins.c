/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:42:32 by mgraaf            #+#    #+#             */
/*   Updated: 2023/05/16 18:53:44 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//pwd done
void	b_pwd(void)
{
	char	str[256];//buff size pode ser qualquer um, usei este como exemplo
	getcwd(str, sizeof(str));
	printf("%s\n", str);
}
//echo done

void	b_echo(char **array, int max, t_mshell *mshell)//argc ==  numero de words, o array sao as palabras provenietes de inputs
{
	int	i;
	int status;
	char *str;
	char trim[1];

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

int	b_cd(char *direct)
{
	int	error;

	error = chdir((const char *)direct);
	if (error != 0)
		return (EXIT_FAILURE);
	return (0);
}

void	b_exit(int status)
{
	exit(status);
}

void	b_env(void) //ver as enviarmental variables
{
	int	i;

	i = 0;
	while (__environ[i] != NULL)
	{
		printf("%s\n", __environ[i]);
		i++;
	}	
}

void b_export(char *variable) //adicionar environmental variables
{
	int	count;
	int	status;
	char *name;
	char **new_environ;

	name = ft_substr(variable, 0, find_char(variable, '='));
	count = 0;
	status = 0;
	while (__environ[count] != NULL)
	{
		if (!ft_strncmp(__environ[count], name, ft_strlen(name)))
			status = 1;
		count++;
	}
	if (status == 0)
		new_environ = (char **)malloc(sizeof(char *) * count + 2);
	else
		new_environ = (char **)malloc(sizeof(char *) * count + 1);
	count = 0;
	while (__environ[count] != NULL)
	{
		if (!ft_strncmp(__environ[count], name, ft_strlen(name)))
			new_environ[count] = ft_strdup(variable);
		else
			new_environ[count] = __environ[count];
		count++;
	}
	if (status == 0)
		new_environ[count] = ft_strdup(variable);
	new_environ[count + 1] = NULL;
	__environ = new_environ;
}

void	b_unset(char *variable)
{
	int	count;
	int	track;
	char **new_environ;

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

void	builtins(char **cmd, int count_words, t_mshell *mshell)
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
	if (cmd)
	{
		if (!ft_strncmp("pwd", cmd[0], 3))
			return (b_pwd());
		if (!ft_strncmp("echo", cmd[0], 4))
			return (b_echo(&cmd[1], count_words - 1, mshell));//transormar i input nos argv[1] ate acabarem	
		if (!ft_strncmp("cd", cmd[0], 2))
			return((void)b_cd(cmd[1]));
		if (!ft_strncmp("ls", cmd[0], 2))
			return((void)b_ls(mshell));
		if (!ft_strncmp("exit", cmd[0], 4))
			return(b_exit(0));
		if (!ft_strncmp("./", cmd[0], 2))
			return(b_exec(cmd[0], &cmd[1]));
		if (!ft_strncmp("env", cmd[0], 3))
			return(b_env());
		if (!ft_strncmp("export", cmd[0], 6))
			return(b_export(cmd[1]));
		if (!ft_strncmp("unset", cmd[0], 5))
			return(b_unset(cmd[1]));
	}
}