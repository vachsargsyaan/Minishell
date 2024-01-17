
#include "minishell.h"

static int	set_values(t_list *var_list, char *new_pwd, char *current_pwd);
static int	cd_default(t_list *home, t_control *ctl, t_wordl **path);
static char	*my_get_cwd(void);

/**
 * @brief 
 * 
 * @param key 
 * @param value Use strdup before passing the argument.
 */
int	cd(t_wordl *args, t_control *ctl)
{
	t_wordl	*path;
	char	*current_pwd;
	char	*new_pwd;

	new_pwd = NULL;
	current_pwd = NULL;
	path = args->next;
	if (!path)
		cd_default(lst_get_by_key(ctl->var_list, "HOME"), ctl, &path);
	if (lst_get_by_key(ctl->var_list, "PWD"))
		current_pwd = ft_strdup(lst_get_by_key(ctl->var_list, "PWD")->value);
	if (chdir(path->word->value) != 0)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", \
			path->word->value, strerror(errno));
		estat_set(ctl->estat, EXIT_FAILURE);
		free(current_pwd);
		return (EXIT_FAILURE);
	}
	args->next = path;
	new_pwd = my_get_cwd();
	return (set_values(ctl->var_list, new_pwd, current_pwd));
}

static int	set_values(t_list *var_list, char *new_pwd, char *current_pwd)
{
	if (!new_pwd)
	{
		free(current_pwd);
		return (EXIT_FAILURE);
	}
	if (!current_pwd)
		current_pwd = ft_strdup("");
	lst_set(var_list, LOCAL, "PWD", new_pwd);
	lst_set(var_list, LOCAL, "OLDPWD", current_pwd);
	free(new_pwd);
	free(current_pwd);
	return (EXIT_SUCCESS);
}

static int	cd_default(t_list *home, t_control *ctl, t_wordl **path)
{
	if (!home)
	{
		ft_dprintf(STDERR_FILENO, ERROR_CD);
		estat_set(ctl->estat, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	*path = wordl_new(word_new(home->value, 0));
	return (EXIT_SUCCESS);
}

static char	*my_get_cwd(void)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		perror(EPERROR);
	return (new_pwd);
}
