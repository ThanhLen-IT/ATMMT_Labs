# Lab 01: Classical Cryptography (Mật mã học Cổ điển)

**Trường Đại học Công nghệ Thông tin - ĐHQG-HCM (UIT)** **Môn học:** An toàn mạng máy tính (NT101.Q22)  

## 👥 Danh sách thành viên nhóm 03

| STT | Họ và tên | MSSV |
| :--- | :--- | :--- | 
| 1 | Khương Thành Lên | 24520949 | 
| 2 | Trần Kim Ngân | 24521135] | 
| 3 | Trần Minh Toàn | 24521798  |

---

## 🎯 1. Mục tiêu bài Lab
Bài lab này giúp nhóm sinh viên làm quen và hiểu rõ cơ chế hoạt động của các hệ thống mật mã cổ điển trước kỷ nguyên máy tính. Mục tiêu cụ thể bao gồm:
* Nắm vững các khái niệm cơ bản về mật mã đối xứng, mã hóa khối, các thao tác thay thế (substitution) và hoán vị (permutation).
* Tự tay lập trình và cài đặt các thuật toán mã hóa/giải mã cơ bản.
* Áp dụng các kỹ thuật thám mã (phá mã) dựa trên toán học và thống kê ngôn ngữ (như Phân tích tần suất - Frequency Analysis, Chỉ số trùng hợp - Index of Coincidence) để giải mã văn bản khi không biết khóa.

---

## 📚 2. Nội dung chính & Cấu trúc thư mục

Kho mã nguồn này chứa các chương trình giải quyết 7 nhiệm vụ thực hành của Lab 01, được chia thành các thư mục tương ứng:

* **`Task2.1_Caesar/`**: Chương trình mã hóa, giải mã và tấn công Brute-force thuật toán Caesar Cipher.
* **`Task2.2_Task2.3_Monoalphabetic/`**: Phân tích tần suất (Frequency Analysis) thủ công và chương trình hỗ trợ giải mã tự động thuật toán Mono-alphabetic Substitution Cipher.
* **`Task2.4_Playfair/`**: Chương trình mã hóa và giải mã Playfair Cipher sử dụng ma trận khóa 5x5.
* **`Task2.5_Task2.6_Vigenere/`**: Chương trình mã hóa, giải mã Vigenère Cipher và công cụ phá mã Vigenère tự động (Ciphertext-only attack) dựa trên IC và Chi-squared.
* **`Task2.7_Extended/`**: Cài đặt thuật toán mật mã cổ điển mở rộng tự chọn (Thuật toán: Rail Fence Cipher).

*(Lưu ý: Các file dữ liệu bản rõ `plaintext.txt` và bản mã `ciphertext.txt` được đính kèm bên trong từng thư mục tương ứng).*


---
## 🚀 3. Ngôn ngữ thực hiện: C++
