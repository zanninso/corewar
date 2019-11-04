/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aait-ihi <aait-ihi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 13:24:59 by souarrak          #+#    #+#             */
/*   Updated: 2019/10/31 01:08:35 by aait-ihi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include "get_next_line.h"
# include "bigint/bigint.h"
# define ABS(Value) (Value > 0 ? Value : -(Value))
# define INFINITY 10. / 0.
# define TRUE 1
# define FALSE 0

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_double_sem
{
	u_int64_t	mantissa:63;
	u_int64_t	p:1;
	u_int64_t	exp:15;
	u_int64_t	sign:1;
}					t_s_double_sem;

typedef union		u_double_sem
{
	t_s_double_sem	s;
	long double		d;

}					t_double_sem;

void				ft_putchar(char c);
void				ft_putstr(const char *str);
void				*ft_memset(void *b, int c, size_t len);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char*s1);
char				*ft_strcpy(char *dst, const char *src);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *hstk, const char *nd, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				*ft_memalloc(size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t size);
void				ft_lstdelone(t_list **alst, void (*del)(void*, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void*, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
void				ft_strdel(char **as);
int					ft_iswhitespace(char c);
int					ft_isln(const char *str, int size);
char				*ft_strinv(char *str);
char				*ft_realloc(char *ptr, size_t size);
int					ft_count_words(char const *str, char c);
char				*ft_strndup(const char *s1, size_t n);
int					ft_nblen(long n);
int					ft_max(int a, int b);
int					ft_isnbr(char *str);
int					ft_isinstr(char c, const char *s);
int					ft_atoi(const char *str);
long				ft_atol(const char *str);
char				*ft_itoa(long long n);
char				*ft_uitoa(unsigned long long n);
char				*ft_itoa_base(long long n, int base);
char				*ft_uitoa_base(unsigned long long n, int base);
long long			ft_pow(long long n, int p);
char				*ft_strtoupper(char *str);
char				*ft_ldtoa (long double n, int precs);
char				*special_case(t_double_sem sem, int precs);
bool				ft_find_int(int *t, int n, size_t size, size_t *index);
u_int64_t			ft_reverse_bits(u_int64_t nb, int n);
#endif
