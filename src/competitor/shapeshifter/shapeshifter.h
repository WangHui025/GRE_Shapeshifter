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

  long long memory_consumption() { return index.total_lipp_alex_size(); }

private:
  fiting::BPTree<KEY_TYPE, PAYLOAD_TYPE> index;
};

template<class KEY_TYPE, class PAYLOAD_TYPE>
void shapeshifterInterface<KEY_TYPE, PAYLOAD_TYPE>::bulk_load(std::pair <KEY_TYPE, PAYLOAD_TYPE> *key_value, size_t num,
                                                      Param *param) {
  // index.construct(key_value,num);
  index.lipp_construct(key_value,num);
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool shapeshifterInterface<KEY_TYPE, PAYLOAD_TYPE>::get(KEY_TYPE key, PAYLOAD_TYPE &val, Param *param) {
  // PAYLOAD_TYPE *res = index.search(key);
  // if (res != nullptr) {
  //   val = *res;
  //   // delete res; // 删除动态分配的内存
  //   return true;
  // }
  // auto res = index.search(key);
  // if (res.has_value()) {
  //     val = res.value();
  //     return true;
  // }

  // auto start_time = std::chrono::high_resolution_clock::now();

  // std::optional<PAYLOAD_TYPE*> opt_res = index.search(key);  // 获取 optional 结果

  // // 记录结束时间
  // auto end_time = std::chrono::high_resolution_clock::now();
  
  // // 计算持续时间，单位为纳秒
  // auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
  
  // // 输出持续时间
  // std::cout << "BTree Time taken for index.search(key): " << duration << " ns" << std::endl;

  if (index.lipp_search(key).has_value()) {
  // if (index.search(key).has_value()) {
    // val = *(opt_res.value());  // 提取 optional 中的值
    return true;
  }
  return false;
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool shapeshifterInterface<KEY_TYPE, PAYLOAD_TYPE>::put(KEY_TYPE key, PAYLOAD_TYPE value, Param *param) {
  // State result = index.delta_insert(key,value);
  // return !result;

  // return index.insert_wh(key, value).second;

  return index.lipp_insert(key, value);
}

template<class KEY_TYPE, class PAYLOAD_TYPE>
bool shapeshifterInterface<KEY_TYPE, PAYLOAD_TYPE>::update(KEY_TYPE key, PAYLOAD_TYPE value, Param *param) {
    // return index.update(key, value);
    return false;
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
      // // return index.range_scan(key_low_bound,key_num,result);
      // if(!result) {
      //     result = new std::pair <KEY_TYPE, PAYLOAD_TYPE>[key_num];
      // }
  return index.lipp_scan(result, key_low_bound, key_num);

  // auto iter = index.lipp_lower_bound(key_low_bound);
  // int scan_size = 0;
  // for (scan_size = 0; scan_size < key_num && !iter.is_end(); scan_size++) {
  //   result[scan_size] = {(*iter).first, (*iter).second};
  //   iter++;
  // }
  // return scan_size;
}