__kernel void particles(global float4 *pos)
{
	int gid = get_global_id(0);
	float2 vel = (float2)(0.0, 0.0);
	pos[gid].x = pos[gid].x + vel.x;
	pos[gid].y = pos[gid].y + vel.y;
}
