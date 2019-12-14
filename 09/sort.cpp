#include <iostream>
#include <fstream>
#include <vector>

#include <thread>
#include <string>
#include <cstdlib>
#include <iterator>
#include <queue>
using namespace std;
int size_f;
int batch_size = 1024 * 1024;
int n;

vector <string> f(1);
void func1(int n1){
    int ost1;
    int ost2;
    ifstream myfile ("file.bin", ios::binary);
    uint64_t *a = new uint64_t[batch_size];
    uint64_t c;int last;int size_cur;int ost;
    string name;
    if (n == 0){
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
    if (n)
        ost2 = last;
    else
        ost1 = last;
    for (int i = 0;i < n;i++) {
        for(int j = 0;j < batch_size;j++){
            myfile.read( (char *) &c, sizeof(uint64_t));
            a[j] = c;
        }
        std::qsort(a, batch_size, sizeof *a, [](const void* a, const void* b)
        {
            uint64_t arg1 = *static_cast<const uint64_t*>(a);
            uint64_t arg2 = *static_cast<const uint64_t*>(b);
            if(arg1 < arg2) return -1;
            if(arg1 > arg2) return 1;
            return 0;
        });
        name=to_string(i * n + n1) + ".txt";
        f.push_back(name);
        {
            ofstream fileStrmIn (name);
            for (int j = 0; j < batch_size; ++j)
                fileStrmIn << a[j] << ' ';
            fileStrmIn.close();
        }       
    }
    if(last){
        uint64_t *a1 = new uint64_t[last];
        if (n1)
            myfile.seekg ((batch_size * 2 * n) * sizeof(uint64_t), ios::beg);
        else
            myfile.seekg ((batch_size * 2 * n + (ost - last)) * sizeof(uint64_t), ios::beg);
        for(int j = 0;j < last;j++){
            myfile.read( ( char * ) &c, sizeof(uint64_t));
            a1[j] = c;
        }
        std::qsort(a1, last, sizeof *a1, [](const void* a, const void* b)
        {
            uint64_t arg1 = *static_cast<const uint64_t*>(a);
            uint64_t arg2 = *static_cast<const uint64_t*>(b);
            if(arg1 < arg2) return -1;
            if(arg1 > arg2) return 1;
            return 0;
        });
        int k = 2 * n + n1;
        name=to_string(k) + ".txt";
        f.push_back(name);

        {
        ofstream myfile1 (name);

        for (int j = 0; j < last; ++j){
            myfile1 << a1[j] << ' ';
        }
        myfile1.close();  
        } 
        delete[] a1;
    }    
    delete[] a;
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
    ifstream myfile ("file.bin", ios::binary);//исходный файл

    streampos begin,end;
    begin = myfile.tellg();
    myfile.seekg (0, ios::end);
    end = myfile.tellg();
    size_f = (end-begin) / sizeof(uint64_t);
    thread Thread1(&func1, 0);
    thread Thread2(&func1, 1);
    Thread1.join();
    Thread2.join();
    myfile.close();
    ofstream result("result.bin", ios::binary);
    typedef istream_iterator<int> It;
    vector <ifstream> file (f.size());
    typedef pair<It, It> Range;
    auto less_first = []( Range lhs,  Range rhs) {
        return *lhs.first > *rhs.first;
    };
    priority_queue<Range, vector<Range>, decltype(less_first)> heap(less_first);
    int c = f.size() - 1;
    for(;c > 0;c--) {
        file[c].open(f[c]);
        heap.emplace(It(file[c]), It());
    }
    merge(heap, result);
    for(size_t i = 0; i < f.size(); ++i)
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
