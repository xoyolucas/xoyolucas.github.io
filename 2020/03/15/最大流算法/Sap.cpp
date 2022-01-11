int gap[maxN];       //层次网络中某一层包含节点的个数
int map[maxN][maxN]; //邻接矩阵
int level[maxN];     //层次
int pre[maxN];       //增广路中节点的前一个节点

//m为节点总个数
int sap(int m)
{
    //一开始所有节点的层次设为0
    int result = 0;
    gap[0] = m;
    pre[1] = 1;
    int u = 1, v;
    while (level[1] < m)
    {
        //找可行弧
        for (v = 1; v <= m; v++)
        {
            if (map[u][v] && level[u] == level[v] + 1)
                break;
        }
        //找到了可行弧
        if (v <= m)
        {
            pre[v] = u;
            u = v;
            //找到了一条增广路，做流量调整
            if (v == m)
            {
                int min = 1e8;
                for (int i = v; i != 1; i = pre[i])
                    if (min > map[pre[i]][i])
                        min = map[pre[i]][i];
                result += min;
                for (int i = v; i != 1; i = pre[i])
                {
                    map[pre[i]][i] -= min;
                    map[i][pre[i]] += min;
                }
                u = 1;
            }
        }
        else
        {
            //未找到可行弧，调节层次网络，将当前节点的层次设为周围所有节点层次最小值+1，
            //以确保下一次能找到可行弧
            int minlevel = 1e5;
            for (int i = 1; i <= m; i++)
                if (map[u][i] && minlevel > level[i])
                    minlevel = level[i];
            //gap优化 如果当前这个节点的层次中只包含这个节点，在这个节点的层次做调整后，
            //当前网络就不再包含具有这个层次的节点了，这个时候是一定没办法找到可行流的，
            //因此算法可以终止了。
            gap[level[u]]--;
            if (gap[level[u]] == 0)
                break;
            level[u] = minlevel + 1;
            gap[minlevel + 1]++;
            u = pre[u];
        }
    }
    return result;
}
//原文链接：https://blog.csdn.net/yjr3426619/article/details/82808303