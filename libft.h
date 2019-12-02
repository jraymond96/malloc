/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jraymond <jraymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 18:29:51 by jraymond          #+#    #+#             */
/*   Updated: 2019/12/02 19:28:37 by jraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>

typedef struct			s_list
{
	void				*content;
	size_t				content_size;
	struct s_list		*next;
}						t_list;

typedef struct			s_bis_list
{
	void				*data;
	struct s_bis_list	*next;
}						t_bis_list;

typedef struct			s_begin_list
{
	t_bis_list			*first_element;
}						t_b_list;

typedef struct			s_btree
{
	void				*ptrdata;
	size_t				data_size;
	struct s_btree		*parent;
	struct s_btree		*left;
	struct s_btree		*right;
}						t_btree;

t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstaddback(t_list **begin_lst, t_list *new);
void					ft_lstdelone(t_list **alst,
										void (*del)(void *, size_t));
void					ft_lstdel(t_list**alst, void(*del)(void*, size_t));
t_list					*ft_lstnew(void const *content, size_t content_size);
t_list					*ft_lstnewnocpy(void const *content);
t_list					*ft_lstrmelem(t_list *begin_lst, t_list *elem);
void					*ft_memset(void *s, int c, size_t n);
void					ft_bzero(void *s, size_t n);
char					**ft_memsplit(char *str, size_t size);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memccpy(void *dest, const void *src,
									int c, size_t n);
size_t					ft_strlen(const char *s);
size_t					ft_strclen(char *str, char c);
void					ft_putchar(char c);
void					ft_putstr(char const *str);
void					*ft_memmove(void *dest, const void *src, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_malloc(size_t size);
char					*ft_strdup(const char *s);
char					*ft_strcpy(char *dest, const char *src);
char					*ft_strncpy(char *dest, const char *src, size_t n);
char					*ft_strcat(char *dest, const char *src);
char					*ft_strncat(char *dest, const char *src, size_t n);
size_t					ft_strlcat(char *dest, const char *src, size_t size);
char					*ft_strchr(const char *s, int c);
char					*ft_strrchr(const char *s, int c);
char					*ft_strstr(const char *meule_de_foin,
									const char *aiguille);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
int						ft_atoi(const char *str);
int						ft_isalpha(int c);
int						ft_isdigit(int c);
int						ft_isalnum(int c);
int						ft_isascii(int c);
int						ft_isprint(int c);
int						ft_toupper(int c);
int						ft_tolower(int c);
void					*ft_memalloc(size_t size);
void					ft_memdel(void **ap);
char					*ft_memdup(char	*str, size_t len);
char					*ft_strnew(size_t size);
void					ft_strdel(char **as);
void					ft_strclr(char *s);
void					ft_striter(char *s, void (*f)(char *));
void					ft_striteri(char *s, void (*f)(unsigned int, char *));
char					*ft_strmap(char const *s, char (*f)(char));
char					*ft_strmapi(char const *s,
									char (*f)(unsigned int, char));
int						ft_strequ(char const *s1, char const *s2);
int						ft_strnequ(char const *s1, char const *s2, size_t n);
char					*ft_strsub(char const *s,
									unsigned int start, size_t len);
char					*ft_strjoin(char const *s1, char const *s2);
char					*ft_strtrim(char const *s);
char					**ft_strsplit(char const *s, char c);
char					*ft_itoa(int n);
void					ft_putendl(char const *s);
void					ft_putnbr(int n);
void					ft_putchar_fd(char c, int fd);
void					ft_putstr_fd(char const *s, int fd);
void					ft_putendl_fd(char const *s, int fd);
void					ft_putnbr_fd(int n, int fd);
char					*ft_strnstr(const char *s1, const char *s2, size_t n);
t_bis_list				*ft_creat_elem(void *data);
void					ft_list_push_front(t_b_list **begin_list, void *data);
void					ft_list_push_back(t_b_list *begin_list, void *data);
void					ft_list_clear(t_b_list **begin_list);
void					ft_list_print(t_b_list *begin_list);
char					*ft_strjoin_free(char const *s1, char const *s2, int i);
t_btree					*ft_btreeinser_ascii(t_btree *root, void *data,
						size_t size_data);
t_btree					*ft_btreeinser_int(t_btree *root, void *data,
						size_t size_data);
t_btree					*ft_newbtree(void const *data, size_t size_data);
void					ft_btreedel(t_btree **root, void (*btdel)(void *));
int						ft_ilen(int nb);
t_btree					*ft_btreeend(t_btree *root, int min_max);
t_list					*ft_lstrev(t_list *begin);
t_list					*ft_lst_sort(t_list *b_list, int (cmp)(t_list *));
void					ft_browsetree(t_btree *root, void (*dothings)(void *));
void					ft_revbrowsetree(t_btree *root,
											void (*dothings)(void *));
t_btree					*ft_btreeinser(t_btree *root, void *data,
							size_t size_data, int (comp)(void *, void *));
int						ft_get_opt(char **argv, int *flags, int (bin)(char *,
									int, int, int));
int						ft_btreelen(t_btree *root, int *i);
char					*ft_strmidjoin(char const *s1, char const *s2,
											char *middle);
int						get_next_line(const int fd, char **line);
void					ft_mem2join(char *dest, char *s1, char *s2,
											size_t size);

void					*ft_malloc(size_t size);
void					ft_free(void *ptr);
void					show_alloc_mem();

#endif
