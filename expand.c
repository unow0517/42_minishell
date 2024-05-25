#include "minishell.h"

int is_al_num_udsc_c(char c)
{
    if (ft_isalnum(c) || c == '_')
        return (1);
    return (0);
}

//if $ in str, return lenth of first varname
int ft_varname_len(char *str)
{
    int         i;
    // char     *ptr;
    i = 0;
    while (*str && str)
    {
        if (*str == '$')
        {
            str++;
            while (is_al_num_udsc_c(*str))
            {
                i++;
                str++;
            }
            if (!is_al_num_udsc_c(*str))
                break ;
        }
        str++;
    }
    return (i);
}

//return var value from string, namelen, envlist.
char    *ft_varvalue(int var_name_len, char *str, t_env_mini *env_mini)
{
    char    *ptr_dollar;
    char    *varname;
    ptr_dollar = ft_strchr(str, '$'); //first $ position
    if (!ptr_dollar)
        return (0);
    varname = ft_substr(ptr_dollar + 1, 0, var_name_len);
    // ft_printf("vn %s\n", varname);
    while (env_mini)
    {
        if (inputis(env_mini->name, varname))
		{
    // ft_printf("value %s\n", env_mini->value);
            return (env_mini->value);
		}
        if (env_mini->next)
            env_mini = env_mini->next;
        else
            break ;
    }
    return (0);
}

// void	replace_bs_dollar(char *inpt)
void	replace_bs_dollar(t_shell *shell_info)
{
	char	*inpt;

	inpt = 0;
  if (shell_info->user_input)
    inpt = shell_info->user_input;
	while (*inpt)
	{
		if (*inpt == '\\' && *(inpt + 1) == '$')
		{
			*(inpt + 1) = '^';
		}
		else if (*inpt == '$' && *(inpt + 1) == '\\')
		{
			*inpt = '^';
		}
		if (inpt + 1)
			inpt++;
	}
}

//MALLOC!
//IF /$ exist => replace it to /^,
char    *replace_expand(char *inpt, char *var_value, int var_name_len)
{
    // int      var_value_len;


    char    *str_till_dollar;
    char    *str_after_varname;
    char    *join1;
    char    *join2;
	char    *ptr_dollar;
    // var_value_len = ft_strlen(var_value);
    // str_till_dollar = ft_substr(inpt, 0, ft_strchr(inpt, '$') - inpt);

	if (!inpt)
		return (0);
	str_till_dollar = 0;
  	str_after_varname = 0;
	ptr_dollar = ft_strchr(inpt, '$');
	// printf("ptr$ %s\n", ptr_dollar );
	// printf("ptr$-1 %c\n", *(ptr_dollar - 1));
	// printf("ptr$-1 %d\n", *(ptr_dollar - 1) == '\\');

	if (ptr_dollar)
  	{
  	  str_till_dollar = ft_substr(inpt, 0, ptr_dollar - inpt);
  	  str_after_varname = ptr_dollar + var_name_len + 1;
  	}
  	else
  	{
  	  str_till_dollar = 0;
  	  str_after_varname = 0;
  	}

	// ft_printf("inptrp %s\n", inpt);
  	// ft_printf("len %d\n", var_name_len);
    // ft_printf("std %s\n", str_till_dollar);
    // ft_printf("sav %s\n", str_after_varname);
    // ft_printf("vv %s\n", var_value);

  	if (str_till_dollar && str_after_varname && var_value)
  	{
  	  // ft_printf("hi");
  	  join1 = ft_strjoin(str_till_dollar, var_value);
  	  join2 = ft_strjoin(join1, str_after_varname);
		return (join2);
  	}
  	else if (ptr_dollar && !var_value)
	{
  	  join1 = ft_strjoin(str_till_dollar, str_after_varname);
  	  return (str_till_dollar);
	}
  	else
  	  return (inpt);						//remove/change one of 2 returns
  	// ft_printf("join2 %s\n", join2);
  	  // return (free(join1), join2);
}

void	replace_dollar_question(t_shell *shell_info)
{
	char	*str;
	char	*inpt;
	// char    *ptr_question;
    char    *str_till_dollar;
    char    *str_after_varname;
    char    *join1;
    char    *join2;

	str = 0;
	if (shell_info->user_input)
		str = shell_info->user_input;
	inpt = str;
	str_till_dollar = 0;
  	str_after_varname = 0;
	while (*str)
	{
		if (*str == '$' && *(str + 1) == '?')
		{
			str_till_dollar = ft_substr(inpt, 0, str - inpt);
    // ft_printf("std %s\n", str_till_dollar);
			str_after_varname = str + 2;
    // ft_printf("sav %s\n", str_after_varname);
  	  		join1 = ft_strjoin(str_till_dollar, ft_itoa(*(shell_info->status)));
  	  		join2 = ft_strjoin(join1, str_after_varname);
			shell_info->user_input = join2;
			free(join1);
		}
		if (str + 1)
			str++;
	}
}

// void	replace_expand1(char *inpt, t_env_mini *env_mini)
void	replace_expands_loop(t_shell *shell_info)
{
	int		varname_len;
	char	*varvalue;
	char	*str;

	str = 0;
	if (shell_info->user_input)
		str = shell_info->user_input;
	// str = inpt;
	// replace_dollar_question(shell_info);
	while (*str)
	{
		if (*str == '$')
		{
			// if (*(str + 1) == '?')
			// {
			// 	// ft_printf("%d\n",*(shell_info->status));
			// 	varvalue = ft_itoa(*(shell_info->status));
			// }
			// else
			varname_len = ft_varname_len(str);
			varvalue = ft_varvalue(varname_len, str, shell_info->env_mini);
			// ft_printf("vv %s\n", varvalue);
			shell_info->user_input = replace_expand(shell_info->user_input, varvalue, varname_len);
		}
		if (str + 1)
			str++;
	}
}


void	replace_caret(t_shell *shell_info)
{
	char  *inpt;
  int   cnt;
  char  *output;
  int i;
  int j;
  
  inpt = shell_info->user_input;
  cnt = 0;
  while (*inpt)
	{
    if (*inpt == '\\' &&  *(inpt + 1) == '^')
      cnt++;
    if (*inpt == '^' &&  *(inpt + 1) == '\\')
      cnt++;	  
    inpt++;
  }
  inpt = shell_info->user_input;
    // ft_printf("stdlen %d\n", ft_strlen(inpt));
  output = malloc(ft_strlen(inpt) - cnt + 1);
  i = 0;
  j = 0;
  while (inpt[i])
  {
    if (inpt[i] == '\\' && inpt[i + 1] == '^')
    {
      output[j] = '$';
      i++;
    }
	else if (inpt[i] == '^' && inpt[i + 1] == '\\')
    {
      output[j] = '$';
      i++;
    }
    else
      output[j] = inpt[i];
    j++;
    i++;
  }
  output[ft_strlen(inpt) - cnt] = '\0';
//   printf("outputlen %s\n", output);
//   printf("output %s\n", output);
  shell_info->user_input = output;
  // free(output);
}

void	expand_except_literal(t_shell *shell_info)
{
	replace_bs_dollar(shell_info);
	replace_dollar_question(shell_info);
	replace_expands_loop(shell_info);
	replace_caret(shell_info);
}

//echo 'hi' ->hi
//echo "hi" ->hi
//echo "$USER" -> yowoo
//echo '$USER' -> $USER
//echo "'$USER' hello" -> 'yowoo' hello
//echo '"$USER" hello' -> "$USER" hello
//echo '"$USER" hello' -> "$USER" hello
// char *rm_outest_q(t_shell *shell_info)
void rm_outest_q_and_exp(t_shell *shell_info)
{
	char	c;
	char	*str;
	// char	*ptr;

	str = shell_info->user_input;
	c = first_quote(str);
	// ptr = str;
	if (c != 'n')
	{
		ft_printf("C %c\n", c);
		ft_printf("Input %s\n", shell_info->user_input);
		// shell_info->user_input = rm_quotes(shell_info->user_input, c);
		// ft_printf("after_rm_quotes %s\n", rm_quotes(shell_info->user_input, c));
		if (c == '"')
			expand_except_literal(shell_info);
	}
	else
		expand_except_literal(shell_info);
}

void rm_outest_q(t_shell *shell_info)
{
	char	c;
	char	*str;
	// char	*ptr;

	str = shell_info->user_input;
	c = first_quote(str);
	// ptr = str;
	if (c != 'n')
	{
		shell_info->user_input = rm_quotes(shell_info->user_input, c);
	}
}

void rm_ws_following_d_less(t_shell *shell_info)
{
	char	*str;
	char	*inpt;
	char	*str_till_dless;
	char	*str_after_dless;
	char	*join;

	str = shell_info->user_input;
	inpt = str;
	str_till_dless = 0;
	str_after_dless = 0;
	while (str && *str)
	{
		if (*str == '<' && *(str + 1) == '<')
		{
			str_till_dless = ft_substr(inpt, 0, (str + 1) - inpt + 1);
			// printf("std %s\n", str_till_dless);
			str_after_dless = str + 2;
			// printf("sad %s\n", str_after_dless);
			shell_info->isheredoc = 1;
			break ;
		}
		if (str + 1)
			str++;
	}
	if (str_after_dless)
		str_after_dless = rm_starting_ws(str_after_dless);
	// printf("sadrmws %s\n", str_after_dless);
	if (str_till_dless && str_after_dless)
	{
		join = ft_strjoin(str_till_dless, str_after_dless);
		shell_info->user_input = join;
	}
}
//when user_input is 0
// char    *expand(t_shell *shell_info)
void	ft_expand(t_shell *shell_info)
{
	if (!shell_info->user_input)
		return ;
  	if (ft_strchr(shell_info->user_input, '$') == 0)
		return ;


	// replace_bs_dollar(shell_info);
    // ft_printf("rebsd %s\n", shell_info->user_input); //OK
    // replaced = replace_expand(inpt, var_value, len);
	// printf("rmq %s\n", rm_quotes(shell_info->user_input, '"'));
	// printf("rmoq %s\n", rm_outest_q(shell_info));
	rm_ws_following_d_less(shell_info);
    // ft_printf("rm << %s\n", shell_info->user_input); //OK
	// ft_printf("rm_ws_following_d_less: %s\n", shell_info->user_input); //OK
	// ft_printf("ishd %d\n", shell_info->isheredoc);
	if (shell_info->isheredoc == 0)
	{
		rm_outest_q_and_exp(shell_info);
	}
	else
	{
		rm_outest_q(shell_info);
		shell_info->isheredoc = 0;
	}
	// expand_except_literal(shell_info);

	// dollar_literal(shell_info);
	// replace_expands_loop(shell_info);
	ft_printf("EXPANDED: %s\n", shell_info->user_input); //OK
    // ft_printf("repex1 %s\n", shell_info->user_input); //OK
    // replace_caret(shell_info);
    // ft_printf("reca %s\n", shell_info->user_input); //OK
}

