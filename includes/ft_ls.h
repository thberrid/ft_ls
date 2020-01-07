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

# define FLAGS_ALLOWD "alrtR"

# define DEBUG_MODE 1

/*
** double list
*/

typedef struct			s_hlist
{
	struct s_dlist	*head;
	struct s_dlist	*tail;
	size_t			length;
	void			*content;
	size_t			content_size;
}						t_hlist;

typedef struct			s_dlist
{
	struct s_dlist	*prev;
	struct s_dlist	*next;
	void			*content;
	size_t			content_size;
}						t_dlist;

t_dlist					*dlist_create(void *content, size_t size);
void					dlist_init(t_dlist *lst, t_hlist *main);
void					dlist_push(t_dlist *lst, t_hlist *main);
void					dlist_unshift(t_dlist *lst, t_hlist *main);
void					dlist_foreach(t_hlist *main, void (*f)(t_dlist *));
int						dlist_map(t_hlist *dest, t_hlist *src, void *options,
							int (*f)(t_hlist*, t_dlist*, void *options));

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

/*
** struct dirent {
**    ino_t          d_ino;       inode number
**    off_t          d_off;       offset to the next dirent
**    unsigned short d_reclen;    length of this record
**    unsigned char  d_type;      type of file; not supported
**                                   by all file system types
**    char           d_name[256]; filename
** };
*/

typedef struct dirent	t_dirent;

/*
** options
*/

typedef struct			s_options
{
	t_hlist			*paths;
	unsigned int	flags_upper;
	unsigned int	flags_lower;
}						t_options;

typedef struct			s_path
{
	int				status;
	char			*name;
}						t_path;

int						options_set(int ac, char **av, t_options *options);
void					options_del(t_dlist *lst);

char					flags_set(int ac, char **av, t_options *options);

int						path_set(int ac, char **av, t_options *options);
void					path_print(t_dlist *lst);
char					*path_concat(char *path1, char *path2);

/*
** directories
*/

typedef struct			s_dirdata
{
	t_dirent	*dirent;
	t_stat		*dirstat;
	t_path		*path;
	DIR			*dir_content;
}						t_dirdata;

int						dirdata_set(t_hlist *dest, t_dlist *lst,
							t_options *options);
int						dirdata_print(t_hlist *dest, t_dlist *lst,
							t_options *options);
void					dirlist_del(t_dlist *lst);

int						ls_root(t_options *options, t_hlist *paths);

#endif
