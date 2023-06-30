/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_neq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:48:29 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/30 21:01:47 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_vars
{
	int		count;
	int		mode;
}	t_vars;

t_vars	get_vars_neq(char *n_var, t_mshell *mshell)
{
	t_vars	vars;

	vars.count = 0;
	vars.mode = 0;
	while (mshell->envior[vars.count])
	{
		if (!ft_strncmp(n_var, mshell->envior[vars.count]
				, ft_strlen(n_var)))
			vars.mode = 1;
		vars.count++;
	}
	if (vars.mode == 1)
		vars.count--;
	return (vars);
}

char	**b_export_aux_neq(t_mshell *mshell, char *n_var, t_vars vars)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (vars.count + 2));
	while (mshell->envior[i])
	{
		if (!ft_strncmp(n_var, mshell->envior[i], ft_strlen(n_var)))
			new_env[i] = ft_strdup(n_var);
		else
			new_env[i] = ft_strdup(mshell->envior[i]);
		i++;
	}
	if (vars.mode == 0)
	{
		new_env[i] = ft_strdup(n_var);
		new_env[i + 1] = NULL;
	}
	else
		new_env[i] = NULL;
	free_envior(mshell);
	return (new_env);
}

void	handle_neq(char *n_var, t_mshell *mshell)
{
	t_vars	vars;

	vars = get_vars_neq(n_var, mshell);
	mshell->envior = b_export_aux_neq(mshell, n_var, vars);
}
