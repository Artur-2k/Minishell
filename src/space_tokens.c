#include <minishell.h>

static char *ft_is_quoted(char *str, char *nstr, bool *flag, int *i)
{
    char       quote_char;

    quote_char = str[*i];
    nstr = ft_append_char_to_str(nstr, str[(*i)++]);
    while(str[*i] && str[*i] != quote_char)
        nstr = ft_append_char_to_str(nstr, str[(*i)++]);
    if (str[*i])
        nstr = ft_append_char_to_str(nstr, str[(*i)++]);
    *flag = true;
    return (nstr);
}

static char *ft_append_redir(char *str, char *nstr, bool *flag, int *i)
{
    if(*flag) 
        nstr = ft_append_char_to_str(nstr, ' ');
    if (str[*i] == str[*i + 1])
    {
        nstr = ft_append_char_to_str(nstr, str[(*i)++]);
        nstr = ft_append_char_to_str(nstr, str[(*i)++]);
    }
    else
        nstr = ft_append_char_to_str(nstr, str[(*i)++]);
    if (str[*i])
        nstr = ft_append_char_to_str(nstr, ' ');
    *flag = false;
    return (nstr);
}

static char *ft_append_pipe(char *str, char *nstr, bool *flag, int *i)
{
    if(*flag) 
        nstr = ft_append_char_to_str(nstr, ' ');
    nstr = ft_append_char_to_str(nstr, str[(*i)++]);
    if (str[*i])
        nstr = ft_append_char_to_str(nstr, ' ');
    *flag = false;
    return (nstr);
}

static char *ft_spacing(char *str, char *nstr, bool *flag, int *i)
{
    if(*flag) 
        nstr = ft_append_char_to_str(nstr, ' ');
    while (str[*i] && ft_isspace(str[*i]))
        (*i)++;
    *flag = false;
    return (nstr);
}
char    *ft_space_tokens(char *str)
{
    bool    flag;
    int     i; 
    
    i = 0;
    flag = false;
    str = ft_trim(str); 
    char *nstr = NULL;
	while(str && str[i])
	{
        if (str[i] == '\'' || str[i] == '"')
			nstr = ft_is_quoted(str, nstr, &flag, &i);
        else if (str[i] == '<' || str[i] == '>')
           nstr = ft_append_redir(str, nstr, &flag, &i);
		else if (str[i] == '|')
            nstr = ft_append_pipe(str, nstr, &flag, &i);
		else if (ft_isspace(str[i]))
            nstr = ft_spacing(str, nstr, &flag, &i);
		else
        {
            nstr = ft_append_char_to_str(nstr, str[i++]);
            flag = true;
        }
    }
    return (nstr);
}
