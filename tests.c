#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "string.h"

#define CEVENT_IMPLEMENTATION
#include "cevent.h"

enum {
    OnMessage = 0,
    OnDestroyScene
} typedef EventType;

struct {
    const char* someInfo;
} typedef PayloadExample;

static int test_counter = 0;
static const char* test_str = "Test examle string";

void handler(int event, void* payload) {
    PayloadExample* p = (PayloadExample*) payload;
    printf("[Message received]: %s\n", p->someInfo);
    test_counter++;
    assert(strcmp(test_str, p->someInfo) == 0);
}

int main(void) {
    PayloadExample pd = { test_str };
    if (!cevent_subscribe(OnMessage, handler)) {
        exit(1);
    }
    cevent_publish(OnMessage, (void*) &pd);
    cevent_unsubscribe(handler);
    cevent_publish(OnMessage, (void*)&pd);
    assert(test_counter == 1);
}
