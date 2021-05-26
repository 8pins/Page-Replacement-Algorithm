#include<iostream>
using namespace std;
#include <vector>
int main()
{
    int nopages, nofaults,  i;
    int tmp;
    std::vector<int> page;
    int count = 0;
    cout << "\n\t nhap so trang muon tinh loi trang : > ";
    cin >> nopages;  
    cout << "\n\t nhap vao Reference String : ";
    for (i = 0; i < nopages; i++)
    {
        cout << "\t";
        cin >> tmp;
        page.push_back(tmp);
    }
    cout << "\n\t nhap vao so luong frame cua kho chua : ";
    cin >> nofaults;
    std::vector<int> frame(nofaults);
    std::vector<int> fcount(nofaults);
    for (i = 0; i < nofaults; i++)
    {
        frame[i] = -1;
        fcount[i] = 0; 
    }
    i = 0;
    while (i < nopages)
    {
        int j = 0, flag = 0;
        while (j < nofaults)
        {
            if (page[i] == frame[j])
            {  
                flag = 1;
                fcount[j] = i + 1;
            }
            j++;
        }
        j = 0;
        cout << "\n\t * **\n";
        cout << "\t" << page[i] << "– > ";
        if (flag == 0)
        {
            int min = 0, k = 0;
            while (k < nofaults - 1)
            {
                if (fcount[min] > fcount[k + 1]) 
                    min = k + 1;
                k++;
            }
            frame[min] = page[i];
            fcount[min] = i + 1;  
            count++;           
            while (j < nofaults)
            {
                cout << "\t | " << frame[j] << " | ";
                j++;
            }
        }
        i++;
    }
    cout << "\n\t * **\n";
    cout << "\n\t Page Fault : " << count;
    return 0;
}