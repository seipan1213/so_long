
#include "so_long.h"

void dc_lst_addfront(t_dc_lst *lst, char *value)
{
	t_dc_lst *new;

	new = malloc(sizeof(t_dc_lst));
	if (!new)
		put_exit_err(ERR_MALLOC);
	while (lst->value != NULL)
		lst = lst->next;
	new->value = value;
	new->next = lst->next;
	new->next->prev = new;
	new->prev = lst;
	lst->next = new;
}

void dc_lst_addback(t_dc_lst *lst, char *value)
{
	t_dc_lst *new;

	new = malloc(sizeof(t_dc_lst));
	if (!new)
		put_exit_err(ERR_MALLOC);
	while (lst->value != NULL)
		lst = lst->next;
	new->value = value;
	new->prev = lst->prev;
	new->prev->next = new;
	new->next = lst;
	lst->prev = new;
}

t_dc_lst *dc_lst_init(void)
{
	t_dc_lst *lst;

	lst = malloc(sizeof(t_dc_lst));
	if (!lst)
		put_exit_err(ERR_MALLOC);
	lst->value = NULL;
	lst->next = lst;
	lst->prev = lst;
	return (lst);
}

int get_lst_size(t_dc_lst *lst)
{
	int i;

	i = 0;
	lst = lst->next;
	while (lst->value != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void clear_lst(t_dc_lst *lst)
{
	int lst_size;
	int index;

	lst_size = get_lst_size(lst) + 1;
	index = 0;
	while (index < lst_size)
	{
		delete_lst(lst->next);
		index++;
	}
}

void delete_lst(t_dc_lst *lst)
{
	t_dc_lst *prev;
	t_dc_lst *next;

	prev = lst->prev;
	next = lst->next;
	prev->next = next;
	next->prev = prev;
	free(lst);
}

t_dc_lst *get_first_lst(t_dc_lst *lst)
{
	while (lst->value != NULL)
		lst = lst->next;
	lst = lst->next;
	return (lst);
}