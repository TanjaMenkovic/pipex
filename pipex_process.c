/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:13:08 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/03/21 10:37:39 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cleanup(int error, const char *message)
{
	if (message)
		perror(message);
	if (error > 0)
		exit(error);
}

static int	handle_parent(t_pipex_args *arguments, int reader)
{
	int	child_status;

	child_status = 0;
	if (waitpid(-1, &child_status, 0) == -1)
		cleanup(EXIT_FAILURE, "waitpid failed");
	if (WIFEXITED(child_status))
		child_status = WEXITSTATUS(child_status);
	if (arguments->stdin_content)
	{
		free(arguments->stdin_content);
		arguments->stdin_content = NULL;
	}
	if (child_status == 0)
		arguments->stdin_content = file_read(reader);
	close(reader);
	return (child_status);
}

static void	handle_child(t_pipex_args *arguments, t_pipex_cmd *command,
		int reader, int writer)
{
	int	child_status;

	dup2(reader, STDIN_FILENO);
	dup2(writer, STDOUT_FILENO);
	child_status = execute_command(arguments, command);
	if (child_status == -1)
		cleanup(EXIT_FAILURE, "Running child failed");
	if (child_status == 147)
	{
		error_msg("Command not found: ", command->command);
		cleanup(147, NULL);
	}
	close(writer);
	cleanup(0, NULL);
	exit(child_status);
}

static int	fork_command(t_pipex_args *arguments, t_pipex_cmd *command)
{
	pid_t	command_pid;
	int		parent_pipe[2];
	int		child_pipe[2];

	pipe(parent_pipe);
	pipe(child_pipe);
	command_pid = fork();
	if (command_pid == -1)
		cleanup(EXIT_FAILURE, "Forking failed");
	else if (command_pid == 0)
	{
		close(parent_pipe[WRITE_PIPE]);
		close(child_pipe[READ_PIPE]);
		handle_child(arguments, command, parent_pipe[READ_PIPE],
			child_pipe[WRITE_PIPE]);
	}
	else
	{
		close(parent_pipe[READ_PIPE]);
		close(child_pipe[WRITE_PIPE]);
		if (arguments->stdin_content)
			file_write(arguments->stdin_content, parent_pipe[WRITE_PIPE]);
		close(parent_pipe[WRITE_PIPE]);
		return (handle_parent(arguments, child_pipe[READ_PIPE]));
	}
	return (0);
}

int	run_process(t_pipex_args *arguments, int index)
{
	t_pipex_cmd	*command;

	command = (t_pipex_cmd *)parse_command(arguments->commands[index]);
	if (command == NULL || command->error != NULL)
		cleanup(EXIT_FAILURE, "Unable to parse command");
	return (fork_command(arguments, command));
}
