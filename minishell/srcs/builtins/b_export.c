/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:31:31 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/07 18:40:00 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_vars
{
	int		count;
	int		mode;
}	t_vars;

t_vars	get_vars(char *n_var, t_mshell *mshell)
{
	t_vars	vars;

	vars.count = 0;
	vars.mode = 0;
	while (mshell->envior[vars.count])
	{
		if (!ft_strncmp(n_var, mshell->envior[vars.count]
				, find_char(n_var, '=')))
			vars.mode = 1;
		vars.count++;
	}
	if (vars.mode == 1)
		vars.count--;
	return (vars);
}

int	b_export(char *n_var, t_mshell *mshell)
{
	t_vars	vars;
	int		i;
	char	**new_env;

	vars = get_vars(n_var, mshell);
	new_env = (char **)malloc(sizeof(char *) * (vars.count + 2));
	i = 0;
	while (mshell->envior[i])
	{
		if (!ft_strncmp(n_var, mshell->envior[i], find_char(n_var, '=')))
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
	free(mshell->envior);
	mshell->envior = new_env;
	return (EXIT_SUCCESS);
}
