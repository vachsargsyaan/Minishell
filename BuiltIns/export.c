#include "minishell.h"
#include "lex.h"

static void	ft_sort(char **env);
static int	ft_default(char **env, t_list *var_list);
static void	set_values(t_control *ctl, t_wordl *tmp, char **key_val, int *fail);

int	export(t_wordl *args, t_control *ctl)
{
	char	**split;
	t_wordl	*temp;
	int		fail;

	fail = FALSE;
	temp = args->next;
	if (!temp)
		return (ft_default(get_env_key(ctl->var_list), ctl->var_list));
	while (temp)
	{
		split = get_key_value(temp->word->value);
		set_values(ctl, temp, split, &fail);
		free_2d(split);
		temp = temp->next;
	}
	estat_set(ctl->estat, fail);
	return (fail);
}

static void	set_values(t_control *ctl, t_wordl *tmp, char **key_val, int *fail)
{
	t_list	*key;

	if (!is_name(key_val[0]))
	{
		ft_dprintf(STDERR_FILENO, ERR_EXPORT, tmp->word->value);
		*fail = TRUE;
		return ;
	}
	key = lst_get_by_key(ctl->var_list, key_val[0]);
	if (key)
	{
		key->type = EXPORT;
		if (key_val[1])
			lst_set(ctl->var_list, EXPORT, key_val[0], key_val[1]);
	}
	else
		lst_set(ctl->var_list, EXPORT, key_val[0], key_val[1]);
}

static int	ft_default(char **env, t_list *var_list)
{
	int		i;
	t_list	*tmp;

	i = 0;
	ft_sort(env);
	while (env[i])
	{
		tmp = lst_get_by_key(var_list, *(env + i));
		printf("%s %s", DL, *(env + i));
		if (tmp->joined && ft_strchr(tmp->joined, EQUALS))
		{
			printf("=\"");
			if (tmp->value)
				printf("%s", tmp->value);
			printf("\"");
		}
		printf("\n");
		i ++;
	}
	free(env);
	return (EXIT_SUCCESS);
}

static void	ft_sort(char **env)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen_2d((const char **)env);
	i = 0;
	while (i < len -1)
	{
		j = i + 1;
		while (j < len)
		{
			if (ft_strcmp(env[i], env[j]) > 0)
				ft_swap((void **)&env[i], (void **)&env[j]);
			j++;
		}
		i++;
	}
}
