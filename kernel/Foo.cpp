//
// Created by merskip on 17.01.18.
//

#include "Foo.h"
extern "C" {
#include "string.h"
}

void Foo::bar() {
    printf("Hello world from C++ :-)\n");
}


void foo() {
    Foo().bar();
}