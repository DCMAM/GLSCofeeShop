#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item
{
	int qty;
	int tempqty;
	int price;
	int bought;
	char start[51];
	char name[51];
	char type[11];
	struct item *next;
	struct item *prev;
}
*head = NULL, *tail = NULL;

void insert(char name[], char type[], int qty, int price)
{
	struct item *newItem = (struct item *)malloc(sizeof(struct item));
	strcpy(newItem->name, name);
	
	if(strcmp(type, "yes") == 0)
	{
		strcpy(newItem->type, "Coffee");
	}
	else if(strcmp(type, "no") == 0)
	{
		strcpy(newItem->type, "Non-coffee");		
	}
	newItem->qty = qty;
	newItem->tempqty = qty;
	newItem->price = price;
	newItem->bought = 0;
	newItem->next = NULL;
	
	if(head == NULL)
	{
		head = tail = newItem;
	}
	else
	{
		tail->next = newItem;
		newItem->prev  = tail;
		tail = newItem;
	}
}

void deleteitem(char name[])
{
	if(head == NULL)
	{
		printf("No Data!\n");
	}
	else if(head == tail)
	{
		struct item *temp = head;
		temp = head = tail = NULL;
		free(temp);
	}
	else
	{
		if(strcmp(head->name, name) == 0)
		{
			struct item *temp = head;
			head = head->next;
			free(temp);
			head->prev = NULL;
		}
		else if(strcmp(tail->name, name) == 0)
		{
			struct item *temp = tail;
			tail = temp->prev;
			free(temp);
			tail->next = NULL;
		}
		else
		{
			struct item *curr = head;
			while(strcmp(curr->next->name, name) != 0)
			{
				curr = curr->next;
			}
			struct item *temp = curr->next;
			curr->next = temp->next;
			temp->next->prev = curr;
			free(temp);
		}
	}
}

void deleteitem0()
{
	int deleted = 0;
	do
	{	 
		deleted = 0;	
		if(head == tail && head->tempqty == 0)
		{
			free(head);
			head = tail = NULL;
			deleted = 1;
			break;
		}
		else if(head->tempqty == 0 && head != tail)
		{
			struct item *temp = head;
			head = head->next;
			free(temp);
			head->prev = NULL;
			deleted = 1;
		}
		else if(tail->tempqty == 0 && head != tail)
		{
			struct item *temp = tail;
			tail = temp->prev;
			free(temp);
			tail->next = NULL;
			deleted = 1;
		}
		else
		{
			struct item *curr = head;
			while(curr->next != NULL)
			{
				if(curr->next->tempqty == 0)
				{
					struct item *temp = curr->next;
					curr->next = temp->next;
					temp->next->prev = curr;
					free(temp);
					deleted = 1;
					curr = curr->next;
				}
				else
				{
					curr = curr->next;
				}
			}
		}
	}
	while(deleted == 1);
}

int totalitem()
{
	struct item *curr = head;
	int i=0;
	while(curr)
	{
		i++;
		curr = curr->next;
	}
	return i;
}

int totalitemqty(int index)
{
	struct item *curr = head;
	int i = 0;
	while(i < (index - 1))
	{
		curr = curr->next;
		i++;
	}
	return curr->tempqty;
}

void tempupdate(int index, int qty)
{
	struct item *curr = head;
	int i = 0;
	while(i < (index - 1))
	{
		curr = curr->next;
		i++;
	}
	curr->tempqty = curr->tempqty - qty;
	curr->bought = curr->bought + qty;
}

void resetqty()
{
	struct item *curr = head;
	while(curr){
		curr->tempqty = curr->qty;
		curr->bought = 0;
		curr = curr->next;
	}
}

void update()
{
	struct item *curr = head;
	while(curr)
	{
		curr->qty = curr->tempqty;
		curr->bought = 0;
		curr = curr->next;
	}
}

void freeAll()
{
	while(head)
	{
		if(head && head == tail)
		{
		free(head);
		head = tail = NULL;
		}
		else if(head)
		{
			struct item *temp = head;
			head = head->next;
			head->prev = NULL;
			free(temp);
		}
	}
}

int list(char n[])
{
	struct item *curr = head;
	while(curr)
	{
		if(strcmp(curr->name, n) == 0)
		{
			return 0;
		}
		curr = curr->next;
	}
	return 1;
}

void viewItem()
{
	struct item *curr = head;
	printf("==========================================================================\n");
	printf("No.| Menu                 |     Type   | Quantity |          Price       |\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
	
	int i=0;
	
	while(curr != NULL)
	{
		printf(" %-3d| %-20s | %10s | %8d |      %15d |\n", i+1, curr->name, curr->type, curr->tempqty, curr->price);
		i++;
		curr = curr->next;
	}
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
}

void viewbuy()
{
	struct item *curr = head;
	printf("==========================================================================\n");
	printf("                                  Bill                                    \n");
	printf("==========================================================================\n");
	printf("No.| Menu                 |     Type   | Quantity |           Price      |\n");
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
	int i=0;
	while(curr != NULL)
	{
		if(curr->bought > 0)
		{
			printf("%-3d| %-20s | %10s | %8d |      %15d |\n", 
				i+1, curr->name, curr->type, curr->bought, (curr->price * curr->bought));
			i++;
		}
		curr = curr->next;
	}
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
}

void Start()
{
	printf("enter your name : ");
}

void AdminMenu()
{
	printf("1. Add Item\n");
	printf("2. Remove item\n");
	printf("3. Exit\n");
	printf("Enter your action: ");
}

void CustMenu()
{
	printf("1. Buy Item\n");
	printf("2. Cancel Item\n");
	printf("3. Exit\n");
	printf("Enter your action: ");
}

int main()
{
	char start[51];
	int choice = 0;
	insert("Americano", "yes", 12, 19000);
	insert("Chocolate Baked", "no", 15, 24000);
	insert("Alberto", "yes", 7, 44000);
	do
	{
		Start();
		scanf("%[^\n]", start);
		
		//admin
		if (strcmp(start,"admin")==0)
		{
			system ("cls");
			do
			{
				viewItem();
				AdminMenu();
				scanf("%d", &choice); getchar();
				
				//add
				if (choice == 1)
				{
					char name[21];
					char type[11];
					int qty = 0;
					int price = 0;
					
					//insert item
					do
					{
						printf("\n");
						printf("Insert item name: ");
						scanf("%[^\n]", &name); getchar();
					} while(strlen(name) <= 5 || strlen(name) >= 20);
					
					//coffee or no
					do
					{
						printf("Type of Coffee[yes/no]: ");
						scanf("%[^\n]", &type); getchar();
						if(strcmp(type, "yes") == 0){
							
							break;
						}
						else if(strcmp(type, "no") == 0)
						{
							break;
						}
					} while(true);
					
					//insert qty
					do
					{
						printf("Insert the quantity of the item: ");
						scanf("%d", &qty); getchar();
					} while(qty < 1 || qty > 100);
					
					//insert price
					do
					{	
						printf("Insert the price of the item: ");
						scanf("%d", &price); getchar();
					} while(price <= 10000 || price >= 200000);
					
					insert(name, type, qty, price);
				}
				
				//remove
				else if (choice == 2)
				{
					if(totalitem() > 0)
					{
						char name[21];
						do
						{
							printf("Insert item name: ");
							scanf("%[^\n]", &name); getchar();
						} while( list(name) );
						
						deleteitem(name);
						printf("%s has been deleted\n", name);
					}
					else
					{
						printf("\nNo item..\n"); 
						printf("Please add item first\n");
					}
				}
				
				//exit
				else if (choice == 3)
				{
					break;
				}
				else
				{
					printf("You should input 1-3\n");
				}
				system("pause");
				system("cls");
			} while(true);
		}
		
		//customer
		else 
		{
			system("cls");
				do
				{
					viewItem();
					CustMenu();
					scanf("%d", &choice); getchar();
					if(choice == 1)
					{
						int choose = 0;
						int itemqty = 0;
						do
						{
							printf("choose your menu [1 - %d]: ", totalitem());
							scanf("%d", &choose); getchar();
						} while(choose < 1 || choose > totalitem());
						
						do
						{
							printf("enter the quantity [1 - %d]:  ", totalitemqty(choose));
							scanf("%d", &itemqty); getchar();
						} while(itemqty < 1 || itemqty > totalitemqty(choose));
						
						tempupdate(choose, itemqty);
					}
					
					else if(choice == 2)
					{
						resetqty();
						printf("Order Canceled!\n");
						break;
					}
					
					else if(choice == 3)
					{
						deleteitem0();
						update();
						break;
					}
					else
					{
						
					}
					system("pause");
					system("cls");
				}while(true);
		}
	} while(true);
}
