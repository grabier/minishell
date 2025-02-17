/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 11:41:54 by gmontoro          #+#    #+#             */
/*   Updated: 2025/02/17 14:43:20 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEO_H
# define PARSEO_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# define WORD 0
# define QS 1
# define QD 2
# define PI 3
# define R1 4
# define R2 5
# define L1 6
# define L2 7

typedef struct s_tkn
{
	char	*token;
	int		type;
	struct	s_tkn	*next;
}			t_tkn;

typedef struct s_cmd
{
	char	**args;
	char	*infile;
	char	*outfile;
	int		append;
	int		hd;
	int		is_cmd;
	int		is_bi;
	struct	s_cmd	*next;
}			t_cmd;

//parseo.c
int		ft_get_input(char *envp[]);
void	ft_free_parse(char *input, t_tkn **t, t_cmd **c, char *prompt);

//expand_quotes.c
int		ft_check_quotes(char *input);
char	*ft_expand(char *input, int start);
char	*ft_check_expands(char *input);
char	*ft_do_quotes(char *input);
void	ft_quotes(t_tkn **tkn);

//delete_quotes.c
char	*ft_delete_squotes(char *input);
char	*ft_delete_dquotes(char *input);
int		ft_count_quotes(char *input, int mode);

//aux
char	*ft_strinsert(char *str, char *word, int start, int end);
void	ft_printsplit(char **sp);
int		ft_strcmp(char *s1, char *s2);

//token_list.c
void	ft_tknadd_back(t_tkn **lst, t_tkn *new);
void	ft_tknadd_front(t_tkn **lst, t_tkn *new);
t_tkn	*ft_tknnew(char *content, int type);
void	ft_tknprint(t_tkn *lst);
int		ft_tknsize(t_tkn *lst);

//tokenize.c
t_tkn	*ft_tokenize(char *input);
int		ft_check_syntax(t_tkn *tokens);
int		ft_find_end_word(char *input);

//tokenize_functions.c
t_tkn	*ft_quote_tkn(t_tkn **tkn_lst, char *input, int *i);
t_tkn	*ft_redir_tkn(t_tkn **tkn_lst, char *input, int *i);
t_tkn	*ft_pipe_tkn(t_tkn **tkn_lst, char *input, int *i);
t_tkn	*ft_word_tkn(t_tkn **tkn_lst, char *input, int *i);

//tokenize_aux.c
void	ft_free_tkn_lst(t_tkn **tkn);
int		ft_find_end_dq(char *input);
int		ft_find_end_sq(char *input);

//command_lst.c
int		ft_count_args(t_tkn	*tkn);
t_cmd	*ft_get_commands(t_tkn *tkn);
int		ft_isbuiltin(char *str);
t_cmd	*ft_cmdnew();

//command_lst2.c
void	ft_cmdprint(t_cmd *lst);
void	ft_cmdadd_back(t_cmd **lst, t_cmd *new);
void	ft_cmdadd_front(t_cmd **lst, t_cmd *new);
int		ft_cmdsize(t_cmd *lst);
void	ft_free_cmd_lst(t_cmd **cmd);

//command_types.c
void	ft_add_cmd(t_tkn **tkn, t_cmd **cmd_lst);
void	ft_add_infile(t_tkn **tkn, t_cmd **cmd_lst);
void	ft_add_outfile(t_tkn **tkn, t_cmd **cmd_lst);
void	ft_add_append(t_tkn **tkn, t_cmd **cmd_lst);
void	ft_add_here_doc(t_tkn **tkn, t_cmd **cmd_lst);

//search_path.c
char	*ft_strcat_cmd(char *s1, char *s2);
char	*ft_find_cmd(char *cmd, char *path);
char	*aux_find_path(char *cmd, char *envp[], char *res, int i);
char	*ft_find_path(char *cmd, char *envp[]);

//execute.c
void	ft_exec_commands(t_cmd *cmd_lst, char **envp[]);
int		ft_execute_cmd(t_cmd *cmd, char **envp[]);

//ex_single_cmd.c
void	ft_exec_single_cmd(t_cmd *cmd, char **envp[]);
int		ft_open_n_redir(t_cmd *cmd, int mode);

//exec_pipeline.c
void	ft_exec_pipeline(t_cmd *cmd, char **envp[]);
int		ft_exec_middle_cmd(t_cmd *cmd, char **envp[], int i_fd, int o_fd);
int		ft_exec_last_cmd(t_cmd *cmd, char **envp[]);

//built-ins.c
void	ft_exec_built_in(t_cmd *cmd, char **envp[]);

//builtin-env.c
char	**ft_unset(char **env_copy, char *str);
char	*ft_get_var_name(char *var);
char	**ft_insert_change(char **env, char *insert, int *changed);
char	**ft_insert_dp(char **env, char *insert);

//builtin-exit.c
int		ft_is_num(char *str);
void	ft_exit(char **args);

//builtin-env-cpy.c
int		ft_strlen_pointers(char *env[]);
char	**ft_copy_dp(char **env);
void	print_env(char **env_copy);
void	print_env_export(char **env_copy);

//here_doc.c
int		ft_here_doc(char *limit);

//get_prompt.c
char	*ft_get_prompt(char **env);
#endif