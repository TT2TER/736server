#include <cstdio>
#include <iostream>
using namespace std;

typedef struct order
{
    int orderid;
    int stockid;
    float price;
    int quantity;
    char type;
} order;

int min(int a, int b)
{
    return a <= b ? a : b;
}

typedef struct QNode
{
    order data;
    struct QNode *link;
} QNode, *QueuePtr;

typedef struct
{
    QueuePtr front; // 队头指针
    QueuePtr rear;  // 队尾指针
} LinkQueue;

void InitQueue(LinkQueue &Q)
{
    // 构造一个有头结点的空队列Q
    Q.front = (QueuePtr)malloc(sizeof(QNode));
    Q.rear = Q.front;
    Q.front->link = NULL;
    return;
} // 出队

void save(LinkQueue &t, QueuePtr p)
{
    QueuePtr q = t.front, q_pre;
    int flag = 0;
    while (q->link != NULL)
    {
        q_pre = q;
        q = q->link;
        if (p->data.stockid == q->data.stockid)
        {
            flag = 1;
            if (p->data.type == 'b')
            {
                while (q != NULL && q->data.price >= p->data.price && q->data.stockid == p->data.stockid)
                {
                    q_pre = q;
                    q = q->link;
                }
                q_pre->link = p;
                p->link = q;
                break;
            }
            else
            {
                while (q != NULL && q->data.price <= p->data.price && q->data.stockid == p->data.stockid)
                {
                    q_pre = q;
                    q = q->link;
                }
                q_pre->link = p;
                p->link = q;
                break;
            }
        }
    }
    if (flag == 0)
    {
        p->link = t.front->link;
        t.front->link = p;
    }
}

void delorder(LinkQueue &t, QueuePtr p)
{
    QueuePtr x = t.front;
    while (x->link->data.orderid != p->data.orderid)
        x = x->link;
    x->link = p->link;
    free(p);
}

int allorderid = 0;

int main()
{
    LinkQueue sell, buy;
    InitQueue(buy);
    InitQueue(sell);
    int command = -1;
    scanf("%d", &command);
    while (command != 0)
    {
        if (command == 1)
        {
            int id, quantity;
            float price;
            char BS;
            scanf("%d %f %d %c", &id, &price, &quantity, &BS);
            order now;
            now.orderid = ++allorderid;
            now.price = price;
            now.quantity = quantity;
            now.stockid = id;
            now.type = BS;
            printf("orderid: %04d\n", now.orderid);
            if (BS == 'b')
            {
                QueuePtr q = sell.front;
                while (q->link != NULL)
                {
                    q = q->link;
                    if (q->data.stockid != now.stockid)
                    {
                        continue;
                    }
                    else if (q->data.price <= now.price)
                    {
                        int dealquantity = min(now.quantity, q->data.quantity);
                        printf("deal--price:%6.1f  quantity:%4d  buyorder:%04d  sellorder:%04d\n", (now.price + q->data.price) / 2.0, dealquantity, now.orderid, q->data.orderid);
                        now.quantity -= dealquantity;
                        q->data.quantity -= dealquantity;
                        if (q->data.quantity == 0)
                            delorder(sell, q);
                        if (now.quantity == 0)
                            break;
                    }
                    else
                        continue;
                }
                if (now.quantity != 0)
                {
                    QueuePtr t = (QueuePtr)malloc(sizeof(QNode));
                    t->data.orderid = now.orderid;
                    t->data.price = now.price;
                    t->data.quantity = now.quantity;
                    t->data.stockid = now.stockid;
                    t->data.type = now.type;
                    t->link = NULL;
                    save(buy, t);
                }
            }
            else
            {
                QueuePtr q = buy.front;
                while (q->link != NULL)
                {
                    q = q->link;
                    if (q->data.stockid != now.stockid)
                    {
                        continue;
                    }
                    else if (q->data.price >= now.price)
                    {
                        int dealquantity = min(now.quantity, q->data.quantity);
                        printf("deal--price:%6.1f  quantity:%4d  sellorder:%04d  buyorder:%04d\n", (now.price + q->data.price) / 2.0, dealquantity, now.orderid, q->data.orderid);
                        now.quantity -= dealquantity;
                        q->data.quantity -= dealquantity;
                        if (q->data.quantity == 0)
                            delorder(buy, q);
                        if (now.quantity == 0)
                            break;
                    }
                    else
                        continue;
                }
                if (now.quantity != 0)
                {
                    QueuePtr t = (QueuePtr)malloc(sizeof(QNode));
                    t->data.orderid = now.orderid;
                    t->data.price = now.price;
                    t->data.quantity = now.quantity;
                    t->data.stockid = now.stockid;
                    t->data.type = now.type;
                    t->link = NULL;
                    save(sell, t);
                }
            }
            QueuePtr t = sell.front;
            while (t->link != NULL)
            {
                t = t->link;
                if (t->data.quantity == 0)
                {
                    delorder(sell, t);
                }
            }
            t = buy.front;
            while (t->link != NULL)
            {
                t = t->link;
                if (t->data.quantity == 0)
                {
                    delorder(buy, t);
                }
            }
        }
        else if(command==2)
        {
            int checkstockid;
            scanf("%d", &checkstockid);
            getchar();
            printf("buy orders:\n");
            QueuePtr p = buy.front;
            while (p->link != NULL)
            {
                p = p->link;
                if (p->data.stockid == checkstockid && p->data.quantity != 0)
                {
                    printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", p->data.orderid, p->data.stockid, p->data.price, p->data.quantity, p->data.type);
                }
            }
            printf("sell orders:\n");
            p = sell.front;
            while (p->link != NULL)
            while (p->link != NULL)
            {
                p = p->link;
                if (p->data.stockid == checkstockid && p->data.quantity != 0)
                {
                    printf("orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", p->data.orderid, p->data.stockid, p->data.price, p->data.quantity, p->data.type);
                }
            }
        }
        else if(command==3)
        {
            int delorderid;
            scanf("%d", &delorderid);
            getchar();
            int flag = 0;
            QueuePtr p = buy.front;
            while (p->link != NULL)
            {
                p = p->link;
                if (p->data.orderid == delorderid)
                {
                    flag = 1;
                    printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", p->data.orderid, p->data.stockid, p->data.price, p->data.quantity, p->data.type);
                    delorder(buy,p);
                    break;
                }
            }
            p = sell.front;
            while (p->link != NULL && !flag)
            {
                p = p->link;
                if (p->data.orderid == delorderid)
                {
                    flag = 1;
                    printf("deleted order:orderid: %04d, stockid:%04d, price: %6.1f, quantity: %4d, b/s: %c\n", p->data.orderid, p->data.stockid, p->data.price, p->data.quantity, p->data.type);
                    delorder(sell, p);
                    break;
                }
            }
            if (flag == 0)
            {
                printf("not found\n");
            }
            flag = 0;
        }
        scanf("%d", &command);
    }
    return 0;
}