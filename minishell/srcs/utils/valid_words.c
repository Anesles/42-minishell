/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 13:57:18 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/06/30 13:57:19 by dbraga-b         ###   ########.fr       */
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
		if (words[i + 1] && (is_redir(words[i]) && is_redir(words[i + 1])))
			return (0);
		i++;
	}
	return (1);
}

int	valid_nvar(char **nvar)
{
	int	i;

	i = 1;
	while (nvar[i])
	{
		if (!(ft_isalpha(nvar[i][0]) || nvar[i][0] == '_' || nvar[i][0] == '?'))
			return (EXIT_FAILURE);
		if (find_char(nvar[i], '=') == -1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	valid_nvar_one(char *nvar)
{
	if (!(ft_isalpha(nvar[0]) || nvar[0] == '_' || nvar[0] == '?'))
		return (EXIT_FAILURE);
	if (find_char(nvar, '=') == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
