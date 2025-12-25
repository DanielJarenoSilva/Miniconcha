/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabalvar <pabalvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 12:40:10 by djareno           #+#    #+#             */
/*   Updated: 2025/12/23 15:07:30 by pabalvar         ###   ########.fr       */
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

static int env_len(char **envp)
{
    int i = 0;
    while (envp && envp[i])
        i++;
    return i;
}

void export(t_mini *mini, int j)
{
    int     i = 1;
    char    *key;
    char    *value;
    char    *eq;

    while (mini->nodes[j]->tokens[i])
    {
        eq = ft_strchr(mini->nodes[j]->tokens[i], '=');
        if (!eq)
        {
            i++;
            continue;
        }

        key = ft_substr(mini->nodes[j]->tokens[i], 0,
                         eq - mini->nodes[j]->tokens[i]);
        value = eq + 1;

        if (set_env(mini->envp, key, value) == 1)
        {
            int len = env_len(mini->envp);
            char **new_env = malloc(sizeof(char *) * (len + 2));

            for (int k = 0; k < len; k++)
                new_env[k] = mini->envp[k];

            new_env[len] = ft_strjoin(key, "=");
            new_env[len] = ft_strjoin_free(new_env[len], ft_strdup(value));
            new_env[len + 1] = NULL;

            free(mini->envp);
            mini->envp = new_env;
        }
        free(key);
        i++;
    }
}

void unset(t_mini *mini, int j)
{
    int arg;
    int i;
    int k;
    int len;

    arg = 1;
    while (mini->nodes[j]->tokens[arg])
    {
        len = ft_strlen(mini->nodes[j]->tokens[arg]);
        i = 0;
        while (mini->envp[i])
        {
            if (ft_strncmp(mini->envp[i],
                           mini->nodes[j]->tokens[arg],
                           len) == 0
                && mini->envp[i][len] == '=')
            {
                free(mini->envp[i]);
                k = i;
                while (mini->envp[k])
                {
                    mini->envp[k] = mini->envp[k + 1];
                    k++;
                }
                break; 
            }
            i++;
        }
        arg++;
    }
}


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
