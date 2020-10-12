// Gregory D. Stula
// CS 325 Fall 2020
// Homework 1 Problem 5
// Octobor 3, 2020

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <random>
#include <chrono>

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

// merges two sorted vectors in descending order
std::vector<int> merge(std::vector<int> left, std::vector<int> right)
{
    std::vector<int> output;

    while (left.size() > 0 || right.size() > 0) {
        if (left.size() > 0 && right.size() > 0) {
            // compare the heads of the two lists
            if (left.front() >= right.front()) {
                // push back the smaller value
                output.push_back(left.front());
                // erase the value from the orignal vector
                left.erase(left.begin());
            }
            else {
                // push back the larger value
                output.push_back(right.front());
                // erase the value from the original vector
                right.erase(right.begin());
            }

        // copy the rest of the vector if any
        }
        else if (left.size() > 0) {
            for (auto&& i : left) {
                output.push_back(i);
            }
            break;
        }
        else if (right.size() > 0) {
            for (auto&& i : right) {
                output.push_back(i);
            }
            break;
        }
    }
    return output;
}

// merge sort algorithm dependent on the merge subroutine
std::vector<int> mergesort(std::vector<int> input)
{
    if (input.size() <= 1) {
        return input;
    }

    std::vector<int> left;
    std::vector<int> right;
    std::vector<int> sorted;

    int middle = static_cast<int>(input.size() + 1) / 2;
    int input_size = static_cast<int>(input.size());

    // divide array
    for (int i = 0; i < middle; i++) {
        left.push_back(input.at(i));
    }
    for (int i = middle; i < input_size; i++) {
        right.push_back(input.at(i));
    }

    // recusively divide
    left = mergesort(left);
    right = mergesort(right);
    // merge sorted arrays
    sorted = merge(left, right);

    return sorted;
}

int main()
{
    // create csv file to output for analysis in excel
    std::ofstream csv_file;
    csv_file.open("mergeTime.csv");
    // write headers
    csv_file << "n,time\n";

    for (int n = 5000; n <= 5000*20; n += 5000) {
        std::vector<int> v =  generate_vector(n);
        // get time before and after and subtract them
        auto time1 = std::chrono::high_resolution_clock::now();
        // sort
        v = mergesort(v);
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


