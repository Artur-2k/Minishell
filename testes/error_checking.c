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

int main()
{
    char *str = "";
    int result = ft_check_unclosed_quotes(str);
    printf("unclosed quotes ==> %d\n", result);
    return 0;
}