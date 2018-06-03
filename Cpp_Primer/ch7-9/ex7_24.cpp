#include <iostream>
#include <string>
using std::string;

class Screen {
public:
    using pos = string::size_type;
    Screen() = default;
    Screen(pos ht, pos wd, int n): height(ht), width(wd), contents(n, ' ') {}
    Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht*wd, c) {}
    char get() const { return contents[cursor]; }
    inline char get(pos ht, pos wd) const;
    Screen &move(pos r, pos c);
    void some_member() const;
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    string contents;
    mutable size_t access_ctr;
};

inline
Screen &Screen::move(pos r, pos c) {
    pos row = r * width;
    cursor = row + c;
    return *this;
}

char Screen::get(pos r, pos c) const {
    pos row = r * width;
    return contents[row+c];
}

void Screen::some_member() const {
    ++access_ctr;
}

int main() {

    return 0;
}
