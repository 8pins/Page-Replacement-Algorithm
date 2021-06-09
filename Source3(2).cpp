#include <iostream>
#include <string>
#include <fstream>
#include <vector>
void swap(int& a, int& b)
{
	int tmp = a;
	a = b;
	b = tmp;
}
bool check_arr(int val, int* arr, int length,int& pos)
{
	pos = -1;

	
	if (length == 0)
	{
		return false;
	}
	for (int i = 0; i < length ; i++)
	{
		if (arr[i] == val)
		{
			pos = i;
			return true;
		}
	}
	return false;
}


class Virtual_mem_manager 
{
	
public:
	
	Virtual_mem_manager();
	Virtual_mem_manager(const std::string Backing_file_name, const std::string Address_file_name, bool FIFO );
	std::vector<int> Translate_address();
	~Virtual_mem_manager();


private:
	
	int* TLB_frame_number;
	char** Physic_memory;
	int* TLB_page_number;
	int* Page_table;
	bool* Reference_bits;
	std::fstream Backing_store_file;
	std::fstream Address_File;
	bool FIFO;
};

Virtual_mem_manager::Virtual_mem_manager()
{
}
Virtual_mem_manager::Virtual_mem_manager(const std::string Backing_file_name, const std::string Address_file_name, bool FIFO = true)
{
	this->TLB_page_number = new(std::nothrow) int[16];
	this->TLB_frame_number = new(std::nothrow) int[16];

	for (int i = 0; i < 16; i++)
	{
		this->TLB_page_number[i] = -1;
		this->TLB_frame_number[i] = -1;
	}
	
	this->Physic_memory = new(std::nothrow) char*[256];
	for (int i = 0; i < 256; i++)
	{
		this->Physic_memory[i] = new (std::nothrow) char[256];
	}
	this->Backing_store_file.open(Backing_file_name, std::ios::in | std::ios::out | std::ios::binary);
	this->Address_File.open(Address_file_name);
	this->Page_table = new(std::nothrow) int[256];
	

		this->Page_table = new(std::nothrow) int[256];


		for (int j = 0; j < 256; j++)
		{
			this->Page_table[j] = -1;
		}
	
	this->Reference_bits = new(std::nothrow) bool[256];
	this->FIFO = FIFO;
}
Virtual_mem_manager::~Virtual_mem_manager()
{
	for (int i = 0; i < 256; i++)
	{
		delete[] this->Physic_memory[i];
	}
	delete[] this->Physic_memory;
	delete[] this->TLB_frame_number;
	delete[] this->TLB_page_number;
	delete[] this->Page_table;
	delete[] this->Reference_bits;
	this->Backing_store_file.close();
	this->Address_File.close();
}
std::vector<int> Virtual_mem_manager::Translate_address()
{
	// dau ra tra ve 1 vector
	// phan tu 1 tra ve so TLB hit
	// phan tu thu 2 tra ve page hit
	// 	   phan tu thu 3 tra ve so loi trang
	// phan tu thu 4 tra ve tong so dia chi
	std::vector <int>res{ 0,0,0,0 };
	int flag = 0;
	if (!this->Backing_store_file.is_open() ||!this->Address_File.is_open())
	{
		
		std::cout << "loi mo File";
		return res;
	}
	
	std::string line;
	int t1 = 0;
	int a = 0;
	int t2 = 0;
	while (std::getline(this->Address_File,line))
	{

		res[3]++;
		
	
		
		// thuc hien viec dich dia chi
		int Page_no = std::stoi(line);
		int pos;
		int frame;
		int Page_offset = Page_no & 255;
		Page_no = (Page_no & 65280) >> 8;
		
		
		
		

		// check TLB
		
		if (check_arr(Page_no, this->TLB_page_number, 16,pos)== true)
		{
			//TLB hit 
			res[0]++;
			if (this->FIFO == false)
			{
				// thuc hien thay the bang LRU, phan tu 
				// cuoi cua TLB se bi day ra ngoai
				// neu nhu xay ra loi trang
				int tmp = this->TLB_page_number[0];
				for (int i = 1; i < pos+1; i++)
				{
					swap(tmp, this->TLB_page_number[i]);
				}
				this->TLB_page_number[0] = Page_no;
			}
		}

		// TLB miss
		// thuc hien tra bang Page_table
		else 
		{
			
			if (check_arr(Page_no, this->Page_table,256, pos) == true)
			{
				
				
			}
			// xay ra loi trang
			else
			{
				if (check_arr(-1, this->Page_table,256, pos) == true)
				{
					
					this->Page_table[pos] = Page_no;
				}
				
				res[2]++;
				
				char* s = new char[256];
				//xu ly loi trang
				//tim trang o backing store
				this->Backing_store_file.seekg(Page_no * 256, std::ios::beg);
				this->Backing_store_file.read(s, 256);
				
				
				//std::cout << int(s[Page_offset]) << std::endl;
				delete[] s;
				// cap nhat page trong TLB va Page table
				// cap nhat bang FIFO
				if (this->FIFO == true)
				{
					this->TLB_page_number[t1] = Page_no;
					t1++;
					t1 = t1 % 16;
				}
				else
				{
					//cap nhat dung LRU
					// day phan tu it dung nhat ra khoi hang doi
					int tmp = this->TLB_page_number[0];
					for (int i = 1; i < 16; i++)
					{
						swap(tmp, this->TLB_page_number[i]);
					}
					this->TLB_page_number[0] = Page_no;

				}
				
		
			
				
			}
		
		
		
		
			
			
		}
		
		a++;
	}
	
	return res;

}

int main()
{
	
	std::string s1("BACKING_STORE.bin");
	std::string s2("addresses.txt");
	/*std::fstream file1;
	file1.open(s1, std::ios::in | std::ios::out | std::ios::binary);
	std::fstream file2;
	file2.open(s2);
	if (file1.is_open() && file2.is_open())
	{
		std::string line;
		while (std::getline(file2, line));
		{
			int page_no = std::stoi(line);
			std::cout << "loi";
			int offset = page_no & 255;
			page_no = (page_no & 65280) >> 8;
			char* s = new char[256];
			
			file1.seekg(page_no*256, std::ios::beg);
			
			file1.read(s, 256);
			std::cout << int(s[offset]) << std::endl;
			delete[] s;
		}
	}
	file1.close();
	file2.close();*/
	int count = 0;
	bool FIFO = false;
	Virtual_mem_manager vmm(s1, s2,FIFO );
	std::vector<int> v =vmm.Translate_address();
	
	
	
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v[i] << std::endl;
	}
	return 0;
}