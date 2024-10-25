#include"./src/src/src/bptree.h"
#include"../indexInterface.h"

#include <chrono>
#include <iostream>

template<class KEY_TYPE, class PAYLOAD_TYPE>
class shapeshifterInterface : public indexInterface<KEY_TYPE, PAYLOAD_TYPE> {
public:
  void init(Param *param = nullptr) {}

  void bulk_load(std::pair <KEY_TYPE, PAYLOAD_TYPE> *key_value, size_t num, Param *param = nullptr);

  bool get(KEY_TYPE key, PAYLOAD_TYPE &val, Param *param = nullptr);

  bool put(KEY_TYPE key, PAYLOAD_TYPE value, Param *param = nullptr);

  bool update(KEY_TYPE key, PAYLOAD_TYPE value, Param *param = nullptr);

  bool remove(KEY_TYPE key, Param *param = nullptr);

  size_t scan(KEY_TYPE key_low_bound, size_t key_num, std::pair<KEY_TYPE, PAYLOAD_TYPE> *result,
              Param *param = nullptr);

  long long memory_consumption() { return index.total_ss_size(); }

private:
  ss::BPTree<KEY_TYPE, PAYLOAD_TYPE> index;
};

template<class KEY_TYPE, class PAYLOAD_TYPE>
void shapeshifterInterface<KEY_TYPE, PAYLOAD_TYPE>::bulk_load(std::pair <KEY_TYPE, PAYLOAD_TYPE> *key_value, size_t num,
                                                      Param *param) {
  index.ss_construct(key_value,num);
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool shapeshifterInterface<KEY_TYPE, PAYLOAD_TYPE>::get(KEY_TYPE key, PAYLOAD_TYPE &val, Param *param) {
  if (index.ss_search(key).has_value()) {
    return true;
  }
  return false;
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool shapeshifterInterface<KEY_TYPE, PAYLOAD_TYPE>::put(KEY_TYPE key, PAYLOAD_TYPE value, Param *param) {
  return index.ss_insert(key, value);
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool shapeshifterInterface<KEY_TYPE, PAYLOAD_TYPE>::update(KEY_TYPE key, PAYLOAD_TYPE value, Param *param) {
    // return index.update(key, value);
    return true;
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool shapeshifterInterface<KEY_TYPE, PAYLOAD_TYPE>::remove(KEY_TYPE key, Param *param) {
    auto num_erase = index.erase(key);
    return num_erase > 0;
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
size_t shapeshifterInterface<KEY_TYPE, PAYLOAD_TYPE>::scan(KEY_TYPE key_low_bound, size_t key_num,
                                                   std::pair<KEY_TYPE, PAYLOAD_TYPE> *result,
                                                   Param *param) {
  return index.ss_scan(result, key_low_bound, key_num);
}