/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:30:32 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/07 18:30:44 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_cd(char *direct, t_mshell *mshell)
{
	int		error;
	char	*temp;
	char	str[256];
	char	*new_dir;

	if (direct == NULL)
		new_dir = ft_strdup(get_env("HOME", mshell->envior));
	else
		new_dir = ft_strdup(direct);
	error = chdir((const char *)new_dir);
	temp = ft_strjoin("OLDPWD=", get_env("PWD", mshell->envior));
	b_export_one(temp, mshell);
	free(temp);
	getcwd(str, sizeof(str));
	temp = ft_strjoin("PWD=", str);
	b_export_one(temp, mshell);
	free(temp);
	free(new_dir);
	if (error != 0)
		return (error_cd(new_dir));
	if (direct == NULL)
		free (direct);
	return (EXIT_SUCCESS);
}
