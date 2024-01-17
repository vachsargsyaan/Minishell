/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 17:05:50 by vacsargs          #+#    #+#             */
/*   Updated: 2024/01/10 15:17:52 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_file(char *path, t_wcard **wcard)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	if (!dir)
	{
		perror("opendir");
		return ;
	}
	while (1)
	{
		entry = readdir(dir);
		if (!entry)
			break ;
		if (ft_strchr(path, '.') || entry->d_name[0] != '.')
			if (wcard_logic(path, entry->d_name))
				lstback_wcard(wcard, lstadd_wcard(entry->d_name));
	}
	closedir(dir);
}

void	fill_wc_matrix(t_parser *stack, t_wcard **wild)
{
	t_parser	*tmp;

	tmp = stack;
	while (tmp)
	{
		if (tmp->tayp == DQUOTE || tmp->tayp == SQUOTE)
			tmp = tmp->next;
		else if (ft_strchr(tmp->cmd, '*'))
		{
			get_file(tmp->cmd, wild);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}

char	**alloc_wc_matrix(char **matrix, t_parser *stack, t_wcard **wcard)
{
	int			i;

	i = 0;
	fill_wc_matrix(stack, wcard);
	if (*wcard)
		matrix = (char **)malloc(sizeof(char *) * \
		(lstsize(stack) + lstsize_wcard(*wcard)));
	else
		matrix = (char **)malloc(sizeof(char *) * (lstsize(stack) + 1));
	if (!matrix)
		return (NULL);
	if (*wcard)
		while (i < lstsize(stack) + lstsize_wcard(*wcard) - 1)
			matrix[i++] = NULL;
	else
		while (i < lstsize(stack))
			matrix[i++] = NULL;
	matrix[i] = NULL;
	return (matrix);
}

char	**alloc_cmd_matrix(char **matrix, char *cmd, t_wcard *wild, int *i)
{
	t_wcard	*temp;

	temp = wild;
	if (temp && ft_strchr(cmd, '*'))
	{
		while (temp)
		{
			*i += 1;
			matrix[*i] = ft_strdup(temp->file);
			temp = temp->next;
		}
	}
	else
	{
		*i += 1;
		matrix[*i] = ft_strdup(cmd);
	}
	return (matrix);
}

char	**restore_cmd_line(t_parser *stack, int i)
{
	char		**cmd_matrix;
	int			mode;
	t_parser	*ptr;
	t_wcard		*wcard;

	ptr = stack;
	wcard = (void *)((cmd_matrix = NULL));
	cmd_matrix = alloc_wc_matrix(cmd_matrix, stack, &wcard);
	if (!cmd_matrix)
		return (NULL);
	while (ptr && ptr->cmd)
	{
		mode = (ptr->flag & (_ISCMD_));
		if (mode == 0 && check_tayp(ptr->tayp) == 0)
		{
			if (i < 0)
				i++;
			cmd_matrix[i] = ft_strjoin(cmd_matrix[i], ptr->cmd, 1);
		}
		else
			cmd_matrix = alloc_cmd_matrix(cmd_matrix, ptr->cmd, wcard, &i);
		ptr = ptr->next;
	}
	lstclear_wcard(&wcard);
	return (cmd_matrix);
}
