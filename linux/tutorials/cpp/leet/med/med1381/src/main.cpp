#include "leet.h"
#include "print.h"

#include <stdint.h>

using namespace Print;

int main() {
    CustomStack st(3);
    st.push(1);
    st.push(2);
    print(st.pop());
    st.push(2);
    st.push(3);
    st.push(4);
    st.increment(5, 100);
    st.increment(2, 100);
    print(st.pop());
    print(st.pop());
    print(st.pop());
    print(st.pop());
    print(st);
    return 0;
}
