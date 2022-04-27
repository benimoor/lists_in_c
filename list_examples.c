// STRUCT
typedef struct s_list {
	int id;
	char *name;
	
	struct s_list *next;
}				t_list;

// INCLUDES
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// FUNCTIONS

int my_cmp(int a, int b){
	if (a > b)
		return 0;
	return 1;
}

void list_swap(t_list *a, t_list *b){
	int tmp_id = a->id;
	char *tmp_name = a->name;
	a->id = b->id;
	a->name = b->name;
	b->id = tmp_id;
	b->name = tmp_name;
}

t_list *makeNewList(int id, char *name){
	t_list *new = (t_list *)malloc(sizeof(t_list));

	new->id = id;
	new->name = name;
	new->next = NULL;

	return new;
}

t_list *connectLists(t_list *first, t_list *next){
	first->next = next;
	return first;
}

t_list *connectLastList (t_list *first, t_list *last){
	t_list *cur = first;
	if (!first)
		return last;
	while (cur->next != 0)
		cur = cur->next;
	cur->next = last;
	return first;
}

t_list *connectFirstList (t_list *first, t_list *last){
	if (!first)
		return last;
	else if (!last)
		return first;
	else
		first->next = last;
	return first;

}

t_list *connectMoreLists(int n_arg, ...){
	va_list lst;
	int i = 0;
	t_list *cur;
	t_list *start;
	va_start(lst, n_arg);
	cur = va_arg(lst, t_list*);
	start = cur;
	while(i < n_arg){
		cur = connectLists(cur, va_arg(lst, t_list*));
		cur = cur->next;
		i++;
	}
	va_end(lst);
	return start;
}

t_list *sortList (t_list *list){
	t_list *cur = list;
	int swapped = 1;
	while(swapped == 1)
	{
		swapped = 0;
		while(cur && cur->next)
		{
			if(my_cmp(cur->id, cur->next->id) == 0){
				swapped = 1;
				list_swap(cur, cur->next);
				cur = sortList(list);
			}
			cur = cur->next;
		}
	}
	return list;
}
// MAIN

int main(){
	t_list *ping = makeNewList(0, "Ping");
	t_list *pong = makeNewList(1, "Pong");
	t_list *last = makeNewList(2, "Last");
	t_list *tmp = ping;
	printf("\n-----------------------------------------------------\n");
	printf("(%d -> %s)", ping->id, ping->name);
	printf("\n-----------------------------------------------------\n");
	ping = connectLists(ping, pong);
	while(tmp != 0)
	{
		if (tmp->next == 0)
			printf("(%d -> %s)", tmp->id, tmp->name);
		else
			printf("(%d -> %s) | ",tmp->id, tmp->name);
		tmp = tmp->next;
	}
	printf("\n-----------------------------------------------------\n");
	ping = connectLastList(ping, last);
	tmp = ping;
	while (tmp != 0){
		if (tmp->next == 0)
			printf("(%d -> %s)",tmp->id, tmp->name);
		else
			printf("(%d -> %s) | ",tmp->id, tmp->name);
		tmp = tmp->next;
	}
	printf("\n-----------------------------------------------------\n");
	t_list *zero = makeNewList(0, "Gago");
	t_list *one = makeNewList(1, "Gugo");
	t_list *two= makeNewList(2, "Vardush");
	t_list *tree = makeNewList(3, "Valod");
	t_list *four = makeNewList(4, "Garnik");
	t_list *five = makeNewList(5, "Vardanchik");
	t_list *six = makeNewList(6, "Pyutagoras");
	t_list *seven = makeNewList(7, "Charencik");
	t_list *eight = makeNewList(8, "Fstx");

	t_list *all = connectMoreLists(8, one, tree, six, two, four, zero, seven, five, eight);
	t_list *temp = all;
	while(temp){
		if (temp->next == 0)
			printf("id:%d | name: %s", temp->id, temp->name);
		else
			printf("id:%d | name: %s\n", temp->id, temp->name);
		temp = temp->next;
	}
	printf("\n-----------------------------------------------------\n");
	t_list *sorted = sortList(all);
	while(sorted){
		if(sorted->next == 0)
			printf("id:%d | name: %s", sorted->id, sorted->name);
		else	
			printf("id:%d | name: %s\n", sorted->id, sorted->name);
		sorted = sorted->next;
	}
	printf("\n-----------------------------------------------------\n");
	return 0;
}
