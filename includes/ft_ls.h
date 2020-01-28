/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 11:03:19 by thberrid          #+#    #+#             */
/*   Updated: 2020/01/05 11:04:24 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <libft.h>
# include <dirent.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/errno.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <limits.h>
# include <sys/xattr.h>

# define DEBUG_MODE 0
# define LEAKS_MODE 0
# define DEBUG_BLUE "\e[94m"
# define DEBUG_GREY "\e[90m"
# define DEBUG_CLEAR "\e[0m"
# define DEBUG_TAG "\n--- debug ---\n\n"

/*
** a: show hidden files .*
** l: long and boring format
** r: reverse sort
** t: sort by time modified (recent first) then lexichoraphic
** R: Recursive
**
**	long format:
**		file type, permissions 
**			{cdb-lsp?}{-rwx} usr, grp, other
**				c character special
**				b block
**				d directory
**				- regular file
**				l symbolic link
**				s socket
**				p fifo
**				? other file type
**		nbr of links
** 		owner name
**		group name
**		file size
**		time last modif
**		file name
*/

# define FLAGS_ALLOWD 	"alrtR"
# define FLAGS_LOWER	0
# define FLAGS_UPPER	1
# define FLAG_A			0
# define FLAG_L			11
# define FLAG_R			17
# define FLAG_T			19

/*
** struct stat {
**    dev_t     st_dev;      ID of device containing file
**    ino_t     st_ino;      inode number
**    mode_t    st_mode;     protection
**    nlink_t   st_nlink;    number of hard links
**    uid_t     st_uid;      user ID of owner
**    gid_t     st_gid;      group ID of owner
**    dev_t     st_rdev;     device ID (if special file)
**    off_t     st_size;     total size, in bytes
**    blksize_t st_blksize;  blocksize for file system I/O
**    blkcnt_t  st_blocks;   number of 512B blocks allocated
**    time_t    st_atime;    time of last access
**    time_t    st_mtime;    time of last modification
**    time_t    st_ctime;    time of last status change
** };
*/

typedef struct stat		t_stat;
typedef struct timespec	t_timespec;

/*
** struct dirent {
**    ino_t          d_ino;       		inode number
**    off_t          d_off;       		offset to the next dirent
**    unsigned short d_reclen;    		length of this record
**    unsigned char  d_type;      		type of file; not supported
**                                   		by all file system types
**    char           d_name[255 + 1];	filename
** };
*/

typedef struct dirent	t_dirent;

/*
** struct passwd {
**     char   *pw_name;       username
**     char   *pw_passwd;     user password
**     uid_t   pw_uid;        user ID
**     gid_t   pw_gid;        group ID
**     char   *pw_gecos;      user information
**     char   *pw_dir;        home directory
**     char   *pw_shell;      shell program
** };
*/

typedef struct passwd	t_passwd;

/*
** struct group {
**     char   *gr_name;       group name
**     char   *gr_passwd;     group password
**     gid_t   gr_gid;        group ID
**     char  **gr_mem;        group members
** };
*/

typedef struct group	t_group;

typedef struct			s_hlist
{
	struct s_dlist	*head;
	struct s_dlist	*tail;
	size_t			length;
	void			*content;
	size_t			content_size;
}						t_hlist;

typedef struct			s_hcontent
{
	size_t			total;
}						t_hcontent;

typedef struct			s_dlist
{
	struct s_dlist	*prev;
	struct s_dlist	*next;
	void			*content;
	t_hlist			*subfiles;
	size_t			content_size;
}						t_dlist;

typedef struct			s_filedata
{
	t_dirent	*dirent;
	t_stat		*stat;
	t_stat		*lstat;
	char		*path;
	DIR			*dir;
}						t_filedata;

typedef struct			s_options
{
	t_hlist			*operands;
	t_hlist			*operands_invalid;
	unsigned int	flags_upper;
	unsigned int	flags_lower;
	int				(*sort_f)(t_dlist *, t_dlist *);
}						t_options;

typedef struct		s_flags_sort
{
	int		flag;
	int		upper_or_lower;
	int		(*sort_f)(t_dlist *, t_dlist *);
}					t_flags_sort;

# define USR	0
# define GRP	3
# define OTHR	6

# define TIME_Y				20
# define TIME_Y_LEN			4
# define TIME_6_MONTHS		15768000
# define TIME_HM			11
# define TIME_HM_LEN		5

typedef struct			s_types
{
	char			symbol;
	unsigned int	mask;
}						t_types;

int						core_loop(t_hlist *files, t_options *options);

/*
** generic list functions
*/

t_dlist					*dlist_create(void *content, size_t size);
void					dlist_init(t_dlist *lst, t_hlist *main);
void					dlist_push(t_dlist *lst, t_hlist *main);
void					dlist_unshift(t_dlist *lst, t_hlist *main);
void					dlist_foreach(t_hlist *main, void (*f)(t_dlist *));

t_dlist					*dlist_head_or_tail(t_hlist *files, t_options *options);
t_dlist					*dlist_next_or_prev(t_dlist *file, t_options *options);
int						dlist_filter(t_hlist *files, t_options *options,
							int (*cond)(t_hlist *handler, t_dlist *, t_options *), 
							int (*f)(t_dlist *, t_options *));
int						dlist_map(t_hlist *dest, t_hlist *src, void *options,
							int (*f)(t_hlist*, t_dlist*, void *options));
void					dlist_insert_before(t_dlist *new_elemnt, t_dlist *ref,
							t_hlist *operands);
t_dlist					*dlist_search(t_dlist *new_elemnt, t_hlist *main,
							int (*f)(t_dlist *, t_dlist *));

/*
** handlers management functions
*/

t_hlist					*handler_create(t_hlist **handler);
void					handler_update(t_hlist *handler, t_dlist *new_elemnt);

/*
** options settings
*/

int						options_set(int ac, char **av, t_options *options);
void					options_set_sort(t_options *options);
void					options_del(t_options *options);
int						operands_set(int ac, char **av, t_options *options);

char					flags_set(int ac, char **av, t_options *options);
int						flag_is_on(unsigned int flags_available, unsigned int flag_code);

/*
** filtering condition options
*/

int						link_is_open(t_dlist *file, t_options *options);
int						file_is_dir(t_stat *filestat);
int						file_is_first_elemnt(t_dlist *elemnt, t_options *options);
int						file_is_last_elemnt(t_dlist *elemnt, t_options *options);
int						file_is_hidden(t_dlist *file);
int						file_exists(char *name);
int						file_is_single(t_dlist *elemnt);
int						filter_recursion_file(t_hlist *handler, t_dlist *file, t_options *options);
int						filter_recursion_dir(t_hlist *handler, t_dlist *file, t_options *options);
int						sort_path_ascii(t_dlist *l1, t_dlist *l2);
int						sort_last_mtime(t_dlist *l1, t_dlist *l2);

/*
** path management functions
*/

int						path_add(char *name, t_hlist *operands, t_options *options);
void					path_print(t_dlist *lst);
void					pathroot_print(t_dlist *this);
char					*path_concat(char *path1, char *path2);

/*
** file, directories
*/

void					filedata_del_this(t_dlist *lst);

int						filedata_print_this(t_dlist *this, t_options *options);
int						filedata_open_this(t_dlist *this, t_options *options);
int						filedata_readdir(DIR *dir_open, t_hlist *dest, t_dlist *root_file, t_options *options);
int						filedata_set_stat(t_filedata *filedata, t_dirent *dirent, char *root_path);

size_t					filedata_get_total(t_dlist *this);

/*
** messages, errors
*/

void					file_openfail_print(t_filedata *filedata);
void					file_unexistent_print(t_dlist *lst);
void					file_print_name(t_dlist *elemnt, t_options *options);
void					print_usage_and_quit(char invalid_char);

int						format_long_print(t_dlist *elemnt, t_options *options);
void					total_print(t_hlist *handler, t_options *options);
void					file_type_permission_print_all(t_filedata *filedata);
void					file_type_print(t_stat *filestat);
void					file_type_permission_print(t_stat *filestat, int level);
void					file_nbrlinks_print(t_stat *filestat);
void					file_ownername_print(t_stat *filestat);
void					file_groupname_print(t_stat *filestat);
void					file_size_print(t_stat *filestat);
int						file_date_print(t_stat *filestat);
int						file_print_link(t_dlist *elemnt);
void					file_extend_attr_print(t_filedata *filedata);

#endif
