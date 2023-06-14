/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:31:31 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 16:29:52 by brumarti         ###   ########.fr       */
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

int	valid_nvar(char *nvar)
{
	if (!(ft_isalpha(nvar[0]) || nvar[0] == '_' || nvar[0] == '?'))
		return (EXIT_FAILURE);
	if (find_char(nvar, '=') == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	**b_export_aux(t_mshell *mshell, char *n_var, t_vars vars)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (vars.count + 2));
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
	return (new_env);
}

int	b_export(char *n_var, t_mshell *mshell)
{
	t_vars	vars;

	if (!n_var)
		return (b_env(mshell));
	if (valid_nvar(n_var))
		return (EXIT_FAILURE);
	if (*(n_var + find_char(n_var, '=') + 1) <= 32)
		n_var = ft_substr(n_var, 0, find_char(n_var, '=') + 1);
	vars = get_vars(n_var, mshell);
	mshell->envior = b_export_aux(mshell, n_var, vars);
	return (EXIT_SUCCESS);
}
