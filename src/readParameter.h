#include <fstream>
#include <string>

class ReadParameter {
public:
ReadParameter(const std::string filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        auto delimiterPos = line.find("=");
        auto name = line.substr(0, delimiterPos);
        auto value = line.substr(delimiterPos + 1);

        // Trim spaces around the name and value
        name.erase(0, name.find_first_not_of(' '));  // trim leading spaces
        name.erase(name.find_last_not_of(' ') + 1);  // trim trailing spaces
        value.erase(0, value.find_first_not_of(' '));  // trim leading spaces
        value.erase(value.find_last_not_of(' ') + 1);  // trim trailing spaces

        if (name == "numMountains") {
            numMountains = std::stoi(value);
        }
    }
}

    int getNumMountains() const {
        return numMountains;
    }

private:
    int numMountains = 0;
};