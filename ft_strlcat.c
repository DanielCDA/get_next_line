/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danagost <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 13:04:24 by danagost          #+#    #+#             */
/*   Updated: 2026/07/30 13:04:26 by danagost         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_l;
	size_t	src_l;
	size_t	i;

	if (dst == NULL)
		return (0);
	if (src == NULL)
		return (ft_strlen(dst));
	dst_l = ft_strlen(dst);
	src_l = ft_strlen(src);
	i = 0;
	if (size <= dst_l)
		return (src_l + size);
	while (src[i] && (dst_l + i) < (size - 1))
	{
		dst[dst_l + i] = src[i];
		i++;
	}
	dst[dst_l + i] = '\0';
	return (dst_l + src_l);
}
