#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool    ft_check_unclosed_quotes(char **tkn_arr)
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

bool    ft_check_redirecitons(char **tkn_arr)
{
	int	i;

	// pipe at the beggining
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

int main()
{
	/*
	 *  | bla bla bla
	 *  bla bla bla |
	 *  bla | | bla
	 *  > bla | > bla bla
	 *  > > bla bla lba
	 *  bla bla bla bla
	 *  bla bla bla <<
	 *  bla bla bla >>
	 *  bla bla bla >
	 *  bla bla bla <
	*/
	char *str = "";
    int result = ft_check_redirecitons(str);
    printf("Redir check ==> %d\n", result);
    return 0;
}