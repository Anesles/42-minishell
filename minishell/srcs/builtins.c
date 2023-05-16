/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:42:32 by mgraaf            #+#    #+#             */
/*   Updated: 2023/05/15 16:34:32 by brumarti         ###   ########.fr       */
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
	char *str;
	char trim[1];

	trim[0] = 34;
	i = -1;
	while (++i < max)
	{
		str = ft_strtrim(array[i], trim);
		if (mshell->current_cmd == mshell->n_cmds - 1)
		{
			ft_putstr_fd(str, STDOUT_FILENO);
			write(STDOUT_FILENO, " ", 1);
		}
		else
		{
			ft_putstr_fd(array[i], mshell->fd[0]);
			write(mshell->fd[0], " ", 1);
		}
		free(str);
	}
	if (mshell->current_cmd == mshell->n_cmds - 1)
		write(STDOUT_FILENO, "\n", 1);
	else
		write(mshell->fd[0], "\n", 1);
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
		if (!ft_strncmp("pwd", cmd[0], ft_strlen("pwd")))
			return (b_pwd());
		if (!ft_strncmp("echo", cmd[0], ft_strlen("echo")))
			return (b_echo(&cmd[1], count_words - 1, mshell));//transormar i input nos argv[1] ate acabarem	
		if (!ft_strncmp("cd", cmd[0], ft_strlen("cd")))
			return((void)b_cd(cmd[1]));
		if (!ft_strncmp("ls", cmd[0], ft_strlen("ls")))
			return((void)b_ls(mshell));
		if (!ft_strncmp("exit", cmd[0], ft_strlen("exit")))
			return(b_exit(0));
	}
}