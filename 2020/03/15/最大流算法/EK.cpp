int EK(int m)
{
	//初始化操作
	int result = 0;
	for (int i = 1; i <= m; i++)
		parent[i] = alpha[i] = 0;
	queue<int> vertexQueue;
	while (true)
	{
		memset(alpha, 0, sizeof(alpha));
		alpha[1] = INF;
		vertexQueue.push(1);
		//BFS过程
		while (!vertexQueue.empty())
		{
			int vtop = vertexQueue.front();
			vertexQueue.pop();
			for (int i = 1 ;  i <= m ; i ++ )
			{
				//如果目标节点还未在增广路中出现并且可以调整流量
				if (!alpha[i] && flow[vtop][i] < capacity[vtop][i])
				{
					parent[i] = vtop;
					alpha[i] = min(capacity[vtop][i] - flow[vtop][i], alpha[vtop]);
					vertexQueue.push(i);
				}
			}
		}
		//汇点可调整流量为0，说明没有增广路了，算法结束
		if (alpha[m] == 0)
		{
			return result;
		}
		//汇点可调整流量不为0，那么找到了增广路，增广路上所有节点做流量调整
		for (int i = m; i != 1; i = parent[i])
		{
			flow[parent[i]][i] += alpha[m];//前向弧流量增加
			flow[i][parent[i]] -= alpha[m];//后向弧流量减少
		}
		//由于一开始流量都为0，调整多少能量就代表整个可行流的流量增加了多少
		result += alpha[m];
	}
}