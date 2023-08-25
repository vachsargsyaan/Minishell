/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacsargs <vacsargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:48:21 by vacsargs          #+#    #+#             */
/*   Updated: 2023/08/25 16:22:13 by vacsargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_init	parser;
	char	*str;

	parser = init(argc, argv, env);
	str = malloc(sizeof(char) * 1024);
	if (argc == 1 && argv)
	{
		printf_minishell();
		while (1)
		{
			str = readline("minishell$ ");
			if (!str)
				break ;
			lex(&parser, str);
		} 
	}
	return (0);
}
