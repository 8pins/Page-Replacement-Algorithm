#include <iostream>
#include <vector>
#include<string>
#include <fstream>
void print_queue(std::vector<int> q)
{
	for(unsigned int i = 0; i < q.size(); i++)
	{
		std::cout << q[i] << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

bool check_queue(int n, std::vector <int> a)
{
	if (a.size() == 0)
	{
		return false;
	}
	for (size_t i = 0; i < a.size(); i++)
	{
		if (n == a[i])
		{
			return true;
		}
	}
	return false;
}
std::vector<double> fifo_replacement(std::vector<int> ref_string, int queue_length)
{
	std::vector<double> res(3);
	int page_fault = 0;
	int total_hit = 0;
	std::vector <int> a;
	std::vector <int> page_year(queue_length);
	if (ref_string.size() == 0)
	{
		
		res;
	}
	a.push_back(ref_string[0]);
	page_fault++;
	for (unsigned int i = 1; i < ref_string.size(); i++)
	{
		if (a.size() < unsigned int(queue_length))
		{
			if (check_queue(ref_string[i], a) == false)
			{
				a.push_back(ref_string[i]);
				page_fault++;
				
			}
			else
			{
				total_hit++;
			}
		}
		else
		{
			if (check_queue(ref_string[i], a) == false)
			{
				a.erase(a.begin());
				a.push_back(ref_string[i]);
				page_fault++;
			}
			else
			{
				total_hit++;
			}
		}
	}
	res[0] = page_fault;
	res[1] = double(total_hit) /ref_string.size();
	res[2] = double(page_fault)/ ref_string.size();
	return res;
}
std::vector<double> optimal_replacement(std::vector<int> ref_string, int queue_length )
{
	int page_fault = 0;
	int total_hit = 0;
	std::vector<std::vector<int>> a;
	
	
	std::vector<double> res(3);
	if (ref_string.size() == 0)
	{
		return res;
	}
	a.push_back(std::vector<int> {ref_string[0],0});
	
	for (unsigned int i = 1; i < ref_string.size(); i++)
	{
		bool new_val = true;
		for (unsigned int j = 0; j < a.size(); j++)
		{
			if (ref_string[i] == a[j][0])
			{
				a[j].push_back(i);
				new_val = false;
				break;
			}

		}
		if (new_val == true)
		{
			std::vector<int> tmp1;
			tmp1.push_back(ref_string[i]);
			tmp1.push_back(i);
			a.push_back(tmp1);
		}
	}
	
	
	
	
	std::vector<int> my_queue;
	for (unsigned int i = 0; i < ref_string.size(); i++)

	{
		for (unsigned int i = 0; i < a.size(); i++)
		{
			for (unsigned int j = 0; j < a[i].size(); j++)
			{
				std::cout << a[i][j] << "  ";
			}
			std::cout << std::endl;
		}
		

	
		if (my_queue.size() < unsigned int(queue_length))
		{
			if (check_queue(ref_string[i], my_queue) == false)
			{
				page_fault++;
				my_queue.push_back(ref_string[i]);
				for (unsigned int j = 0; j < a.size(); j++)
				{
					if (ref_string[i] == a[j][0])
					{
						a[j].erase(a[j].begin() + 1);
					}
				}
			}
			else
			{
				total_hit++;
				for (unsigned int j = 0; j < a.size(); j++)
				{
					if (ref_string[i] == a[j][0])
					{
						a[j].erase(a[j].begin() + 1);
						break;
					}
				}
				
			}
		}
		else
		{
			if (check_queue(ref_string[i], my_queue) == true)
			{
				total_hit++;
				for (unsigned int j = 0; j < a.size(); j++)
				{
					if (ref_string[i] == a[j][0])
					{
						a[j].erase(a[j].begin() + 1);
						break;
					}
				}
			}
			else
			{
				page_fault++;
				int max = 0;
				int queue_pivot = 0;
				int a_pivot = 0;
				for (unsigned int j = 0; j < my_queue.size(); j++)

				{
					for (unsigned int k = 0; k < a.size(); k++)
					{
						if (my_queue[j] == a[k][0])
						{
							if (a[k].size() == 1)
							{
								queue_pivot = j;
								a_pivot = k;
								max = 9999999;
								
							}
							else
							{
								if (max < a[k][1])
								{
									max = a[k][1];
									queue_pivot = j;
									a_pivot = k;
									
								}
							}
							
						}
					}
				}
				my_queue.erase(my_queue.begin() + queue_pivot);
				my_queue.push_back(ref_string[i]);
	
				for (unsigned int j = 0; j < a.size(); j++)
				{
					if (ref_string[i] == a[j][0])
					{
						a[j].erase(a[j].begin() + 1);
						break;
					}
				}
				
			}
		}
	}
	res[0] = page_fault;
	res[1] = double(total_hit) / ref_string.size();
	res[2] = double(page_fault) / ref_string.size();
	return res;
}




int main()
{
	
	const std::string str("C:\\Users\\Admin\\Downloads\\addresses.txt");
	const std::string out_put_fifo_name("output_fifo.txt");
	const std::string out_put_opt_name("output_opt.txt");
	
	std::ifstream f(str);
	std::string line;
	std::vector<int> v;
	int mask = 255;
	if (f.is_open())
	{
		while (std::getline(f,line))
		{
			int tmp= std::stoi(line);
			tmp >> 8;
			tmp = tmp & mask;
			v.push_back(tmp);

		}
		f.close();
	}
	std::ofstream out_put_fifo(out_put_fifo_name);
	std::ofstream out_put_opt(out_put_opt_name);
	if (out_put_fifo.is_open())
	{
		out_put_fifo << "frame_size,page_fault,hit_rate,miss_rate" << std::endl;

		for (int i = 10; i < 1000; i++)
		{
			std::vector<double> res = fifo_replacement(v, i);
			out_put_fifo << std::to_string(i) << "," << std::to_string(res[0]) << "," << std::to_string(res[1]) << "," << std::to_string(res[2])<<std::endl;
		}
	}
	out_put_fifo.close();

	if (out_put_opt.is_open())
	{
		out_put_opt << "frame_size,page_fault,hit_rate,miss_rate" << std::endl;
		for (int i = 10; i < 1000; i++)
		{
			std::vector<double> res = fifo_replacement(v, i);
			out_put_opt << std::to_string(i) <<","<<std::to_string(res[0]) << "," << std::to_string(res[1]) << "," << std::to_string(res[2]) << std::endl;
		}
	}
	out_put_opt.close();
	return 0;
}