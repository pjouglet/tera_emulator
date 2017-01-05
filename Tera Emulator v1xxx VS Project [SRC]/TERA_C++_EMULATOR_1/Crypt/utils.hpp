#ifndef _UTILS_HPP_
#define _UTILS_HPP_


#include <cstdio>
#include <cstdlib>

#include "data_type.hpp"

uint	l_sizeof(char *src);
char*	l_malloc(uint size);
void	l_free(char *src);
char*	l_realloc(char *src, uint size);
char*	l_mem2mem(char *src);

char*	bytedump(const char *value);
char*	strdump(const char *value);
char*	strndump(const char *value, int len);
void	strupdate(char **src, const char *value);

int	utf8_to_unicode_length(const unsigned char *c);
Wchar	utf8_to_unicode(const unsigned char *c, int *pos);
int	unicode_to_utf8_length(const Wchar *c);
int	unicode_to_utf8(char* b, Wchar c);

int	WCHARlen(const Wchar *wc);
int	cpy_WCHAR(Wchar *wc, const char *c, int len);
int	cpy_WCHAR2(Wchar *wc, const char *c);
Wchar*	to_WCHARi(const char *c, int *size);
Wchar*	to_WCHAR(const char *c);

char*	to_CHAR(const Wchar *wc);
int	to_CHARi(const Wchar *wc, char *c);

char	dir_exist(const char *dirname);
char	file_exist(const char *filename);
size_t	file_size(const char *filename);
void	l_mkdir(const char* dirname);

float	atof2(char* val);
bool	atob(char* val);
short	is_atoi(char* val);

long	microsec();

char*	l_realpath(const char * src);

void	hexdump(const char* function, const char* title, const void *Vbuffer, unsigned long index);

void	DEBUG(const char*, ...);
void	DEBUG2(const char*, ...);

#endif // _UTILS_HPP_
