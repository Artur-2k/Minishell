#include "minishell.h"

static bool    ft_check_unclosed_quotes(char **tkn_arr)
{
    int     i;
    int     j;
    char    quote_char;

    j = 0;
    while (tkn_arr[++j])
    {
        i = 0;
        while (tkn_arr[j][i])
        {
            if (tkn_arr[j][i] == '\'' || tkn_arr[j][i] == '"')
            {
                quote_char = tkn_arr[j][i++];
                while (tkn_arr[j][i] && tkn_arr[j][i] != quote_char)
                    i++;
                if (tkn_arr[j][i] != quote_char)
                    return (true);
                i++;
            }
            else
                i++;
        }
        j++;
    }
    return (false);
}

static bool    ft_check_redirecitons(char **tkn_arr)
{
	int	i;

	// pipe no inicio
	if (tkn_arr[0] && tkn_arr[0][0] == '|')
		return (true);

	// double redirs || |> ><...
	i = 0;
	while (tkn_arr[i] != NULL)
	{
		if (tkn_arr[i][0] == '|' || tkn_arr[i][0] == '<' || tkn_arr[i][0] == '>')
		{
			if (tkn_arr[i + 1] && (tkn_arr[i + 1][0] == '|' || tkn_arr[i + 1][0] == '<' || tkn_arr[i + 1][0] == '>'))
				return (true);
		}
		i++;
	}

	// > < | at the end(double redir are filtered)
	--i;
	if (tkn_arr[i][0] == '|' || tkn_arr[i][0] == '<' || tkn_arr[i][0] == '>')
		return (true);
	return (false);
}

 static void ft_find_syntax_errors(char **tkn_arr)
{
/*
 *   pipe at the start and end   | .................|           ✅
 *   heredoc no eof             ...  <<{nothing after}          ✅
 *   > >> e < without file      ...   > file < file >> file ... ✅
 *   double pipe token          ...     | |        ...          ✅
 *   pipe or redir              ...     | >                     ✅
 *   double redir token         ...  << >  > <  >> < ...        ✅
 *   "" '' nao fechadas											✅
 *      /MAIS NAO PLEASE T-T ❌
*/


    if (ft_check_unclosed_quotes(tkn_arr)) //todo
        ft_error(); // todo
    if (ft_check_double_redireciton(tkn_arr)) // todo atencao aspas
        ft_error();
    if (ft_check_pipes(tkn_arr)) // todo  atencao aspas
        ft_error();
    if (ft_check_redirs(tkn_arr)) // todo atencao aspas
        ft_error();

}