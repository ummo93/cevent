#ifndef CEVENT_H
#define CEVENT_H

typedef void (*cevent_callback)(int,void*);
void cevent_publish(int eventType,void* payload);

#ifdef CEVENT_IMPLEMENTATION

#ifdef GLOBAL_EVENT_BUS_IMPL

void cevent_setup(cevent_callback cb);
static cevent_callback globalHandler;

void cevent_setup(cevent_callback callback) {
    globalHandler = callback;
}

void cevent_publish(int eventType,void* payload) {
    globalHandler(eventType,payload);
}

#endif

#ifndef GLOBAL_EVENT_BUS_IMPL

typedef struct {
    int eventType;
    void (*callback)(int,void*);
} cevent_subscriber;

unsigned short cevent_subscribe(int eventType,cevent_callback cb);
void cevent_unsubscribe(cevent_callback cb);

#ifndef CEVENT_MAX_SUBSCRIBERS
#define CEVENT_MAX_SUBSCRIBERS 50
#endif

static cevent_subscriber subscribers[CEVENT_MAX_SUBSCRIBERS];
static int subscriberCount = 0;

unsigned short cevent_subscribe(int eventType,cevent_callback callback) {
    if(subscriberCount >= CEVENT_MAX_SUBSCRIBERS) {
        return 0;
    }
    subscribers[subscriberCount].eventType = eventType;
    subscribers[subscriberCount].callback = callback;
    subscriberCount++;
    return 1;
}

void cevent_publish(int eventType,void* payload) {
    for(int i = 0; i < subscriberCount; i++) {
        if(subscribers[i].eventType == eventType) {
            subscribers[i].callback(eventType,payload);
        }
    }
}

void cevent_unsubscribe(cevent_callback callback) {
    for(int i = 0; i < subscriberCount; i++) {
        if(subscribers[i].callback == callback) {
            for(int j = i; j < subscriberCount - 1; j++) {
                subscribers[j] = subscribers[j + 1];
            }
            subscriberCount--;
            break;
        }
    }
}
#endif
#endif
#endif
