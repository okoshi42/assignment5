//
//  sort.h
//  
//  Functions for merge sort, quicksort, and a hybrid sort.
//  You SHOULD modify this file.
//
//  IMPORTANT NOTE: For this particular assignment you may not add
//  any additional utility functions.
//
//  Copyright 2019 David Kopec
//
//  Permission is hereby granted, free of charge, to any person
//  obtaining a copy of this software and associated documentation files
//  (the "Software"), to deal in the Software without restriction,
//  including without limitation the rights to use, copy, modify, merge,
//  publish, distribute, sublicense, and/or sell copies of the Software,
//  and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice
//  shall be included in all copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
//  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
//  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
//  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
//  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
//  OTHER DEALINGS IN THE SOFTWARE.

#ifndef sort_hpp
#define sort_hpp
#include<iostream>
#include <algorithm> // for swap(), merge()
#include <random>

using namespace std;

namespace csi281 {
    
    // Performs an in-place ascending sort of *array*
    // using the merge sort algorithm
    // *start* is the first element of the array to start sorting from
    // *end* is the end element for the elements to be sorted
    // *end* will be the length of the array - 1 for a first run
    // NOTE: Your solution MUST use std::inplace_merge
    // http://www.cplusplus.com/reference/algorithm/inplace_merge/
    template <typename T>
    void mergeSort(T array[], const int start, const int end) {
        // YOUR CODE HERE
        /* pseudocode from https://www.geeksforgeeks.org/merge-sort/
        MergeSort(arr[], l,  r)
        If r > l
     1. Find the middle point to divide the array into two halves:  
             middle m = l+ (r-l)/2
     2. Call mergeSort for first half:   
             Call mergeSort(arr, l, m)
     3. Call mergeSort for second half:
             Call mergeSort(arr, m+1, r)
     4. Merge the two halves sorted in step 2 and 3:
             Call merge(arr, l, m, r)*/
        if (start >= end)
            return;      
        int split = start + (end-start) / 2;//midpoint of start and end
        mergeSort(array, start, split);//merge sorts first half, works recursively
        mergeSort(array, split + 1, end);//merge sorts second half, works recursively
        inplace_merge(array+start, array+(split+1), array+(end+1)); //merges the two returned sorted halfs
    }
    
    // setup random number generator
    static random_device rd;
    static mt19937 rng(rd());
    // you can use uniform_int_distribution and rng to create
    // a random int in a certain range
    
    // Performs an in-place ascending sort of *array*
    // using the quicksort algorithm
    // *start* is the first element of the array to start sorting from
    // *end* is the end element for the elements to be sorted
    // *end* will be the length of the array - 1 for a first run
    // NOTE: Your solution should use std::swap
    // http://www.cplusplus.com/reference/algorithm/swap/
    // NOTE: Your solution MUST use a random pivot
    // TIP: It may be helpful to swap the pivot to the end,
    // sort the center of the range, and then move the pivot back to
    // the appropriate place
    template <typename T>
    void quickSort(T array[], const int start, const int end) {
        // YOUR CODE HERE
        /* pseudocode from https://www.geeksforgeeks.org/quick-sort/
         low  --> Starting index,  high  --> Ending index 
        quickSort(arr[], low, high)
        {
            if (low < high)
            {
                 pi is partitioning index, arr[pi] is now
                   at right place 
                pi = partition(arr, low, high);

                quickSort(arr, low, pi - 1);  // Before pi
                quickSort(arr, pi + 1, high); // After pi
            }
        }
        */
     //a Quicksort Algorithm
        if (start >= end)//returns the fully sorted algorithm up through the iterations.
            return;
        T baseLine = array[end];//sets anchor to the right extreme
        int pivot = start;//sets the "split" between elements greater than and less than the anchor to left extreme
        for (int x = start; x <= end; x++)
        {
            if (array[x] <= baseLine) {
                //checks if current index is greater than or less than the anchor, if its less it will be sent to the left of the split.
                //swap method
                swap(array[x], array[pivot]);
                pivot++;
            }
        }
        quickSort(array, start, pivot - 2);//recursive call to the left of the split
        quickSort(array, pivot, end);//recursive call to the right of the split
    }
    
    // Performs an in-place ascending sort of *array*
    // using the insertion sort algorithm
    // *start* is the first element of the array to start sorting from
    // *end* is the end element for the elements to be sorted
    // *end* will be the length of the array - 1 for a first run
    // NOTE: You can modify your old implementation from assignment 4
    // OR if you believe yours was incorrect, email me and I will
    // send you mine assuming you are done with assignment 4,
    // but you will still need to modify it for this assignment
    // as described below
    // NOTE: You will need to modify the implementation to only
    // sort part of the array as per the parameters of this version
    template <typename T>
    void insertionSort(T array[], const int start, const int end) {
        // YOUR CODE HERE
        for (int x = start+1; x < end+1; x++) {
            T targetVal = array[x]; //value to be compared against, initialized at index x
            //checks every value left of x
            int y = x - 1;
            while (y >= start && array[y] > targetVal) { //if the current index is larger than targetVal, the loop breaks
                //shifts each value to the right by one
                array[y + 1] = array[y];
                y--;
            }
            //inserts targetVal into index left of the last index shifted
            array[y + 1] = targetVal;
        }      
    }
}
    
    // Performs an in-place ascending sort of *array*
    // using merge sort until there is less than 10 elements, and then
    // the insertion sort algorithm
    // *start* is the first element of the array to start sorting from
    // *end* is the end element for the elements to be sorted
    // *end* will be the length of the array - 1 for a first run
    // TIP: You can copy your implementation of merge sort in here, and
    // should be able to call the insertionSort above
    template <typename T>
    void hybridSort(T array[], const int start, const int end) {
        // YOUR CODE HERE
        if (start >= end)
        {
            return;
        }
        if (end - start <= 10)//checks range between start and end, this is our unsorted section
        {
            insertionSort(array, start, end);
        }
        else {
            int split = start + (end - start) / 2;//midpoint of start and end
            hybridSort(array, start, split);//merge sorts first half, works recursively
            hybridSort(array, split + 1, end);//merge sorts second half, works recursively
            inplace_merge(array + start, array + (split + 1), array + (end + 1)); //merges the two returned sorted halfs
        }
    }
#endif /* sort_hpp */
