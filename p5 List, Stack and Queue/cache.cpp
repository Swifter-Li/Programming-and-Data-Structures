#include "dlist.h"
#include <iostream>
#include <sstream>
using namespace std;

struct block
{
    int address; // its address in memory
    int data;
};
class except{};
class unknown {};
class toomany {};
class notenough {};
class exited {};
class LRUCache
{
private:
    int mem_size; // size of memory
    int *memory;

    Dlist<block> cache;
    int cur_cache_size; // current length of `cache`
    int max_cache_size; // maximum length of `cache`
    static bool compare(const block *a, const block *b);
    // EFFECTS: returns true if two blocks have the same address
public:
    LRUCache(int cache_size, int memory_size);
    // constructor
    // Initialize `cur_cache_size`, `max_cache_size`, `memory`
    // Initialize all elements in `memory` to 0
    ~LRUCache();
    // destructor
    int read(int address);
    // EFFECTS: returns data corresponding to address,
    // 0 <= address < mem_size;
    // if address is out of bound, throws an exception
    //
    // if hit,
    //   removes this block and insert it to the front;
    //   returns `data`;
    // if miss,
    //    if `cur_cache_size` equals to `max_cache_size`,
    //      removes the last (least recently used) block
    //     in the `cache`;
    //    writes data in the last block
    //    to the corresponding address in `memory`;
    //    if `cur_cache_size` < `max_cache_size`,
    //      increment `cur_cache_size` by 1;
    //    reads `data` of `address` from `memory`,
    //    inserts the block with `address` and `data`
    //    to the front of `cache`;
    //   returns `data`
    void write(int address, int data);
    // EFFECTS: writes data to address, 0 <= address < mem_size
    // if address is out of bound, throws an exception
    //
    // if hit,
    //   removes this block from list,
    //   writes `data` to this block,
    //   and inserts this block to the front;
    // if miss,
    //    if `cur_cache_size` equals to `max_cache_size`,
    //    removes the last (least recently used) block
    //    in the `cache`;
    //    writes data in the last block
    //    to the corresponding address in `memory`;
    // if `cur_cache_size` < `max_cache_size`,
    // increment `cur_cache_size` by 1;
    // inserts the block with `address` and `data`
    // to the front of `cache`
    void printCache();
    // EFFECTS: prints the cache in given format
    void printMem();
    // EFFECTS: prints the memory in given format
};

LRUCache::LRUCache(int cache_size, int memory_size):cache()
{
    this->mem_size=memory_size;
    this->max_cache_size=cache_size;
    this->cur_cache_size=0;
    memory=new int[mem_size];
    for (int i=0;i<mem_size;i++)
    {
        memory[i]=0;
    }
}

LRUCache::~LRUCache()
{
    delete[] memory;
}
void LRUCache::printCache()
{
    Dlist<block> copy(cache);
    block* p;
    while (!copy.isEmpty())
    {
        p=copy.removeFront();
        cout<<p->address<<" "<<p->data<<endl;
        delete p;
    }
}

void LRUCache::printMem()
{
    for (int i=0; i<mem_size; i++)
    {
        cout<<memory[i]<< " ";
    }
    cout<<endl;
}

bool LRUCache::compare(const block *a, const block *b)
{
    if (a==nullptr||b==nullptr) return false;
    if(a->address==b->address) return 1;
    else return 0;
}

int LRUCache::read(int address)
{
    if (address<0||address>=mem_size) throw except();
    block temp={address,0};
    block *np=this->cache.remove(compare, &temp);
    if (np!=nullptr)
    {
        this->cache.insertFront(np);
        return np->data;
    }
    if (cur_cache_size == max_cache_size)
    {
        this->cur_cache_size--;
        block *p=this->cache.removeBack();
        memory[p->address]=p->data;
        delete p;
    }
    if (cur_cache_size<max_cache_size)
    {                
        this->cur_cache_size++;
        np = new block({address, memory[address]});
        this->cache.insertFront(np);
        return np->data;
    }
    return 0;
}

void LRUCache::write(int address, int data)
{
    if (address<0||address>=mem_size) throw except();
    block p={address,data};
    block *np = this->cache.remove(compare, &p);
    if (np!=nullptr)
    {
        np->data = data;
        this->cache.insertFront(np);
        return;
    }
    else 
    {
    if (cur_cache_size==max_cache_size)
        {
            this->cur_cache_size--;
            block *a=cache.removeBack();
            memory[a->address]=a->data;
            delete a;
        }
    if (cur_cache_size<max_cache_size)
    {
        this->cur_cache_size++;
        np=new block({address, data});
        this->cache.insertFront(np);
    }
    }
}
int numofword(const string&line)
{
    int index=0; 
    int num=0;
    while(line.find(' ',index)!=string::npos)
    {
        num++;
        index=line.find(' ',index)+1;
    }
    num++;
    return num;
}
void server(const string &line, LRUCache &mod)
{
    stringstream read(line);
    string command;
    read>>command;
    if (command=="EXIT") 
    {
        throw exited();
        return;
    }
    else 
    {
        if (command=="READ")
        {
            if(numofword(line)>2) throw toomany();
            else if (numofword(line)<2) throw notenough();
            else 
            {
                int num;
                read>>num;
                cout<<mod.read(num)<<endl;
            }
        }
        else if (command=="WRITE")
        {
            if(numofword(line)>3) throw toomany();
            else if (numofword(line)<3) throw notenough();
            else 
            {
                int address,answer;
                read>>address>>answer;
                mod.write(address,answer);
            }
        }
        else if (command=="PRINTCACHE")
        {
            if (numofword(line)!=1) throw toomany();
            else mod.printCache();
        }
        else if (command=="PRINTMEM")
        {
            if (numofword(line)!=1) throw toomany();
            else mod.printMem();
        }
        else throw unknown();
    }
    return;
}
int main()
{
    string line;
    int cache_size, mem_size;
    getline(cin, line);
    stringstream read(line);
    read>>cache_size;
    read>>mem_size;
    LRUCache mod(cache_size,mem_size);
    while(getline(cin,line))
    {
        try {
            server(line,mod);
            cin.clear();
        }
        catch (unknown &a)
        {
           cout << "ERROR: Unknown instruction" << endl;
        }
        catch (toomany &b)
        {
            cout << "ERROR: Too many operands" << endl;
        }
        catch (notenough &c)
        {
            cout << "ERROR: Not enough operands" << endl;
        }
        catch (except &d)
        {
            cout << "ERROR: Address out of bound" << endl;
        }
        catch (exited &e)
        {
            return 0;
        }
    }
    return 0;
}

