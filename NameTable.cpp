// NameTable.cpp

// This is a correct but inefficient implementation of
// the NameTable functionality.

#include "NameTable.h"
#include <string>
#include <vector>
#include<list>
#include<functional>
#include <iostream>
using namespace std;

  // This class does the real work of the implementation.

//*********** Vector of iterators **************
class NameTableImpl
{
  public:
    void enterScope();
    bool exitScope();
    bool declare(const string& id, int lineNum);
    int find(const string& id) const;
    NameTableImpl();
    ~NameTableImpl();

  private:
    unsigned int hashFunc(const string& id) const; //returns bucket index
    struct Variable{
        string name;
        int line;
        Variable(string n, int l) : name(n), line(l){}
    };
    struct Iterators{
        list<Variable>::iterator it;
        int bucketNum;
        Iterators() : bucketNum(-1){}
        Iterators(list<Variable>::iterator i, int b) : it(i), bucketNum(b){}
    };
    list<Variable>* buckets[20000]{nullptr};
    vector<Iterators> itrsVector;
};

NameTableImpl::NameTableImpl(){}

NameTableImpl::~NameTableImpl(){
    for(int i=0; i<20000; i++){
        if(buckets[i]!=nullptr){
            for(list<Variable>::iterator p = buckets[i]->begin(); p!=buckets[i]->end();){
                p=buckets[i]->erase(p);
            }
            delete buckets[i];
        }
    }
}

unsigned int NameTableImpl::hashFunc(const string& id) const{
    unsigned int hash = 2166136261u;
    for(int i=0; i<id.length(); i++){
        hash += id[i];
        hash *= 16777619;
    }
    return hash%20000;
}

void NameTableImpl::enterScope()
{
      // Extend the id vector with an empty string that
      // serves as a scope entry marker.
    itrsVector.push_back(Iterators());
}

bool NameTableImpl::exitScope()
{
      // Remove ids back to the last scope entry.
    while(!itrsVector.empty() && itrsVector.back().bucketNum!=-1)
    {
        buckets[itrsVector.back().bucketNum]->erase(itrsVector.back().it);
        itrsVector.pop_back();
    }
    if(itrsVector.empty())
        return false;


      // Remove the scope entry marker itself.
    itrsVector.pop_back();
    return true;
}

bool NameTableImpl::declare(const string& id, int lineNum)
{
    if (id.empty())
        return false;

      // Check for another declaration in the same scope.
      // Return if found, break out if encounter the scope
      // entry marker.

    size_t k = itrsVector.size();
    while (k > 0)
    {
        k--;
        if(itrsVector[k].bucketNum==-1)
            break;
        if(itrsVector[k].it->name == id)
            return false;
    }

      // Save the declaration
    unsigned int index = hashFunc(id);
    if(buckets[index]==nullptr){
        buckets[index] = new list<Variable>;
    }
    buckets[index]->push_back(Variable(id,lineNum));
    list<Variable>::iterator end = buckets[index]->end();
    end--;
    itrsVector.push_back(Iterators(end,index));
    return true;
}

int NameTableImpl::find(const string& id) const
{
    if (id.empty())
        return -1;

      // Search back for the most recent declaration still
      // available.

    unsigned int index = hashFunc(id);
    if(buckets[index]==nullptr){
        return -1;
    }
    int mostRecent=-1;
    for(list<Variable>::iterator p = buckets[index]->begin(); p!=buckets[index]->end(); p++){
        if(p->name==id){
            if(p->line>mostRecent) mostRecent = p->line;
        }
    }
    return (mostRecent==-1) ? -1 : mostRecent;
}


//*********** NameTable functions **************

// For the most part, these functions simply delegate to NameTableImpl's
// functions.

NameTable::NameTable()
{
    m_impl = new NameTableImpl;
}

NameTable::~NameTable()
{
    delete m_impl;
}

void NameTable::enterScope()
{
    m_impl->enterScope();
}

bool NameTable::exitScope()
{
    return m_impl->exitScope();
}

bool NameTable::declare(const string& id, int lineNum)
{
    return m_impl->declare(id, lineNum);
}

int NameTable::find(const string& id) const
{
    return m_impl->find(id);
}
//class NameTableImpl
//{
//  public:
//    void enterScope();
//    bool exitScope();
//    bool declare(const string& id, int lineNum);
//    int find(const string& id) const;
//  private:
//    vector<string> m_ids;
//    vector<int> m_lines;
//};
//
//void NameTableImpl::enterScope()
//{
//      // Extend the id vector with an empty string that
//      // serves as a scope entry marker.
//
//    m_ids.push_back("");
//    m_lines.push_back(0);
//}
//
//bool NameTableImpl::exitScope()
//{
//      // Remove ids back to the last scope entry.
//
//    while (!m_ids.empty()  &&  m_ids.back() != "")
//    {
//        m_ids.pop_back();
//        m_lines.pop_back();
//    }
//    if (m_ids.empty())
//        return false;
//
//      // Remove the scope entry marker itself.
//
//    m_ids.pop_back();
//    m_lines.pop_back();
//    return true;
//}
//
//bool NameTableImpl::declare(const string& id, int lineNum)
//{
//    if (id.empty())
//        return false;
//
//      // Check for another declaration in the same scope.
//      // Return if found, break out if encounter the scope
//      // entry marker.
//
//    size_t k = m_ids.size();
//    while (k > 0)
//    {
//        k--;
//        if (m_ids[k].empty())
//            break;
//        if (m_ids[k] == id)
//            return false;
//    }
//
//      // Save the declaration
//
//    m_ids.push_back(id);
//    m_lines.push_back(lineNum);
//    return true;
//}
//
//int NameTableImpl::find(const string& id) const
//{
//    if (id.empty())
//        return -1;
//
//      // Search back for the most recent declaration still
//      // available.
//
//    size_t k = m_ids.size();
//    while (k > 0)
//    {
//        k--;
//        if (m_ids[k] == id)
//            return m_lines[k];
//    }
//    return -1;
//}
//
////*********** NameTable functions **************
//
//// For the most part, these functions simply delegate to NameTableImpl's
//// functions.
//
//NameTable::NameTable()
//{
//    m_impl = new NameTableImpl;
//}
//
//NameTable::~NameTable()
//{
//    delete m_impl;
//}
//
//void NameTable::enterScope()
//{
//    m_impl->enterScope();
//}
//
//bool NameTable::exitScope()
//{
//    return m_impl->exitScope();
//}
//
//bool NameTable::declare(const string& id, int lineNum)
//{
//    return m_impl->declare(id, lineNum);
//}
//
//int NameTable::find(const string& id) const
//{
//    return m_impl->find(id);
//}
