//
// Created by Briana on 4/12/2021.
//

#ifndef COMP4370ASS2MERGFIB_MERGESORT_H
#define COMP4370ASS2MERGFIB_MERGESORT_H

#include <vector>

// Definitions
template <typename T>
void merge(std::vector<T> &s, typename std::vector<T>::size_type low,
           typename std::vector<T>::size_type middle, typename std::vector<T>::size_type high);

//void merge_sort(item_type s[], int low, int high) {
//void merge_sort(std::vector<int> &s, typename std::vector<int>::size_type low, typename std::vector<int>::size_type high);

// Implementation Below
#include <deque>

template <typename T>
void merge(std::vector<T> &s, typename std::vector<T>::size_type low,
           typename std::vector<T>::size_type middle, typename std::vector<T>::size_type high) {

    //queue left, right; /* buffers to hold elements for merging */
    //init_queue(&left);
    //init_queue(&right);
    std::deque<T> left, right;

    //    for (i = low; i <= middle; i++) enqueue(&left, s[i]);
    for (typename std::vector<T>::size_type i = low; i <= middle; ++i) {
        left.push_back(s[i]);
    }

    //for (i = middle + 1; i <= high; i++) enqueue(&right, s[i]);
    for (typename std::vector<T>::size_type i = middle + 1; i <= high; ++i) {
        right.push_back(s[i]);
    }

    //i = low;
    typename std::vector<T>::size_type out = low;
    //while (!(empty_queue(&left) || empty_queue(&right))) {
    while (!(left.empty() || right.empty())) {
        //if (headq(&left) < headq(&right)) {
        if (left.front() < right.front()) {
            //s[i++] = dequeue(&left);
            s[out] = left.front();
            left.pop_front();
        } else {
            //s[i++] = dequeue(&right);
            s[out] = right.front();
            right.pop_front();
        }
        ++out;
    }
    //while (!empty_queue(&left)) {
    while (!left.empty()) {
        //s[i++] = dequeue(&left);
        s[out] = left.front();
        left.pop_front();
        ++out;
    }
    //while (!empty_queue(&right)) {
    while (!right.empty()) {
        //s[i++] = dequeue(&right);
        s[out] = right.front();
        right.pop_front();
        ++out;
    }
}
template <typename T>
void merge_sort(std::vector<T> &s, typename std::vector<T>::size_type low, typename std::vector<T>::size_type high) {
    //int middle; /* index of middle element */
   //typename std::vector<int>::size_type middle;
    //if (low < high) {
    if (low < high){
        //middle = (low + high) / 2;
        typename std::vector<T>::size_type middle = (low + high) /2;
        //merge_sort(s, low, middle);
        merge_sort(s, low,  middle);
        //merge_sort(s, middle + 1, high);
        merge_sort(s,  middle +1,  high);
        //merge(s, low, middle, high);
        merge<T>(s, low, middle, high);
    }
}
#endif //COMP4370ASS2MERGFIB_MERGESORT_H
