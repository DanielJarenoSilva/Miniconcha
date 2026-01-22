/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 17:17:25 by kfuto             #+#    #+#             */
/*   Updated: 2026/01/16 04:35:41 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	i;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	if (!str)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < ft_strlen(s2))
	{
		str[ft_strlen(s1) + i] = s2[i];
		i++;
	}
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (free(s1), free(s2), str);
}

char	*ft_strjoin_char_free(char *s, char c)
{
	char	*s2;

	s2 = malloc(2);
	s2[0] = c;
	s2[1] = '\0';
	return (ft_strjoin_free(s, s2));
}

void	expand_tokens(t_node *node, t_mini *mini)
{
	int		i;
	char	*tmp;

	if (node->expand == 0)
		return ;
	i = 0;
	while (node->tokens[i])
	{
		tmp = expand_token(node->tokens[i], mini);
		free(node->tokens[i]);
		node->tokens[i] = tmp;
		i++;
	}
}
