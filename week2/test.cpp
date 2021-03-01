#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<tuple>
#include<vector>
#include<string>
#include<algorithm>


int main() {
    std::vector<std::string> double_vector;

    double_vector.push_back("word1");
    double_vector.push_back("word2");
    double_vector.push_back("word3");

    std::vector<std::string>::iterator vector_begin{double_vector.begin()};
    std::vector<std::string>::iterator vector_end{double_vector.end()};

    std::sort(vector_begin, vector_end);

    std::cout<<"sorted data"<<std::endl;
    std::vector<std::string>::iterator vector_iterator;
    for(vector_iterator=vector_begin; vector_iterator<vector_end;++vector_iterator)
    std::cout <<*vector_iterator<<std::endl;
    return 0;    

}
