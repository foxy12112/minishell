/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldick <ldick@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 10:58:18 by ldick             #+#    #+#             */
/*   Updated: 2024/06/19 10:14:46 by ldick            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @brief checks if character is alphabetical
 * 
 * @param[in] c - the character to check
 * @return 1 if the test is true
 * @return 0 if the test is false
*/
int					ft_isalpha(int c);

char				*ft_strcat(char *dst, char *src);

int					ft_wordcount(char *str, int delimiter);

/**
 * @brief checks if character is a number
 * 
 * @param[in] c - the character to check
 * @return 1 if the test is true
 * @return 0 if the test is false
*/
int					ft_isdigit(int c);

/**
 * @brief checks if character is alphanumerical
 * 
 * @param[in] c - the character to check
 * @return 1 if the test is true
 * @return 0 if the test is false
*/
int					ft_isalnum(int c);

/**
 * @brief checks if character is a valid ascii character
 * 
 * @note ascii characters are between 0 and 127
 * 
 * @param[in] c - the character to check
 * @return 1 if the test is true
 * @return 0 if the test is false
*/
int					ft_isascii(int c);

/**
 * @brief checks if character is printable
 * 
 * @param[in] c - the character to check
 * @return 1 if the test is true
 * @return 0 if the test is false
*/
int					ft_isprint(int c);

/**
 * @brief turns a lowercase character into an uppercase character
 * @note only works if the character is lowercase
 * 
 * @param[in] c - the character to turn
 * @return lowercase->uppercase input character
 * @return nothing if its not a lowercase character
*/
int					ft_toupper(int c);

/**
 * @brief turns a uppercase character into an lowercase character
 * @note only works if the character is uppercase
 * 
 * @param[in] c - the character to turn
 * @return uppercase->lowercase input character
 * @return nothing if its not a uppercase character
*/
int					ft_tolower(int c);

/**
 * @brief this function take a character string and turns it into an integer
 * @brief it skips all whitespaces at the beginning of a string
 * @note only works if the character is lowercase
 * 
 * @param[in] str - the character string
 * @return str as an integer
*/
int					ft_atoi(const char *str);

/**
 * @brief this function take a character string and turns it into an double
 * 
 * @param[in] s - the  string
 * @return s as a double
*/
double				atodbl(char *s);

/**
 * @brief compares the ascii value between two strings
 * @note only compares until a difference is found or until n
 * 
 * @param[in] s1 - string to compare
 * @param[in] s2 - string to compare to
 * @param[in] n - how much of the string to compare
 * @return the ascii difference between the two strings
*/
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief compares the ascii value between two strings
 * @note only compares until a difference is found
 * 
 * @param[in] s1 - string to compare
 * @param[in] s2 - string to compare to
 * @return the ascii difference between the two strings
*/
int					ft_strcmp(const char *s1, const char *s2);

/**
 * @brief compares the ascii value between two strings
 * @note only compares until a difference is found or until n
 * 
 * @param[in] s1 - memory area to compare
 * @param[in] s2 - memory area to compare to
 * @param[in] n - how much of to compare
 * @return the ascii difference between the two memory areas
*/
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief counts the number in nodes in a list
 * 
 * @param[in] lst - the beginning of the list
 * @return the lenght of the list
*/
int					ft_lstsize(t_list *lst);

/**
 * @brief counts the lenght of a string but skips a letter
 * @note skips the letter you input as int c
 * 
 * @param[in] str - the string to count
 * @param[in] c - a character to skip over while counting
 * @return the lenght of the string
*/
size_t				ft_strlen_s(char *str, int c);

/**
 * @brief counts the lenght of a string
 * 
 * @param[in] s - the string to count
 * @return the lenght of the string
*/
size_t				ft_strlen(const char *s);

/**
 * @brief appends a string src to dst
 * @note appends at most dstsize characters
 * 
 * @param[in] dst - the string to append src to
 * @param[in] src - the string to append
 * @param[in] dstsize - how many characters to append
 * @return the lenght of src + dst
*/
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);

/**
 * @brief copies up to dstsize characters from src to dst
 * 
 * @param[in] dst - the destination you want to copy src to
 * @param[in] src - the string to copy
 * @param[in] dstsize - how many characters to copy
 * @return the lenght of src
*/
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);

/**
 * @brief allocates enough memory for count objects 
 * that are size big and sets the allocated memory to zero
 * 
 * @param[in] count - the amount of objects
 * @param[in] size - the size of each count object
 * @return a pointer to the zeroed memory
*/
void				*ft_calloc(size_t count, size_t size);

/**
 * @brief writes n zeroed bytes into s
 * 
 * @param[in] s - the string to zero
 * @param[in] n - how many zeroes to write
*/
void				ft_bzero(void *s, size_t n);

/**
 * @brief writes len bytes of c to the string b
 * 
 * @param[in] b - the string to write into
 * @param[in] c - value converted into unsigned char
 * @param[in] len - the amount of times to write c
*/
void				*ft_memset(void *b, int c, size_t len);

/**
 * @brief locates the first occurance of c 
 * 
 * @param[in] s - the string to search
 * @param[in] c - the character to find
 * @param[in] n - how many bytes to search
 * @return a pointer to the byte located or
 * @return NULL if it hasnt been found within n bytes
*/
void				*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief copies n bytes from memory src to memory dst
 * 
 * @param[in] dst - the memory area to copy to
 * @param[in] src - the memory area to copy from
 * @param[in] n - how many bytes to copy
 * @return returns the original value of dst
*/
void				*ft_memcpy(void *dst, const void *src, size_t n);

/**
 * @brief copies len bytes from src to dst
 * @note if the two strings overlap the copy is done in a non-destructive manner
 * 
 * @param[in] src - the string to copy from
 * @param[in] dst - the string to copy to
 * @param[in] len - how many bytes to copy
*/
void				*ft_memmove(void *dst, const void *src, size_t len);

/**
 * @brief writes the int n to the file desriptor fd
 * 
 * @param[in] n - the integer to write
 * @param[in] fd - the file descriptor on which to write
*/
void				ft_putnbr_fd(int n, int fd);

/**
 * @brief writes the char c to the file desriptor fd
 * 
 * @param[in] c - the character to write
 * @param[in] fd - the file descriptor on which to write
*/
void				ft_putchar_fd(char c, int fd);

long				ft_atol(const char *str);

/**
 * @brief writes the string s to the file desriptor fd followed by a newline
 * 
 * @param[in] s - the string to write
 * @param[in] fd - the file descriptor on which to write
*/
void				ft_putendl_fd(char *s, int fd);

/**
 * @brief writes the string s to the file desriptor fd
 * 
 * @param[in] s - the string to write
 * @param[in] fd - the file descriptor on which to write
*/
void				ft_putstr_fd(char *s, int fd);

/**
 * @brief applies the function f on each character of the string s
 * @note passes its index as first argument 
 * 
 * @param[in] f - the function to apply
 * @param[in] s - the string to apply f to
*/
void				ft_striteri(char *s, void (*f)(unsigned int, char*));

/**
 * @brief adds the node new at the beginning of the list
 * 
 * @param[in] lst - a pointer to the first link of a list
 * @param[in] new - a pointer to the node to add
*/
void				ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief adds the node new at the end of the list
 * 
 * @param[in] lst - a pointer to the first link of a list
 * @param[in] new - ta pointer to the node to add
*/
void				ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief takes a node and frees the memory
 *  of the ndoes content using the function del
 * 
 * @param[in] del - the node of the function used to delete the content
 * @param[in] lst - the node to free
*/
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief deletes and frees the given node 
 * and every successo of that node using the function del and free
 * @note the pointer to the list is set to NULL
 * 
 * @param[in] lst - the address of a pointer to a node
 * @param[in] del - the address of the function 
 * used to delete the content of the node
*/
void				ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief iterates the list lst and applies
 *  the function f on the content of each node
 * 
 * @param[in] lst - the address of a pointer to a node
 * @param[in] f - the adress of a function used to iterate on the list
*/
void				ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief locates the first occurance of c in the string s
 * 
 * @param[in] s - the string to search
 * @param[in] c - the character to find
 * @return a pointer to the located character or
 * @return NULL if c is not found
*/
char				*ft_strchr(const char *s, int c);

/**
 * @brief allocates memory to copy the 
 * string s1, makes the copy and returns a pointer to it
 * 
 * @param[in] s1 - the string to copy
 * @return the copied string
*/
char				*ft_strdup(const char *s1);

/**
 * @brief locates the last occurance of c in the string s 
 * 
 * @param[in] s - the string to search
 * @param[in] c - the character to find
 * @return a pointer to the located character
*/
char				*ft_strrchr(const char *s, int c);

/**
 * @brief locates the first occurance 
 * of the null terminated string needle in the string haystack
 * 
 * @param[in] needle - the string to find
 * @param[in] haystack - the string to search
 * @return a pointer to the first occurance of needle
*/
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);

/**
 * @brief allocates and returns a substring from string s
 * @note the substring begins at index start and is of maximum size len
 * 
 * @param[in] s - the string from which to create the substring
 * @param[in] start - start index of the substring
 * @param[in] len - the maximum size of the substring
 * @return the substring
*/
char				*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief concates the string s1 and s2
 * 
 * @param[in] s1 - the prefix string
 * @param[in] s2 - the suffix string
 * @return the concated string
*/
char				*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief itterates through the string s 
 * and applies the funciton f on each character
 * 
 * @param[in] s - the string to which to apply the functinos to
 * @param[in] f - the function to apply
 * @return the string created from the succesive applicaiton of f
*/
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief removes set from the beginnign and end of the string
 * 
 * @param[in] s1 - the string to be trimmed
 * @param[in] set - the refference set of characters to trim
 * @return the trimmed string
*/
char				*ft_strtrim(char const *s1, char const *set);

/**
 * @brief turns an integer into a character string
 * 
 * @param[in] n - the integer to convert
 * @return the string representing the int n
*/
char				*ft_itoa(int n);

/**
 * @brief splits the string s at each point of the delimiter c
 * 
 * @param[in] s - the string to split
 * @param[in] c - the delimiter
 * @return an array of strings slpit up at the point of the delimiter c
*/
char				**ft_split(char *s, char c);

/**
 * @brief creates a new node using the variable content
 * 
 * @param[in] content - the content to create the note with
 * @return the new node
*/
t_list				*ft_lstnew(void *content);

/**
 * @brief returns the last node of the list
 * 
 * @param[in] lst - the beginning of the list
 * @return the last node of the list
*/
t_list				*ft_lstlast(t_list *lst);

/**
 * @brief iterates the list lst and applies
 *  the function
 *  f on the content of each node, creates
 *  a new list 
 * resulting of the successice application 
 * of the function f
 * @note del us ysed ti dekete the content 
 * of a node if needed
 * 
 * @param[in] lst - the address of a pointer to a node
 * @param[in] f -  the address of the function used to iterate on the list
 * @param[in] del - the address of the funciton
 *  used to delete the content of a node if needed
 * @return the new list
*/
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void(*del)(void *));

#endif