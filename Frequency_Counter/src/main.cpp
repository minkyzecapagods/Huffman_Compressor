#include "../include/frequencyCounter.hpp"
#include "../include/utils.hpp"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

int main (int argc, char* argv[]){

    if(argc != 2){
        cerr << "Error: incorrect number of arguments!" << endl;
        return 1;
    }
    string path = argv[1];

    getFullCharMap();

    // if path is a directory, process every .cpp file inside
    fs::path p(path);
    if (fs::exists(p) && fs::is_directory(p)) {
        for (const auto& entry : fs::directory_iterator(p)) {
            if (!entry.is_regular_file()) continue;
            if (entry.path().extension() == ".cpp" || entry.path().extension() == ".hpp") {
                processFile(entry.path().string());
            }
        }
    } else {
        // single file
        processFile(path);
    }

    sortedTokens = unifyAndSort(stringFrequency, charFrequency);

    printToFile("output");

    return 0;
}