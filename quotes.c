#include "minishell.h"

// char *quote_handler(t_shell *shell_info, t_token *iterate, char *quoted_str, t_token_type flag)
// {
// 	char		*temp2;
// (void)shell_info;
// 	temp2 = NULL;
// 	while (iterate && iterate->token_type != flag)
// 	{
// 		if (temp2 == NULL)
// 			temp2 = "";
// 		else
// 			temp2 = quoted_str;
// 		if (iterate->token_type == WORD)
// 			quoted_str = ft_strjoin(temp2, get_first_word(iterate->content));
// 		else if (iterate->token_type == PIPE)
// 			quoted_str = ft_strjoin(temp2, "|");
// 		else if (iterate->token_type == S_QUOTE)
// 			quoted_str = ft_strjoin(temp2, "\'");
// 		else if (iterate->token_type == S_LESS)
// 			quoted_str = ft_strjoin(temp2, "<");
// 		else if (iterate->token_type == S_MORE)
// 			quoted_str = ft_strjoin(temp2, ">");
// 		else if (iterate->token_type == D_LESS)
// 			quoted_str = ft_strjoin(temp2, "<<");
// 		else if (iterate->token_type == D_MORE)
// 			quoted_str = ft_strjoin(temp2, ">>");
// 		iterate = iterate->next;
// 	}
// 	return (quoted_str);
// }

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
	while (iterate->content[len] != '\0' && iterate->content[len] != c)
		len++;
	quoted_str = ft_calloc(sizeof(char), len + 1);
	if (!quoted_str)
		return(NULL);
	while (len > 0)
	{
		quoted_str[i] = iterate->content[i];
		i++;
		len--;
	}
	
	return (quoted_str);
}

t_token	*skip_quoted_str(t_token *to_skip, t_token_type flag)
{
	while (to_skip && to_skip->token_type != flag)
		to_skip = to_skip->next;
	if (to_skip)
		to_skip = to_skip->next;
	return (to_skip);
}
