/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:21:24 by brumarti          #+#    #+#             */
/*   Updated: 2023/05/16 16:29:32 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*join_split_str(char **split_str, char *new_str, int count_words);

#include "minishell.h"

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

void	executables(char **cmd, int count_words, t_mshell *mshell)//ao tentar executar duas vezes, da core dump
{
	char *bin;
	char *path;

	(void)count_words;
	(void)mshell;
	path = mshell->PATH;
//	bin = test(mshell->envior, cmd[0])
	
//	exec = join_split_str(cmd, NULL, count_words);//o que vem do cmd? e o porque de ter 2 casas a mais
/* 	int i;
	i = 0;
	printf("words:%d\n", count_words);
	while(count_words > 0)
	{
		printf("%s\n", cmd[i]);
		count_words--;
		i++;
	} */
//	exec = ft_strjoin(bin, exec);

	execve(bin, &cmd[1], mshell->envior);
	printf("end\n");
	//execve(cmd, words, env);
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
		if (ft_strcmp(pwd[i], "PATH", 4)) //adicionar condicao de que o path tem de ser 4
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
