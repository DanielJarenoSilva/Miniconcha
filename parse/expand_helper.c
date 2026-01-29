/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:17:25 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/29 11:22:54 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(len1 + len2 + 1);
	if (!str)
		return (free(s1), NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = '\0';
	free(s1);
	return (str);
}

char	*ft_strjoin_char_free(char *s, char c)
{
	char	buf[2];

	buf[0] = c;
	buf[1] = '\0';
	return (ft_strjoin_free(s, buf));
}

void	expand_tokens(t_node *node, t_mini *mini)
{
	int		i;
	char	*tmp;

	if (!node || !node->expand || !node->tokens)
		return ;
	i = 1;
	while (node->tokens[i])
	{
		if (node->tokens[i])
		{
			tmp = expand_token(node->tokens[i], mini);
			free(node->tokens[i]);
			node->tokens[i] = tmp;
		}
		i++;
	}
}
