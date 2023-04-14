#include <iostream>
#include <math.h>
#include <list>
#include <forward_list>

void BinarySortSLL(std::forward_list<int> arr)
{
    int i = 0;
    for (int& elem : arr)
    {
        int lowerBound = 0;
        int upperBound = i - 1;
        int currentHalf;

        std::forward_list<int>::iterator lowerBoundPtr = arr.begin();
        std::forward_list<int>::iterator upperBoundPtr = arr.begin();
        std::forward_list<int>::iterator currentHalfPtr = arr.begin();

        for (int j = 0; j < upperBound; j++)
        {
            upperBoundPtr = std::next(upperBoundPtr);
        }

        std::forward_list<int>::iterator prevToCurrentElemPtr = upperBoundPtr;

        while (upperBound > lowerBound)
        {
            currentHalf = lowerBound + floor((upperBound - lowerBound) / 2);
            currentHalfPtr = lowerBoundPtr;

            for (int j = 0; j < (currentHalf - lowerBound); j++)
            {
                currentHalfPtr = std::next(currentHalfPtr);
            }

            if (elem == *currentHalfPtr)
            {
                lowerBound = currentHalf;
                upperBound = currentHalf;
            }
            else if (elem < *currentHalfPtr)
            {
                upperBoundPtr = lowerBoundPtr;
                for (int j = 0; j < (upperBound - lowerBound); j++)
                {
                    upperBoundPtr = std::next(upperBoundPtr);
                }
                upperBound = currentHalf - 1;
            }
            else
            {
                for (int j = 0; j < ((currentHalf + 1) - lowerBound); j++)
                {
                    lowerBoundPtr = std::next(lowerBoundPtr);
                }
                lowerBound = currentHalf + 1;
            }
        }
        if (elem > *currentHalfPtr)
        {
            arr.emplace_after(std::next(currentHalfPtr), elem);
            arr.erase_after(prevToCurrentElemPtr);
        }
        else
        {
            arr.emplace_after(currentHalfPtr, elem);
            arr.erase_after(prevToCurrentElemPtr);
        }
        i++;
    }
    for (int& i : arr)
    {
        std::cout << i << " ";
    }
}

int main()
{
    std::forward_list<int> list1;
    list1.assign({ 1,2,3,4,5 });
    BinarySortSLL(list1);
}
