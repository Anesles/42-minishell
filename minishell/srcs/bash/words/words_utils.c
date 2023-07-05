/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   words_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbraga-b <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 14:49:25 by dbraga-b          #+#    #+#             */
/*   Updated: 2023/07/05 14:49:25 by dbraga-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_special_char(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	is_double_special_char(char c1, char c2)
{
	return (c1 == c2 && (c1 == '<' || c1 == '>'));
}
