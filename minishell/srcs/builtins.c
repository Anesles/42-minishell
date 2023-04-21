/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:42:32 by mgraaf            #+#    #+#             */
/*   Updated: 2023/04/21 17:34:23 by brumarti         ###   ########.fr       */
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
void	b_echo(char **array, int max)//argc ==  numero de words, o array sao as palabras provenietes de inputs
{
	int	i;
	
	i = -1;
	while (++i < max)
	{
		ft_putstr_fd(array[i], STDOUT_FILENO);
		write(1, " ", 1);
	}	
	write(1, "\n", 1);
}

int	b_cd(char *direct)
{
	int	error;

	error = chdir((const char *)direct);
	if (error != 0)//mudar a msg inicial para o novo diretorio
	{
		ft_putstr_fd("minishell:", STDERR_FILENO);
		ft_putstr_fd(direct, STDERR_FILENO);
		ft_putstr_fd(" ", STDERR_FILENO);
	}
	if (error == 0)
		return (EXIT_FAILURE);
	return (0);
}

void	b_exit(int status)
{
	exit(status);
}

void	builtins(char **cmd, int words)
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
			return (b_echo(&cmd[1], words - 1));//transormar i input nos argv[1] ate acabarem	
		if (!ft_strncmp("cd", cmd[0], ft_strlen("cd")))
			return((void)b_cd(cmd[1]));
	}
}