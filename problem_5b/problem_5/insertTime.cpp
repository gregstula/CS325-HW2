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


std::vector<int> insertsort(std::vector<int>& v)
{
    // start index at 1 since 0 is already sorted
    for (size_t i = 1; i < v.size(); i++) {
        int key = v.at(i);
        int j = i - 1; // second index to start at 0 for comparison
        // compare the current value to all the previously sorted ones
        while (j >= 0 && key > v.at(j)) {
            // shift the array
            v.at(j + 1) = v.at(j);
            j--; // comparing the key down the list right to left
        }
        // insert the key at the position where the left is smaller and sorted
        v[j + 1] = key;
    }
    return v;
}

int main()
{
    // create csv file to output for analysis in excel
    std::ofstream csv_file;
    csv_file.open("insertTime.csv");
    // write headers
    csv_file << "n,time\n";

    for (int n = 5000; n <= 5000*20; n += 5000) {
        std::vector<int> v =  generate_vector(n);
        // get time before and after and subtract them
        auto time1 = std::chrono::high_resolution_clock::now();
        // sort
        insertsort(v);
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


