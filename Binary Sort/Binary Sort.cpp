#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <chrono>

class Node {
private:
    int data;
    Node* next;
    Node* prev;
public:
    Node(int num)
    {
        data = num;
        next = nullptr;
        prev = nullptr;
    }
    int getData() { return data; }
    void setData(int d) { data = d; }
    Node* getNext() { return next; }
    Node* getPrev() { return prev; }
    void setNext(Node* n) { next = n; }
    void setPrev(Node* p) { prev = p; }
};

class SinglyLinkedList {
private:
    Node* head;
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
        Node* node = new Node(data);
        Node* ref = head;
        for (int i = 0; i < pos - 1; i++)
        {
            ref = ref->getNext();
        }
        if (pos == 0)
        {
            if (length > 0)
            {
                node->setNext(head);
            }
            head = node;
        }
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
        if (oldPos == newPos)
        {
            return true;
        }
        Node* oldNodeNeighbor;
        Node* nodeToMove;
        Node* newNodeNeighbor;
        oldNodeNeighbor = head;
        for (int i = 0; i < (oldPos - 1); i++)
        {
            oldNodeNeighbor = oldNodeNeighbor->getNext();
        }
        nodeToMove = oldNodeNeighbor->getNext();
        if (oldPos != 0)
        {
            oldNodeNeighbor->setNext(nodeToMove->getNext());
        }
        else
        {
            nodeToMove = head;
            head = head->getNext();
        }
        newNodeNeighbor = head;
        for (int i = 0; i < (newPos - 1); i++)
        {
            newNodeNeighbor = newNodeNeighbor->getNext();
        }
        nodeToMove->setNext(newNodeNeighbor->getNext());
        if (newPos == 0)
        {
            Node* temp = head;
            head = nodeToMove;
            head->setNext(temp);
        }
        else
        {
            newNodeNeighbor->setNext(nodeToMove);
        }
        return true;
    }
    Node* nodeAt(int pos)
    {
        if (pos > length - 1)
            return nullptr;
        Node* ref = head;
        for (int i = 0; i < pos; i++)
            ref = ref->getNext();
        return ref;
    }
    Node* nodeAtFrom(int pos, Node* startingNode, int startingNodeIndex)
    {
        if (pos > length - 1)
            return nullptr;
        if (startingNodeIndex > pos)
        {
            return nodeAt(pos);
        }
        Node* ref = startingNode;
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
        Node* ref = head;
        while (ref != nullptr)
        {
            std::cout << ref->getData() << ", ";
            ref = ref->getNext();
        }
        std::cout << std::endl;
    }
    bool isSorted()
    {
        Node* ref = head;
        for (int i = 0; i < length - 1; i++)
        {
            if (ref->getNext()->getData() < ref->getData())
                return false;
            ref = ref->getNext();
        }
        return true;
    }
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
    int length;
public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }
    bool add(int data, int pos)
    {
        if (pos > length)
            return false;
        Node* node = new Node(data);
        Node* ref = head;
        for (int i = 0; i < pos - 1; i++)
            ref = ref->getNext();
        if (pos == 0)
        {
            if (length > 0)
            {
                head->setPrev(node);
                node->setNext(head);
            }
            head = node;
        }
        if (pos > 0 && pos < length)
        {
            node->setPrev(ref);
            node->setNext(ref->getNext());
            ref->getNext()->setPrev(node);
            ref->setNext(node);
        }
        if (pos == length)
        {
            tail = node;
            node->setPrev(ref);
            if (pos != 0)
                ref->setNext(node);
        }

        length += 1;
        return true;
    }
    bool move(int oldPos, int newPos, Node* nodeToMove, Node* newNodeNeighborRight)
    {
        if (oldPos > length - 1 || newPos > length - 1 || newPos < 0 || oldPos < 0)
        {
            return false;
        }
        if (oldPos == newPos)
        {
            return true;
        }
        if (newPos > oldPos)
        {
            newNodeNeighborRight = newNodeNeighborRight->getNext();
        }
        // Declaring pointers
        Node* oldNodeNeighborLeft = nodeToMove->getPrev();
        Node* oldNodeNeighborRight = nodeToMove->getNext();
        Node* newNodeNeighborLeft = newNodeNeighborRight->getPrev();
        // Fixing up the old position
        if (oldPos == 0)
        {
            nodeToMove = head;
            head = head->getNext();
            head->setPrev(nullptr);
        }
        else if (oldPos == length - 1)
        {
            nodeToMove = tail;
            tail = tail->getPrev();
            tail->setNext(nullptr);
        }
        else
        {
            oldNodeNeighborLeft->setNext(oldNodeNeighborRight);
            oldNodeNeighborRight->setPrev(oldNodeNeighborLeft);
        }
        // Fixing up the new position
        if (newPos == 0)
        {
            nodeToMove->setPrev(nullptr);
            nodeToMove->setNext(head);
            head->setPrev(nodeToMove);
            head = nodeToMove;
        }
        else if (newPos == length - 1)
        {
            nodeToMove->setNext(nullptr);
            nodeToMove->setPrev(tail);
            tail->setNext(nodeToMove);
            tail = nodeToMove;
        }
        else
        {
            newNodeNeighborLeft->setNext(nodeToMove);
            newNodeNeighborRight->setPrev(nodeToMove);
            nodeToMove->setPrev(newNodeNeighborLeft);
            nodeToMove->setNext(newNodeNeighborRight);
        }
        return true;
    }
    Node* nodeAt(int pos)
    {
        if (pos > length - 1)
            return nullptr;
        Node* ref = head;
        for (int i = 0; i < pos; i++)
            ref = ref->getNext();
        return ref;
    }
    Node* nodeAtFrom(int pos, Node* startingNode, int startingNodeIndex)
    {
        if (pos > length - 1)
        {
            return nullptr;
        }
        int difference = pos - startingNodeIndex;
        Node* ref = startingNode;
        if (difference > 0)
        {
            for (int i = startingNodeIndex; i < pos; i++)
            {
                ref = ref->getNext();
            }
            return ref;
        }
        else if (difference < 0)
        {
            for (int i = startingNodeIndex; i > pos; i--)
            {
                ref = ref->getPrev();
            }
            return ref;
        }
        return startingNode;
    }
    void display_forward()
    {
        Node* ref = head;
        while (ref != nullptr)
        {
            std::cout << ref->getData() << ", ";
            ref = ref->getNext();
        }
        std::cout << std::endl;
    }
    void display_backward()
    {
        Node* ref = tail;
        while (ref != nullptr)
        {
            std::cout << ref->getData() << ", ";
            ref = ref->getPrev();
        }
        std::cout << std::endl;
    }
    int size()
    {
        return length;
    }
    bool isSorted()
    {
        Node* ref = head;
        for (int i = 0; i < length - 1; i++)
        {
            if (ref->getNext()->getData() < ref->getData())
                return false;
            ref = ref->getNext();
        }
        ref = tail;
        for (int i = 0; i < length - 1; i++)
        {
            if (ref->getPrev()->getData() > ref->getData())
                return false;
            ref = ref->getPrev();
        }
        return true;
    }
};

void BinarySortSLL(SinglyLinkedList& list)
{
	//std::cout << "--- Starting sort! ---\n";
	Node* it = list.nodeAt(0);
	for (int i = 0; i < list.size(); i++)
	{
		//std::cout << "Handling " << it->getData() << " at index " << i;
		int lowerBound = 0;
		int upperBound = i - 1;
		int currentHalf = lowerBound + floor((upperBound - lowerBound) / 2);
		Node* lbPtr = list.nodeAt(lowerBound);
		Node* chPtr = list.nodeAtFrom(currentHalf, lbPtr, lowerBound);
		//SEARCH FOR LOCATION
		while (upperBound > lowerBound)
		{
			//std::cout << "\nupperBound: " << upperBound << "\nlowerBound: " << lowerBound << "\ncurrentHalf: " << currentHalf << std::endl;
			if (it->getData() == chPtr->getData())
			{
				lbPtr = list.nodeAtFrom(currentHalf, lbPtr, lowerBound);
				lowerBound = currentHalf;
				upperBound = currentHalf;
			}
			else if (it->getData() > chPtr->getData())
			{
				lbPtr = list.nodeAtFrom(currentHalf + 1, chPtr, currentHalf);
				lowerBound = currentHalf + 1;
			}
			else
			{
				upperBound = currentHalf - 1;
			}
			currentHalf = lowerBound + floor((upperBound - lowerBound) / 2);
			chPtr = list.nodeAtFrom(currentHalf, lbPtr, lowerBound);
		}
		Node* nextIter = it->getNext();
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
}

void BinarySortDLL(DoublyLinkedList& list)
{
    //std::cout << "--- Starting sort! ---\n";
    Node* it = list.nodeAt(0);
    for (int i = 0; i < list.size(); i++)
    {
        //std::cout << "Handling " << it->getData() << " at index " << i;
        int lowerBound = 0;
        int upperBound = i - 1;
        int currentHalf = lowerBound + floor((upperBound - lowerBound) / 2);
        Node* chPtr = list.nodeAt(currentHalf);
        //SEARCH FOR LOCATION
        while (upperBound > lowerBound)
        {
            //std::cout << "\nupperBound: " << upperBound << "\nlowerBound: " << lowerBound << "\ncurrentHalf: " << currentHalf << std::endl;
            if (it->getData() == chPtr->getData())
            {
                lowerBound = currentHalf;
                upperBound = currentHalf;
            }
            else if (it->getData() > chPtr->getData())
            {
                lowerBound = currentHalf + 1;
            }
            else
            {
                upperBound = currentHalf - 1;
            }
            chPtr = list.nodeAtFrom(lowerBound + floor((upperBound - lowerBound) / 2), chPtr, currentHalf);
            currentHalf = lowerBound + floor((upperBound - lowerBound) / 2);
        }
        Node* nextIter = it->getNext();
        //MOVE NODE TO LOCATION
        //std::cout << std::endl;
        //list.display_forward();
        if (it->getData() <= chPtr->getData())
        {
            //std::cout << it->getData() << " is less than or equal to " << lbPtr->getData() << std::endl;
            list.move(i, currentHalf, it, chPtr);
        }
        else
        {
            //std::cout << it->getData() << " is greater than " << lbPtr->getData() << std::endl;
            list.move(i, currentHalf + 1, it, chPtr->getNext());
        }
        //list.display_forward();
        //std::cout << std::endl;
        it = nextIter;
    }
    //std::cout << "--- Sorted! ---\n";
}

int main()
{
    srand(time(NULL));
    double totalTime = 0;
    std::cout << "Starting sort test for singly linked list";
    for (int j = 0; j < 100; j++)
    {
        if (j % 10 == 0)
        {
            std::cout << ".";
        }
        SinglyLinkedList list;
        for (int i = 0; i < 20000; i++)
        {
            list.add(rand() % 20000, 0);
        }
        //list.display_forward();
        auto begin = std::chrono::steady_clock::now();
        BinarySortSLL(list);
        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() / 1000000.0;
        //list.display_forward();
        //std::cout << "Time: " << duration << " seconds" << std::endl;
        totalTime += duration;
        if (!list.isSorted())
        {
            std::cout << "\nERROR: List is not sorted!";
            break;
        }
    }
    std::cout << "\nAverage time SLL: " << totalTime / 100 << std::endl;
	totalTime = 0;
    std::cout << "\nStarting sort test for doubly linked list";
	for (int j = 0; j < 100; j++)
	{
        if (j % 10 == 0)
        {
            std::cout << ".";
        }
		DoublyLinkedList dList;
		for (int i = 0; i < 20000; i++)
		{
			dList.add(rand() % 20000, 0);
		}
		//dList.display_forward();
		//dList.display_backward();
		auto begind = std::chrono::steady_clock::now();
		BinarySortDLL(dList);
		auto endd = std::chrono::steady_clock::now();
		auto durationd = std::chrono::duration_cast<std::chrono::microseconds>(endd - begind).count() / 1000000.0;
		//dList.display_forward();
		//dList.display_backward();
		//std::cout << "Time: " << durationd << " seconds" << std::endl;
		totalTime += durationd;
        if (!dList.isSorted())
        {
            std::cout << "\nERROR: List is not sorted!";
            break;
        }
	}
    std::cout << "\nAverage time DLL: " << totalTime / 100 << std::endl;
}