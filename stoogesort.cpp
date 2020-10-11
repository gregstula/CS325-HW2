// Gregory D. Stula
// CS 325 Fall 2020
// Homework 2 Problem 5a
// Octobor 11, 2020

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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

void write_vector(std::vector<int> v)
{
    std::ofstream insert_out;
    // open the file and set to append the file
    insert_out.open("stooge.out", std::ios_base::app);

    int size = static_cast<int>(v.size());
    for (int i = 0; i < size; i++) {
        insert_out << v.at(i) << " ";
    }
    insert_out << std::endl;
    insert_out.close();
}

int main()
{
    std::string line;
    std::vector<int> nums;

    // open the data file
    std::ifstream data;
    data.open("data.txt");

    // get the line
    while (std::getline(data, line)) {
        // convert line into a input string stream
        std::istringstream iss(line);
        int num;
        // store the numbers in the vector
        while (iss >> num) {
            nums.push_back(num);
        }

        // sort
        stoogesort(nums, 0, nums.size() - 1);
        // write to file
        write_vector(nums);
        // clear the vector
        nums.clear();
    }
    return 0;
}
