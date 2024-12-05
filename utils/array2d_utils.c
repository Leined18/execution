/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array2d_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-h <mvidal-h@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:19:55 by mvidal-h          #+#    #+#             */
/*   Updated: 2024/12/05 11:33:17 by mvidal-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe.h"

size_t	array2d_len(char **array)
{
	size_t	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

void	print_array2d(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
}
