static float soft_length(float3 vec)
{
	return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

static float3 soft_normalize(float3 vec)
{
	float l = soft_length(vec);
	if (l == 0.0f)
		return (vec);
	return (vec / l);
}

// static float soft_dot(float3 vec_a, float3 vec_b)
// {
// 	return (vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z);
// }
//
// static float3		float3_reflect(const float3 v, const float3 normal)
// {
// 	return (v - (normal * 2.0f * soft_dot(v, normal)));
// }

typedef struct			s_system
{
	float4				gravity;
	float4				mouse;
	int					mode;
}						t_system;

__kernel void particles(global float4 *pos,
	global float4 *vel,
	__constant t_system *sys)
{
	int gid = get_global_id(0);
	float3 grav = (float3)(0, 0, 0);

	grav = soft_normalize(sys->gravity.xyz - pos[gid].xyz);
	vel[gid].z += grav.z * vel[gid].w;
	if (sys->mode == 1)
	{
		float rad = atan2(pos[gid].y - sys->gravity.y, pos[gid].x - sys->gravity.x);
		rad += M_PI * 0.25f;
		float2 next = (float2)(cos(rad), sin(rad));
		vel[gid].x += (next.x + grav.x) * vel[gid].w;
		vel[gid].y += (next.y + grav.y) * vel[gid].w;
	}
	else
	{
		vel[gid].x += grav.x * vel[gid].w;
		vel[gid].y += grav.y * vel[gid].w;
	}

	pos[gid].x = pos[gid].x + vel[gid].x;
	pos[gid].y = pos[gid].y + vel[gid].y;
	pos[gid].z = pos[gid].z + vel[gid].z;

	float len = soft_length(sys->gravity.xyz - pos[gid].xyz);
	if (len >= 1.0)
	{
		if (grav.x > 0 && vel[gid].x < 0)
			vel[gid].x *= 0.95f;
		if (grav.x < 0 && vel[gid].x > 0)
			vel[gid].x *= 0.95f;
		if (grav.y > 0 && vel[gid].y < 0)
			vel[gid].y *= 0.95f;
		if (grav.y < 0 && vel[gid].y > 0)
			vel[gid].y *= 0.95f;
		if (grav.z > 0 && vel[gid].z < 0)
			vel[gid].z *= 0.95f;
		if (grav.z < 0 && vel[gid].z > 0)
			vel[gid].z *= 0.95f;
	}

	// if (pos[gid].x > 1.0)
	// {
	// 	pos[gid].x = 1.0;
	// }
	// if (pos[gid].x < -1.0)
	// {
	// 	pos[gid].x = -1.0;
	// }
	// if (pos[gid].y > 1.0)
	// {
	// 	pos[gid].y = 1.0;
	// }
	// if (pos[gid].y < -1.0)
	// {
	// 	pos[gid].y = -1.0;
	// }
	// if (pos[gid].z > 1.0)
	// {
	// 	pos[gid].z = 1.0;
	// }
	// if (pos[gid].z < -1.0)
	// {
	// 	pos[gid].z = -1.0;
	// }
}
