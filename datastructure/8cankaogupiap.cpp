#include "stdio.h"
#include "stdlib.h"

int flag;
typedef struct Node
{
    int orderid;
    int stockid;
    float price;
    int quantity;
    char type;
    struct Node *next;
} NODE;

int Min(int a, int b)
{
    return a <= b ? a : b;
}

NODE *head1, *p, *head2; // head1 buy; head2 sell;

void InitBuyQueue()
{
    head1 = (NODE *)malloc(sizeof(NODE));
    head1->orderid = -1;
    head1->stockid = -1;
    head1->price = -1.0;
    head1->quantity = -1;
    head1->type = 'x';
    head1->next = NULL;
}

void InitSellQueue()
{
    head2 = (NODE *)malloc(sizeof(NODE));
    head2->orderid = -1;
    head2->stockid = -1;
    head2->price = -1.0;
    head2->quantity = -1;
    head2->type = 'x';
    head2->next = NULL;
}

void SaveBuy(NODE *p)
{
    NODE *q = head1, *q_pre;
    int flag1 = 0;
    while (q->next != NULL)
    {
        q_pre = q;
        q = q->next;
        if (p->stockid == q->stockid)
        {
            flag1 = 1;
            while (q != NULL && (q->price > p->price || q->price == p->price) && q->stockid == p->stockid)
            {
                q_pre = q;
                q = q->next;
            }
            q_pre->next = p;
            p->next = q;
            break;
        }
    }
    if (flag1 == 0)
    {
        p->next = head1->next;
        head1->next = p;
    }
}

void SaveSell(NODE *p)
{
    NODE *q = head2, *q_pre;
    int flag1 = 0;
    while (q->next != NULL)
    {
        q_pre = q;
        q = q->next;
        if (p->stockid == q->stockid)
        {
            flag1 = 1;
            while (q != NULL && (q->price < p->price || q->price == p->price) && q->stockid == p->stockid)
            {
                q_pre = q;
                q = q->next;
            }
            q_pre->next = p;
            p->next = q;
            break;
        }
    }
    if (flag1 == 0)
    {
        p->next = head2->next;
        head2->next = p;
    }
}

void DeleteBuy(NODE *p)
{
    NODE *x = head1;
    while (x->next->orderid != p->orderid)
        x = x->next;
    x->next = p->next;
}

void DeleteSell(NODE *p)
{
    NODE *x = head2;
    while (x->next->orderid != p->orderid)
        x = x->next;
    x->next = p->next;
}
void Delete()
{
    NODE *x;
    x = head1;
    while (x->next != NULL)
    {
        x = x->next;
        if (x->quantity == 0)
            DeleteBuy(x);
    }
    x = head2;
    while (x->next != NULL)
    {
        x = x->next;
        if (x->quantity == 0)
            DeleteSell(x);
    }
}

int main()
{
    int choice, stockid, quantity, orderid = 1;
    float price;
    char bs;
    InitBuyQueue();
    InitSellQueue();
    while ((scanf("%d ", &choice)) && choice != 0)
    {
        if (choice == 0)
        {
            exit(0);
            break;
        }
        else if (choice == 1)
        {
            //è¾“å…¥
            scanf("%d %f %d %c", &stockid, &price, &quantity, &bs);
            getchar();
            p = (NODE *)malloc(sizeof(NODE));
            p->orderid = orderid++;
            p->price = price;
            p->stockid = stockid;
            p->quantity = quantity;
            p->type = bs;
            printf("orderid: %04d\n", p->orderid);
            if (bs == 'b')
            {
                NODE *q = head2;
                while (q->next != NULL)
                {
                    q = q->next;
                    if (q->stockid != p->stockid)
                        continue;
                    else
                    {
                        if (q->price < p->price || q->price == p->price)
                        {
                            int dealquantity = Min(p->quantity, q->quantity);
                            printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (p->price + q->price) / 2.0, dealquantity, p->orderid, q->orderid);
                            p->quantity -= dealquantity;
                            q->quantity -= dealquantity;
                            if (q->quantity == 0)
                                DeleteSell(q);
                            if (p->quantity == 0)
                                break;
                        }
                        else
                            continue;
                    }
                }
                if (p->quantity == 0)
                    free(p);
                else
                {
                    SaveBuy(p);
                }
            }
            else
            {
                NODE *q = head1;
                while (q->next != NULL && p->quantity != 0)
                {
                    q = q->next;
                    if (q->stockid != p->stockid)
                        continue;
                    else
                    {
                        if (q->price > p->price || q->price == p->price)
                        {
                            int dealquantity = Min(p->quantity, q->quantity);
                            printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (p->price + q->price) / 2.0, dealquantity, p->orderid, q->orderid);
                            p->quantity -= dealquantity;
                            q->quantity -= dealquantity;
                            if (q->quantity == 0)
                                DeleteBuy(q);
                        }
                        else
                            continue;
                    }
                }
                if (p->quantity == 0)
                    free(p);
                else
                {
                    SaveSell(p);
                }
            }
            Delete();
        }
        else if (choice == 2)
        {
            int stockid1;
            scanf("%d", &stockid1);
            getchar();
            printf("buy orders:\n");
            p = head1;
            while (p->next != NULL)
            {
                p = p->next;
                if (p->stockid == stockid1 && p->quantity != 0)
                {

                    printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", p->orderid, p->stockid, p->price, p->quantity, p->type);
                }
            }
            printf("sell orders:\n");
            p = head2;
            while (p->next != NULL)
            {
                p = p->next;
                if (p->stockid == stockid1 && p->quantity != 0)
                {

                    printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", p->orderid, p->stockid, p->price, p->quantity, p->type);
                }
            }
        }
        else if (choice == 3)
        {
            int orderid1;
            scanf("%d", &orderid1);
            getchar();
            flag = 0;
            p = head1;
            while (p->next != NULL)
            {
                p = p->next;
                if (p->orderid == orderid1)
                {
                    flag = 1;
                    printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", p->orderid, p->stockid, p->price, p->quantity, p->type);
                    DeleteBuy(p);
                    break;
                }
            }
            p = head2;
            while (p->next != NULL && !flag)
            {
                p = p->next;
                if (p->orderid == orderid1)
                {
                    flag = 1;
                    printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", p->orderid, p->stockid, p->price, p->quantity, p->type);
                    DeleteSell(p);
                    break;
                }
            }
            if (flag == 0)
            {
                printf("not found\n");
            }
            flag = 0;
        }
    }
    return 0;
}