
/**
   选择质数分辨算法构造一棵哈希树
*/
#include <string.h>
#include <iostream>
using namespace std;


const int SIZE = 32;                                  //第10个质数为29，余数不可能大于32，所以数组的固定长度设置为32
const int Prime[10] = {2,3,5,7,11,13,17,19,23,29};

//哈希结点类型
template<class T1, class T2>
class HashNode
{
public:
    HashNode();                  //默认构造函数
    HashNode(T1 key, T2 value);  //一般构造函数
    ~HashNode();

public:
    T1 m_key;                 //结点的关键字
    T2 m_value;               //结点的数据对象
    bool occupied;            //结点是否被占据，如果是表示结点的关键字有效
    HashNode *child[SIZE];    //结点的子结点数组
};

template<class T1, class T2>
HashNode<T1,T2>::HashNode()
{
    occupied=false;
    memset(child, NULL, SIZE*sizeof(HashNode<T1,T2>*));
}

template<class T1, class T2>
HashNode<T1,T2>::HashNode(T1 key, T2 value)
{
    this->m_key = key;
    this->m_value = value;
    occupied=false;
    memset(child, NULL, SIZE*sizeof(HashNode<T1,T2>*));
}

template<class T1, class T2>
HashNode<T1,T2>::~HashNode()
{

}

//哈希树类型
template<class T1, class T2>
class HashTree
{
public:
    HashTree();
    ~HashTree();
    void InsertNode(T1 key, T2 value);
    bool FindNode(T1 key, T2 &value);
    void DeleteNode(T1 key);


private:
    HashNode<T1,T2> *root;
    void Insert(HashNode<T1,T2> *hashNode, int level, T1 key, T2 value);   //插入结点
    bool Find(HashNode<T1,T2> *hashNode, int level, T1 key, T2 value);     //查找
    void Delete(HashNode<T1,T2> *hashNode, int level,T1 key);              //删除结点
};

template<class T1, class T2>
HashTree<T1,T2>::HashTree()
{
    root = new HashNode<T1,T2>;
}

template<class T1, class T2>
HashTree<T1,T2>::~HashTree()
{

}

template<class T1, class T2>
void HashTree<T1,T2>::InsertNode(T1 key, T2 value)
{
    Insert(root,0,key,value);
}

//插入结点
template<class T1, class T2>
void HashTree<T1,T2>::Insert(HashNode<T1, T2> *hashNode, int level, T1 key, T2 value)
{
     if(hashNode->occupied == false)
     {
         hashNode->m_key = key;
         hashNode->m_value = value;
         hashNode->occupied = true;
         cout << "Insert key: " << key << " value: " << value << endl;
         return;
     }

     int index = key%Prime[level];

     if (hashNode->child[index] == NULL)
     {
          hashNode->child[index] = new HashNode<T1,T2>;
     }

     level += 1;
     Insert(hashNode->child[index], level, key, value);

}

template<class T1, class T2>
bool HashTree<T1,T2>::FindNode(T1 key, T2 &value)
{
     return Find(root, 0, key, value);
}

//查找
template<class T1, class T2>
bool HashTree<T1,T2>::Find(HashNode<T1,T2> *hashNode, int level, T1 key, T2 value)
{
     if (hashNode->occupied == true)
     {
         if (hashNode->m_key == key)
         {
             value = hashNode->m_value;
             cout << "Find key: " << key << ", value: " << value << endl;
             return true;
         }
     }

     int index = key%Prime[level];
     if (hashNode->child[index] == NULL)
     {
         cout << "Not found key: " << key<< endl;
         return false;
     }

     level += 1;
     return Find(hashNode->child[index], level, key, value);
}

template<class T1, class T2>
void HashTree<T1,T2>::DeleteNode(T1 key)
{
    Delete(root, 0, key);
}

//删除结点
template<class T1, class T2>
void HashTree<T1,T2>::Delete(HashNode<T1,T2> *hashNode, int level, T1 key)
{
   if (hashNode->occupied == true)
   {
       if (hashNode->m_key == key)
       {
           hashNode->occupied = false;
           cout << "Delete key: " << key << " successful" << endl;
           return;
       }
   }

   int index = key%Prime[level];
   if (hashNode->child[index] == NULL)
   {
       cout << "Delete key: " << key << " not exist" << endl;
       return;
   }

   level += 1;
   Delete(hashNode->child[index], level, key);
}

int main(int argc, char* argv[])
{
    cout<<"---Start---"<<endl;
    HashTree<int, int> ht;
    cout<<"\n==Insert 10 2 300 44 53 509 7000"<<endl;
    ht.InsertNode(10, 8);
    ht.InsertNode(2, 0);
    ht.InsertNode(300, 4);
    ht.InsertNode(44, 7);
    ht.InsertNode(53, 4);
    ht.InsertNode(609, 3);
    ht.InsertNode(7000, 8);

    int nvalue = 0;
    cout<<"\n==Find 5 and 609"<<endl;
    ht.FindNode(5,nvalue);
    ht.FindNode(609,nvalue);

    cout<<"\n==Delete 609 7000 2100"<<endl;
    ht.DeleteNode(609);
    ht.DeleteNode(7000);
    ht.DeleteNode(2100);

    cout<<"\n---End---"<<endl;

    return 0;
}
