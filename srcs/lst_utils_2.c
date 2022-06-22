
#include "so_long.h"

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
