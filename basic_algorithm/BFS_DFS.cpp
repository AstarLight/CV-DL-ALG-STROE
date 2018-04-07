/** 
 * 广度优先搜索 
 * @param Vs 起点 
 * @param Vd 终点 
 */  
bool BFS(Node& Vs, Node& Vd)
{  
    queue<Node> Q;  
    Node Vn, Vw;  
    int i;  

    //初始状态将起点放进队列Q  
    Q.push(Vs);  
    hash(Vw) = true;//设置节点已经访问过了！  

    while (!Q.empty())
    {
        //队列不为空，继续搜索！  
        //取出队列的头Vn  
        Vn = Q.front();  

        //从队列中移除  
        Q.pop();  

        while(Vw = Vn)  //通过某规则能够到达的节点
        {  
            if (Vw == Vd){//找到终点了！  
                //把路径记录，这里没给出解法  
                return true;//返回  
            }  

            if (isValid(Vw) && !visit[Vw])
            {  
                //Vw是一个合法的节点并且为白色节点  
                Q.push(Vw);//加入队列Q  
                hash(Vw) = true;//设置节点颜色  
            }  
        }  
    }  
    return false;//无解  
}  


/** 
 * DFS核心伪代码 
 * 前置条件是visit数组全部设置成false 
 * @param n 当前开始搜索的节点 
 * @param d 当前到达的深度 
 * @return 是否有解 
 */  
bool DFS(Node n, int d)
{  
    if (isEnd(n, d))
    {
        //一旦搜索深度到达一个结束状态，就返回true  
        return true;  
    }  

    for (Node nextNode in n)
    {
        //遍历n相邻的节点nextNode  
        if (!visit[nextNode])
        { 
            visit[nextNode] = true;//在下一步搜索中，nextNode不能再次出现  
            if (DFS(nextNode, d+1))
            {
                //如果搜索出有解  
                //做些其他事情，例如记录结果深度等  
                return true;  
            }  

            //重新设置成false，因为它有可能出现在下一次搜索的别的路径中  
            visit[nextNode] = false;  
        }  
    }  
    return false;//本次搜索无解  
}  
