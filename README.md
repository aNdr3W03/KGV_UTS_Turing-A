# KGV_UTS_Turing-A
#### Ujian Tengah Semester Mata Kuliah Komputer Grafik dan Visualisasi
#### Dosen Pengampu: Jos Timanta Tarigan, S.Kom., M.Sc.
#### Ilmu Komputer - Universitas Sumatera Utara

# 
**Kelompok Alan Turing Kom A**  
**1. 201401032 - Al Imamul Luthfi**  
**2. 201401035 - Andrew Benedictus Jamesie**  
**3. 201401038 - Ariel Matius Surbakti**  
**4. 201401040 - Avin Chaili Salim**  

**YouTube Video**  
[![YouTube Video](screenshot/screenshot.jpg)](https://youtu.be/xxxxxxxxxxx)

# 
# UTS KGV Kelompok Turing-A
**UTS_ColorOctagon**
> - Project ini berupa program visual untuk menampilkan bangun datar segi delapan atau poligon segi delapan ( _octagon_) dengan warna acak (_random_) yang berbeda-beda untuk seitap bagiannya yang dibentuk dari delapan (8) segitiga. Bangun datar _octagon_ ini bisa berubah warna setiap detik dan bisa juga **mengubah warnanya** secara langsung dengan menekan tombol `C` di keyboard. Bangun data _octagon_ ini juga bisa diubah ukurannya dengan menekan tombol `panah kiri (←)` untuk **memperkecil** ukurannya, dan tombol `panah kanan (→)` untuk **memperbesar** ukurannya.
> - Folder ini merupakan project/solution **Console Application** Visual Studio, sehingga bisa di-_compile_ dan dijalankan dengan menggunakan Microsoft Visual Studio.
> - Dalam folder ini terdapat file Program `.sln` yang dapat dibuka dengan menggunakan Visual Studio.
> - Sedangkan jika hanya ingin melihat _source code_-nya akan dijelaskan di bawah.
> 
> **Colored Octagon**  
> ![Screenshot UTS KGV](screenshot/UTS_ColorOctagon.png)

# 
# Note:
#### Dalam folder ini terdapat 4 file yang penting, yaitu:
- **UTS_ColorOctagon.cpp**  
  Ini adalah file utama dari project/solution ini. Dalam file ini dilakukan pembuatan window untuk menampilkan gambar bangun datar _octagon_, perintah untuk mengganti warna dan ukuran, perintah untuk melakukan penggambaran dan pewarnaan bangun datar _octagon_ dengan `vertices vertexBuffer` dan `indexArr indexBuffer`, serta melakukan _link_ dan _bind_ dengan file `vertex.vert` dan `fragment.frag` untuk melakukan _render shader_.
- **Util.h**  
  Ini adalah file untuk menghubungkan file utama `UTS_ColorOctagon.cpp` dengan file vertex dan fragment, yaitu `vertex.vert` dan `fragment.frag`. File ini juga berfungsi untuk melakukan _debugging_ yang akan ditampilkan pada console/terminal pada saat menjalankan (_run_) program.
- **vertex.vert**  
  Ini adalah file untuk menentukan penggambaran posisi dari `vertices` dan `indexBuffer` yang akan dihubungkan dengan variabel uniform `size` untuk melakukan pengubahan ukuran gambar bangun datar _octagon_. Serta menentukan warna `color` yang diambil dari `vColor` dengan pointer location 1, sedangkan `vPos` dengan pointer location 0.
- **fragment.frag**  
  Ini adalah file untuk menentukan pewarnaan fragment color, yaitu `fragColor` yang diambil dari `color` milik `vertex.vert` untuk menghasilkan warna yang acak atau _random_.
