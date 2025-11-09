# 第一次实验报告

**姓名**: 宋家鑫  
**学号**: 2425121022  
**班级**: 24软件工程一班

---

## 实验任务

### Task 1: 顺序表的基本操作及有序表的合并

实现线性表的顺序存储结构（顺序表），支持：
- 基本操作：创建、插入（头插/尾插/按位置插）、查找、获取元素
- 工具操作：获取最大/最小值、反转、排序
- **核心算法**：两个有序表的合并（去重）

---

## 核心数据结构

### 顺序表（SqList）

**设计特点**：
- 基于动态数组实现
- 使用**环形缓冲区**（循环数组）设计，通过 `_startIndex` 偏移实现 O(1) 头插
- 支持自动扩容（容量不足时扩展为原来的 2 倍）

**关键成员变量**：
```cpp
int _physicsSize;   // 物理容量
int _size;          // 逻辑大小（实际元素个数）
int _startIndex;    // 起始索引（环形缓冲区偏移量）
T* _elems;          // 元素数组指针
```

**时间复杂度**：
- `insertHead()`: O(1)（通过偏移起始索引）
- `insertTail()`: O(1)（均摊，扩容时 O(n)）
- `insert(elem, index)`: O(n)（需要移动元素）
- `get(index)`: O(1)
- `sort()`: O(n²)（冒泡排序）
- `pureMerge()`: O(n + m)（双指针归并）

**空间复杂度**：O(n)

---

## 算法设计

### 1. 环形缓冲区索引映射

**逻辑索引 → 物理索引转换**：
```cpp
int getTrueIndex(int index) {
    return (_physicsSize + index + _startIndex) % _physicsSize;
}
```

**优势**：
- 头插操作无需移动元素，只需调整 `_startIndex`
- 避免频繁的数组复制

### 2. 动态扩容策略

```cpp
void resize(int newSize) {
    T* newElems = new T[newSize];
    for (int i = 0; i < _size; i++) {
        newElems[i] = get(i);  // 逻辑顺序复制
    }
    delete[] _elems;
    _elems = newElems;
    _physicsSize = newSize;
    _startIndex = 0;  // 重置起始索引
}
```

### 3. 有序表合并去重算法（核心）

**算法思路**（双指针 + 去重）：
1. 使用两个索引 `indexA` 和 `indexB` 分别指向两个有序表的当前位置
2. 每次取两个指针所指元素的较小值 `x`
3. **去重判断**：只有当 `x` 不等于结果表的末尾元素时才插入
4. **跳过重复元素**：将两个表中所有等于 `x` 的连续元素全部跳过
5. 当某一表遍历完毕时，调用 `pureSingleHelper` 追加剩余元素

**核心代码**：
```cpp
static SqList<T>* pureMerge(SqList<T>* listA, SqList<T>* listB) {
    SqList<T>* newList = new SqList(2 * (listA->size() + listB->size()));
    
    // 边界情况处理
    if (listA->isEmpty() && listB->isEmpty()) return newList;
    if (listA->isEmpty()) return pureSingleHelper(listB, newList);
    if (listB->isEmpty()) return pureSingleHelper(listA, newList);
    
    int indexA = 0, indexB = 0;
    while (true) {
        // 终止条件：某一表遍历完毕
        if (indexA >= listA->size()) {
            return pureSingleHelper(listB, newList, indexB);
        }
        if (indexB >= listB->size()) {
            return pureSingleHelper(listA, newList, indexA);
        }
        
        // 取较小值
        T a = listA->get(indexA);
        T b = listB->get(indexB);
        T x = min(a, b);
        
        // 去重插入：只有与末尾元素不同时才插入
        if (newList->isEmpty() || newList->get(newList->size() - 1) != x) {
            newList->insert(x);
        }
        
        // 跳过两个表中所有等于 x 的连续元素
        while (indexA < listA->size() && listA->get(indexA) == x) indexA++;
        while (indexB < listB->size() && listB->get(indexB) == x) indexB++;
    }
}
```

**辅助函数**：
```cpp
static SqList<T>* pureSingleHelper(SqList<T>* origin, SqList<T>* target, int fromIndex = 0) {
    for (int index = fromIndex; index < origin->size(); index++) {
        T v = origin->get(index);
        // 去重：只有与目标表末尾元素不同时才插入
        if (target->isEmpty() || !(target->get(target->size() - 1) == v)) {
            target->insert(v);
        }
    }
    return target;
}
```

---

## 测试用例

### Input 文件设计

#### input1.txt - 有重叠的有序表
```
5
1 2 3 4 5
6
2 3 4 5 6 7
```
**预期输出**：`1 2 3 4 5 6 7`  
**测试点**：普通有序表合并、部分元素重叠去重

---

#### input2.txt - 一个空表
```
0

3
1 2 3
```
**预期输出**：`1 2 3`  
**测试点**：边界情况（空表与非空表合并）

---

#### input3.txt - 全部重复元素
```
4
1 1 1 1
4
1 1 1 1
```
**预期输出**：`1`  
**测试点**：极端去重（所有元素相同）

---

#### input4.txt - 无重叠的交错表
```
5
1 3 5 7 9
5
2 4 6 8 10
```
**预期输出**：`1 2 3 4 5 6 7 8 9 10`  
**测试点**：完全交错的有序表（无重复元素）

---

#### input5.txt - 多重复元素混合
```
7
1 2 2 3 3 3 4
6
3 3 4 4 5 5
```
**预期输出**：`1 2 3 4 5`  
**测试点**：复杂去重（多处连续重复 + 跨表重复）

---

## 运行结果

### 测试命令
```powershell
g++ -o lab1.exe lab1.cpp -fexec-charset=utf-8
.\lab1.exe < input1.txt
.\lab1.exe < input2.txt
.\lab1.exe < input3.txt
.\lab1.exe < input4.txt
.\lab1.exe < input5.txt
```

### 实际输出
```
测试用例 1:
合并后的顺序表（已去重）: 1 2 3 4 5 6 7

测试用例 2:
合并后的顺序表（已去重）: 1 2 3

测试用例 3:
合并后的顺序表（已去重）: 1

测试用例 4:
合并后的顺序表（已去重）: 1 2 3 4 5 6 7 8 9 10

测试用例 5:
合并后的顺序表（已去重）: 1 2 3 4 5
```

**结论**：✅ 所有测试用例通过

---

## 关键实现要点

1. **环形缓冲区设计**：通过 `_startIndex` 偏移实现 O(1) 头插，避免大量元素移动
2. **动态扩容机制**：容量不足时自动扩展为 2 倍，并重新线性化数组（重置 `_startIndex`）
3. **去重策略**：利用有序性，只需与结果表末尾元素比较，避免全表扫描
4. **跳过重复元素**：双指针同步推进，跳过所有等于当前最小值的连续元素
5. **边界处理**：
   - 空表合并
   - 单表遍历完毕后的剩余元素追加
   - 索引越界保护

---

## 算法复杂度分析

### 时间复杂度
- **pureMerge 主循环**：O(n + m)
  - 每个元素最多被访问一次
  - 跳过重复元素的 while 循环总次数不超过 n + m
- **pureSingleHelper 追加剩余**：O(k)，k 为剩余元素数
- **总时间复杂度**：O(n + m)

### 空间复杂度
- 结果表空间：O(n + m)
- 辅助空间：O(1)（仅使用常数个变量）
- **总空间复杂度**：O(n + m)

---

## 可能的改进方向

1. **内存管理优化**：
   - 实现拷贝构造函数和赋值运算符（深拷贝）
   - 使用智能指针（`std::unique_ptr`）避免内存泄漏

2. **错误处理增强**：
   - 使用异常类代替字符串字面量
   - 添加更详细的错误信息（如越界时显示索引值）

3. **性能优化**：
   - 排序算法改用快速排序或归并排序（O(n log n)）
   - 扩容策略可采用更激进的增长因子（如 1.5 倍或黄金比例）

4. **功能扩展**：
   - 支持迭代器（Iterator）遍历
   - 实现 `erase()` 方法（按位置删除元素）
   - 支持自定义比较器（Comparator）用于排序和合并

---

## 实验总结

本次实验通过实现顺序表及其有序合并算法，深入理解了：
1. **线性表的顺序存储**：环形缓冲区设计显著优化了头插性能
2. **动态数组管理**：扩容策略和内存复制的权衡
3. **双指针算法**：利用有序性进行高效去重合并
4. **边界条件处理**：空表、全重复、无重叠等极端情况的鲁棒性

**实验难点**：
- 环形缓冲区的索引映射计算（负数取模问题）
- 去重逻辑的正确性（末尾比较 + 跳过连续重复）
- 扩容后的状态重置（`_startIndex` 归零）

**收获**：
- 掌握了模板类的设计和实现
- 理解了顺序表的物理存储与逻辑存储的映射关系
- 提升了算法设计和边界条件分析能力
