#include "minishell.h"

char *quote_handler(t_shell *shell_info, t_token *iterate, char *quoted_str, t_token_type flag)
{
	int		len;
	int		i;
	char	c;

	if (flag == D_QUOTE)
		c = '"';
	else if (flag == S_QUOTE)
		c = '\'';
	i = 0;
(void)shell_info;
	len = 0;
	while (iterate->content[len] != '\0' && (iterate->content[len] != c || len == 0))
		len++;
	len += 1;
	quoted_str = ft_calloc(len + 1, sizeof(char));
	if (!quoted_str)
		return(NULL);
	while (len > 0)
	{
		quoted_str[i] = iterate->content[i];
		i++;
		len--;
	}
// printf("quoted_str = %s\n", quoted_str);
	return (quoted_str);
}

t_token	*skip_quoted_str(t_token *to_skip, t_token_type flag)
{
	to_skip = to_skip->next;
	while (to_skip && to_skip->token_type != flag)
		to_skip = to_skip->next;
	if (to_skip)
		to_skip = to_skip->next;
	return (to_skip);
}
