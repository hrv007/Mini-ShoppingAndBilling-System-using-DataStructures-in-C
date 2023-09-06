#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

char adminID[20] = "admin123";
char Password[20] = "admin123";

int flag;

struct Items* shop_items[3];
struct Items* search_point;

struct Items
{
    struct Items* lchild;
    int item_id;
    char Name[50];
    int QTY;
    float MRP;
    struct Items* rchild;
};

void insert_item(int id, char item_name[], int quant, float mrp, int x)
{
    int temp;
    struct Items* node = (struct Items*)malloc(sizeof(struct Items));
    strcpy(node->Name, item_name);
    node->item_id = id;
    node->QTY = quant;
    node->MRP = mrp;
    node->lchild = NULL;
    node->rchild = NULL;

    if(shop_items[x])
    {
        struct Items* p = shop_items[x];
        struct Items* q = NULL;

        while(p)
        {
            if(p->item_id > id)
            {
                q = p;
                p = p->lchild;
                temp=1;
            }
            else if(p->item_id < id)
            {
                q = p;
                p = p->rchild;
                temp=0;
            }
            else
            {
                printf("Item already Exists!!!\nPress Enter to Continue...\n");
                getch();
                free(node);
                return;
            }
        }

        if(temp)
            q->lchild = node;
        else
            q->rchild = node;
    }
    else
    {
        shop_items[x] = node;
    }
}

struct Items* SUCC(struct Items* t)
{
    t = t->rchild;
    while(t->lchild)
    {
        t = t->lchild;
    }
    return t;
}

void delete_item(int id, int x)
{
    struct Items* node = shop_items[x];
    struct Items* p = NULL;
    struct Items* q = NULL;

    int id_cpy, qty;
    float mrp;
    char name[50];

    int temp = 0;


    while(node)
    {
        if(node->item_id>id)
        {
            p = node;
            node = node->lchild;
        }
        else if(node->item_id<id)
        {
            p = node;
            node = node->rchild;
        }
        else
        {
            temp = 1;
            break;
        }
    }

    if(temp == 0)
    {
        printf("Item Not Available!!!\nPress Enter to Continue...\n");
        getch();
        return;
    }

    if((node->lchild == NULL)&&(node->rchild == NULL))
    {
        if(p->lchild == node)
        {
            p->lchild = NULL;
        }
        else
        {
            p->rchild = NULL;
        }
        free(node);
    }
    else
    {
        if((node->lchild!=NULL)&&(node->rchild!=NULL))
        {
            q = SUCC(node);
            id_cpy = q->item_id;
            strcpy(name, q->Name);
            qty = q->QTY;
            mrp = q->MRP;

            delete_item(q->item_id, x);

            node->item_id = id_cpy;
            strcpy(node->Name, name);
            node->QTY = qty;
            node->MRP = mrp;
        }
        else
        {
            if(p->lchild == node)
            {
                if(node->lchild == NULL)
                {
                    p->lchild = node->rchild;
                }
                else
                {
                    p->lchild = node->lchild;
                }
            }
            else
            {
                if(node->lchild == NULL)
                {
                    p->rchild = node->rchild;
                }
                else
                {
                    p->rchild = node->lchild;
                }
            }
            free(node);
        }
    }
}

void update_item(int id, int x)
{
    search_item(id, x);
    struct Items* node = search_point;

    if(node)
    {
        printf("Enter the Updated Data of %d %s:\n", node->item_id, node->Name);

        printf("Quantity:");
        scanf("%d",&(node->QTY));

        printf("MRP: Rs.");
        scanf("%f",&(node->MRP));

        printf("%d, %s has been updated.\nPress Enter to Continue...\n", node->item_id, node->Name);
        getch();
    }
    else
    {
        printf("Item not available!!!\n Press Enter to Continue...\n");
        getch();
    }
}

void search_item(int id, int x)
{
    struct Items* p = shop_items[x];

    if(p)
    {
        while(p)
        {
            if(p->item_id > id)
            {
                p = p->lchild;
            }
            else if(p->item_id < id)
            {
                p = p->rchild;
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        printf("NotAvailable!!!\nPress Enter to Continue...\n");
        getch();
    }
    search_point = p;
}

struct Q
{
    int q_id;
    char item_name[50];
    int qty;
    float price;
    struct Q* next;
};

struct Q* front = NULL;
struct Q* rear = NULL;

int isEmpty_Q()
{
    if((front == NULL)&&(rear == NULL))
        return 1;
    else
        return 0;
}

void enQueue(int id, char name[], int quan, float cost)
{
    struct Q *node = (struct Q*)malloc(sizeof(struct Q));

    strcpy(node->item_name,name);
    node->q_id = id;
    node->qty = quan;
    node->price = cost;  //Search for price in BST-not done yet
    node->next = NULL;

    if(front)
    {
        rear->next = node;
        rear = node;
    }
    else
    {
        front = node;
        rear = node;
    }

    flag = 2; //item added to cart
}

struct Q* deQueue()
{
    struct Q* tempo = front;

    if((front == rear)&&(front!=NULL))
    {
        front = NULL;
        rear = NULL;
    }
    else
    {
        front = front->next;
    }
    return tempo;
}

void Inorder_cust(struct Items* root)
{
    if(root)
    {
        Inorder_cust(root->lchild);
        printf("%d\t\t|\t\t%s\t\t|\t\t%.2f\n", root->item_id, root->Name, root->MRP);
        Inorder_cust(root->rchild);
    }
}

void list(int x)
{
    struct Items* p = shop_items[x];
    struct Items* q = NULL;
    int id, qty, que = 1;

    while(que==1)
    {
        system("cls");
        printf("ID\t\t|\t\t\tItem\t\t\t|\t\tPrice\n");
        Inorder_cust(p);

        printf("\nEnter Item ID:");
        scanf("%d",&id);
        printf("Enter Quantity:");
        scanf("%d",&qty);

        search_item(id, x);
        q = search_point;
        if(!q)
        {
            printf("Not Available!!!\nPress Enter to Continue...\n");
            getch();
            return;
        }

        if(qty>0)
        {
            q->QTY -= qty;
            enQueue(id, q->Name, qty, q->MRP);
        }

        printf("\nWould you Like to Add another Item(1. Yes/2. No):");
        scanf("%d", &que);
    }
}

void Shop()
{
    int n_shop;

    for(;;)
    {
        system("cls");
        printf("1. Electronics\n");
        printf("2. Food Items\n");
        printf("3. Stationary\n");
        printf("4. Menu\n");

        printf("Your Choice:");
        scanf("%d",&n_shop);

        switch(n_shop)
        {
        case 1:
            list(0);
            break;
        case 2:
            list(1);
            break;
        case 3:
            list(2);
            break;
        case 4:
            return;
        default:
            printf("Enter Valid Choice\nPress Enter to Continue...\n");
            getch();
        }
    }
}

void Total()
{
    system("cls");
    FILE* fptr;
    fptr = fopen("Bill.txt","w");
    struct Q* p = rear;
    struct Q* q = NULL;

    float sum = 0;

    if(p)
    {
        printf("ID\t\t|\t\t\tItem\t\t\t|\t\tQunatity\t\t|\t\tPrice\t\t|\t\tTotal\n");
        //fprintf(fptr,"ID\t\t|\t\t\tItem\t\t\t|\t\tQunatity\t\t|\t\tPrice\t\t|\t\tTotal\n");
        while(!isEmpty_Q())
        {
            q = deQueue();
            printf("%d\t\t|\t\t\t%s\t\t\t|\t\t%d\t\t|\t\t%.2f\t\t|\t\t%.2f\n",q->q_id, q->item_name, q->qty, q->price, (q->qty)*(q->price));
            sum += ((q->qty)*(q->price));
            fprintf(fptr,"%d\t\t|\t\t\t%s\t\t\t|\t\t%d\t\t|\t\t%.2f\t\t|\t\t%.2f\n",q->q_id, q->item_name, q->qty, q->price, (q->qty)*(q->price));
            free(q);
            //enter the data in file named bill
        }
        printf("Grand Total:%.2f\n",sum);
        fprintf(fptr,"Grand Total:%.2f\n",sum);
        printf("\nPress Enter to Continue...\n");
        getch();
    }
    fclose(fptr);
}

void remove_item()
{
    struct Q* p = front;
    struct Q* q = NULL;

    int pro_id, temp=0;

    system("cls");
    if(p)
    {
        printf("Enter Product ID:");
        scanf("%d",&pro_id);

        if(front->q_id == pro_id)
        {
            front = front->next;
            free(p);
            temp = 1;
        }
        else if(rear->q_id == pro_id)
        {
            while(p->next != rear) p = p->next;
            q = p;
            p = rear;
            rear = q;
            rear->next = NULL;
            free(p);
            temp = 1;
        }
        else
        {
            p = front->next;
            q = front;
            while(p->next!=rear)
            {
                if(p->q_id == pro_id)
                {
                    q->next = p->next;
                    free(p);
                    temp = 1;
                    break;
                }
                q = p;
                p = p->next;
            }
        }
        if(temp == 0)
        {
            printf("The item is not added in the Cart.\nPress Enter to Continue...\n");
            getch();
        }
    }
    else
    {
        printf("Cart is Empty!!!\nPress Enter to Continue...\n");
        getch();
    }
}

void Cart()
{
    struct Q* p = front;
    int n_cart;

    if(!isEmpty_Q())
    {
        Again:
        system("cls");
        if(p)
        {
            printf("ID\t\t|\t\t\tItem\t\t\t|\t\tQuantity\t\t|\t\tPrice\t\t|\t\tTotal\n");
            while(p)
            {
                printf("%d\t\t|\t\t\t%s\t\t\t|\t\t%d\t\t|\t\t%.2f\t\t|\t\t%.2f\n",p->q_id, p->item_name, p->qty, p->price, (p->qty)*(p->price));
                p = p->next;
            }
            p = front;
        }

        printf("1. Billing of Cart\n");
        printf("2. Remove Item from Cart\n");
        printf("3. Return to Menu\n");

        printf("Your Choice:");
        scanf("%d", &n_cart);
        if(n_cart == 1)
        {
            Total();
        }
        else if(n_cart == 2)
        {
            remove_item();
        }
        else if(n_cart == 3)
        {
            return;
        }
        else
        {
            system("cls");
            printf("Enter Valid Choice!!!\nPress Enter to Continue...\n");
            getch();
            goto Again;
        }
    }
    else
    {
        system("cls");
        printf("Your Cart is Currently Empty!!!\n");
        getch();
        return;
    }
}

void Customer()
{
    int n_custom;

    for(;;)
    {
        system("cls");
        printf("1. Shop\n");
        printf("2. Cart\n");
        printf("3. MainMenu\n");

        printf("Your Choice:");
        scanf("%d",&n_custom);

        switch(n_custom)
        {
        case 1:
            Shop();
            break;
        case 2:
            Cart();
            break;
        case 3:
            return;
        default:
            printf("Enter a valid choice.\nPress Enter to Continue...\n");
            getch();
        }
    }
}

void login()
{
    char id[20], pass[20];

    for(int i=0; i<3; i++)
    {
        printf("Administrator ID:");
        scanf("%s",id);

        printf("Password:");
        for(int j=0; j<=10; j++)
        {
            pass[j] = getch();
            if(pass[j] == 13)
            {
                pass[j] = '\0';
                break;
            }
            printf("*");
        }

        if((strcmp(id,adminID)==0) && (strcmp(pass, Password)==0))
        {
            flag = 1;
            break;
        }
        else if((strcmp(id,adminID)!=0) || (strcmp(pass, Password)!=0))
        {
            system("cls");
            printf("INVALID ADMINISTRATOR ID OR PASSWORD!!! ENTER AGAIN\n");
            flag = 0;
        }
    }
}

void Inorder_admin(struct Items* root)
{
    if(root)
    {
        Inorder_admin(root->lchild);

        if(root->QTY<=10)
            printf("%d\t\t|\t\t%d\t\t|\t\t%.2f\t\t|\t\t%s!!!\n", root->item_id, root->QTY, root->MRP, root->Name);
        else
            printf("%d\t\t|\t\t%d\t\t|\t\t%.2f\t\t|\t\t%s\n", root->item_id, root->QTY, root->MRP, root->Name);

        Inorder_admin(root->rchild);
    }
}

void edit(int x)
{
    struct Items* p = shop_items[x];

    int n_up;
    int id, qty;
    char name[50];
    float price;

    for(;;)
    {
        system("cls");
        p = shop_items[x];
        printf("ID\t\t|\t\tQuantity\t\t|\t\tPrice(Per Unit)\t\t|\t\t\tItem\n");
        Inorder_admin(p);

        printf("1. Add Item\n");
        printf("2. Delete Item\n");
        printf("3. Update Item\n");
        printf("4. Return\n");

        printf("\nYour Choice:");
        scanf("%d",&n_up);

        switch(n_up)
        {
        case 1:
            system("cls");
            printf("Item ID:");
            scanf("%d",&id);
            printf("Item Name:");
            scanf("%s",name);
            printf("Price Per Unit:");
            scanf("%f",&price);
            printf("Quantity:");
            scanf("%d",&qty);

            insert_item(id, name, qty, price, x);
            break;
        case 2:
            system("cls");
            printf("Enter Item ID to Delete:");
            scanf("%d",&id);

            delete_item(id, x);
            break;
        case 3:
            system("cls");
            printf("Enter Item ID to Update:");
            scanf("%d",&id);

            update_item(id, x);
            break;
        case 4:
            return;
        default:
            printf("Enter Valid Choice!!!\nPress Enter to Continue...\n");
            getch();
        }
    }
}

void update()
{
    int n_up;

    for(;;)
    {
        system("cls");
        printf("1. Electronics\n");
        printf("2. Food Items\n");
        printf("3. Stationary\n");
        printf("4. Return\n");

        printf("\nYour Choice:");
        scanf("%d",&n_up);

        switch(n_up)
        {
        case 1:
            edit(0);
            break;
        case 2:
            edit(1);
            break;
        case 3:
            edit(2);
            break;
        case 4:
            return;
        default:
            printf("Enter Valid Choice!!!\nPress Enter to Continue...\n");
            getch();
        }
    }
    printf("Update the stock by inserting, searching or deleting in BST.\n");
}

void Administrator()
{
    system("cls");
    login();
    if(flag == 0)
    {
        printf("You Failed to LOGIN!!!\nPress Enter to Continue...\n");
        getch();
        return;
    }
    int n_admin;

    for(;;)
    {
        system("cls");
        printf("1. Update Stock\n");
        printf("2. MainMenu\n");

        printf("Your Choice:");
        scanf("%d",&n_admin);

        switch(n_admin)
        {
        case 1:
            update();
            break;
        case 2:
            return;
        default:
            printf("Enter a valid choice.\nPress Enter to Continue...\n");
            getch();
        }
    }
}

void animation()
{
    getch();
    for(int i=0; i<=5; i++)
    {
        for(int j=5; j>=i; j--)
        {
            printf("\n\n\n\n\n");
        }
        printf("\t\t\t\t\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
        printf("\t\t\t\t\t\t\t|                                 |\n");
        printf("\t\t\t\t\t\t\t*              AMAZUN             *\n");
        printf("\t\t\t\t\t\t\t|             ------->            |\n");
        printf("\t\t\t\t\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
        sleep(1.00);
        system("cls");
    }

    sleep(1.00);
    for(int i=0; i<20; i++) printf("\n");
    printf("\t\t\t\t\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
    printf("\t\t\t\t\t\t\t|                                 |\n");
    printf("\t\t\t\t\t\t\t*              AMAZUN             *\n");
    printf("\t\t\t\t\t\t\t|             ------->            |\n");
    printf("\t\t\t\t\t\t\t*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");

    getch();
    system("cls");
}

void main()
{
    for(int i=0; i<3; i++)
    {
        shop_items[i] = NULL;
    }
    animation();
    import();

    int N;

    for(;;)
    {
        system("cls");
        printf("1. Customer\n");
        printf("2. Administrator\n");
        printf("3. Exit\n");

        printf("Your Choice:");
        scanf("%d",&N);

        switch(N)
        {
        case 1:
            Customer();
            break;
        case 2:
            Administrator();
            break;
        case 3:
            save();
            goto Finish;
        default:
            printf("Please enter a valid choice.\n");
        }
    }

    Finish:
        system("cls");
    printf("Thank You! Please visit Again!!!\n");
}

struct Items* Stack[10];
int top = -1;

void push(struct Items* t)
{
    Stack[++top] = t;
}

struct Items* pop()
{
    struct Items* p = Stack[top--];

    return p;
}

void pre_save(struct Items* t, int x)
{
    FILE *fptr;
    if(x==0)
    {
        fptr = fopen("Electronics.war","w");
    }
    else if(x==1)
    {
        fptr = fopen("FoodItems.war","w");
    }
    else if(x==2)
    {
        fptr = fopen("Stationary.war","w");
    }

    while(top>-1 || t!=NULL)
    {
        if(t!=NULL)
        {
            fprintf(fptr,"%d %s %f %d\n", t->item_id, t->Name, t->MRP, t->QTY);
            push(t);
            t = t->lchild;
        }
        else
        {
            t = pop();
            t = t->rchild;
        }
    }
    fclose(fptr);
}

void save()
{
    struct Items* p = NULL;

    p = shop_items[0];
    pre_save(p, 0);


    p = shop_items[1];
    pre_save(p, 1);

    p = shop_items[2];
    pre_save(p, 2);
}

void import()
{
    FILE *fptr;

    int id, qty;
    float cost;
    char name[50];

    fptr = fopen("Electronics.war","r");

    while(fscanf(fptr, "%d %s %f %d", &id, name, &cost, &qty)!=EOF)
    {
        insert_item(id, name, qty, cost, 0);
    }

    fclose(fptr);

    fptr = fopen("FoodItems.war","r");

    while(fscanf(fptr, "%d %s %f %d", &id, name, &cost, &qty)!=EOF)
    {
        insert_item(id, name, qty, cost, 1);
    }

    fclose(fptr);

    fptr = fopen("Stationary.war","r");

    while(fscanf(fptr, "%d %s %f %d", &id, name, &cost, &qty)!=EOF)
    {
        insert_item(id, name, qty, cost, 2);
    }

    fclose(fptr);
}

