## cevent - Event bus on pure C

#### How to use

You need to define CEVENT_IMPLEMENTATION before first include (this is necessary to ensure that the implementation is defined only once)

```c
//main.c
#define CEVENT_IMPLEMENTATION
#include "cevent.h"

enum {
    OnMessage = 0,
    OnDestroyScene
} typedef EventType;

struct {
    const char* someInfo;
} typedef PayloadExample;

int main(void) {
    PayloadExample pd = { test_str };
    if (!cevent_subscribe(OnMessage, handler)) {
        exit(1);
    }

    cevent_publish(OnMessage, (void*) &pd);
    cevent_publish(OnMessage, (void*)&pd);
    cevent_unsubscribe(handler);
}

```

#### List of features:
TODO: comming soon