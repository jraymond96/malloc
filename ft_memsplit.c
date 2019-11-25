/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 07:15:21 by jraymond          #+#    #+#             */
/*   Updated: 2018/07/03 05:08:43 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		nb_of_words(char *str, int size)
{
	int	words;

	words = 0;
	while (size && *str)
	{
		while (size && *str && (*str == ' ' || *str == '\t' || *str == '\n'))
		{
			size--;
			str++;
		}
		if (*str && *str != ' ' && *str != '\t' && *str != '\n')
			words++;
		while (size && *str && *str != ' ' && *str != '\t' && *str != '\n')
		{
			str++;
			size--;
		}
	}
	return (words);
}

int		handle_word(char *str, char **new, int size)
{
	int	len;

	while (size > 0 && (str[size] == ' ' || str[size] == '\t' ||
			str[size] == '\n'))
		size--;
	len = 0;
	while (size > 0 && str[size] != ' ' && str[size] != '\t' &&
			str[size] != '\n')
	{
		size--;
		len++;
	}
	if (size == 0)
		len++;
	if (str[size] == ' ' || str[size] == '\t' || str[size] == '\t')
		*new = ft_memdup(&str[size + 1], len);
	else
		*new = ft_memdup(&str[size], len);
	if (!(*new))
		exit(0);
	return (size);
}

char	**ft_memsplit(char *str, size_t size)
{
	int		words;
	char	**new;

	words = nb_of_words(str, --size);
	if (!(new = (char**)ft_malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	new[words] = NULL;
	while (--words >= 0)
		size = handle_word(str, &new[words], size);
	return (new);
}
