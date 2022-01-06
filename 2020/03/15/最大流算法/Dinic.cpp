//构建层次网络
void bfs()
{
    memset(visit, false, sizeof(visit));
    memset(dist, 0, sizeof(dist));
    queue<int> vertQue;
    vertQue.push(1);
    dist[1] = 0;
    visit[1] = true;
    while (!vertQue.empty())
    {
        int vTop = vertQue.front();
        vertQue.pop();
        for (int i = head[vTop]; i != -1; i = Edges[i].next)
        {
            //目标节点还未被确立层次，并且可以到达目标节点，就进行层次更新
            if (Edges[i].capacity && !visit[Edges[i].to])
            {
                dist[Edges[i].to] = dist[vTop] + 1;
                visit[Edges[i].to] = true;
                vertQue.push(Edges[i].to);
            }
        }
    }
}
//dfs查找所有增广路并做流量调整
int dfs(int end, int u, int delta)
{
    if (u == end)
        return delta;
    int res = 0;
    for (int i = head[u]; i != -1; i = Edges[i].next)
    {
        if (dist[Edges[i].to] == dist[u] + 1)
        {
            int dd = dfs(end, Edges[i].to, min(Edges[i].capacity, delta));
            Edges[i].capacity -= dd;     //前向弧流量增加(capacity为可调整流量)
            Edges[i ^ 1].capacity += dd; //反向弧流量减少
            delta -= dd;
            res += dd;
        }
    }
    return res;
}

int dinic(int end)
{
    int ret = 0;
    while (true)
    {
        bfs();
        if (!visit[end])
        {
            return ret;
        }
        ret += dfs(end, 1, 1e8);
    }
    return ret;
}