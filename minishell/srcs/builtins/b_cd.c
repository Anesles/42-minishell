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
	char	str[256];

	if (direct == NULL)
		direct = ft_strdup(get_env("HOME", mshell->envior));
	error = chdir((const char *)direct);
	b_export_one(ft_strjoin("OLDPWD=", get_env("PWD", mshell->envior)), mshell);
	getcwd(str, sizeof(str));
	b_export_one(ft_strjoin("PWD=", str), mshell);
	if (error != 0)
		return (error_cd(direct));
	return (EXIT_SUCCESS);
}
