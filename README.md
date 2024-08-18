# GIỚI THIỆU GAME SHOOTFLY
---
## Giới thiệu chung
Game Shootfly là một trò chơi đơn giản nhưng thú vị, nơi bạn điều khiển một chiếc máy bay chiến đấu để bắn hạ các máy bay địch xuất hiện trên màn hình. Nhiệm vụ của bạn là bắn hạ càng nhiều máy bay địch càng tốt mà không để bị chúng va chạm.
![alt text](Home.png)

## Cài đặt
1. **Cài đặt `Visual Studio 2022`**

2. **Tải game**
Cách 1: Truy cập [link github](https://github.com/huynguyen1908/game_sdl2) và clone repository về bằng lệnh "git clone" trên terminal máy của bạn.
Cách 2: Chọn Code -> Download Zip. Giải nén code ra 1 folder.

3. **Mở file `Shootfly.sln` trong Visual Studio**
Thiết lập C/C++ Configuration(IntelliSense)
Các thư viện SDL cần thiết đã được thêm vào project(trong thư mục LibSdl2)
Đưa mode build về debug-x86
4. **Bấm vào `Local Windows Debugger` để khởi động game**

---
## Hướng Dẫn Chơi

- **Di chuyển**: Sử dụng các phím mũi tên  `←` `→` `↑` `↓`   hoặc `A` `D` `W` `S` để điều khiển máy bay di chuyển sang 2 bên và lên xuống để né đạn và kẻ thù.
- **Bắn**: Nhấn trái chuột để bắn đạn và phải chuột để bắn laze.
- **Mục tiêu**: Tiêu diệt càng nhiều máy bay địch càng tốt. Tránh va chạm với máy bay địch để không bị thua.
- **Kết thúc game**: Game kết thúc khi máy bay của bạn hết thanh máu.

---
# Một vài chức năng chính
- **Bắt đầu game**: ấn vào Start để chơi, Exit để thoát ra.
![alt text](Home.png)
- **Tạm dừng**: ấn phím `SPACE` để tạm dừng, ấn `Resume` để tiếp tục chơi.
![alt text](Pause.png)
- **Tính điểm**: mỗi lần phá hủy 1 máy bay của địch thì sẽ được tính là 1 điểm, riêng 2 máy bay cố định màu đỏ thì tính 3 điểm.
- **Thanh máu**: Với mỗi lần va chạm với máy bay địch hoặc trúng đạn thì sẽ bị trừ 1 cọc, hết thanh máu tương ứng với 5 lần va chạm thì sẽ thua cuộc.
![alt text](Blood-and-point.png)
- **Âm thanh**: âm thanh khi bắn đạn, khi va chạm,...

---
## Các công nghệ sử dụng
- Ngôn ngữ phát triển: C++
- Thư viện đồ họa: SDL2
- Công cụ phát triển: Visual Studio 2022
- Trình quản lý: Github
## Các kỹ thuật được sử dụng
- Áp dụng lập trình hướng đối tượng OOP trong việc quản lý các đối tượng có trong game.
- Xử lý va chạm, tính toán điểm va chạm.
- Xử lý dữ kiện bàn phím, âm thanh, hình ảnh.
---
## Nguồn tham khảo
- [LazyFoo SDL Tutorial](https://lazyfoo.net/tutorials/SDL/index.php)
- [Lập trình game C++](https://www.youtube.com/c/Ph%C3%A1tTri%E1%BB%83nPh%E1%BA%A7nM%E1%BB%81m123AZ)
- [Aircraft-Battle](https://github.com/ConstantSun/Aircraft-Battle-2.6)