/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:21:24 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/23 17:29:30 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char	*returnvalue(char **cmd, t_mshell *mshell);
char	*join_split_str(char **split_str, char *new_str, int count_words);


/* void	b_ls(t_mshell *mshell)
{
	struct dirent *entry;
	DIR *dir;

	if (mshell->current_cmd == mshell->n_cmds - 1)
	{
		dir = opendir(".");
		if (dir == NULL)
			send_error("opendir");
		entry = readdir(dir);
		while (entry != NULL)
		{
			if (!ft_strncmp(".", entry->d_name, ft_strlen(".")))
				entry = readdir(dir);
			else
			{
				if(mshell->current_cmd == mshell->n_cmds - 1)
					ft_putstr_fd(ft_strjoin(entry->d_name, "\n"), STDOUT_FILENO);
				else
					ft_putstr_fd(ft_strjoin(entry->d_name, "\n"), mshell->fd[0]);
				entry = readdir(dir);
			}
		}
	}
} */

void	executables(char **cmd, t_mshell *mshell)//ao tentar executar duas vezes, da core dump
{
	char *bin;

	bin = returnvalue(cmd, mshell);
	mshell->current_cmd++;
	execve(bin , &cmd[0], mshell->envior);
}

char	*returnvalue(char **cmd, t_mshell *mshell)
{
	char **available;
	char *str;
	int i;

	available = ft_split(mshell->PATH, ':');
	i = 0;
	while (available[i])
	{
		str = ft_strjoin(available[i], "/");
		str = ft_strjoin(str, cmd[0]);
		if (!access(str, X_OK))
			return (str);
		i++;
	}
	return (NULL);
}


char	*Get_PATH(char **pwd)
{
	int i;
	char **str;

	i = 0;
	if (!pwd)
		return (NULL);
	while (pwd[i])
	{
		if (!ft_strncmp(pwd[i], "PATH", 4)) //adicionar condicao de que o path tem de ser 4
			break;
		i++;
	}
	str = ft_split(pwd[i], '=');
	return (str[1]);
}


int	ft_strcmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;
	char			*t1;
	char			*t2;

	i = 0;
	t1 = (char *)s1;
	t2 = (char *)s2;
	if (n == 0)
		return (0);
	while (*t1 && *t2 && (*t1 == *t2) && i < n - 1)
	{
		t1++;
		t2++;
		i++;
	}
	return ((int)(unsigned char)(*t1) - (int)(unsigned char)(*t2));
}



char	*join_split_str(char **split_str, char *new_str, int count_words)
{
	char	*tmp;
	char	*add_space;
	int		i;

	tmp = ft_strdup(split_str[0]);
//	printf("e os:%s: \n", split_str[1]);
	
	i = 1;
	while (count_words > 1)//independente dos inputs, entra sempre duas vezes no loop, mesmo so com 1 input
	{
		printf("entrou\n");
		new_str = tmp;
		add_space = ft_strjoin(new_str, " ");
		free(new_str);
		tmp = ft_strjoin(add_space, split_str[i]);
		free(add_space);
		i++;
		count_words--;
	}
	new_str = ft_strdup(tmp);
	return (new_str);
}
