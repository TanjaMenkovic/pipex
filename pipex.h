/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmenkovi <tmenkovi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:57:14 by tmenkovi          #+#    #+#             */
/*   Updated: 2024/03/21 10:30:16 by tmenkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdbool.h>

# define WRITE_PIPE 1
# define READ_PIPE 0
# define READ_BUFF 255
# define DEBUG 0

/* used for both bonus and 
 standard ./pipex input_file command1 command2 output_file */
typedef struct s_pipex_args
{
	char	*input_file;
	char	*output_file;
	char	*heredoc;
	char	**paths;
	char	**env;
	char	**commands;
	char	*stdin_content;
	int		size;
}	t_pipex_args;

typedef struct s_pipex_cmd
{
	char	*error;
	char	*command;
	char	**arguments;
}	t_pipex_cmd;

/* pipex_file.c */
char	*file_read(int source);
int		file_write(char *content, int fd);

/* pipex_input.c */
void	*assert_parse_arguments(int argc, char **argv, char **env);

/* pipex_command.c */
int		execute_command(t_pipex_args *args, t_pipex_cmd *cmd);
void	*parse_command(char *input);

/* pipex_process.c */
void	cleanup(int err, const char *msg);
int		run_process(t_pipex_args *arguments, int index);

/* pipex_error.c */
void	error_msg(char *c, char *str);

/* split_utils.c */
int		ft_numofstr(char *s);
char	*ft_word(const char *str, int start, int finish);
int		ft_checkmem(char **str, size_t num);

/* pipex_env.c */
char	**env_paths(char **env);
char	*exec_exists(char *cmd, char *cmd_path);
char	*exec_in_paths(char *cmd, char **paths);

/* ft_split_new.c */
char	**ft_split_new(char *s);

#endif
