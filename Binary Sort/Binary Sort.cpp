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
    bool add(int data, int pos)
    {
        if (pos > length || pos < 0)
        {
            return false;
        }

        SinglyLinkedNode* node = new SinglyLinkedNode(data);

        SinglyLinkedNode* ref = head;
        for (int i = 0; i < pos - 1; i++)
        {
            ref = ref->getNext();
        }
        if (pos == 0)
            head = node;
        if (pos > 0 && pos < length)
        {
            node->setNext(ref->getNext());
            ref->setNext(node);
        }
        if (pos == length)
        {
            if (pos != 0)
                ref->setNext(node);
        }

        length += 1;
        return true;
    }
    bool move(int oldPos, int newPos)
    {
        if (oldPos > length - 1 || newPos > length - 1)
        {
            return false;
        }
        SinglyLinkedNode* oldNodeNeighbor = head;
        for (int i = 0; i < (oldPos - 1); i++)
        {
            oldNodeNeighbor = oldNodeNeighbor->getNext();
        }
        SinglyLinkedNode* nodeToMove = oldNodeNeighbor->getNext();
        if (oldPos != 0)
        {
            oldNodeNeighbor->setNext(nodeToMove->getNext());
        }
        else
        {
            nodeToMove = head;
            head = head->getNext();
        }
        SinglyLinkedNode* newNodeNeighbor = head;
        for (int i = 0; i < (newPos - 1); i++)
        {
            newNodeNeighbor = newNodeNeighbor->getNext();
        }
        nodeToMove->setNext(newNodeNeighbor->getNext());
        if (newPos == 0)
        {
            SinglyLinkedNode* temp = head;
            head = nodeToMove;
            head->setNext(temp);
        }
        else
        {
            newNodeNeighbor->setNext(nodeToMove);
        }
        return true;
    }
    SinglyLinkedNode* nodeAt(int pos)
    {
        if (pos > length - 1)
            return nullptr;
        SinglyLinkedNode* ref = head;
        for (int i = 0; i < pos; i++)
            ref = ref->getNext();
        return ref;
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
    SinglyLinkedNode* it = list.nodeAt(0);
    for (int i = 0; i < list.size(); i++)
    {
        int lowerBound = 0;
        int upperBound = i - 1;
        int currentHalf;

        SinglyLinkedNode* lbPtr = list.nodeAt(0);
        SinglyLinkedNode* ubPtr = lbPtr;
        SinglyLinkedNode* chPtr = lbPtr;

        //SEARCH FOR LOCATION
        while (upperBound > lowerBound)
        {

        }

        //MOVE NODE TO LOCATION

        std::cout << it->getData() << " ";
        it = it->getNext();
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
    for (int i = 0; i < 1000; i++)
    {
        list.add(i, i);
    }
    list.display_forward();
    list.move(0, 5);
    list.display_forward();
    BinarySortSLL(list);
}
