/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djareno <djareno@student.42madrid.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 12:40:10 by djareno           #+#    #+#             */
/*   Updated: 2025/12/15 13:09:50 by djareno          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	cd(char **envp, char **cmd)
{
	char	*tmp;

	if (!cmd[1])
	{
		tmp = ft_getenv(envp, "PWD");
		set_env(envp, "OLDPWD", tmp);
		free(tmp);
		tmp = ft_getenv(envp, "HOME");
		tmp = ft_strjoin("/", tmp);
		chdir(tmp);
		set_env(envp, "PWD", tmp);
		free(tmp);
	}
	else
	{
		tmp = ft_getenv(envp, "PWD");
		set_env(envp, "OLDPWD", tmp);
		free(tmp);
		chdir(cmd[1]);
		tmp = malloc(1024);
		getcwd(tmp, 1024);
		set_env(envp, "PWD", tmp);
		free(tmp);
	}
}

void	pwd(char **envp)
{
	char	*tmp;

	tmp = ft_getenv(envp, "PWD");
	printf("%s\n", tmp);
	free(tmp);
}

void	env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		printf("\n");
		i++;
	}
}

void	my_exit(void)
{
	exit(0);
}
