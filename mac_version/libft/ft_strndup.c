/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksuebtha <ksuebtha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 22:45:00 by ksuebtha          #+#    #+#             */
/*   Updated: 2025/06/13 22:48:52 by ksuebtha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int len)
{
	char	*des;
	int		i;

	des = malloc(len + 1);
	if (des == 0)
		return (0);
	i = 0;
	while (i < len && s1[i])
	{
		des[i] = s1[i];
		i++;
	}
	des[i] = 0;
	return (des);
}
