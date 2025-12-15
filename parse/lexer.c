void lexer(const char *input, t_token *token)
{
    int i = 0;
    while (input[i] != '\0')
    {
        if (input[i] == ' ')
        {
            i++;
        }
        else if (input[i] == '|')
        {
            token->is_pipe = 1;
            i++;
        }
        else
        {
            int start = i;
            while (input[i] != ' ' && input[i] != '|' && input[i] != '\0')
                i++;
        }
    }
}