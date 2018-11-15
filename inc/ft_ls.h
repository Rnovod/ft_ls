/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnovodra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 19:47:16 by rnovodra          #+#    #+#             */
/*   Updated: 2018/09/24 19:47:17 by rnovodra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libft.h"
# include "ft_printf.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <pwd.h>
# include <errno.h>
# include <sys/acl.h>
# include <stdbool.h>
# include <sys/ioctl.h>

# define SIXMONTHS ((365 / 2) * 86400)

typedef	enum			e_filetype
{
	unknown,
	fifo,
	chardev,
	normal,
	blockdev,
	symbolic_link,
	sock,
	directory,
	arg_directory
}						t_filetype;

typedef struct			s_file
{
	char			*name;
	char			*realname;
	struct stat		stat;
	char			*linkname;
	t_filetype		filetype;
}						t_file;

typedef struct			s_pend
{
	char			*name;
	char			*realname;
	bool			command_arg;
	struct s_pend	*next;
}						t_pend;

enum					e_timetype
{
	time_mtime,
	time_ctime,
	time_btime,
	time_atime
};

enum e_timetype			time_type;

typedef struct s_data	t_data;

typedef	void			(t_printfunc)(t_data*, t_file **);
typedef	int				(t_sortfunc)(const t_file *, const t_file *);

struct					s_data
{
	t_file		**sorted_files;
	int			sorted_alloc;
	t_file		*files;
	int			files_alloc;
	int			files_used;
	t_pend		*queue_dir;
	int			inode_w;
	int			nlink_w;
	int			owner_w;
	int			group_w;
	int			major_w;
	int			minor_w;
	int			file_size_w;
	int			blksize_w;
	int			ino_w;
	bool		immediate_dirs;
	bool		dot_files;
	bool		reverse;
	bool		print_dir_name;
	bool		print_inode;
	bool		print_block_size;
	bool		recursive;
	bool		print_owner;
	bool		print_group;
	bool		type;
	bool		color;
	bool		link_follow;
	bool		slash;
	bool		sectime;
	bool		colacross;
	bool		longform;
	bool		singlecol;
	bool		commas;
	bool		sort_size;
	bool		sort_time;
	bool		nonsort;
	int			termwidth;
	int			notabs;
	t_sortfunc	*sfunc;
	t_printfunc	*pfunc;
};

void					reinit_data(t_data *d);

uintmax_t				manage_file(t_data *d, const char *name,
						const char *dirname, bool command_arg);
void					queue_dir(t_data *d, const char *name,
						const char *realname, bool command_arg);
void					extract_dirs_from_files(t_data *d, const char *dirname,
						bool command_arg);
int						manage_options(t_data *d, char **av);
void					print_current_files(t_data *d);
void					print_all_dir(t_data *d);

void					attach(char *dest, const char *dirname,
						const char *name);

void					mode(mode_t st_mode);

void					sort_files(t_data *d, t_sortfunc *func);

int						sort_by_size(const t_file *restrict f1,
						const t_file *restrict f2);
int						sort_by_time(const t_file *restrict f1,
						const t_file *restrict f2);
int						sort_by_ascii(const t_file *restrict f1,
						const t_file *restrict f2);

int						rev_sort_by_size(const t_file *restrict f1,
						const t_file *restrict f2);
int						rev_sort_by_time(const t_file *restrict f1,
						const t_file *restrict f2);
int						rev_sort_by_ascii(const t_file *restrict f1,
						const t_file *restrict f2);

void					print_longform(t_data *d, t_file **sorted_files);
void					print_singlecol(t_data *d, t_file **sorted_files);
void					print_cols(t_data *d, t_file **sorted_files);
void					print_commas(t_data *d, t_file **sorted_files);

int						printtype(bool slash, u_int mode);
int						printname(t_data *d, t_file *f);
int						set_color(t_filetype filetype, u_int mode);

void					realloc_files(t_data *d);
void					clear_files(t_data *d);
void					free_files(t_data *d);
void					error(t_data *d);

#endif
