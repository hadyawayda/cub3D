/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hawayda <hawayda@student.42beirut.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:12:51 by hawayda           #+#    #+#             */
/*   Updated: 2025/07/16 20:12:51 by hawayda          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <ctype.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

bool				ft_is_only_whitespace(char *s);

int					ft_putchar(char c);
int					ft_putstr(char *s);
int					ft_putnbr(int n);
int					ft_puthex(unsigned long nb, char format);
int					ft_putunbr(unsigned int nb);
int					ft_putptr(unsigned long long *ptr);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_atoi(const char *nptr);
int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_strcasecmp(char *s1, char *s2);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_lstsize(t_list *lst);
int					ft_isspace(int c);
int					ft_isdelimiter(char c);
int					ft_max(int a, int b);

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strdup(const char *s);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(const char *s, char c);
char				**ft_split_charset(char *str, char *charset);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_itoa(int n);
char				*ft_strndup(const char *s, size_t n);
char				*ft_strtok(char *str, const char *delim);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_substring(const char *src, int start, int end);

void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				*ft_calloc(size_t nmemb, size_t size);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_strcpy(char *dest, char *src);
void				ft_strcat(char *dest, char *source);
void				*ft_realloc(void *ptr, size_t size);

size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);

#endif
