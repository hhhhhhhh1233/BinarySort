#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <time.h>

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
        std::cout << "List: ";
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
    std::cout << "--- Starting sort! ---\n";
    SinglyLinkedNode* it = list.nodeAt(0);
    for (int i = 0; i < list.size(); i++)
    {
        //std::cout << "Handling " << it->getData() << " at index " << i;
        
        int lowerBound = 0;
        int upperBound = i - 1;
        int currentHalf = lowerBound + floor((upperBound - lowerBound)/2);

        SinglyLinkedNode* lbPtr = list.nodeAt(lowerBound);
        SinglyLinkedNode* ubPtr = list.nodeAt(upperBound);
        SinglyLinkedNode* chPtr = list.nodeAt(currentHalf);

        //SEARCH FOR LOCATION
        while (upperBound > lowerBound)
        {
            //std::cout << "\nupperBound: " << upperBound << "\nlowerBound: " << lowerBound << "\ncurrentHalf: " << currentHalf << std::endl;
            if (it->getData() == chPtr->getData())
            {
                upperBound = currentHalf;
                ubPtr = list.nodeAt(upperBound);
                lowerBound = currentHalf;
                lbPtr = list.nodeAt(lowerBound);
            }
            else if (it->getData() > chPtr->getData())
            {
                lowerBound = currentHalf + 1;
                lbPtr = list.nodeAt(lowerBound);
            }
            else
            {
                upperBound = currentHalf - 1;
                ubPtr = list.nodeAt(upperBound);
            }
            currentHalf = lowerBound + floor((upperBound - lowerBound) / 2);
            chPtr = list.nodeAt(currentHalf);
        }
        
        SinglyLinkedNode* nextIter = it->getNext();

        //MOVE NODE TO LOCATION
        //std::cout << std::endl;
        //list.display_forward();
        if (it->getData() <= lbPtr->getData())
        {
            //std::cout << it->getData() << " is less than or equal to " << lbPtr->getData() << std::endl;
            list.move(i, lowerBound);
        }
        else
        {
            //std::cout << it->getData() << " is greater than " << lbPtr->getData() << std::endl;
            list.move(i, lowerBound + 1);
        }
        //list.display_forward();
        //std::cout << std::endl;
        it = nextIter;
    }
    std::cout << "--- Sorted! ---\n";
    list.display_forward();
}

int main()
{
    srand(time(NULL));
    SinglyLinkedList list;
    for (int i = 0; i < 10000; i++)
    {
        list.add(rand() % 10000, i);
    }
    list.display_forward();
    list.move(0, 3);
    list.display_forward();
    BinarySortSLL(list);
}
