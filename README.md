# Laporan Soal Shift Modul 2

### Kelompok A04
- Ihsannur Rahman Qalbi 05111940000090
- Muhamad Fikri Sunandar 05111940000135
- Reyhan Naufal Rahman 05111940000171
### Daftar isi
1. [NO 1](#NO1)
2. [NO 2](#NO2)
3. [NO 3](#NO3)

## NO1
Soal nomor 1 membutuhkan konsep daemon dan konsep execv yang berjalan baik di dalam konsep fork. Maka no 1 membuat fungsi make_daemon untuk membuat daemon dan fungsi fork_f untuk mengeksekusi execv di dalam konsep fork. 
Fungsi make_daemon memiliki parameter pid untuk menyimpan id, sid ......, dan dirPath untuk menyimpan path yang akan menjadi root path dari fungsi daemon. Fungsi fork_f berisi parameter comm untuk menyimpan command apa yang akan dijalankan, dan argv[] untuk menyimpan argumen yang akan dijalankan oleh comm. Selanjutnya setelah membuat daemon dengan fungsi daemon di dalam while(1) diisi algoritma untuk menyelesaikan soal no 1. 
### 1a
Steven ingin membuat Musyik untuk mp3, Fylm untuk mp4, dan Pyoto untuk jpg maka dibuatlah fungsi make_folder yang berisi [[[code]]] dengan command mkdir untuk membuat folder yang diinginkan.
### 1b
Serta Steven akan mendownload musik, film, dan foto dari link yang disediakan. Penjelasan dibuat fungsi download_zip yang berisi argv link dan command yang sesuai dengan kebutuhan. 
### 1c
Steven tidak ingin filenya bertipe zip sehingga perlu mengekstraknya. 
Penjelasannya
Membuat fungsi extract_zip yang memiliki parameter dirPath untuk mempassing path yang akan melakukan proses unzip. Di dalam fungsi extract_zip terdapat variabel argv untuk menyimpan command unzip dan nama file zip yang akan diunzip. Selanjutnya memanggil fungsi fork_f untuk menjalankan command yang telah dibuat tadi. 
### 1d
Program memindahkan file yang telah diextrak ke folder yang telah dibuat tadi. Membuat fungsi move_file yang memiliki 2 parameter yakni dirPath untuk menyimpan path folder yang berisi semua file yang akan dipindahkan berada dan destPath yang berisi path yang akan dijadikan destinasi file tadi. Di dalam fungsi tersebut berisi algoritma untuk membua sebuah folder (dgn path yang disimpan di dirPath) dan membaca semua file di dalam folder tersebut lalu memindahkannya dengan command mv dan fungsi fork_f. 
### 1e
Stevan ingin program dari 1.a-1.d dijalankan 6 jam sebelum waktu ulang tahun si Stevany. Di dalam main membuat variabel integer yang berisi angka 58920 yang jika dikonversi ke waktu jam dan menit menjadi 16 jam 22 menit (waktu 6 jam sebelum ulang tahun). Variabel ini akan digunakan untuk pengkondisian pada nantinya program dijalankan, jika waktu yang diset telah terlewati atau sama maka program berjalan. 
### 1f
Stevan ingin ketika waktu ulang tahun si Stevany maka program akan menzip semua folder. Maka dibuat variabel lagi di main untuk menyimpan angka 80520 yang jika dikonversi akan menjadi jam yang sesuai dengan ulang tahun Stevany. Di dalam pengkondisian ulang tahun dengan variabel tadi dibuat memanggil dua fungsi yakni zip_folder dan delete_folder. Fungsi zip_folder berfungsi untuk menzip semua folder yang ada, sedangkan delete_folder untuk menghapus semua folder yang ada. Di dalam fungsi zip_folder berisi argv untuk menyimpan command zip dan nama file untuk menyimpan zip serta folder-folder yang akan dizip. Sedangkan, pada folder delete_folder disimpan fungsi command rm untuk menghapus semua folder yang ada. 
