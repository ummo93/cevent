#ifndef CEVENT_H
#define CEVENT_H

#ifndef CEVENT_MAX_SUBSCRIBERS
#define CEVENT_MAX_SUBSCRIBERS 50
#endif

typedef struct {
    int eventType;
    void (*callback)(int, void*);
} cevent_subscriber;

static cevent_subscriber subscribers[CEVENT_MAX_SUBSCRIBERS];
static int subscriberCount = 0;

inline unsigned short cevent_subscribe(int eventType, void (*callback)(int, void*)) {
    if (subscriberCount >= CEVENT_MAX_SUBSCRIBERS) {
        return 0;
    }
    subscribers[subscriberCount].eventType = eventType;
    subscribers[subscriberCount].callback = callback;
    subscriberCount++;
    return 1;
}

inline void cevent_publish(int eventType, void* payload) {
    for (int i = 0; i < subscriberCount; i++) {
        if (subscribers[i].eventType == eventType) {
            subscribers[i].callback(eventType, payload);
        }
    }
}

inline void cevent_unsubscribe(void (*callback)(int, void*)) {
    for (int i = 0; i < subscriberCount; i++) {
        if (subscribers[i].callback == callback) {
            for (int j = i; j < subscriberCount - 1; j++) {
                subscribers[j] = subscribers[j + 1];
            }
            subscriberCount--;
            break;
        }
    }
}

#endif