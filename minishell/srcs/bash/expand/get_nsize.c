/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_nsize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 16:07:58 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/30 16:31:43 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_env
{
	char	*name;
	char	*value;
	bool	sing;
	int		i;
	int		count;
}	t_env;

static void	handle_expand(char *str, t_mshell *mshell, t_env *env)
{
	if (str[env->i] == '$' && env->sing == false)
	{
		env->name = get_name(str + env->i);
		env->count += ft_strlen(get_env(env->name, mshell->envior));
		free(env->name);
		env->i++;
		while (ft_isalnum(str[env->i]))
			env->i++;
	}
	else
	{
		env->count++;
		env->i++;
	}
}

static void	handle_db(t_env *env, char *str, t_mshell *mshell)
{
	env->i++;
	while (str[env->i] != '\"' && str[env->i] != 0)
		handle_expand(str, mshell, env);
	if (str[env->i] == '\"')
		env->i++;
}

int	get_nsize(char *str, t_mshell *mshell)
{
	t_env	env;

	env.i = 0;
	env.count = 0;
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
			handle_db(&env, str, mshell);
		else
			handle_expand(str, mshell, &env);
	}
	return (env.count);
}
