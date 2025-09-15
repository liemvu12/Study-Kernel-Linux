# 📑 Bài tập vận dụng STL

## 1. `vector`

* **Bài tập**:

  1. Đọc n số, lưu vào `vector`, in ra đảo ngược.
  2. Xóa tất cả số lẻ trong vector.
  3. LeetCode #88 – *Merge Sorted Array*.
* **Mục tiêu**: làm quen push\_back, erase, duyệt.

---

## 2. `string`

* **Bài tập**:

  1. Đếm số lần xuất hiện của ký tự ‘a’ trong chuỗi.
  2. In chuỗi con từ vị trí i đến j.
  3. LeetCode #344 – *Reverse String*.
  4. LeetCode #125 – *Valid Palindrome*.
* **Mục tiêu**: `substr`, `find`, `push_back`, so sánh chuỗi.

---

## 3. `stack`

* **Bài tập**:

  1. Kiểm tra biểu thức ngoặc đúng/sai (`()[]{}`).
  2. Chuyển số thập phân sang nhị phân bằng stack.
  3. LeetCode #20 – *Valid Parentheses*.
  4. LeetCode #155 – *Min Stack*.
* **Mục tiêu**: push, pop, top, empty.

---

## 4. `queue` & `deque`

* **Bài tập**:

  1. Mô phỏng hàng đợi: nhập vào n người, lần lượt ra theo FIFO.
  2. LeetCode #933 – *Number of Recent Calls* (dùng queue).
  3. LeetCode #239 – *Sliding Window Maximum* (dùng deque).
* **Mục tiêu**: FIFO cơ bản, sliding window.

---

## 5. `set` & `unordered_set`

* **Bài tập**:

  1. Nhập n số, in ra tập hợp không trùng, tự động sắp xếp.
  2. Kiểm tra xem 2 mảng có phần tử chung không.
  3. LeetCode #217 – *Contains Duplicate*.
  4. LeetCode #349 – *Intersection of Two Arrays*.
* **Mục tiêu**: tính unique, kiểm tra tồn tại.

---

## 6. `map` & `unordered_map`

* **Bài tập**:

  1. Đếm tần suất ký tự trong chuỗi.
  2. Đếm số lần xuất hiện mỗi số trong mảng.
  3. LeetCode #1 – *Two Sum*.
  4. LeetCode #242 – *Valid Anagram*.
* **Mục tiêu**: key-value, count, truy cập nhanh.

---

## 7. `priority_queue`

* **Bài tập**:

  1. Cho n số, in ra theo thứ tự giảm dần bằng max-heap.
  2. Tìm k phần tử lớn nhất.
  3. LeetCode #215 – *Kth Largest Element in an Array*.
  4. LeetCode #1046 – *Last Stone Weight*.
* **Mục tiêu**: luyện min-heap, max-heap.

---

## 8. `<algorithm>` cơ bản

* **Bài tập**:

  1. Sắp xếp mảng số nguyên.
  2. Xóa số trùng bằng `unique+erase`.
  3. LeetCode #35 – *Search Insert Position* (dùng `lower_bound`).
  4. LeetCode #278 – *First Bad Version*.
* **Mục tiêu**: `sort`, `unique`, `lower_bound`, `upper_bound`.

---

## 9. `pair`, `tuple`

* **Bài tập**:

  1. Lưu danh sách học sinh (id, điểm), sắp xếp theo điểm.
  2. LeetCode #1122 – *Relative Sort Array* (dùng pair index+value).
  3. Tạo `tuple<int,string,double>`, in ra giá trị.
* **Mục tiêu**: nhóm dữ liệu, custom comparator.

---

## 10. `bitset`

* **Bài tập**:

  1. Lưu dãy 0/1 bằng bitset, đếm số bit 1.
  2. LeetCode #401 – *Binary Watch*.
  3. LeetCode #191 – *Number of 1 Bits*.
* **Mục tiêu**: `set`, `count`, thao tác bit nhanh.

---

## 11. `multiset`, `multimap`

* **Bài tập**:

  1. Lưu nhiều bản ghi trùng nhau, xóa 1 bản ghi.
  2. LeetCode #480 – *Sliding Window Median* (dùng multiset).
* **Mục tiêu**: cho phép phần tử trùng.

---

## 12. Nâng cao

* **`nth_element`**: tìm median trong O(n).

  * Bài: LeetCode #973 – *K Closest Points to Origin*.
* **`partial_sort`**: lấy k phần tử nhỏ nhất.
* **`stable_sort`**: sắp xếp ổn định (dữ liệu giữ nguyên thứ tự nếu bằng nhau).
* **Bẫy `unique` không sort trước**: thử chạy với vector chưa sort để thấy duplicates còn sót.

---
