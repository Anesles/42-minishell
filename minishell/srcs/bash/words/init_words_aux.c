/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_words_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:37:15 by brumarti          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/07/12 20:06:57 by brumarti         ###   ########.fr       */
=======
/*   Updated: 2023/07/12 18:47:45 by brumarti         ###   ########.fr       */
>>>>>>> 6b4a117866a781eddd97475de3779a7baa1f2d67
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_w_quote_aux(char *str, int *i, char *c)
{
	if (str[*i] && str[*i] != ' ' && str[*i] != '\t')
	{
<<<<<<< HEAD
		while (str[*i] && str[*i] != ' '
=======
		while (str[*i] && str[*i] != ' ' 
>>>>>>> 6b4a117866a781eddd97475de3779a7baa1f2d67
			&& str[*i] != '\t' && !is_quote(str[*i]))
			(*i)++;
		if (is_quote(str[*i]))
		{
			(*c) = str[*i];
			(*i)++;
			while (str[*i] == ' ')
				(*i)++;
			return (0);
		}
	}
	return (1);
}

int	check_pipe(char	**words, int count)
{
	if (!ft_strncmp(words[--count], "|", 1))
	{
		free_array(words);
		ft_printf("minishell: syntax error near unexpected token '|'\n");
		return (0);
	}
	return (1);
}
