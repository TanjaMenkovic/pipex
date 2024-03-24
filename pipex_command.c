/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 08:43:42 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/03/21 09:54:52 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	load_command(char **command_split, t_pipex_cmd *cmd)
{
	if (command_split[0])
		cmd->command = ft_strdup(command_split[0]);
	cmd->arguments = command_split;
}

int	execute_command(t_pipex_args *args, t_pipex_cmd *cmd)
{
	char	*local_exec;
	char	*paths_exec;

	local_exec = exec_exists(cmd->command, "");
	paths_exec = exec_in_paths(cmd->command, args->paths);
	if (!local_exec && !paths_exec)
		return (127);
	else
	{
		if (local_exec && execve(cmd->command, cmd->arguments, args->env) == -1)
		{
			error_msg("execve: ", local_exec);
			return (-1);
		}
		else if (paths_exec
			&& execve(paths_exec, cmd->arguments, args->env) == -1)
		{
			error_msg("execve: ", paths_exec);
			return (-1);
		}
		return (0);
	}
	return (1);
}

void	*parse_command(char *input)
{
	t_pipex_cmd	*command;
	char		**command_split;

	command = malloc(sizeof(t_pipex_cmd));
	if (command == NULL)
		return (NULL);
	command->error = NULL;
	command->command = NULL;
	command->arguments = NULL;
	command_split = ft_split_new(input);
	if (command_split == NULL)
	{
		command->error = ft_strdup("Unable to split command");
		if (command->error == NULL)
			return (NULL);
	}
	else
		load_command(command_split, command);
	return (command);
}
