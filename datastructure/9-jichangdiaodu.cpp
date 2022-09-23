#include <cstdio>
#include <queue>
#include <iostream>
#include <cstring>
using namespace std;
const int landing = 5000; //降落的标签
struct Way
{
    int curtime; //剩余占用时长
    int alltime; //该跑道总占用时长
};
struct Plane
{
    int num;        //编号
    int arrivetime; //开始等待时间
};
int tik; //时间记录

queue<Plane> air;  //在天上的
queue<Plane> land; //在地上的
Way way[10005];

int main()
{
    tik = 0;
    printf("Current Time: %4d\n", tik);
    int ways, s2ltime, l2stime; // number of way,time*2;
    scanf("%d%d%d", &ways, &s2ltime, &l2stime);
    int onair = 0, atland = 0, onairtotal = 0, atlandtotal = 0;
    int landwaittotal = 0, airwaittotal = 0; //总等待时间
    //初始化
    while (!air.empty())
        air.pop();
    while (!land.empty())
        land.pop();
    for (int i = 1; i <= ways; i++)
    {
        way[i].curtime = 0;
        way[i].alltime = 0;
    }

    while (true)
    {
        bool all_way_clear = true;
        for (int i = 1; i <= ways; i++)
        {
            if (way[i].curtime > 0)
            {
                way[i].curtime--;
                if (way[i].curtime == 0)
                {
                    printf("runway %02d is free\n", i);
                }
                else
                    all_way_clear = false;
            }
        }

        tik++;

        if (onair >= 0 && atland >= 0)
        {
            scanf("%d%d", &onair, &atland);
            for (int i = 1; i <= onair; i++)
            {
                Plane t;
                //onairtotal++;
                t.arrivetime = tik;
                t.num = ++onairtotal;
                air.push(t);
            }
            for (int i = 1; i <= atland; i++)
            {
                Plane t;
                //atlandtotal++;
                t.arrivetime = tik;
                t.num = ++atlandtotal;
                land.push(t);
            }
        }

        if (onair < 0 && atland < 0 && land.empty() && air.empty() && all_way_clear)
            break;

        for (int i = 1; i <= ways; i++)
        {
            if (way[i].curtime == 0)
            {

                if (!air.empty())
                {
                    Plane now;
                    now = air.front();
                    air.pop();
                    airwaittotal += tik - now.arrivetime;
                    printf("airplane %04d is ready to land on runway %02d\n", now.num + landing, i);
                    way[i].curtime = s2ltime;
                    way[i].alltime += s2ltime;
                }
                else if (!land.empty())
                {
                    Plane now;
                    now = land.front();
                    land.pop();
                    landwaittotal += tik - now.arrivetime;
                    printf("airplane %04d is ready to takeoff on runway %02d\n", now.num, i);
                    way[i].curtime = l2stime;
                    way[i].alltime += l2stime;
                }
            }
        }
        printf("Current Time: %4d\n", tik);
    }
    tik--;
    printf("simulation finished\n");
    printf("simulation time: %4d\n", tik);
    printf("average waiting time of landing: %4.1f\n", (float)airwaittotal / onairtotal);
    printf("average waiting time of takeoff: %4.1f\n", (float)landwaittotal / atlandtotal);
    int all = 0; //总用时
    for (int i = 1; i <= ways; i++)
    {
        printf("runway %02d busy time: %4d\n", i, way[i].alltime);
        all += way[i].alltime;
    }
    printf("runway average busy time percentage: %4.1f%%\n", (float)(((float)all / ways) * 100) / tik);
    return 0;
}