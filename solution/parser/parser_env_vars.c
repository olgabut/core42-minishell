#include "minishell.h"

/*
	* # DESCRIPTION
	* Search for environment variable `key` in `env_list`, makes a copy of its value with `ft_strdup`
	* # RETURN VALUE
	* On success, the `get_env_value()` returns a pointer to a duplicated variable's value. It returens empty string ("") on failure.
*/
static char	*get_env_value(t_env *env_list, const char *key)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->key, key, ft_strlen(key) + 1) == 0)
			return (ft_strdup(env_list->value));
		env_list = env_list->next;
	}
	return (ft_strdup("")); 
}

static char	*expand_variables(t_minishell *mshell, const char *word)
{
	char	*result;
	size_t	i;
	size_t	start;
	char	lit[2];
	char	*key;
	char	*value;

	i = 0;
	lit[0] = word[i++];
	lit[1] = '\0';
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (word[i])
	{
		if (word[i] == '$')
		{
			start = ++i;
			if (!ft_isalpha(word[i]) && word[i] != '_')
			{
				lit = ft_substr(word, i - 1, 1);
				result = ft_strjoin_free(result, lit);
				free(lit);
				continue ;
			}
			while (ft_isalnum(word[i]) || word[i] == '_')
				i++;
			key = ft_substr(word, start, i - start);
			if (!key)
			{
				free(result);
				return (NULL);
			}
			if (ft_strncmp(key, "?", ft_strlen(key)) == 0)
			{
				value = ft_itoa(mshell->exit_code);
			}
			else
			{
				value = get_env_value(mshell->env_list, key);
			}
			free(key);
			if (!value)
			{
				free(result);
				return (NULL);
			}
			result = ft_strjoin_free(result, value);
			free(value);
			if (!result)
				return (NULL);
		}
		else
		{
			result = ft_strjoin_free(result, lit);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}

static t_list	*split_on_ifs(const char *str, const char *ifs)
{
	t_list	*fields;
	size_t	start;
	bool	in_field;
	char	*field;
	int		i;

	i = 0;
	fields = NULL;
	start = 0;
	in_field = false;
	while (str[i])
	{
		if (ft_strchr(ifs, str[i]))
		{
			if (in_field)
			{
				field = ft_substr(str, start, i - start);
				if (field && *field)
					ft_lstadd_back(&fields, ft_lstnew(field));
				else
					free(field);
				in_field = false;
			}
			i++;
			start = i;
		}
		else
		{
			if (!in_field)
				start = i;
			in_field = true;
			i++;
		}
	}
	if (in_field)
	{
		field = ft_substr(str, start, i - start);
		if (field && *field)
			ft_lstadd_back(&fields, ft_lstnew(field));
		else
			free(field);
	}
	return (fields);
}

char	*trim_quotes(char *word, enum e_quote flag)
{
	char	*trim_set;
	char	*trimmed;

	if (flag == SINGLE)
		trim_set = "'";
	else if (flag == DOUBLE)
		trim_set = "\"";
	else
		trim_set = NULL;
	if (trim_set)
	{
		trimmed = ft_strtrim(word, trim_set);
		free(word);
		if (!trimmed)
			return (NULL);
	}
	else
	{
		trimmed = ft_strdup(word);
		free(word);
		if (!trimmed)
			return (NULL);
	}
	return (trimmed);
}
t_list	*check_word(t_minishell *mshell, char *word)
{
	enum e_quote	flag;
	char			*trimmed;
	char			*expanded;
	t_list			*fields;
	char			*ifs;

	if (!word)
		return (NULL);
	flag = NONE;
	if (word[0] == SINGLE || word[0] == DOUBLE)
		flag = word[0];
	if (flag)
		trimmed = trim_quotes(word, flag);
	if (flag == SINGLE)
		expanded = trimmed;
	else
	{
		expanded = expand_variables(mshell, trimmed);
		free(trimmed);
		if (!expanded)
			return (NULL);
	}
	if (flag == NONE)
	{
		ifs = get_env_value(mshell->env_list, "IFS");
		if (!ifs || !*ifs)
		{
			free(ifs);
			ifs = ft_strdup(" \t\n");
		}
		fields = split_on_ifs(expanded, ifs);
		free(ifs);
		free(expanded);
	}
	else
		fields = ft_lstnew(expanded);
	// if (is_redir)
	// {
	// 	size = ft_lstsize(fields);
	// 	if (size != 1 || !fields || !*((char *)fields->content))
	// 	{
	// 		ft_lstclear(&fields, free);
	// 		mshell->exit_code = 1;
	// 	}
	// }
	if (!fields)
		return (NULL);
	return (fields);
}
