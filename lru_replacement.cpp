#include <iostream>
#include <vector>
bool check_queue(int n, std::vector <int> a, int& pos)
{
	/// kiem tra page_table neu co thi tra ve true
	/// va vi tri, khong co tra ve false
	/// va vi tri -1( khong co trong page_table)
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
}