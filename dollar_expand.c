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
            return (env_mini->value);
        if (env_mini->next)
            env_mini = env_mini->next;
        else
            break ;
    }
    return (0);
}

// int	cnt_backslash(char *inpt)
// {
// 	int	i;

// 	i = 0;
// 	while (*inpt)
// 	{
// 		if (*inpt == '\\')
// 			i++;
// 		inpt++;
// 	}
// 	return (i);
// }

//	char	*ptr_inpt;
//	int		cnt_bs;
//	char	*bs_expanded;
// 	ptr_inpt = inpt;
// 	cnt_bs = cnt_backslash(ptr_inpt);
// 	bs_expanded = malloc(ft_strlen(ptr_inpt) - cnt_bs + 1);

// 	while (*ptr_inpt)
// 	{
// 		if (*ptr_inpt != '\\')
// 			*(bs_expanded++) == *(ptr_inpt++);
// 	}

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
	printf("ptr$ %s\n", ptr_dollar );
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

	// if (ptr_dollar && (*(ptr_dollar - 1) == '\\'))
	// 	*ptr_dollar = '^';
	// else if (ptr_dollar && (*(ptr_dollar - 1) != '\\'))
  	// {
  	//   str_till_dollar = ft_substr(inpt, 0, ptr_dollar - inpt);
  	//   str_after_varname = ptr_dollar + var_name_len + 1;
  	// }
  	// else
  	// {
  	//   str_till_dollar = 0;
  	//   str_after_varname = 0;
  	// }
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
  	  return (str_till_dollar);  //PROBLEM
  	else
  	  return (inpt);						//remove/change one of 2 returns
  	// ft_printf("join2 %s\n", join2);
  	  // return (free(join1), join2);
}

// void	replace_expand1(char *inpt, t_env_mini *env_mini)
void	replace_expand1(t_shell *shell_info)
{
	int		varname_len;
	char	*varvalue;
	char	*str;

	str = 0;
	if (shell_info->user_input)
		str = shell_info->user_input;
	// str = inpt;
	while (*str)
	{
		if (*str == '$')
		{
			varname_len = ft_varname_len(str);
			varvalue = ft_varvalue(varname_len, str, shell_info->env_mini);
			ft_printf("vv %s\n", varvalue);
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


// // char	*replace_caret(char *inpt)
// void	replace_caret(t_shell *shell_info)
// {
// 	char  *ptr_inpt;
// 	char  *output;
//   char  *str_till_dollar;
// 	char  *ptr_backslash;
// 	char  *inpt;

// 	inpt = shell_info->user_input;
// 	if (!inpt)
// 		return ;
// 	ptr_inpt = inpt;
// 	// ptr_backslash = 0;
//     ft_printf("ptr_inpt %s\n", ptr_inpt);
// 	// str_till_dollar = ft_substr(inpt, 0, ptr_backslash - inpt);
//     // printf("std %s\n", str_till_dollar);
//     ft_printf("stdlen %d\n", ft_strlen(ptr_inpt));

// 	while (*inpt)
// 	{
// 		if (*inpt == '\\' &&  *(inpt + 1) == '^')
// 		{
// 	    str_till_dollar = ft_substr(ptr_inpt, 0, inpt - ptr_inpt);
// 	    ptr_backslash = ft_strchr(inpt, '\\');
//       printf("pb %s\n", ptr_backslash);
//       printf("std %s\n", str_till_dollar);
//       ft_printf("hi\n");
// 			output = malloc(ft_strlen(ptr_inpt));
// 			ft_memset(output, 0, ft_strlen(ptr_inpt));
// 			ft_strlcat(output, str_till_dollar, ft_strlen(ptr_inpt));
// 			ft_strlcat(output, "$", ft_strlen(ptr_inpt));
// 			ft_strlcat(output, inpt + 2, ft_strlen(ptr_inpt));
//       printf("output %s\n", shell_info->user_input);
//       shell_info->user_input = output;

//       // return (output);
// 		}
// 		if (inpt++)
// 			inpt++;
// 	}
// 	// shell_info->user_input = ptr_inpt;
// 	// return (ptr_inpt);
// }

//when user_input is 0
// char    *expand(t_shell *shell_info)
void	ft_expand(t_shell *shell_info)
{
  if (!shell_info->user_input)
    return ;
	  replace_bs_dollar(shell_info);
    // ft_printf("rebsd %s\n", shell_info->user_input); //OK
    // replaced = replace_expand(inpt, var_value, len);
	  replace_expand1(shell_info);
    // ft_printf("repex1 %s\n", shell_info->user_input); //OK
    replace_caret(shell_info);
    // ft_printf("reca %s\n", shell_info->user_input); //OK

    // t_env_mini  *env_mini;
    // char        *inpt;
    // char        *var_value;
    // int         len;
    // // char        *replaced;

	// len = 0;
    // inpt = NULL;
    // if (shell_info->user_input)
    //     inpt = shell_info->user_input;
    // else
    //     return (NULL);
    // //          ft_printf("i %d\n", i);
    // // ft_printf("inpt %s\n", inpt);
    // // ft_printf("isalnumun %s\n", is_al_num_underscore(0));
    // env_mini = shell_info->env_mini;
    // len = ft_varname_len(inpt);
    // // ft_printf("lens %d\n", len);
  	// if (!len && ft_strchr(inpt, '$'))
    // 	return (inpt);
    // // ft_printf("minishell: $: command not found\n");
    // var_value = ft_varvalue(len, inpt, env_mini);
    // // ft_printf("vv %s\n", var_value);
    // // replaced = replace_bs_dollar(inpt);

    // ft_printf("repex %s\n", inpt); // echo \$USER $USER => echo \^USER yowoo
	// replaced = replace_caret(replaced);
    // ft_printf("repca %s\n", replaced);
    // if (replaced && ft_strlen(replaced))
    // 	return (replaced);
  	// else
    // 	return (inpt);
    // return (inpt);
}

// char	*expand_loop(char *inpt)
// {
// 	char	*ptr_inpt;

// 	if (!inpt)
// 		return (0);
// 	ptr_inpt = inpt;
// 	while (*inpt)
// 	{
// 		if (*inpt == '$')
// 		{
// 			replace_expand(inpt, )
// 		}
// 	}
// }


//$? required
//$$$ =>in bash 882882?
//expand is case sensitive

//
//SQUOTE,  << $USER not expand

//caret == \^, Malloc
