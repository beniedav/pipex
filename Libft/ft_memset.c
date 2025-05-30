/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badou <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 12:15:40 by badou             #+#    #+#             */
/*   Updated: 2024/10/03 12:43:41 by badou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stddef.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ptrs;

	i = 0;
	ptrs = (char *)s;
	while (i < n)
	{
		ptrs[i] = (char)c;
		i++;
	}
	return (s);
}
