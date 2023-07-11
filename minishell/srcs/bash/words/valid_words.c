/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:57:18 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/07/11 14:46:47 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_words(char **words)
{
	int	i;

	i = 0;
	if (words[0] == NULL)
		return (0);
	else if (words[0][0] == '|')
		return (0);
	else if (words[0][0] == ';')
		return (0);
	else if (words[0][0] == '<')
		return (0);
	else if (words[0][0] == '>')
		return (0);
	else if (words[0][0] == '&')
		return (0);
	while (words[i])
	{
		if (words[i][0] == '<' && words[i + 1][0] == '>')
		{
			i++;
			continue ;
		}
		if (words[i + 1] && (is_redir(words[i]) && is_redir(words[i + 1])))
			return (0);
		i++;
	}
	return (1);
}

int	valid_nvar(char **nvar)
{
	int	i;
	int	j;

	i = 1;
	while (nvar[i])
	{
		if (nvar[i][0] == '?')
			return (EXIT_SUCCESS);
		if (!ft_isalpha(nvar[i][0]) || nvar[i][0] == '_')
			return (EXIT_FAILURE);
		j = 1;
		while (nvar[i][j] != '=' && nvar[i][j] != '\0')
		{
			if (!(ft_isalnum(nvar[i][j])))
				return (EXIT_FAILURE);
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	valid_nvar_one(char *nvar)
{
	int	i;

	if (nvar[0] == '?')
		return (EXIT_SUCCESS);
	if (!ft_isalpha(nvar[0]) || nvar[0] == '_')
		return (EXIT_FAILURE);
	i = 1;
	while (nvar[i] != '=' && nvar[i] != '\0')
	{
		if (!ft_isalnum(nvar[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
