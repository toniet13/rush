#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

struct str
{
    char *nbr;
    char *word;
};

int ft_is_alpha(char c)
{
    if((c >= 'a' && c <='z') ||  (c >= 'A' && c <= 'Z'))
        return 1;
    return 0;
}

int ft_is_num(char c)
{
    if(c >= '0' && c <= '9')
        return 1;
    return 0;
}

int ft_n_of_lines(char *file)
{
    int f;
    char temp[1];
    temp[0] = '0';
    int count = 0;

    f = open(file, O_RDONLY);
    if (f == -1)
        return -1;
    while (read(f, &temp[0], 1))
    {
        if (temp[0] == '\n')
            count++;
    }
    close(f);
    return (count);
}

struct str *mem_alloc(struct str* dict, int nlines)
{
    int i;

    i = 0;
   
    while(i < nlines)
    {
        if (!(dict[i].nbr = (char *)malloc(sizeof(char) * 50)))
            exit (1);
        if (!(dict[i].word = (char *)malloc(sizeof(char) * 100)))
            exit (1);
        i++;
    }
    return (dict);
}

void dict_init(struct str* dict, int file)
{
    int i;
    int j;
    char temp[1];

    j = 0;
    i = 0;
    while(read(file, &temp[0], 1))
    {
        if(ft_is_alpha(temp[0]))
            dict[i].word[j++] = temp[0];
        else if (ft_is_num(temp[0]))
            dict[i].nbr[j++] = temp[0];
        else if(temp[0] == '\n')
        {
            i++;
            j = 0;
        }
        else
            j = 0;
    }
}

int ft_check_nbr(char *nbr)
{
    int i;

    i = 0;
    while (nbr[i] != '\0')
    {
        if (!(ft_is_num(nbr[i])))
            return (0);
        i++;
    }
    return (1);
}

int     ft_len(char *str)
{
    int ret;

    ret = 0;
    while (str[ret] != '\0')
    {
        ret++;
    }
    return (ret);
}

char    *ft_rm_chars(char *nbr, int n)
{
    int i;
    char    *ret;

    if(!(ret = (char *)malloc(sizeof(char)* (ft_len(nbr)))))
        exit(1);
    i = 0;
    while(nbr[i + n])
    {
        ret[i] = nbr[i + n];
        i++;
    }
    ret[i] = '\0';
    return (ret);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	iterator;

	iterator = 0;
	while (src[iterator] != '\0')
	{
		dest[iterator] = src[iterator];
		iterator++;
	}
	dest[iterator] = '\0';
	return (dest);
}

void	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	iterator;

	iterator = 0;
	while (src[iterator] != '\0' && iterator <= (size - 1))
	{
		dest[iterator] = src[iterator];
		iterator++;
	}
	dest[iterator] = '\0';
}

char    *ft_rm_zero(char *nbr)
{

    while (*nbr == '0' && ft_len(nbr) > 1)
        ft_strcpy(nbr , ft_rm_chars(nbr, 1));
    return (nbr);        
}

int     ft_strcmp(char *s1, char *s2)
{
	while (*s1 != '\0' || *s2 != '\0')
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	return (0);
}


char    *ft_get_wrd(char *nbr, struct str *dict, int nlines)
{
    int     i;
    
    i = 0;
    while (i < nlines)
    {
        if (ft_strcmp(dict[i].nbr, nbr) == 0)
            return (dict[i].word);
        i++;
    }
    return ("Dict Error\n");
}

void ft_putstr(char *str)
{
    while (*str != '\0')
    {
        write(1, &*str, 1);
        str++;
    }
    write(1, " ", 1);
}

void    ft_print_num(char *nbr, struct str *dict, int nlines);

void    ft_print_two(char *nbr, struct str *dict, int nlines)
{
    char temp[3];

    if (nbr[0] == '1')
        ft_putstr(ft_get_wrd(nbr, dict, nlines));
    else if (nbr[1] == '0')
        ft_putstr(ft_get_wrd(nbr, dict, nlines));
    else
    {
        if(nbr[0] != '0')
        {
            temp[0] = nbr[0];
            temp[1] = '0';
            temp[2]  = '\0';
            ft_putstr(ft_get_wrd(temp, dict, nlines));
        }     
        temp[0] = nbr[1];
        temp[1] = '\0';
        ft_print_num(temp, dict, nlines);
    }
}

void    ft_print_three(char *nbr, struct str *dict, int nlines)
{
    char temp[3];

    if (nbr[1] == '0' && nbr[2] == '0')
    {
        if(nbr[0] != '0')
        {
            ft_strlcpy(temp, nbr, 1);
            ft_putstr(ft_get_wrd(temp, dict, nlines));
            ft_putstr(ft_get_wrd("100", dict, nlines));
        }
    }
    else
    {
        if(nbr[0] != '0')
        {
            ft_strlcpy(temp, nbr, 1);
            ft_putstr(ft_get_wrd(temp, dict, nlines));
            ft_putstr(ft_get_wrd("100", dict, nlines));
        }
        temp[0] = nbr[1];
        temp[1] = nbr[2];
        temp[2] = '\0';
        ft_print_num(temp, dict, nlines);
    } 
}


void    ft_print_num(char *nbr, struct str *dict, int nlines)
{
    char temp[3];

    if (ft_len(nbr) == 1)
        ft_putstr(ft_get_wrd(nbr, dict, nlines));
    else if (ft_len(nbr) == 2)
        ft_print_two(nbr, dict, nlines);
    else
        ft_print_three(nbr, dict, nlines);
}

char    *ft_build_nbr(int size)
{
    char    *ret;
    int     i;

    if(!(ret = (char *)malloc(sizeof(char) * size)))
        exit(1);
    i = 1;
    ret[0] = '1';
    while(i < size)
    {
        ret[i] = '0';
        i++;
    }
    ret[i] = '\0';

    return (ret);
}

void    ft_print_position(char *nbr, struct str *dict, int nlines, int mod)
{
        char    *build;
        int     i;

        if(mod == 0)
            i = 2;
        else if(mod == 1)
            i = 0;
        else
            i = 1;
        build = ft_build_nbr(ft_len(nbr) - i);
        ft_putstr(ft_get_wrd(build, dict, nlines));
        free(build);
}

void solve(char *nbr, struct str *dict, int nlines)
{
    char    temp[4];
    if (ft_len(nbr) > 3)
    {
        if (ft_len(nbr) % 3 == 0)
            ft_strlcpy(temp, nbr, 3);
        else if (ft_len(nbr) % 3 == 2)
            ft_strlcpy(temp, nbr, 2); 
        else
            ft_strlcpy(temp, nbr, 1);
        ft_print_num(temp, dict, nlines);
        if(!(ft_len(temp) == 3 && (temp[0] == '0' && temp[1] == '0' && temp[2] == '0')))
        {
            ft_print_position(nbr, dict, nlines, (ft_len(nbr) % 3));
        }
        if(ft_len(nbr) % 3 == 0)
            ft_strcpy(nbr, ft_rm_chars(nbr, 3));
        else
            ft_strcpy(nbr, ft_rm_chars(nbr, ft_len(nbr) % 3));
        solve(nbr, dict, nlines);
    }
    else
        ft_print_num(nbr, dict, nlines);
}

int     ft_check_file(char *argv[], int arg)
{
    int     file;

    if(arg == 1)
        file = open("numbers.dict", O_RDONLY);
    else
        file = open(argv[1], O_RDONLY);
    if(file == -1)
    {
        write(1, "Dict Error\n", 11);
        return (0);
    }
    return file;
}

int     ft_check_input(int argc, char *argv[])
{
    if(argc == 2)
    {
        if(!(ft_check_nbr(argv[1])) || argv[1][0] == '\0')
            write(1, "Error\n", 6);
        else
            return(1);
    }
    else if(argc == 3)
    {
        if(!(ft_check_nbr(argv[2])) || argv[2][0] == '\0')
            write(1, "Error\n", 6);
        else
            return(2);
    }
    else
        write(1, "Error\n", 6);
    return (-1);
}

void    ft_free_struct(struct str *dict, int nlines)
{
    int     i;
    
    i = 0;
    while(i < nlines)
    {
        free(dict[i].word);
        free(dict[i].nbr);
        i++;
    }
}
int main(int argc, char *argv[])
{
    int file;
    int nlines;
    char    *nbr;
    struct str *dict;
    int     arg;

    if(!(nbr = (char *)malloc(sizeof(char) * 50)))
        return (1);
    nlines = ft_n_of_lines("numbers.dict");
    if (!(dict = (struct str*)malloc(sizeof(*dict) * nlines)))
        return (1);
    arg = ft_check_input(argc, argv);
    if(arg == -1 || (!(file = ft_check_file(argv, arg))))
        return (1);
    dict = (mem_alloc(dict, nlines));
    dict_init(dict, file);
    close(file);
    ft_strcpy(nbr, ft_rm_zero(argv[arg]));
    solve(nbr, dict, nlines);
    free(nbr);
    ft_free_struct(dict, nlines);
    free(dict);
    return (0);
}
