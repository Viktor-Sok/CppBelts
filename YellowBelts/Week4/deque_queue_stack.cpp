#include <iostream>
#include <deque>
#include <algorithm> // all the algorithms with iterators

using namespace std;
// deque - double ended queue, push_front/back; pop_front/back are equally fast, d[i] -- access by index
// #inlude <queue> only push (to front) and pop (from back), pick front/back, check whether is empty
// #include <stack> only push/pop (from the end), top, size and empty
int main() {
    deque<int> d = {1, 2, 3};
    d.pop_back();
    d.pop_front();
    d.push_back(4);
    d.push_front(4);
    for (const auto& i : d) {
        cout << i << " ";
    }
    return 0;
}