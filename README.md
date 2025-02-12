## cevent - Event bus on pure C

#### USAGE

You need to define CEVENT_IMPLEMENTATION before first include (this is necessary to ensure that the implementation is defined only once) !
 
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

void handler(int event, void* payload) {
    PayloadExample* p = (PayloadExample*) payload;
    printf("[Message received]: %s\n", p->someInfo);
}

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

You can also make a convenient header file and override the functions to suit your code style, and override the length of the subscribers array and tie it to, say, the number of your events.
For example:

```c
// events.h
#ifndef CEVENT_EVENT_TYPES_H
#define CEVENT_EVENT_TYPES_H

enum {
    SomeEvent = 0,
    DifferentEvent,
    AnotherOne,
    //---------------------
    LENGTH
} typedef EventType;

#define CEVENT_MAX_SUBSCRIBERS LENGTH

#include "cevent.h"

#define EmitEvent cevent_publish
#define OnEvent cevent_subscribe

#endif
```

And then:

```c
// main.c
#define CEVENT_IMPLEMENTATION
#include "events.h"

void handler(EventType event, void* omit) {
    // Do something...
}

int main(void) {
    OnEvent(SomeEvent, handler);
    OnEvent(DifferentEvent, handler);
    //...
    EmitEvent(DifferentEvent, NULL);
    EmitEvent(SomeEvent, NULL);
}

```
