#include<stdio.h>
#include<stdlib.h>
#include"singly_linked_list.h"

static int init_flag=0;

node_t *create_node_memory(void)
{
	node_t *root=(node_t*)malloc(sizeof(node_t));
	if(root==NULL)
		return NULL;
	return root;
}

node_t *list_init(int data)
{
	node_t *root=create_node_memory();
	if(root==NULL)
	{
		printf("Unable to create Memory\n");
		exit(1);
	}
	root->data=data;
	root->next=NULL;
	return root;
}

int add_node_position(node_t *root,int position,int data)
{
	int pos=position;
	int i;
	node_t *temp=create_node_memory();
	node_t *trav=root;

	if(init_flag==0)
	{
		if(pos!=0)
		{
			printf("invalid position\n");
			free(temp);
			return -1;
		}
		root=list_init(data);
		init_flag=1;
		list_size++;
	}
	else
	{
		if(pos<0 || pos>list_size)
		{
			printf("Invalid position\n");
			return -1;
		}
		if(!(pos^list_size))/* Add at end */
		{
			add_node_at_tail(root,data);
			return 0;
		}
		if(!(pos^0))/* Add at start */
		{
			add_node_at_head(root,data);
			return 0;
		}
		if(trav==NULL)
		{
			printf("Unable to create Memory\n");
			exit(1);
		}

		if(root==NULL)
		{
			printf("NULL pointer address\n");
			return -1;
		}

		for(i=0;i<pos-1;i++)
		{
			trav=trav->next;
		}
		temp->data=data;
		temp->next=trav->next;
		trav->next=temp;
		list_size++;
	}
	return 0;
}

int delete_node_position(node_t *root,int position)
{
	int pos=position;
	int i=0;
	node_t *trav=root;
	node_t *temp=create_node_memory();
	if(pos<0 || pos>list_size-1)
	{
		printf("Invalid position\n");
		return -1;
	}
	if(trav==NULL)
	{
		printf("NULL pointer address\n");
		return -1;
	}

	for(i=0;i<pos-1;i++)
	{
		trav=trav->next;
	}

	temp->next=trav->next->next;
	free(trav->next);
	trav->next=temp->next;
	list_size--;
	free(temp);
	return 0;
}

node_t *add_node_at_head(node_t *root,int data)
{
	if(init_flag==0)
	{
		root=list_init(data);
		init_flag=1;
		list_size++;
		return root;
	}
	else
	{
		node_t *temp=create_node_memory();
		temp->data=data;
		temp->next=root;
		list_size++;
		printf("2\n");
		return temp;
	}
}

void add_node_at_tail(node_t *root,int data)
{
	node_t *temp=create_node_memory();
	node_t *trav=root;

	while(trav->next)
	{
		trav=trav->next;
	}
	temp->data=data;
	temp->next=NULL;
	trav->next=temp;
	list_size++;
}

node_t *delete_node_at_head(node_t *root)
{
	static node_t temp;	
	if(!list_size)
	{
		printf("Empty list\n");
		return NULL;
	}
	temp.next=root->next;
	free(root);
	list_size--;
	return temp.next;
}


int size_of_list(node_t *root)
{
	int size=0;

	if(root==NULL)
		return 0;

	node_t *trav=create_node_memory();
	trav->next=root->next;

	for(size=0;trav->next != NULL;trav->next=trav->next->next,size++);
	free(trav);
	return size+1;
}

void print_list(node_t *root)
{
	node_t *trav=root;
	int i=0;
	if(trav==NULL)
	{
		printf("Empty list\n");
		return;
	}
	printf("[START]  ");
	while(trav->next)
	{
		printf("%d->",trav->data);
		trav=trav->next;
	}
	printf("%d [END]\n",trav->data);

}

void free_list(node_t *root)
{
	node_t *temp;
	while(root->next)
	{
		temp=root->next;
		free(root);
		root=temp;
	}
	free(root);
}
