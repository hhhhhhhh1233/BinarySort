#include <iostream>
#include <math.h>
#include <vector>

class SinglyLinkedNode {
private:
    int data;
    SinglyLinkedNode* next;
    SinglyLinkedNode* prev;
public:
    SinglyLinkedNode(int num)
    {
        data = num;
        next = nullptr;
        prev = nullptr;
    }
    int getData() { return data; }
    void setData(int d) { data = d; }
    SinglyLinkedNode* getNext() { return next; }
    void setNext(SinglyLinkedNode* n) { next = n; }
};

class SinglyLinkedList {
private:
    SinglyLinkedNode* head;
    int length;
public:
    SinglyLinkedList()
    {
        length = 0;
        head = nullptr;
    }
    ~SinglyLinkedList()
    {
        while (length > 0)
        {
            SinglyLinkedNode* ref = head;
            for (int i = 0; i < length - 1; i++)
            {
                ref = ref->getNext();
            }
            delete ref;
            length--;
        }
    }
    bool add(SinglyLinkedNode* data, int pos)
    {
        if (pos > length || pos < 0)
        {
            return false;
        }
        SinglyLinkedNode* ref = head;
        for (int i = 0; i < pos - 1; i++)
        {
            ref = ref->getNext();
        }
        if (pos == 0)
            head = data;
        if (pos > 0 && pos < length)
        {
            data->setNext(ref->getNext());
            ref->setNext(data);
        }
        if (pos == length)
        {
            if (pos != 0)
                ref->setNext(data);
        }

        length += 1;
        return true;
    }
    //bool remove(int pos);
    //bool replace(SinglyLinkedNode* old, SinglyLinkedNode* neww);
    bool move(int oldPos, int newPos)
    {
        if (oldPos > length - 1 || newPos > length - 1)
        {
            return false;
        }
        // Node to move
        // New Node
        // old-1 -> old+1
        // old -> new
        // new-1 -> old
        SinglyLinkedNode* nodeOldNeighbor = head;
        for (int i = 0; i < (oldPos - 1); i++)
        {
            nodeOldNeighbor = nodeOldNeighbor->getNext();
        }
        SinglyLinkedNode* nodeToMove = nodeOldNeighbor->getNext();
        nodeOldNeighbor->setNext(nodeOldNeighbor->getNext()->getNext());
        SinglyLinkedNode* nodeNewNeighbor = head;
        for (int i = 0; i < (newPos - 1); i++)
        {
            nodeNewNeighbor = nodeNewNeighbor->getNext();
        }
        nodeToMove->setNext(nodeNewNeighbor->getNext());
        nodeNewNeighbor->setNext(nodeToMove);
        return true;
    }
    //int search(SinglyLinkedNode* data);
    SinglyLinkedNode* nodeAt(int pos)
    {

    }
    int size()
    {
        return length;
    }
    void display_forward()
    {
        SinglyLinkedNode* ref = head;
        while (ref != nullptr)
        {
            std::cout << ref->getData() << ", ";
            ref = ref->getNext();
        }
        std::cout << std::endl;
    }
};

void BinarySortSLL(SinglyLinkedList list)
{
    for (int i = 0; i < list.size(); i++)
    {

    }
    //int i = 0;
    //for (int& elem : arr)
    //{
    //    int lowerBound = 0;
    //    int upperBound = i - 1;
    //    int currentHalf;

    //    std::forward_list<int>::iterator lowerBoundPtr = arr.begin();
    //    std::forward_list<int>::iterator upperBoundPtr = arr.begin();
    //    std::forward_list<int>::iterator currentHalfPtr = arr.begin();

    //    for (int j = 0; j < upperBound; j++)
    //    {
    //        upperBoundPtr = std::next(upperBoundPtr);
    //    }

    //    std::forward_list<int>::iterator prevToCurrentElemPtr = upperBoundPtr;

    //    while (upperBound > lowerBound)
    //    {
    //        currentHalf = lowerBound + floor((upperBound - lowerBound) / 2);
    //        currentHalfPtr = lowerBoundPtr;

    //        for (int j = 0; j < (currentHalf - lowerBound); j++)
    //        {
    //            currentHalfPtr = std::next(currentHalfPtr);
    //        }

    //        if (elem == *currentHalfPtr)
    //        {
    //            lowerBound = currentHalf;
    //            upperBound = currentHalf;
    //        }
    //        else if (elem < *currentHalfPtr)
    //        {
    //            upperBoundPtr = lowerBoundPtr;
    //            for (int j = 0; j < (upperBound - lowerBound); j++)
    //            {
    //                upperBoundPtr = std::next(upperBoundPtr);
    //            }
    //            upperBound = currentHalf - 1;
    //        }
    //        else
    //        {
    //            for (int j = 0; j < ((currentHalf + 1) - lowerBound); j++)
    //            {
    //                lowerBoundPtr = std::next(lowerBoundPtr);
    //            }
    //            lowerBound = currentHalf + 1;
    //        }
    //    }
    //    if (elem > *currentHalfPtr)
    //    {
    //        arr.emplace_after(std::next(currentHalfPtr), elem);
    //        arr.erase_after(prevToCurrentElemPtr);
    //    }
    //    else
    //    {
    //        arr.emplace_after(currentHalfPtr, elem);
    //        arr.erase_after(prevToCurrentElemPtr);
    //    }
    //    i++;
    //}
    //for (int& i : arr)
    //{
    //    std::cout << i << " ";
    //}
}

int main()
{
    SinglyLinkedList list;
    //std::vector<SinglyLinkedNode*> arr(10);
    //for (int i = 0; i < 10; i++)
    //{
    //    arr.push_back(new SinglyLinkedNode(5));
    //    list.add(arr[i], i);
    //}
    SinglyLinkedNode* n0 = new SinglyLinkedNode(2);
    SinglyLinkedNode* n1 = new SinglyLinkedNode(5);
    SinglyLinkedNode* n2 = new SinglyLinkedNode(7);
    SinglyLinkedNode* n3 = new SinglyLinkedNode(3);
    list.add(n0, 0);
    list.add(n1, 1);
    list.add(n2, 2);
    list.add(n3, 3);
    list.display_forward();
    list.move(3, 1);
    list.display_forward();
    //std::forward_list<int> list1;
    //list1.assign({ 1,2,3,4,5 });
    //BinarySortSLL(list1);
}
