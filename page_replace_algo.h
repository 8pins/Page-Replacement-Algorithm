#include <vector>
#include <string>
#include <iostream>
void print_queue(std::vector<int> q)
{
	for (unsigned int i = 0; i < q.size(); i++)
	{
		std::cout << q[i] << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}
bool check_queue(int n, std::vector <int> a, int& pos)
{
	/// kiem tra page_table neu co thi tra ve true
	/// va vi tri, khong co tra ve false
	/// va vi tri -1( khong co trong page_table);
	/// ;
	/// 

	pos = -1;
	if (a.size() == 0)
	{
		pos = -1;
		return false;
	}
	for (size_t i = 0; i < a.size(); i++)
	{
		if (n == a[i])
		{
			pos = i;
			return true;
		}
	}
	return false;
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
		return res;
	}

	for (unsigned int i = 0; i < ref_string.size(); i++)
	{
		int pivot = 0;
		if (a.size() < unsigned int(queue_length))
		{
			if (check_queue(ref_string[i], a, pivot) == false)
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
			if (check_queue(ref_string[i], a, pivot) == false)
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
	res[1] = double(total_hit) / ref_string.size();
	res[2] = double(page_fault) / ref_string.size();
	return res;
}
std::vector<double> optimal_replacement(std::vector<int> ref_string, int queue_length)
{
	int page_fault = 0;
	int total_hit = 0;
	std::vector<std::vector<int>> a;


	std::vector<double> res(3);
	if (ref_string.size() == 0)
	{
		return res;
	}
	a.push_back(std::vector<int> {ref_string[0], 0});

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

std::vector<double> lru_replacement(std::vector<int> ref_string, int queue_length)
{
	std::vector<double> res(3);
	int page_fault = 0;
	int page_hit = 0;
	/// su dung page_frame de chua cac page
	/// khi mot page duoc tem vao thi dua no xuong cuoi
	/// neu nhu phai thay the se thay the page dau tien
	/// 
	/// 
	/// 
	/// 
	std::vector<int> page_frame;
	for (unsigned int i = 0; i < ref_string.size(); i++)
	{
		print_queue(page_frame);
		int pivot = 0;
		if (page_frame.size() < unsigned int(queue_length))
		{
			if (check_queue(ref_string[i], page_frame, pivot) == false)
			{
				page_frame.push_back(ref_string[i]);
				page_fault++;
			}
			else
			{
				page_frame.erase(page_frame.begin() + pivot);
				page_frame.push_back(ref_string[i]);
				page_hit++;
			}
		}
		else
		{
			if (check_queue(ref_string[i], page_frame, pivot) == false)
			{
				page_frame.erase(page_frame.begin());
				page_frame.push_back(ref_string[i]);
				page_fault++;
			}
			else
			{
				page_frame.erase(page_frame.begin() + pivot);
				page_frame.push_back(ref_string[i]);
				page_hit++;
			}
		}
	}
	res[0] = page_fault;
	res[1] = double(page_hit) / ref_string.size();
	res[2] = double(page_fault) / ref_string.size();
	return res;
}#pragma once
