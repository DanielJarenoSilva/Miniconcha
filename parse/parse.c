/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:37:33 by djareno           #+#    #+#             */
/*   Updated: 2025/12/15 15:16:29 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	count_tokens(const char *s)
{
	int	count;
	int	quote;

	count = 0;
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (!*s)
			break ;
		count++;
		quote = 0;
		while (*s)
		{
			if (!quote && ft_isquote(*s))
				quote = *s;
			else if (quote && *s == quote)
			{
				s++;
				break ;
			}
			else if (!quote && ft_isspace(*s))
				break ;
			s++;
		}
	}
	return (count);
}

char	**tokenizer(const char *s)
{
	char		**tokens;
	int			i;
	int			len;
	char		quote;
	const char	*start;

	i = 0;
	tokens = malloc(sizeof(char *) * (count_tokens(s) + 1));
	if (!tokens)
		return (NULL);
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (!*s)
			break ;
		start = s;
		len = 0;
		quote = 0;
		if (ft_isquote(*s))
		{
			quote = *s++;
			start = s;
			while (s[len] && s[len] != quote)
				len++;
			tokens[i++] = word_dup(start, len);
			s += len + 1;
		}
		else
		{
			while (s[len] && !ft_isspace(s[len]) && !ft_isquote(s[len]))
				len++;
			tokens[i++] = word_dup(start, len);
			s += len;
		}
	}
	tokens[i] = NULL;
	return (tokens);
}

int	get_quotes(char *s)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (s[i])
	{
		if (ft_isquote(s[i]))
			quote++;
		i++;
	}
	if (quote == 0)
		return (-1);
	if (quote % 2 == 0)
		return (1);
	return (0);
}

char	**get_nodes(const char *s)
{
	int			i;
	int			len;
	char		quote;
	char		**nodes;
	const char	*start;

	i = 0;
	nodes = malloc(sizeof(char *) * 1024);
	if (!nodes)
		return (NULL);
	if (get_quotes((char *)s) == 0)
	{	
		printf("Error: Unmatched quotes\n");
		return (NULL);
	}
	while (*s)
	{
		while (*s && ft_isspace(*s))
			s++;
		if (!*s)
			break ;
		if (*s == '|')
			s++;
		start = s;
		len = 0;
		quote = 0;
		while (s[len])
		{
			if (!quote && ft_isquote(s[len]))
				quote = s[len];
			else if (quote && s[len] == quote)
				quote = 0;
			else if (!quote && s[len] == '|')
				break ;
			len++;
		}
		nodes[i++] = word_dup(start, len);
		s += len;
	}
	nodes[i] = NULL;
	return (nodes);
}

void	parser(const char *s)
{
	char	**cmds;
	int		i;
	t_mini	mini;

	i = 0;
	mini.nodes = malloc(sizeof(t_node *) * 1024);
	cmds = get_nodes(s);
	if (!cmds)
		return ;
	while (cmds[i])
	{
		mini.nodes[i] = malloc(sizeof(t_node));
		mini.nodes[i]->tokens = tokenizer(cmds[i]);
		i++;
	}
	mini.nodes[i] = NULL;
	print_nodes(mini);
}




// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parse.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/12/01 12:37:33 by djareno           #+#    #+#             */
// /*   Updated: 2025/12/15 15:16:29 by pabalvar         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// //TODO: cambiar tokenizer para que gestione comillas ademas de espacios, y pasando por argumento el struct mini para guardar los tokens en el nodo correspondiente


// void	get_tookens(t_mini *mini)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (mini->nodes[i])
// 	{
// 		j = 0;
// 		while (mini->nodes[i]->tokens[j])
// 		{
// 			mini->nodes[i]->tokens = tokenizer(mini->nodes[i]->tokens[j]);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	parser(const char *s)
// {
// 	char	**t;
// 	int		i;
// 	int		j;
// 	t_mini	mini;

// 	i = 0;
// 	j = 0;
// 	mini.nodes = malloc(sizeof(t_node *) * 1024);
// 	t = get_nodes(s);
// 	if (!t)
// 		return ;
// 	while (t[i])
// 	{
// 		mini.nodes[i] = malloc(sizeof(t_node));
// 		mini.nodes[i]->tokens = malloc(sizeof(char *) * 1024);
// 		j = 0;
// 		mini.nodes[i]->tokens[j++] = ft_strdup(t[i]);
// 		mini.nodes[i]->tokens[j] = NULL;
// 		// printf("node %d: %s\n", i, mini.nodes[i]->tokens[0]);
// 		i++;
// 	}
// 	mini.nodes[i] = NULL;
// 	get_tookens(&mini);
// 	print_nodes(mini);
// }

// static int	ft_count_words(const char *s)
// {
// 	int	count;

// 	if (!*s)
// 		return (0);
// 	count = 0;
// 	while (*s)
// 	{
// 		while (*s && ft_isspace(*s))
// 			s++;
// 		if (*s)
// 			count++;
// 		while (!ft_isspace(*s) && *s)
// 			s++;
// 	}
// 	return (count);
// }

// int	get_quotes(char *s)
// {
// 	int	quote;
// 	int	i;

// 	quote = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		if (ft_isquote(s[i]))
// 		{
// 			quote++;
// 			i++;
// 		}
// 		i++;
// 	}
// 	if (quote == 0)
// 		return (-1);
// 	if (quote != 0 && quote % 2 == 0)
// 		return (1);
// 	return (0);
// }

// char	**get_nodes(const char *s)
// {
// 	int			i;
// 	int			len;
// 	char		quote;
// 	char		**nodes;
// 	const char	*start;

// 	i = 0;
// 	nodes = malloc(sizeof(char *) * 1024);
// 	if (!nodes)
// 		return (NULL);
// 	if (get_quotes((char *)s) == 0)
// 		return (NULL);
// 	while (*s)
// 	{
// 		while (*s && ft_isspace(*s))
// 			s++;
// 		if (!*s)
// 			break ;
// 		if (*s == '|')
// 		{
// 			s++;
// 		}
// 		start = s;
// 		len = 0;
// 		quote = 0;
// 		while (s[len])
// 		{
// 			if (!quote && ft_isquote(s[len]))
// 				quote = s[len];
// 			else if (quote && s[len] == quote)
// 				quote = 0;
// 			else if (!quote && s[len] == '|')
// 				break ;
// 			len++;
// 		}
// 		nodes[i++] = word_dup(start, len);
// 		s += len;
// 	}
// 	nodes[i] = NULL;
// 	return (nodes);
// }

// // char	**get_nodes(const char *s)
// // {
// // 	int			i;
// // 	char		**nodes;
// // 	const char	*start;
// // 	int			len;

// // 	i = 0;
// // 	nodes = malloc(sizeof(char *) * 1024);
// // 	if (!nodes)
// // 		return (NULL);
// // 	if (get_quotes((char *)s) == 1)
// // 	{
// // 		while (*s)
// // 		{
// // 			while (*s && ft_isquote(*s))
// // 				s++;
// // 			if (*s && !ft_isquote(*s))
// // 			{
// // 				start = s;
// // 				len = 0;
// // 				while (s[len] && !ft_isquote(s[len]))
// // 					len++;
// // 				nodes[i++] = word_dup(start, len);
// // 				s += len;
// // 			}
// // 		}
// // 	}
// // 	else
// // 	{
// // 		while (s[i])
// // 		{
// // 			while (s[i] && (ft_isspace(s[i]) || ft_ispipe(s[i])))
// // 				s++;
// // 			if (s[i] && !ft_isspace(s[i]) && !ft_ispipe(s[i]))
// // 			{
// // 				start = s;
// // 				len = 0;
// // 				while (s[len] && !ft_ispipe(s[len]))
// // 					len++;
// // 				nodes[i++] = word_dup(start, len);
// // 				i += len;
// // 			}
// // 		}
// // 	}
// // 	nodes[i] = NULL;
// // 	return (nodes);
// // }

// char	**tokenizer(const char *s)
// {
// 	int			words;
// 	char		**tokens;
// 	int			i;
// 	const char	*start;
// 	int			len;

// 	words = ft_count_words(s);
// 	tokens = malloc(sizeof(char *) * (words + 1));
// 	i = 0;
// 	if (!tokens)
// 		return (NULL);
// 	while (*s)
// 	{
// 		while (*s && ft_isspace(*s))
// 			s++;
// 		if (*s && !ft_isspace(*s))
// 		{
// 			start = s;
// 			len = 0;
// 			while (s[len] && !ft_isspace(s[len]))
// 				len++;
// 			tokens[i++] = word_dup(start, len);
// 			s += len;
// 		}
// 	}
// 	tokens[i] = NULL;
// 	return (tokens);
// }

// // Hacer que divida por pipes etc y demas, pipex????????¿¿¿¿¿¿