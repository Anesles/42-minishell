/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 15:18:16 by brumarti          #+#    #+#             */
/*   Updated: 2023/04/21 17:35:34 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void parser(t_cmds *cmds)
{
	cmds[0].built(cmds[0].words, cmds[0].count_words);
	cmds[1].built(cmds[1].words, cmds[1].count_words);
}