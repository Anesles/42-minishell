/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 15:22:12 by brumarti          #+#    #+#             */
/*   Updated: 2023/04/11 16:11:55 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_words(char **words)
{
	int	count;

	count = 0;
	while (words[count])
		count++;
	return (count);
}

void	clear_words(char **words, int n)
{
	int	i;

	i = -1;
	while (i < n)
		free(words[i]);
	free(words);
}