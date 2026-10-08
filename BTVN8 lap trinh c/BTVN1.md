## 1. Mô tả lỗi

Chương trình có nhiệm vụ duyệt danh sách 4 tài khoản và kiểm tra số ngày quá hạn thanh toán.

Quy tắc nghiệp vụ:

* `days_overdue <= 3`: Tài khoản **Hop le**, được tính phí tháng vào tổng doanh thu.
* `days_overdue > 3`: Tài khoản **Qua han**, không được tính phí tháng vào tổng doanh thu.

Lỗi xuất hiện trong vòng lặp `for`.

Mã nguồn cũ sử dụng:

```c
if (user_list[0].days_overdue <= 3)
```

và:

```c
total_revenue += user_list[0].monthly_fee;
```

Trong khi vòng lặp đang sử dụng biến `i` để duyệt từng phần tử.

## 2. Phân tích nguyên nhân lỗi

Mảng `user_list` có 4 phần tử:

* `user_list[0]`: tài khoản 1001
* `user_list[1]`: tài khoản 1002
* `user_list[2]`: tài khoản 1003
* `user_list[3]`: tài khoản 1004

Vòng lặp:

```c
for (i = 0; i < 4; i++)
```

có nghĩa là `i` lần lượt nhận các giá trị:

```text
0 → 1 → 2 → 3
```

Do đó khi kiểm tra phần tử hiện tại phải sử dụng:

```c
user_list[i]
```

Tuy nhiên code cũ lại sử dụng cố định:

```c
user_list[0]
```

Điều này làm chương trình luôn kiểm tra tài khoản đầu tiên có `days_overdue = 0`.

Vì `0 <= 3` nên điều kiện luôn đúng trong cả 4 lần lặp.

Do đó:

* Tài khoản 1002 quá hạn 5 ngày vẫn bị in là `Hop le`.
* Tài khoản 1004 quá hạn 4 ngày vẫn bị in là `Hop le`.
* Phí tháng của tài khoản 1001 bị cộng lặp lại 4 lần.

Đây là lỗi **array indexing bug** và đồng thời gây ra lỗi logic nghiệp vụ.

## 3. Dòng lệnh sai

### Lỗi 1: Kiểm tra sai phần tử

Code sai:

```c
if (user_list[0].days_overdue <= 3)
```

Code đúng:

```c
if (user_list[i].days_overdue <= 3)
```

### Lỗi 2: Cộng sai phí tháng

Code sai:

```c
total_revenue += user_list[0].monthly_fee;
```

Code đúng:

```c
total_revenue += user_list[i].monthly_fee;
```

Hai lỗi trên đều xuất phát từ việc sử dụng chỉ số cố định `0` thay vì chỉ số `i` của vòng lặp.

## 4. Test Cases

| Trường hợp kiểm thử                          | Dữ liệu đầu vào                                                                                   | Kết quả sai thực tế           | Kết quả đúng mong đợi                     |
| -------------------------------------------- | ------------------------------------------------------------------------------------------------- | ----------------------------- | ----------------------------------------- |
| TC01 - Kiểm tra trạng thái tài khoản quá hạn | User 1002, `monthly_fee = 90000`, `days_overdue = 5`                                              | Hiển thị `Hop le`             | Hiển thị `Qua han`, không cộng 90.000 VND |
| TC02 - Kiểm tra tổng doanh thu               | 4 tài khoản: 1001 = 180000/0 ngày, 1002 = 90000/5 ngày, 1003 = 260000/1 ngày, 1004 = 90000/4 ngày | Tổng doanh thu = `720000 VND` | Tổng doanh thu = `440000 VND`             |

## 5. Tính toán kết quả đúng

Tài khoản 1001:

```text
days_overdue = 0 <= 3
=> Hop le
=> +180000
```

Tài khoản 1002:

```text
days_overdue = 5 > 3
=> Qua han
=> +0
```

Tài khoản 1003:

```text
days_overdue = 1 <= 3
=> Hop le
=> +260000
```

Tài khoản 1004:

```text
days_overdue = 4 > 3
=> Qua han
=> +0
```

Tổng doanh thu:

```text
180000 + 260000 = 440000 VND
```

## 6. Kết quả sau khi sửa

Chương trình sau khi sửa sẽ cho kết quả:

```text
=== DANH SACH TAI KHOAN SUBSCRIPTION ===
MA TK      PHI THANG    NO CUOC (NGAY)   TRANG THAI
---------------------------------------------------
1001       180000       0                Hop le
1002       90000        5                Qua han
1003       260000       1                Hop le
1004       90000        4                Qua han
---------------------------------------------------
Tong doanh thu thuc thu: 440000 VND
```

## 7. Kết luận

Lỗi của chương trình nằm ở việc sử dụng `user_list[0]` bên trong vòng lặp thay vì `user_list[i]`.

Sau khi thay thế đúng chỉ số mảng:

```c
user_list[i]
```

chương trình đã duyệt đúng từng tài khoản, xác định đúng trạng thái và tính chính xác tổng doanh thu thực thu theo quy định nghiệp vụ.

Kết quả cuối cùng:

```text
Tong doanh thu thuc thu: 440000 VND
```
