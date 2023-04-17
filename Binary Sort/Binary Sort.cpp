#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>

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
    SinglyLinkedNode* getPrev() { return prev; }
    void setNext(SinglyLinkedNode* n) { next = n; }
    void setPrev(SinglyLinkedNode* p) { prev = p; }
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
    SinglyLinkedNode* nodeAtFrom(int pos, SinglyLinkedNode* startingNode, int startingNodeIndex)
    {
        if (pos > length - 1)
            return nullptr;
        if (startingNodeIndex > pos)
        {
            return nodeAt(pos);
        }
        SinglyLinkedNode* ref = startingNode;
        for (int i = startingNodeIndex; i < pos; i++)
        {
            ref = ref->getNext();
        }
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

SinglyLinkedList BinarySortSLL(SinglyLinkedList list)
{
    //std::cout << "--- Starting sort! ---\n";
    SinglyLinkedNode* it = list.nodeAt(0);
    for (int i = 0; i < list.size(); i++)
    {
        //std::cout << "Handling " << it->getData() << " at index " << i;
        
        int lowerBound = 0;
        int upperBound = i - 1;
        int currentHalf = lowerBound + floor((upperBound - lowerBound)/2);

        SinglyLinkedNode* lbPtr = list.nodeAt(lowerBound);
        SinglyLinkedNode* ubPtr = list.nodeAtFrom(upperBound, lbPtr, lowerBound);
        SinglyLinkedNode* chPtr = list.nodeAtFrom(currentHalf, lbPtr, lowerBound);

        //SEARCH FOR LOCATION
        while (upperBound > lowerBound)
        {
            //std::cout << "\nupperBound: " << upperBound << "\nlowerBound: " << lowerBound << "\ncurrentHalf: " << currentHalf << std::endl;
            if (it->getData() == chPtr->getData())
            {
                lowerBound = currentHalf;
                lbPtr = list.nodeAt(lowerBound);
                upperBound = currentHalf;
                ubPtr = list.nodeAtFrom(upperBound, lbPtr, lowerBound);
            }
            else if (it->getData() > chPtr->getData())
            {
                lowerBound = currentHalf + 1;
                lbPtr = list.nodeAt(lowerBound);
            }
            else
            {
                upperBound = currentHalf - 1;
                ubPtr = list.nodeAtFrom(upperBound, lbPtr, lowerBound);
            }
            currentHalf = lowerBound + floor((upperBound - lowerBound) / 2);
            chPtr = list.nodeAtFrom(currentHalf, lbPtr, lowerBound);
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
    //std::cout << "--- Sorted! ---\n";
    return list;
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
    auto begin = std::chrono::steady_clock::now();
    list = BinarySortSLL(list);
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
    list.display_forward();
    std::cout << "Time: " << duration << " seconds" << std::endl;
}
