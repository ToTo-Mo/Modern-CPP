#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <string>


int CountLines(const std::string& filepath)
{
    std::ifstream in(filepath);

    return std::count(
        std::istreambuf_iterator<char>(in),
        std::istreambuf_iterator<char>(),
        '\n'
    );
}

std::ifstream OpenFile(const std::string filepath)
{
    return std::ifstream(filepath);
}


int CountLinesInFiles(const std::vector<std::string>& filepaths)
{

    std::vector<int> results(filepaths.size());

    std::transform(filepaths.cbegin(), filepaths.cend(), results.begin(), CountLines);

    return std::accumulate(results.begin(),results.end(), 0);
}

int main()
{
    std::vector<std::string> filepaths;

    filepaths.push_back(R"(FuntionalProgramming\Overview\CountLinesInFiles\sample\Cinderella.txt)");
    filepaths.push_back(R"(FuntionalProgramming\Overview\CountLinesInFiles\sample\The Funny Little Woman.txt)");
    filepaths.push_back(R"(FuntionalProgramming\Overview\CountLinesInFiles\sample\The Talking Eggs.txt)");

    std::cout<<CountLinesInFiles(filepaths)<<std::endl;
}
