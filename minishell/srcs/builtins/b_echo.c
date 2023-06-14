/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:29:12 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 15:47:03 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_echo_aux(int mode, char **words, int max_words)
{
	int	i;

	i = -1;
	if (mode == 1)
		i++;
	while (words[++i])
	{
		if (i == max_words - 1)
		{
			if (mode == 0)
				printf("%s\n", words[i]);
			else
				printf("%s", words[i]);
		}
		else
			printf("%s ", words[i]);
	}
}

int	b_echo(char **words, int max_words)
{
	int	mode;

	mode = 0;
	if (!words[0])
	{
		ft_printf("\n");
		return (EXIT_SUCCESS);
	}
	if (!ft_strncmp(words[0], "-n", 2))
		mode = 1;
	b_echo_aux(mode, words, max_words);
	return (EXIT_SUCCESS);
}
