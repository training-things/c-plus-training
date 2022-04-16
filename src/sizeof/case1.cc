#include <iostream>

class BufferEntry {
 public:
  static const size_t buffer_size = 64 * 1024;
  BufferEntry* next;

  void reset() {
    next = NULL;
    cur_pos = buffer;
  }

  size_t remain() { return buffer_size - (cur_pos - buffer); }

  const char* save(const char* data, size_t len) {
    memcpy(cur_pos, data, len);
    cur_pos[len] = '\0';
    char* last_pos = cur_pos;
    cur_pos += len + 1;
    return last_pos;
  }

 private:
  char buffer[buffer_size];
  char* cur_pos;
};


int main() {
    std::cout << "BufferEntry sizeof " << sizeof(BufferEntry) << std::endl; // BufferEntry sizeof 65552

}

//  ObjectPool中 Block 和 BlockGroup 如上图，
//  每个 Block 是一个连续的内存，大小为sizeof(T) * 256，即256个 BufferEntry ，单个 Block 大小 = 65552 * 256 / 1024 / 1024 = 16MB
//  BlockGroup 里有 65536 个Block。


// 65552 * 
/*
class BufferPool {
 public:
  BufferPool() {
    head = butil::ObjectPool<BufferEntry>::singleton()->get_object();
    cur_buff = head;
    cur_buff->reset();
  }
  ~BufferPool() {
    for (BufferEntry* it = head; it != NULL;) {
      BufferEntry* next = it->next;
      butil::ObjectPool<BufferEntry>::singleton()->return_object(it);
      it = next;
    }
  }
  const char* save(const char* data, size_t len) {
    if (len >= BufferEntry::buffer_size) return NULL;
    if (len >= cur_buff->remain()) {
      cur_buff->next = butil::ObjectPool<BufferEntry>::singleton()->get_object();
      cur_buff = cur_buff->next;

      cur_buff->reset();
    }
    return cur_buff->save(data, len);
  }

 private:
  BufferEntry* head;
  BufferEntry* cur_buff;

  BufferPool(const BufferPool&) = delete;
  BufferPool& operator=(const BufferPool&) = delete;
};
*/