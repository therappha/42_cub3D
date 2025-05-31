/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndupto.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaelfe <rafaelfe@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 20:28:28 by rafaelfe          #+#    #+#             */
/*   Updated: 2025/05/30 20:28:55 by rafaelfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndupto(const char *str, int start, int end)
{
	char	*newstr;
	int		i;
	int		total_len;

	i = 0;
	total_len = end - start + 1;
	newstr = (char *)malloc(total_len + 1);
	if (!newstr)
		return (NULL);
	while (i < total_len)
	{
		newstr[i] = str[start];
		i++;
		start++;
	}
	newstr[i] = '\0';
	return (newstr);
}
