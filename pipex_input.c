/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:13:08 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/03/21 10:38:25 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_heredoc(t_pipex_args *arguments, int argc,
		char **argv, int *offset)
{
	arguments->heredoc = ft_strdup(argv[2]);
	arguments->input_file = NULL;
	arguments->size = argc - 4;
	*offset = 3;
}

static void	init_else(t_pipex_args *arguments, int argc,
		char **argv, int *offset)
{
	arguments->input_file = ft_strdup(argv[1]);
	arguments->size = argc - 3;
	*offset = 2;
}

static int	init_both(t_pipex_args *arguments, int argc,
		char **argv, int *offset)
{
	if (ft_strcmp("heredoc", argv[1]) == 0)
	{
		if (argc < 7)
			return (-1);
		init_heredoc(arguments, argc, argv, offset);
	}
	else
		init_else(arguments, argc, argv, offset);
	arguments->output_file = ft_strdup(argv[argc - 1]);
	arguments->commands = (char **)malloc(sizeof(char *) * arguments->size);
	return (0);
}

static int	init_args(t_pipex_args *arguments, int argc,
		char **argv, char **env)
{
	int	index;
	int	offset;

	if (argc < 5)
		return (-1);
	if (init_both(arguments, argc, argv, &offset) == -1)
		return (-1);
	index = offset;
	while (index < (arguments->size + offset))
	{
		arguments->commands[index - offset] = ft_strdup(argv[index]);
		index++;
	}
	arguments->stdin_content = NULL;
	arguments->env = env;
	arguments->paths = env_paths(env);
	return (0);
}

static t_pipex_args	*parse_arguments(int argc, char **argv, char **env)
{
	t_pipex_args	*arguments;
	char			*err_msg;
	int				stdin_fd;

	if (argc < 5)
		return (NULL);
	arguments = (t_pipex_args *)malloc(sizeof(t_pipex_args));
	if (arguments == NULL)
		return (NULL);
	if (init_args(arguments, argc, argv, env) == -1)
		return (NULL);
	stdin_fd = open(arguments->input_file, O_RDONLY);
	if (stdin_fd != -1)
	{
		arguments->stdin_content = file_read(stdin_fd);
		close(stdin_fd);
	}
	else
	{
		err_msg = ft_strjoin("pipex: ", argv[1]);
		perror(err_msg);
		free(err_msg);
	}
	return (arguments);
}

void	*assert_parse_arguments(int argc, char **argv, char **env)
{
	t_pipex_args	*arguments;

	arguments = parse_arguments(argc, argv, env);
	if (arguments == NULL)
	{
		error_msg("Unable to parse arguments", "");
		exit(EXIT_FAILURE);
	}
	return (arguments);
}
