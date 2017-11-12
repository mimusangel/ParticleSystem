__kernel void particles(global float4 *pos)
{
	int gid = get_global_id(0);
	float4 p = (float4)(pos[gid].x * -0.0124 + pos[gid].y * (gid + 1) * -0.00142, pos[gid].y * -0.0124 + pos[gid].x * (gid + 1) * -0.00142, 0.0, 1.0);
	pos[gid] = pos[gid] + p;
}
