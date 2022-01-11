struct Vert
{
    int ef;   //盈余
    int x;    //节点编号
    int dist; //节点层次
    Vert(){};
    inline bool operator<(const Vert &v) const
    {
        return this->dist < v.dist;
    }
} Verts[maxN];

//出现断层时，将所有高于该层的节点的层次都设为 源点层次+1，好让它们流回到源点
//因为由于断层这些节点再也没办法将流量流到汇点了
void Ga(int m, int d)
{
    for (int i = 1; i <= m; i++)
        if (i != 1 && i != m && Verts[i].dist > d && Verts[i].dist <= m)
            Verts[i].dist = m + 1;
}

//推进流量 如果推进了0流量 就返回false 表示实际上并不可以推进流量
bool pushFlow(int from, int to, int edge)
{
    int w = min(Verts[from].ef, Edges[edge].capacity);
    Edges[edge].capacity -= w;
    Edges[edge ^ 1].capacity += w;
    Verts[from].ef -= w;
    Verts[to].ef += w;
    return w;
}

int preMaxFlow(int t)
{
    memset(Verts, 0, sizeof(Verts));
    for (int i = 1; i <= t; i++)
        Verts[i].x = i;
    priority_queue<Vert> vertQue;
    Verts[1].dist = t;
    Verts[1].x = 1;
    Verts[1].ef = 1e8;
    vertQue.push(Verts[1]);
    Gap[Verts[1].dist] = 1;
    Gap[0] = t - 1;
    while (!vertQue.empty())
    {
        Vert topV = vertQue.top();
        vertQue.pop();
        if (!Verts[topV.x].ef)
            continue;
        for (int i = head[topV.x]; i != -1; i = Edges[i].next)
        {
            int v = Edges[i].to;
            //源点直接推流量出去  其余情况只在相邻层推流量
            if ((topV.x == 1 || (Verts[topV.x].dist == Verts[v].dist + 1)) &&
                pushFlow(topV.x, v, i) && v != 1 && v != t)
            {
                vertQue.push(Verts[v]);
            }
        }
        //仍有流量但没推出去，就将当前节点的层次抬高，以让其尽可能流出
        if (Verts[topV.x].ef && topV.x != 1 && topV.x != t)
        {
            if (!--Gap[Verts[topV.x].dist])
                Ga(t, Verts[topV.x].dist);
            ++Gap[++Verts[topV.x].dist];
            vertQue.push(Verts[topV.x]);
        }
    }
    return Verts[t].ef;
}
//原文链接：https://blog.csdn.net/yjr3426619/article/details/82808303