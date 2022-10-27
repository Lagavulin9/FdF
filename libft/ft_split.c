/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jinholee <jinholee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:29:12 by jinholee          #+#    #+#             */
/*   Updated: 2022/10/13 14:09:11 by jinholee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	free_all(char **words)
{
	size_t	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}

int	is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	count_words(char *str, char *charset)
{
	int	count;
	int	after_sep;

	count = 0;
	after_sep = 1;
	while (*str)
	{
		if (is_charset(*str, charset))
			after_sep = 1;
		else if (after_sep)
		{
			count++;
			after_sep = 0;
		}
		str++;
	}
	return (count);
}

static char	*return_word(char *word, char *str, char *charset)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (is_charset(*str, charset))
		i++;
	while (str[i + len] && !is_charset(str[i + len], charset))
		len++;
	word = malloc(sizeof(char) * len + 1);
	if (!word)
		return (0);
	len = 0;
	while (str[i + len] && !is_charset(str[i + len], charset))
	{
		word[len] = str[i + len];
		len++;
	}
	word[i + len] = '\0';
	return (word);
}

char	**ft_split(char const *s, char *charset)
{
	const size_t	word_count = count_words((char *)s, charset);
	size_t			i;
	char			**words;

	words = malloc(sizeof(char *) * (word_count + 1));
	if (!words)
		return (words);
	i = 0;
	while (i < word_count)
	{
		if (is_charset(*s, charset))
			s++;
		else
		{
			words[i] = return_word(words[i], (char *)s, charset);
			if (!words[i])
			{
				free_all(words);
				return (0);
			}
			s += ft_strlen(words[i++]);
		}
	}
	words[word_count] = 0;
	return (words);
}
