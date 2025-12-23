/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 12:40:10 by djareno           #+#    #+#             */
/*   Updated: 2025/12/23 13:27:39 by pabalvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	echo(t_mini *mini, int j)
{
	int i;

	i = 1;
	while (mini->nodes[j]->tokens[i])
	{
		if (i > 1)
			ft_putstr_fd(" ", 1);
		if (mini->nodes[j]->tokens[i][0] == '$')
			ft_putstr_fd(ft_getenv(mini->envp, mini->nodes[j]->tokens[i]), 1);
		ft_putstr_fd(mini->nodes[j]->tokens[i], 1);
		i++;
	}
	if (mini->nodes[j]->tokens[i] == NULL)
		ft_putstr_fd("\n", 1);
}

void export(t_mini *mini, int j)
{
	int i;

	i = 1;
	while (mini->nodes[j]->tokens[i])
	{
		char *arg;
		char *equal_sign;
		arg = mini->nodes[j]->tokens[i];
	    equal_sign = ft_strchr(arg, '=');

		if (equal_sign)
		{
			mini->envp[i] = ft_substr(arg, 0, ft_strlen(arg) - i + 1);
			set_env(mini->envp, mini->envp[i], equal_sign + 1);
		}
		i++;
	}
}

// void	unset(t_mini *mini)
// {
	
// }

int	set_env(char **envp, const char *key, const char *value)
{
	int		i;
	int		key_len;
	char	*new_entry;

	i = 0;
	key_len = ft_strlen(key);
	new_entry = malloc(key_len + 1 + strlen(value) + 1);
	if (!new_entry)
		return (-1);
	strcpy(new_entry, key);
	new_entry[key_len] = '=';
	strcpy(new_entry + key_len + 1, value);
	while (envp[i])
	{
		if (strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			free(envp[i]);
			envp[i] = new_entry;
			return (0);
		}
		i++;
	}
	free(new_entry);
	return (1);
}

void	cd(t_mini mini, char **cmd)
{
	char	*tmp;

	if (!cmd[1])
	{
		tmp = ft_getenv(mini.envp, "PWD");
		set_env(mini.envp, "OLDPWD", tmp);
		free(tmp);
		tmp = ft_getenv(mini.envp, "HOME");
		tmp = ft_strjoin("/", tmp);
		chdir(tmp);
		set_env(mini.envp, "PWD", tmp);
		free(tmp);
	}
	else
	{
		tmp = ft_getenv(mini.envp, "PWD");
		set_env(mini.envp, "OLDPWD", tmp);
		free(tmp);
		chdir(cmd[1]);
		tmp = malloc(1024);
		getcwd(tmp, 1024);
		set_env(mini.envp, "PWD", tmp);
		free(tmp);
	}
}

void	pwd(t_mini mini)
{
	char	*tmp;

	tmp = ft_getenv(mini.envp, "PWD");
	printf("%s\n", tmp);
	free(tmp);
}

void	env(t_mini mini)
{
	int	i;

	i = 0;
	while (mini.envp[i])
	{
		ft_putstr_fd(mini.envp[i], 1);
		printf("\n");
		i++;
	}
}

void	my_exit(t_mini mini)
{
	exit(mini.exit_code);
}
