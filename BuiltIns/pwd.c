#include "minishell.h"

int	pwd(t_wordl *cmd, t_control *ctl)
{
	char	*pwd;

	(void)cmd;
	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		printf("%s\n", pwd);
		free(pwd);
		estat_set(ctl->estat, EXIT_SUCCESS);
		return (EXIT_SUCCESS);
	}
	perror(EPERROR);
	estat_set(ctl->estat, EXIT_FAILURE);
	return (EXIT_FAILURE);
}
