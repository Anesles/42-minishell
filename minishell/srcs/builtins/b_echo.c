/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:29:12 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/13 21:13:17 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	b_echo(char **words, int max_words)
{
	int	i;
	int	mode;

	mode = 0;
	if (!words[0])
	{
		ft_printf("\n");
		return (EXIT_SUCCESS);
	}
	i = -1;
	if (!ft_strncmp(words[i + 1], "-n", 2))
		mode = 1;
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
	return (EXIT_SUCCESS);
}
