#include "minishell.h"


static char	*ft_trim(char *str)
{
	char *end;

	if (!str || !*str)
		return NULL;
	while (*str == ' ')
		str++;
	end = str + ft_strlen(str) - 1;
	while (end > str && *end == ' ')
		end--;
	end[1] = '\0';
	return (str);
}

static int	ft_count_tokens(char *str)
{
	int		count = 0;
	int		i = 0;
	char	quote_char = 0;
	bool	counter_flag = true;

	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote_char = str[i];
			i++;
			while(str[i] && str[i] != quote_char)
				i++;
			i++;
		}
		else if (str[i] == '<' || str[i] == '>')
		{
			if (str[i] == str[i + 1])
				i += 2;
			else
				i++;
			count++;
		}
		else if (str[i] == '|')
		{
			i++;
			count++;
		}
		else if (ft_isspace(str[i]))
		{
			while (str[i] && ft_isspace(str[i]))
				i++;
			counter_flag = true;
		}
		else
		{
			i++;
			if (counter_flag)
			{
				count++;
				counter_flag = false;
			}
		}
	}
	return (count);
}

int main()
{
	char *str = "";
	int n = ft_count_tokens(str);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str1 = "cmd";
	n = ft_count_tokens(str1);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str2 = "    ";
	n = ft_count_tokens(str2);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str3 = " ";
	n = ft_count_tokens(str3);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str4 = "<";
	n = ft_count_tokens(str4);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str5 = ">";
	n = ft_count_tokens(str5);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str6 = "<<";
	n = ft_count_tokens(str6);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str7 = ">>";
	n = ft_count_tokens(str7);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str8 = "|";
	n = ft_count_tokens(str8);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str9 = ">>>";
	n = ft_count_tokens(str9);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str10 = "<>";
	n = ft_count_tokens(str10);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str11 = "| ";
	n = ft_count_tokens(str11);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str12 = "||";
	n = ft_count_tokens(str12);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str13 = ">>>||";
	n = ft_count_tokens(str13);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str14 = "cmd |< cmd";
	n = ft_count_tokens(str14);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);



	char *str15 = "cmd |< cmd |";
	n = ft_count_tokens(str15);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str16 = "    cmd    cmd    ";
	n = ft_count_tokens(str16);
	printf("str:%s\n", str);
	printf("No tokens = %d\n", n);

	char *str17 = "cmd      cmd";
	n = ft_count_tokens(str);
	printf("str:%s\n", str17);
	printf("No tokens = %d\n", n);

	char *str18 = "cmd cmd";
	n = ft_count_tokens(str);
	printf("str:%s\n", str18);
	printf("No tokens = %d\n", n);

	return 0;
}