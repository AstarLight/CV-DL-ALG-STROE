
#include<iostream>  
#include <vector>

using namespace std;

int shuffle(vector<int>& vec)
{
    for (int i = vec.size()-1; i > 0; i--)
    {
        int index = rand() % (i+1);
        swap(vec[i], vec[index]);
    }
    return 0;
}


int main()
{
    vector<int> test;
    for (int i = 1; i <= 53; i++)
    {
        test.push_back(i);
    }

    shuffle(test);

    for (int i = 0; i < test.size(); i++)
    {
        cout << test[i] << " ";
        if (i % 10 == 0)
            cout << endl;
    }

    cout << endl;


    system("pause");

    return 0;
}
