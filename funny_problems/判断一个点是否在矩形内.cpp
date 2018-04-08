//对于一个点是否在矩形内的判断。
//只需要判断该点是否在上下两条边和左右两条边之间就行，判断一个点是否在两条线段之间夹着，就转化成，
//判断一个点是否在某条线段的一边上，就可以利用叉乘的方向性，来判断夹角是否超过了180度 如下图：
//只要判断(p1 p2 X p1 p ) * (p3 p4 X p3 p1)  >= 0 就说明p在p1p2,p3p4中间夹着，同理计算另两边就可以了

// 计算 |p1 p2| X |p1 p|
float get_cross(const Point& p1, const Point& p2, const Point& p) 
{
    float cross = (p2.x - p1.x) * (p.y - p1.y) - (p.x - p1.x) * (p2.y - p1.y);
    return cross;
}

bool Rect::is_point_in(const Point& p) const 
{
    bool inbox = get_cross(p1, p2, p) * get_cross(p3, p4, p) >= 0 && get_cross(p2, p3, p) * get_cross(p4, p1, p) >= 0;
    return inbox;
}
