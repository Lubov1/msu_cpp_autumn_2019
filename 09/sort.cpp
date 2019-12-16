#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <string>
#include <cstdlib>
#include <iterator>
#include <queue>
using namespace std;

void func1( int n1, int size_f,int batch_size){
    vector<uint64_t> a(batch_size);
    int ost1;
    int ost2;
    ifstream myfile ("file.bin", ios::binary);
    int n;
    uint64_t c;int last;int size_cur;int ost;
    string name;
    if (n1 == 0){
        size_cur = int(size_f / 2);
        myfile.seekg (0, ios::beg);
    }
    else{
        size_cur = int(size_f / 2) + size_f % 2;
        myfile.seekg ((size_f / 2) * sizeof(uint64_t) - (size_f % 2 + 1) * sizeof(uint64_t), ios::beg);
    }
    n = size_cur / batch_size;
    ost = size_f % ( 2 * batch_size);
    last = size_cur % batch_size;
    if (n1)
        ost2 = last;
    else
        ost1 = last;
    for (int i = 0;i < n;i++) {
        for(int j = 0;j < batch_size;j++)
            myfile.read( (char *) &a[j], sizeof(uint64_t));
        sort(a.begin(),a.end());
        name = to_string(i * n + n1) + ".txt";
        {
            ofstream fileStrmIn (name);
            for (int j = 0; j < batch_size; ++j)
                fileStrmIn << a[j] << ' ';
            fileStrmIn.close();
        }       
    }
    if(last){
        vector<uint64_t> a1(last);
        if (n1)
            myfile.seekg ((batch_size * 2 * n) * sizeof(uint64_t), ios::beg);
        else
            myfile.seekg ((batch_size * 2 * n + (ost - last)) * sizeof(uint64_t), ios::beg);
        for(int j = 0;j < last;j++)
            myfile.read( ( char * ) &a1[j], sizeof(uint64_t));
        sort(a1.begin(),a1.end());
        name = to_string(2 * n + n1) + ".txt";
        {
        ofstream myfile1 (name);
        for (int j = 0; j < last; ++j){
            myfile1 << a1[j] << ' ';
        }
        myfile1.close();  
        } 
    }    
    myfile.close();
}
template <class MinHeap, class OutIt>
void merge(MinHeap& heap, OutIt& out)
{
  while(!heap.empty()) {
    auto range = heap.top(); 
    heap.pop();
    uint64_t n = *range.first++;
    out.write((char *)(&n), sizeof(uint64_t));
    if (range.first != range.second) 
      heap.emplace(range); 
  }
}

int main()
{
    int size_f;
    int batch_size = 5;
    ifstream myfile ("file.bin", ios::binary);//исходный файл
    streampos begin,end;
    begin = myfile.tellg();
    myfile.seekg (0, ios::end);
    end = myfile.tellg();
    size_f = (end-begin) / sizeof(uint64_t);
    int s1 = size_f / 2;
    int s2 = (size_f / 2 ) + size_f % 2;
    int k = int(s1 / batch_size) + int(s2 / batch_size);
    if (s2 % batch_size) k++;
    if (s1 % batch_size) k++;
    thread Thread1(&func1, 0, size_f, batch_size);
    thread Thread2(&func1, 1, size_f, batch_size);
    Thread1.join();
    Thread2.join();
    myfile.close();
    ofstream result("result.bin", ios::binary);
    typedef istream_iterator<int> It;
    vector <ifstream> file (k);
    typedef pair<It, It> Range;
    auto less_first = []( Range lhs,  Range rhs) {
        return *lhs.first > *rhs.first;
    };
    priority_queue<Range, vector<Range>, decltype(less_first)> heap(less_first);
    int c = k - 1;
    for(;c >= 0;c--) {
        file[c].open(to_string(c) + ".txt");
        heap.emplace(It(file[c]), It());
    }
    merge(heap, result);
    for(size_t i = 0; i < k; ++i)
        file[i].close();
    result.close();
    ifstream myfile1 ("file.bin", ios::binary);
    uint64_t s;
    cout<<"исходный файл\n";
    for(int j = 0;j < size_f;j++){
        myfile1.read( ( char * ) &s, sizeof(uint64_t));
        cout << s << ' ';
    }
    cout << "\nрезультат\n";
    ifstream result1 ("result.bin", ios::binary);
    for(int j = 0;j < size_f;j++){
        result1.read( ( char * ) &s, sizeof(uint64_t));
        cout<<s<<' ';
    }
    result1.close();
    myfile1.close();
    return 0;
}
