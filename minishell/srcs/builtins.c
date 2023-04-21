/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mgraaf <mgraaf@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/15 11:42:32 by mgraaf        #+#    #+#                 */
/*   Updated: 2022/04/19 15:24:14 by maiadegraaf   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
{

	void (*trans)(char *)=&builtins
	trans(echo);
}
void	builtins(char **cmd)
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
			return (b_echo());//transormar i input nos argv[1] ate acabarem	
		if (!ft_strncmp("cd", cmd[0], ft_strlen("cd")))
			return(b_cd(cmd[1]));
	}
}
//pwd done
void	b_pwd(void)
{
	char	str[256];//buff size pode ser qualquer um, usei este como exemplo
	getcwd(str, sizeof(str));
	printf("%s\n", str);
}
//echo done
void	b_echo(char **array, int argc)//argc ==  numero de words, o array sao as palabras provenietes de inputs
{
	int	i;

	i = -1;
	while (++i < argc)
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