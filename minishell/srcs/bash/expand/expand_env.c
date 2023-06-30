/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 15:45:30 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/30 20:35:13 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_env
{
	char	*name;
	char	*value;
	bool	sing;
	int		i;
	int		j;
}	t_env;

void	handle_expand(char *str, t_mshell *mshell, t_env *env, char *ret)
{
	size_t	j;

	if (str[env->i] == '$' && str[env->i + 1] 
		&& (ft_isalnum(str[env->i + 1]) || str[env->i + 1] == '?'))
	{
		env->name = get_name(str + env->i);
		env->value = get_env(env->name, mshell->envior);
		while (*env->value)
			ret[env->j++] = *(env->value++);
		env->i++;
		j = 0;
		while (j < ft_strlen(env->name))
		{
			j++;
			env->i++;
		}
		free(env->name);
	}
	else
		ret[env->j++] = str[env->i++];
}

void	handle_db(char *str, t_mshell *mshell, t_env *env, char *ret)
{
	env->i++;
	while (str[env->i] != '\"' && str[env->i] != 0)
		handle_expand(str, mshell, env, ret);
	if (str[env->i] == '\"')
		env->i++;
}

void	expand_env_aux(char *str, t_mshell *mshell, char *ret, t_env env)
{
	env.sing = false;
	while (str[env.i])
	{
		if (str[env.i] == '\'')
		{
			env.sing = !env.sing;
			env.i++;
			continue ;
		}
		if (str[env.i] == '\"' && env.sing == false)
			handle_db(str, mshell, &env, ret);
		else if (str[env.i] == '$' && env.sing == false)
			handle_expand(str, mshell, &env, ret);
		else
			ret[env.j++] = str[env.i++];
	}
}

char	*expand_env(char *str, t_mshell *mshell)
{
	int		size;
	char	*ret;
	t_env	env;

	env.i = 0;
	env.j = 0;
	size = get_nsize(str, mshell);
	ret = (char *) malloc(sizeof(char) * (size + 1));
	ret[size] = 0;
	expand_env_aux(str, mshell, ret, env);
	return (ret);
}
