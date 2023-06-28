/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:42:32 by mgraaf            #+#    #+#             */
/*   Updated: 2023/06/14 17:43:56 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_exit(int status, t_mshell *mshell)
{
	int	i;

	i = -1;
	while (mshell->envior[++i])
		free(mshell->envior[i]);
	free(mshell->envior[i]);
	free(mshell->envior);
	free(mshell->path);
	exit(status);
}

int	b_pwd(void)
{
	char	str[256];

	getcwd(str, sizeof(str));
	if (!str[0])
		return (EXIT_FAILURE);
	printf("%s\n", str);
	return (EXIT_SUCCESS);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	char			*t1;
	char			*t2;

	i = 0;
	t1 = (char *)s1;
	t2 = (char *)s2;
	while (*t1 && *t2 && (*t1 == *t2))
	{
		t1++;
		t2++;
	}
	return ((int)(unsigned char)(*t1) - (int)(unsigned char)(*t2));
}

void	order_array(char **str)
{
	int 	i;
	int		j;
	char 	*temp;
	int		size;

	i = 0;
	j = 0;
	size = 0;
	while (str[size])
		size++;
	while(j < size - 1)
	{
		i = 0;
		while (i < size - j - 1)
		{
			if (ft_strcmp(str[i], str[i + 1]) > 0)
			{
				temp = str[i];
				str[i] = str[i + 1];
				str[i + 1] = temp;
			}
			i++;
		}
		j++;
	}
}

int	next_one(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

int	b_declare(t_mshell *mshell)
{
	int	i;
	char **array;
	char *str;
	int 	j;

	array = arraydup(mshell->envior);
	order_array(array);
	i = 0;
	while (array[i])
	{
		j = 0;
		ft_printf("declare -x ");
		str = ft_substr(array[i], j, next_one(array[i], '='));
		ft_printf("%s=", str);
		free(str);
		j = j + next_one(array[i], '=') + 1;
		str = ft_substr(array[i], j, ft_strlen(array[i]));
		ft_printf("\"%s\"\n", str);
		free(str);
		i++;
	}
	return (EXIT_SUCCESS);
}

int b_env(t_mshell *mshell)
{
	int i;

	i = 0;
	while (mshell->envior[i])
	{
		ft_printf(mshell->envior[i]);
		i++;
	}
		return (EXIT_SUCCESS);
}

void	check_redirect(t_cmds *cmds)
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
}

int	builtins(t_cmds *cmds, t_mshell *mshell)
{
	check_redirect(cmds);
	if (cmds->words)
	{
		if (!ft_strncmp("pwd", cmds->words[0], 3))
			return (b_pwd());
		else if (!ft_strncmp("echo", cmds->words[0], 4))
			return (b_echo(&cmds->words[1], cmds->count_words - 1));
		else if (!ft_strncmp("cd", cmds->words[0], 2))
			return (b_cd(cmds->words[1], mshell));
		else if (!ft_strncmp("exit", cmds->words[0], 4))
			b_exit(0, mshell);
		else if (!ft_strncmp("env", cmds->words[0], 3))
			return (b_env(mshell));
		else if (!ft_strncmp("export", cmds->words[0], 6))
			return (b_export(cmds->words[1], mshell));
		else if (!ft_strncmp("unset", cmds->words[0], 5))
			return (b_unset(cmds->words[1], mshell));
		else
			executables(cmds->words, mshell);
	}
	return (error_cmd_not_found(cmds->words[0]));
}
