// Gregory D. Stula
// CS 325 Fall 2020
// Homework 1 Problem 4
// Octobor 3, 2020

#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <chrono>
#include <iostream>
#include <random>

// generates a vector with random integers up to size n
// randomly generated values are between 0 to 10,000
std::vector<int> generate_vector(int n)
{
    std::vector<int> v;
    std::random_device rd;
    // mr19937 random number generator engine
    std::mt19937 rng{rd()};
    // int distribution keeps random numbers bounded while being evenly distributed
    std::uniform_int_distribution<int> dist{0, 10000};

    for (int i = 0; i < n; i++) {
        // push back
        v.push_back(dist(rng));
    }
    return v;
}


// was used for debugging
void print_vector(std::vector<int> v)
{
    for (auto&& i : v) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

void stoogesort(std::vector<int>& v, int start, int end)
{

    if (start > end) return;

    // end is n - 1 calculate n so that it works as the size for each recursive call
    // rounding upward (ceiling)
    int n = end - start + 1;
    // if n is 2 swap the end and start if the start is greater
    if (n == 2 && v[start] > v[end]) {
        std::swap(v[start], v[end]);
    }

    if (n > 2) {
        // get the 2/3ds value which is a size used to 'split' into 2/3rds
        // n is already calculated as the first portion of the ceiling formula for int division into 2/3ds
        // (end - start + 1) / 3
        int m = n / 3;
        // call recusively on the first two thirds of the vector
        stoogesort(v, start, end - m);
        // call on recusively on the last two thirds of the vector
        stoogesort(v, start + m, end);
        // call again on the first two thirds of the vector
        stoogesort(v, start, end - m);
    }
}

int main()
{
    // create csv file to output for analysis in excel
    std::ofstream csv_file;
    csv_file.open("insertTime.csv");
    // write headers
    csv_file << "n,time\n";

    for (int n = 500; n <= 500*10; n += 500) {
        std::vector<int> v =  generate_vector(n);
        // get time before and after and subtract them
        auto time1 = std::chrono::high_resolution_clock::now();
        // sort
        stoogesort(v, 0, v.size() - 1);
        auto time2 = std::chrono::high_resolution_clock::now();
        // get the duration
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(time2 - time1).count();
        // output to user
        std::cout << "n = " << n << " duration: " << duration;
        // output to csv
        csv_file << n << "," << duration << "\n";
        std::cout << std::endl;
    }
    // close file
    csv_file.close();
}


