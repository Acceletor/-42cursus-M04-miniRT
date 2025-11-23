#include "../include/minirt.h"

void ft_err(char *str, t_collector **g_root)
{
    ft_printf("Error: %s\n", str);
    gc_free_all(g_root);
    exit(1);
}

t_collector *new_node(void *adr)
{
    t_collector *node;

    node = malloc(sizeof(t_collector));
    if (!node)
        return (NULL);
    node->adr = adr;
    node->next = NULL;
    return (node);  
}

int gc_append_adr(t_collector **g_root, void *adr)
{
    t_collector *node;
    t_collector *tmp;

    node = new_node(adr);
    if (!node)
        return (0);
    if (!*g_root)
    {
        *g_root = node;
        return (1);
    }
    tmp = *g_root;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = node;
    return (1);
}

void * gc_malloc(t_collector **g_root ,size_t size)
{
    void *ptr;
    ptr = malloc(size);
    if (!ptr)
        return (NULL);
    if (!gc_append_adr(g_root, ptr))
    {
        free(ptr);
        return(NULL);
    }
    return (ptr);
}

int allocate_scene(t_scene **sc, t_collector **g_root)
{
    *sc = gc_malloc(g_root, sizeof(t_scene));
    if (!*sc)
        return (0);
    (*sc)->objs = NULL;
    (*sc)->light = NULL;
    (*sc)->amb.is_set = false;
    (*sc)->cam.is_set = false;
    return (1);
}

void gc_free_all(t_collector **g_root)
{
    t_collector *tmp;

    while (*g_root)
    {
        tmp = (*g_root)->next;
        free((*g_root)->adr);
        free(*g_root);
        *g_root = tmp;
    }
}

int invalid_file(int argc, char **argv, int *fd, t_collector **g_root)
{
    int len;
    if (argc != 2)
        return (1);
    len = ft_strlen(argv[1]);
    if (len < 3)
        return (1);
    if (argv[1][len - 3] != '.' ||
        argv[1][len - 2] != 'r' ||
        argv[1][len - 1] != 't')
        return (1);
    *fd = open(argv[1], O_RDONLY);
    if (*fd == -1)
        ft_err("failed to read the file", g_root);
    return (0);
}

int main(int argc, char **argv)
{
    t_scene *sc;
    t_collector *g_root;
    int fd;

    g_root = NULL;
    if (invalid_file(argc, argv, &fd, &g_root))
        ft_err("Incorrect argument: ./miniRT file_name.rt", &g_root);
    if (!allocate_scene(&sc, &g_root))
        ft_err("allocation", &g_root);
    // .......program logic.......
    gc_free_all(&g_root);
    // close(fd)

    return 0;
}