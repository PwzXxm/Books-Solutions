#include <iostream>
#include <map>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sstream>
using std::string, std::map, std::ifstream, std::runtime_error, std::istringstream, std::cout, std::endl;

const string &transform(const string &s, const map<string,string> &m) {
    auto map_it = m.find(s);

    if (map_it != m.cend()) {
        return map_it->second;
    } else {
        return s;
    }
}


map<string, string> buildMap(ifstream &map_file) {
    map<string, string> trans_map;
    string key;
    string value;
    while (map_file >> key && getline(map_file, value)) {
        if (value.size() > 1) {
            trans_map[key] = value.substr(1);
        } else {
            throw runtime_error("no rule for " + key);
        }
    }
    return trans_map;
}

void word_transform(ifstream &map_file, ifstream &input) {
    auto trans_map = buildMap(map_file);
    string text;
    while (getline(input, text)) {
        istringstream ss(text);
        string word;
        bool firstword = true;
        while (ss >> word) {
            if (firstword) {
                firstword = false;
            } else {
                cout << " ";
            }
            cout << transform(word, trans_map);
        }
        cout << endl;
    }
}

int main() {

    return 0;
}
