/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 17:39:56 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 16:31:37 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *str)
{
	int		i;
	int		j;
	int		count;
	char	*name;

	count = 0;
	i = find_char(str, '$') + 1;
	if (str[i] == '?')
		count = 1;
	else
	{
		while (ft_isalnum(str[i++]))
			count++;
	}
	name = malloc(sizeof (char) * count + 1);
	if (!name)
		return (NULL);
	i = find_char(str, '$') + 1;
	j = 0;
	while (j < count)
		name[j++] = str[i++];
	name[j] = 0;
	return (name);
}

int	get_nsize(char *str, t_mshell *mshell)
{
	bool	sing;
	char	*name;
	int		count;
	int		i;

	i = 0;
	count = 0;
	sing = false;
	while(str[i])
	{
		if (str[i] == '\'')
		{
			sing = !sing;
			i++;
			continue;
		}
		if (str[i] == '\"' && sing == false)
		{
			i++;
			while (str[i] != '\"' && str[i] != 0)
			{
				if (str[i] == '$')
				{
					name = get_name(str + i);
					count += ft_strlen(get_env(name, mshell->envior));
					free(name);
					i++;
					while (ft_isalnum(str[i]))
						i++;
					continue;
				}
				count++;
				i++;
			}
			if (str[i] == '\"')
				i++;
			continue;
		}
		else if (str[i] == '$' && sing == false)
		{
			name = get_name(str + i);
			count += ft_strlen(get_env(name, mshell->envior));
			free(name);
			i++;
			while (ft_isalnum(str[i]))
				i++;
			continue;
		}
		count++;
		i++;
	}
	return (count);
}

void	handle_single_quotes(char *str, t_mshell *mshell)
{
	bool	sing;

	sing = true;
	mshell->i++;
	while (str[mshell->i] && str[mshell->i] != '\'' && sing)
		mshell->i++;
	if (str[mshell->i] == '\'')
		mshell->i++;
}

void	double_q(char *str, t_mshell *mshell, char *ret)
{
	char	*name;
	char	*env;

    mshell->i++;
    while (str[mshell->i] && str[mshell->i] != '\"')
    {
        if (str[mshell->i] == '$')
        {
            name = get_name(str + (mshell->i));
            env = get_env(name, mshell->envior);
            while (*env)
                ret[(mshell->j)++] = *(env++);
            free(name);
            mshell->i++;
            while (ft_isalnum(str[mshell->i]))
                (mshell->i)++;
            continue;
        }
        ret[mshell->j++] = str[mshell->i++];
    }
    if (str[mshell->i] == '\"')
        mshell->i++;
}

void handle_env_variable(char *str, t_mshell *mshell, char *ret)
{
	char	*name;
	char	*env;

	name = get_name(str + mshell->i);
	env = get_env(name, mshell->envior);
	while (*env)
		ret[mshell->j++] = *(env++);
	mshell->j += ft_strlen(env);
	free(name);
	mshell->i++;
	while (ft_isalnum(str[mshell->i]))
		mshell->i++;
}

bool is_in_single_quotes(char *str, int pos)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < pos)
	{
		if (str[i] == '\'')
	        count++;
		i++;
	}
	return (count % 2 == 1);
}

char	*expand_env(char *str, t_mshell *mshell)
{
	int		size;
	char	*ret;


	size = get_nsize(str, mshell);
	ft_printf("size:%d\n", size);
	ret = (char *)malloc(sizeof(char) * (size + 1));
	ret[size] = 0;
	mshell->i = 0;
	mshell->j = 0;
	while (str[mshell->i])
	{
		if (str[mshell->i] == '\'')
			handle_single_quotes(str, mshell);
		else if (str[mshell->i] == '\'' && !is_in_single_quotes(str, mshell->i))
			double_q(str, mshell, ret);
		else if (str[mshell->i] == '$' && !is_in_single_quotes(str, mshell->i))
			handle_env_variable(str, mshell, ret);
		else
			ret[mshell->j++] = str[mshell->i++];
	}
	return (ret);
}

/* char	*expand_env(char *str, t_mshell *mshell)
{
	char	*ret;
	char 	*env;
	char	*name;
	bool	sing;
	int		size;
	int		j;
	int		i;

	size = get_nsize(str, mshell);
	sing = false;
	ret = (char *) malloc(sizeof(char) * (size + 1));
	ret[size] = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if(str[i] == '\'')
		{
			sing = !sing;
			i++;
			continue;
		}
		if(str[i] == '\"' && sing == false)
		{
			i++;
			while (str[i] != '\"' && str[i] != 0)
			{
				if (str[i] == '$')
				{
					name = get_name(str + i);
					env = get_env(name, mshell->envior);
					while(*env)
						ret[j++] = *(env++);
					free(name);
					i++;
					while (ft_isalnum(str[i]))
						i++;
					continue;
				}
				ret[j++] = str[i++];
			}
			if (str[i] == '\"')
				i++;
			continue;
		}
		else if (str[i] == '$' && sing == false)
		{
			name = get_name(str + i);
			env = get_env(name, mshell->envior);
			while(*env)
				ret[j++] = *(env++);
			j += ft_strlen(env);
			free(name);
			i++;
			while (ft_isalnum(str[i]))
				i++;
			continue;
		}
		ret[j++] = str[i++];
	}
	return (ret);
} */

char	*expand(char *str, t_mshell *mshell)
{
	if (ft_strchr(str, '$') != NULL)
		return (expand_env(str, mshell));
	else
		return (ft_strdup(str));
}
