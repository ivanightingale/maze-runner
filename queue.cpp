#include "queue.h"

Queue::Queue(int maxlen) {
   contents = new Location[maxlen];
   head = 0;
   tail = 0;
}

Queue::~Queue() {
   delete[] contents;
}

void Queue::add_to_back(Location loc) {
   contents[tail].row = loc.row;
   contents[tail].col = loc.col;
   tail++;
}

Location Queue::remove_from_front() {
    return contents[head++];
}

bool Queue::is_empty() {
   return head == tail;
}
