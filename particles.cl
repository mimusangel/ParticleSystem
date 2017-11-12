__kernel void particles(__global int *input)
{
	int id = get_global_id(0);
	int result = 0;
	result = input[id] * input[id];
}
