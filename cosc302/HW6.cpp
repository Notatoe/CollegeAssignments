//Noah Morris
//HW6

template <typename T>
void randperm(vector<T> &v) 
{
	for(int i = 0; i < (int)v.size() - 1; i++)
	{
		swap(v[i], v[rand() % ((int)v.size() - 1 - i) + i]);
	}
}
