#include "parse.h"

int handle_redir(const char *s, int *i, t_node *node)
{
    if (!ft_ischev(s[*i]))
        return (0);

    if (s[*i] == '<')
    {
        if (s[*i + 1] == '<')
        {
            *i += 2;
            add_redir(node, HEREDOC, get_next_word(s, i));
        }
        else
        {
            (*i)++;
            add_redir(node, REDIR_IN, get_next_word(s, i));
        }
        return (1);
    }
    if (s[*i] == '>')
    {
        if (s[*i + 1] == '>')
        {
            *i += 2;
            add_redir(node, REDIR_APPEND, get_next_word(s, i));
        }
        else
        {
            (*i)++;
            add_redir(node, REDIR_OUT, get_next_word(s, i));
        }
        return (1);
    }
    return (0);
}

char *get_next_word(const char *s, int *i)
{
    int start = *i;
    int len = 0;

    while (s[*i] && ft_isspace(s[*i]))
        (*i)++;

    start = *i;
    while (s[*i] && !ft_isspace(s[*i]) && !ft_ischev(s[*i]))
    {
        (*i)++;
        len++;
    }
    return (word_dup(s + start, len));
}

void add_redir(t_node *node, t_redir_type type, char *file)
{
    node->redirs = realloc(node->redirs,
        sizeof(t_redir) * (node->redir_count + 1));
    node->redirs[node->redir_count].type = type;
    node->redirs[node->redir_count].file = file;
    node->redir_count++;
}

