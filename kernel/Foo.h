//
// Created by merskip on 17.01.18.
//

#pragma once

#if __cplusplus

class Foo {

public:
    void bar();

};

#endif

#ifdef __cplusplus
extern "C" {
#endif

void foo(void);

#ifdef __cplusplus
}
#endif