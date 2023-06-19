/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   send_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 18:20:44 by brumarti          #+#    #+#             */
/*   Updated: 2022/12/07 18:30:03 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	send_error(char *msg)
{
	ft_printf("Error\n%s\n", msg);
	exit(EXIT_FAILURE);
}
