#include "minishell.h"

int	env(t_wordl *cmd, t_control *ctl)
{
	t_list	*temp;

	(void)cmd;
	temp = ctl->var_list;
	while (temp)
	{
		if (temp->type == EXPORT && temp->joined \
			&& ft_strchr(temp->joined, EQUALS))
		{
			printf("%s=", temp->key);
			if (temp->value)
				printf("%s", temp->value);
			printf("\n");
		}
		temp = temp->next;
	}
	estat_set(ctl->estat, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
