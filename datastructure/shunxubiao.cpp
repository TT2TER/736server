#define initSize 100
#define LISTINCREEMENT 10
#define DataType int
# include<cstdio>
#include<cstring>
using namespace std;
typedef struct
{
    DataType *data;
    int n;
    int maxSize;
} Seqlist;

int Init(Seqlist&L)
{
    L.data=(DataType*)malloc(initSize*sizeof(DataType));
	if(……)；
}