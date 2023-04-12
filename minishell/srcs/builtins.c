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

void	builtins(char *str)
{
/* 	static void	*builtins[7][2] = {
	{"echo", b_echo}, TODO
	{"cd", b_cd}, TODO
	{"pwd", b_pwd}, DONE
	{"export", b_export}, TODO
	{"unset", b_unset}, TODO
	{"env", b_env}, TODO
	{"exit", b_exit} TODO
	}; */
	
	if (str)
	{
		if (!ft_strncmp("pwd", str, ft_strlen("pwd")))
			return (b_pwd());	
	}
}
//pwd done
void	b_pwd()
{
	char str[256];

	getcwd(str, sizeof(str));
	printf("%s\n", str);
}
