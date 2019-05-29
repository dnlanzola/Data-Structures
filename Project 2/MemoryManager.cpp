#include <cassert>
#include <iostream>
#include "MemoryManager.h"

MemoryManager::MemoryManager(unsigned int memtotal)
{
   memsize = memtotal; // size of the "heap"
   baseptr = new unsigned char[memsize]; // allocate the heap
   // create empty blocknode list
   header = new blocknode();
   trailer = new blocknode();
   header->next = trailer;
   trailer->prev = header;
   // create blocknode to represent the entire heap
   blocknode *  originalBlocknode = new blocknode(memsize,baseptr,true);  
   header->insertAfter(originalBlocknode);
}

void MemoryManager::showBlockList() 
{
    blocknode * curr = header->next;
    
    if (curr->next == trailer)
        cout << curr << endl;
    else
    {
        for (curr = header->next; curr != trailer; curr = curr->next)
        {
            if (curr->next == trailer)
                cout << curr << endl;
            else
                cout << curr << "->";
        }
    }
    
    cout << endl;
    cout << endl;
}


void MemoryManager::splitBlock(blocknode *p, unsigned int chunksize)
{
    if (p->free == false || p->blocksize <= chunksize)
    {
        cout << "Error" << endl;
        return;
    }
    
    blocknode * heap = new blocknode(p->blocksize,p->blockptr + chunksize,true,0,0);
    heap->blocksize = p->blocksize - chunksize;
    heap->prev = p;
    p->blocksize = chunksize;
    p->next = heap;
    heap->next = trailer;
}

unsigned char * MemoryManager::malloc(unsigned int request)
{
    blocknode * cur = header->next;
    
    while(cur != trailer)
    {
        if(cur->blocksize >= request && cur->free)
        {
            splitBlock(cur, request);
            cur->free = false;
            return cur->blockptr;
        }
        cur = cur->next;
    }
    
    return nullptr;
}

void MemoryManager::mergeForward(blocknode *p)
{
    if(p->next->free)
    {
        p->blocksize += p->next->blocksize;
        p->next = trailer;
        delete(p->next->next);
    }
}

void MemoryManager::mergeBackward(blocknode *p)
{
    mergeForward(p->prev);
}

void MemoryManager::free(unsigned char *ptr2block)
{
    blocknode * cur = header->next;
    
    while(cur != trailer)
    {
        if(cur->blockptr == ptr2block && cur->free == false)
        {
            cur->free = true;
            if (cur->next->free == true)
                mergeForward(cur);
            if (cur->prev->free == true)
                mergeBackward(cur);
            
            return;
        }
        
        cur = cur->next;
    }
}
