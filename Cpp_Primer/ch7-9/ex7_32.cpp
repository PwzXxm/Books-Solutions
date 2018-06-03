#include <iostream>
#include <vector>
#include <string>
using std::string;

class Screen;

class Window_mgr {
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);
private:
    std::vector<Screen> screens;
};

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

    Screen &set(char);
    Screen &set(pos, pos, char);

    Screen &display(std::ostream &os) { do_display(os); return *this; }
    const Screen &display(std::ostream &os) const { do_display(os); return *this; }
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    string contents;
    mutable size_t access_ctr;

    void do_display(std::ostream &os) const { os << contents; }

    friend void Window_mgr::clear(ScreenIndex);
};

void Window_mgr::clear(ScreenIndex i) {
    if (i >= screens.size()) return;
    Screen &s = screens[i];
    s.contents = std::string(s.height*s.width, ' ');
}

inline
Screen &Screen::set(char c) {
    contents[cursor] = c;
    return *this;
}

inline
Screen &Screen::set(pos r, pos col, char ch) {
    contents[r*width + col] = ch;
    return *this;
}

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

    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#').display(std::cout);
    std::cout << "\n";
    myScreen.display(std::cout);
    std::cout << "\n";

    return 0;
}
