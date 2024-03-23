/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 10:39:29 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/03/21 10:10:39 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex_args	*arguments;
	int				output;
	int				command_index;
	int				command_status;

	arguments = (t_pipex_args *)assert_parse_arguments(argc, argv, env);
	command_index = 0;
	while (command_index < arguments->size)
	{
		command_status = run_process(arguments, command_index);
		if (command_status != 0)
			break ;
		command_index++;
	}
	output = open(arguments->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (output != -1 && arguments->stdin_content)
		file_write(arguments->stdin_content, output);
	cleanup(0, NULL);
	return (command_status);
}
