#include "minishell.h"

int is_al_num_udsc_c(char c)
{
    if (ft_isalnum(c) || c == '_')
        return (1);
    return (0);
}

//if $ in str, return lenth of first varname
int varname_len(char *str)
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
char    *varvalue(int var_name_len, char *str, t_env_mini *env_mini)
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

	str_till_dollar = 0;
  	str_after_varname = 0;
	ptr_dollar = ft_strchr(inpt, '$');
	// printf("ptr$ %s\n", ptr_dollar );
	// printf("ptr$-1 %c\n", *(ptr_dollar - 1));
	// printf("ptr$-1 %d\n", *(ptr_dollar - 1) == '\\');
    
	
	if (ptr_dollar && (*(ptr_dollar - 1) == '\\'))
		*ptr_dollar = '^';
	else if (ptr_dollar && (*(ptr_dollar - 1) != '\\'))
  	{
  	  str_till_dollar = ft_substr(inpt, 0, ptr_dollar - inpt);
  	  str_after_varname = ptr_dollar + var_name_len + 1;
  	}
  	else
  	{
  	  str_till_dollar = 0;
  	  str_after_varname = 0;
  	}


	// if (ft_strchr(inpt, '$'))
  	// {
	// 	// printf("$ - 1 %s\n", ft_strchr(inpt, '$') - 1 );
	// 	// printf("$ - 1=%c\n", *(ft_strchr(inpt, '$') - 1));
	// 	// printf("isb=%d\n", is_backslash(ft_strchr(inpt, '$') - 1));
	// 	// printf("$ - 1=%d\n", *(ft_strchr(inpt, '$') - 1) == '\\');
	// 	if (*(ft_strchr(inpt, '$') - 1) != '\\')
	// 	{
	// 		printf("hi");
  	//   		str_till_dollar = ft_substr(inpt, 0, ft_strchr(inpt, '$') - inpt);
  	//   		str_after_varname = ft_strchr(inpt, '$') + var_name_len + 1;
	// 	}
  	// }
	// else
  	// {
  	//   str_till_dollar = 0;
  	//   str_after_varname = 0;
  	// }

	// if (ft_strchr(inpt, '$'))
  	// {
  	//   str_till_dollar = ft_substr(inpt, 0, ft_strchr(inpt, '$') - inpt);
  	//   str_after_varname = ft_strchr(inpt, '$') + var_name_len + 1;
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
  else if (!var_value)
  {
    return (str_till_dollar);
  }
  else
    return ("");						//remove/change one of 2 returns
  // ft_printf("join2 %s\n", join2);
    // return (free(join1), join2);
}

//caret == \^, Malloc
char	*replace_caret(char *inpt)
{
	char	*ptr_inpt;
	char	*output;
    char    *str_till_dollar;
	char    *ptr_backslash;

	ptr_inpt = inpt;
	ptr_backslash = ft_strchr(inpt, '\\');
	str_till_dollar = ft_substr(inpt, 0, ptr_backslash - inpt);
    // ft_printf("std %s\n", str_till_dollar);
    ft_printf("stdlen %d\n", ft_strlen(ptr_inpt));

	while (*inpt)
	{
		if (*inpt == '\\' &&  *(inpt + 1) == '^')
		{
		    ft_printf("hi");
			output = malloc(ft_strlen(ptr_inpt));
			ft_memset(output, 0, ft_strlen(ptr_inpt));
			ft_strlcat(output, str_till_dollar, ft_strlen(ptr_inpt));
			ft_strlcat(output, "$", ft_strlen(ptr_inpt));
			ft_strlcat(output, inpt + 2, ft_strlen(ptr_inpt));
			return (output);
		}
		inpt++;
	}
	return (ptr_inpt);
}
//when user_input is 0
char    *dollar_expand(t_shell *shell_info)
{
    t_env_mini  *env_mini;
    char        *inpt;
    char        *var_value;
    int         len;
    char        *replaced;

	len = 0;
    inpt = NULL;
    if (shell_info->user_input)
        inpt = shell_info->user_input;
    else
        return (NULL);
    //          ft_printf("i %d\n", i);
    // ft_printf("inpt %s\n", inpt);
    // ft_printf("isalnumun %s\n", is_al_num_underscore(0));
    env_mini = shell_info->env_mini;
    len = varname_len(inpt);
    // ft_printf("lens %d\n", len);
  	if (!len && ft_strchr(inpt, '$'))
    	return (inpt);
    // ft_printf("minishell: $: command not found\n");
    var_value = varvalue(len, inpt, env_mini);
    // ft_printf("vv %s\n", var_value);
    replaced = replace_expand(inpt, var_value, len);
    // ft_printf("repex %s\n", replaced); // echo \$USER $USER => echo \^USER yowoo
	replaced = replace_caret(replaced);
    ft_printf("repca %s\n", replaced);
    if (replaced && ft_strlen(replaced))
    	return (replaced);
  	else
    	return (inpt);
    // return (replaced);
}

//$? required
//$$$ =>in bash 882882?
//expand is case sensitive

//
//SQUOTE,  << $USER not expand