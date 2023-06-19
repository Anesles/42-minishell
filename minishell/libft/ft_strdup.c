/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brumarti <brumarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 22:35:04 by brumarti          #+#    #+#             */
/*   Updated: 2023/06/14 17:39:51 by brumarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;

	ret = (char *)malloc(ft_strlen(s) + 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s, (ft_strlen(s) + 1));
	return (ret);
}
