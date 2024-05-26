#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
using namespace std;

const int Maks_Hewan = 100;
const int Maks_Member = 100; 

// Struct Hewan
struct Hewan {
    string habitat;
    string nama;
    int umur;
};

// Struct Member
struct Member {
    string username;
    int bintang;
    string komentar;
};

Hewan dataHewan[Maks_Hewan]; // Array datahewan
int jumlahHewan = 0;

Member dataMember[Maks_Member]; // Array datamember
int jumlahMember = 0;

// Fungsi untuk membaca data dari file CSV #1.
void baca_data_dari_file(const string& nama_file) {
    ifstream file(nama_file);
    file.is_open();
    string line;
    while (getline(file, line) && jumlahHewan < Maks_Hewan) {
        stringstream ss(line);
        string habitat, nama, umur_str;
        if (getline(ss, habitat, ',') && getline(ss, nama, ',') && getline(ss, umur_str)) {
            Hewan& hewan = dataHewan[jumlahHewan++];
            hewan.habitat = habitat;
            hewan.nama = nama;
            hewan.umur = stoi(umur_str);
        }
    }
    file.close();
}

// Fungsi untuk menyimpan data ke file CSV #.2
void simpan_data_ke_file(const string& nama_file) {
    ofstream file(nama_file);
    file.is_open();
    for (int i = 0; i < jumlahHewan; ++i) {
        file << dataHewan[i].habitat << ',' << dataHewan[i].nama << ',' << dataHewan[i].umur << '\n';
    }
    file.close();
}

// Fungsi untuk membaca data member dari file CSV #.3
void baca_data_member_dari_file(const string& nama_file) {
    ifstream file(nama_file);
    file.is_open();
    string line;
    while (getline(file, line) && jumlahMember < Maks_Member) {
        stringstream ss(line);
        string username, bintang_str, komentar;
        if (getline(ss, username, ',') && getline(ss, bintang_str, ',') && getline(ss, komentar)) {
            Member& member = dataMember[jumlahMember++];
            member.username = username;
            member.bintang = stoi(bintang_str);
            member.komentar = komentar;
        }
    }
    file.close();
}

// Fungsi untuk menyimpan data member ke file CSV #.4
void simpan_data_member_ke_file(const string& nama_file) {
    ofstream file(nama_file);
    file.is_open();
    for (int i = 0; i < jumlahMember; ++i) {
        file << dataMember[i].username << ',' << dataMember[i].bintang << ',' << dataMember[i].komentar << '\n';
    }
    file.close();
}

// Fungsi untuk menambahkan data hewan #.5
void tambahkan_data_hewan() {
    if (jumlahHewan >= Maks_Hewan) {
        cout << "Kapasitas Data Hewan Telah Mecapai Batas maksimal.\n";
        return;
    }
    Hewan& hewanBaru = dataHewan[jumlahHewan];
    cout << "Masukkan Habitat Hewan: ";
    cin.ignore();
    getline(cin, hewanBaru.habitat);
    cout << "Masukkan Nama Hewan: ";
    getline(cin, hewanBaru.nama); 
    while (true) {
        cout << "Masukkan Umur Hewan: ";
        if (cin >> hewanBaru.umur) {
            break;
        } else {
            cout << "Inputan Anda Harus Berupa Angka!" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    jumlahHewan++;
    simpan_data_ke_file("datahewan.csv");  // Simpan data ke file setelah menambahkan
    cout << "Data berhasil Ditambahkan\n";
}

// Fungsi untuk mengubah data hewan #.6
void ubah_data_hewan() {
    if (jumlahHewan == 0) {
        cout << "Tidak Ada Data Hewan\n";
        return;
    }
    string nama_lama, nama_baru ,habitat_baru;
    cout << "Masukkan Nama Hewan Yang Ingin Diubah: ";
    cin.ignore();
    getline(cin, nama_lama);
    for (int i = 0; i < jumlahHewan; ++i) {
        if (dataHewan[i].nama == nama_lama) {
            cout << "Masukkan Nama Baru: ";
            getline(cin, nama_baru);
            cout << "Masukkan Habitat Baru: ";
            getline(cin, habitat_baru);
            while (true) {
                cout << "Masukkan Umur Baru: ";
                if (cin >> dataHewan[i].umur) {
                    break;
                } else {
                    cout << "Inputan Anda Harus Berupa Angka!" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            dataHewan[i].nama = nama_baru; // Mengubah nama hewan
            dataHewan[i].habitat = habitat_baru;
            simpan_data_ke_file("datahewan.csv");  // Simpan data ke file setelah mengubah
            cout << "Data Berhasil Diubah\n";
            return;
        }
    }
    cout << "Data Hewan Tidak Ditemukan.\n";
}


// Fungsi untuk menghapus semua data member #.7
void hapus_semua_data_member(int* jumlahMember) {
    *jumlahMember = 0; //pointer
    simpan_data_member_ke_file("datamember.csv");
    cout << "Semua Data Member Berhasil Dihapus.\n";
}

// Fungsi untuk menghapus data hewan atau member #.8
void hapus_data() {
    while (true) {
        int pilih_hapus_data;
        cout << "\n==============Silahkan Pilih============" << endl;
        cout << "|       1. Hapus Data Hewan            |" << endl;
        cout << "|       2. Hapus Semua Data Member     |" << endl;
        cout << "|       3. Kembali Ke Menu admin       |" << endl;
        cout << "========================================"<<endl;
        cout << "Silahkan PIlih 1/2/3: ";
        cin >> pilih_hapus_data;
        if (pilih_hapus_data == 1) {
            if (jumlahHewan == 0) {
                cout << "Tidak Ada Data Hewan Untuk Dihapus.\n";
                return;
            }
            string nama;
            cout << "Masukkan Nama Hewan Yang Ingin Dihapus: ";
            cin.ignore();
            getline(cin, nama);
            for (int i = 0; i < jumlahHewan; ++i) {
                if (dataHewan[i].nama == nama) {
                    for (int j = i; j < jumlahHewan - 1; ++j) {
                        dataHewan[j] = dataHewan[j + 1];  // Shift elements to the left
                    }
                    jumlahHewan--;
                    simpan_data_ke_file("datahewan.csv");  // Simpan data ke file setelah menghapus
                    cout << "Data Berhasil Dihapus\n"<<endl;
                    return;
                }
            }
            cout << "Data Hewan Tidak Ditemukan.\n"<<endl;
        } else if (pilih_hapus_data == 2) {
            string konfirmasi;
            cout << "Apakah Anda Yakin Ingin Menghapus Semua Data Member? (ya/tidak): ";
            cin >> konfirmasi;
            if (konfirmasi == "ya" || konfirmasi == "Ya") {
                hapus_semua_data_member(&jumlahMember);
                return;
            } else if (konfirmasi == "tidak" || konfirmasi == "Tidak") {
                return;
            } else {
                cout << "Input Tidak valid. Silahkan Coba Lagi!\n";
            }
        } else if (pilih_hapus_data == 3) {
            return;
        } else {
            cout << "Inputan Anda Tidak Valid. Silahkan Pilih 1/2/3!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Fungsi Untuk Menampilkan Data Hewan #.9
void tampilkan_seluruh_data_hewan() {
    if (jumlahHewan == 0) {
        cout << "Tidak Ada Data Hewan.\n"<<endl;
        return;
    }
    ifstream file("datahewan.csv");
    file.is_open();
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string habitat, nama, umur_str;
        if (getline(ss, habitat, ',') && getline(ss, nama, ',') && getline(ss, umur_str)) {
            int umur = stoi(umur_str);
            cout << "Habitat: " << habitat << ", Nama: " << nama << ", Umur: " << umur << " Tahun" << endl;
        }
    }
    file.close();

}

// Fungsi Untuk Menampilkan Data Hewan #.10
void tampilkan_data_hewan() {
    if (jumlahHewan == 0) {
        cout << "Tidak Ada Data Hewan.\n"<<endl;
        return;
    }
    for (int i = 0; i < jumlahHewan; ++i) {
        cout << "Habitat: " << dataHewan[i].habitat << ", Nama: " << dataHewan[i].nama << ", Umur: " << dataHewan[i].umur << " Tahun" << endl;
    }
    return;
}

// Fungsi untuk Menampilkan data member #.11
void tampilkan_data_member(){
    if (jumlahMember == 0) {
        cout << "Tidak Ada Data Member.\n"<<endl;
        return;
    }
    for (int i = 0; i < jumlahMember; ++i){
        cout << "Nama: " << dataMember[i].username << ", Bintang Ulasan: " << dataMember[i].bintang << ", Komentar: " << dataMember[i].komentar << endl;
    }
    return;
}

// Fungsi Untuk Login Admin #.12
bool login_admin(int batas_login = 0) {
    string password;
    while (batas_login < 3) {
        cout << "\nMasukkan Password admin: ";
        cin >> password;
        if (password == "123") {
            cout << "Selamat Datang admin" << endl;
            return true;
        } else {
            cout << "Password Salah!!!" << endl;
            return login_admin(batas_login + 1); //Rekursif
        }
    }
    if (batas_login == 3) {
        cout << "Anda Telah Mencapai Batas Percobaan Login!!!\n" << endl;
    }
    return false;
}

// Fungsi Untuk Menu Admin #.13
int menu_admin() {
    int pilih_menu_admin;
    do {
        cout << "\n=========================Menu admin========================="<<endl;
        cout << "|              1. Menambah Data Hewan                      |" << endl;
        cout << "|              2. Mengubah Data Hewan                      |" << endl;
        cout << "|              3. Menghapus Data Hewan Atau Member         |" << endl;
        cout << "|              4. Menampilkan Data Hewan                   |" << endl;
        cout << "|              5. Melihat Review Member                    |" << endl;
        cout << "|              6. Keluar Program                           |" << endl;
        cout << "============================================================"<<endl;
        cout << "Silahkan Pilih-Pilihan Anda 1/2/3/4/5/6: ";
        cin >> pilih_menu_admin;
        switch (pilih_menu_admin) {
            case 1:
                tambahkan_data_hewan();
                break;
            case 2:
                ubah_data_hewan();
                break;
            case 3:
                hapus_data();
                break;
            case 4:
                tampilkan_seluruh_data_hewan();
                break;
            case 5:
                tampilkan_data_member();
                break;
            case 6:
                cout << "Terima Kasih Sudah Menggunakan Program Admin\n" << endl;
                return 0;
            default:
                cout << "Masukkan Pilihan Yang Benar 1/2/3/4/5/6!\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (true);
    return 0;
}

// Prosedur Selection Sort Umur Hewan #.14
void selection_sort_umur() {
    for (int i = 0; i < jumlahHewan - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < jumlahHewan; ++j) {
            if (dataHewan[j].umur < dataHewan[min_index].umur) {
                min_index = j;
            }
        }
        // Tukar elemen pada posisi i dengan elemen terkecil
        if (min_index != i) {
            swap(dataHewan[i], dataHewan[min_index]);
        }
    }
    cout << "Data Hewan Yang Diurutkan Berdasarkan Umur:" << endl;
    tampilkan_data_hewan();
}

// Prosedur Selection Sort Habitat Hewan #.15
void selection_sort_habitat() {
    for (int i = 0; i < jumlahHewan - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < jumlahHewan; ++j) {
            if (dataHewan[j].habitat < dataHewan[min_index].habitat) {
                min_index = j;
            }
        }
        // Tukar elemen pada posisi i dengan elemen terkecil
        if (min_index != i) {
            swap(dataHewan[i], dataHewan[min_index]);
        }
    }
}

// Prosedur Binary Search  Habitat Hewan #.16
void binary_search_habitat() {
    selection_sort_habitat();
    string habitat_cari;
    cout << "Masukkan habitat yang ingin Anda cari: ";
    cin.ignore();
    getline(cin, habitat_cari);
    int low = 0;
    int high = jumlahHewan - 1;
    bool found = false;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (dataHewan[mid].habitat == habitat_cari) {
            found = true;
            cout << "Habitat: " << dataHewan[mid].habitat << ", Nama: " << dataHewan[mid].nama << ", Umur: " << dataHewan[mid].umur << " Tahun" << endl;
            // Cek apakah ada data yang sama sebelumnya atau setelahnya
            int index = mid - 1;
            while (index >= 0 && dataHewan[index].habitat == habitat_cari) {
                cout << "Habitat: " << dataHewan[index].habitat << ", Nama: " << dataHewan[index].nama << ", Umur: " << dataHewan[index].umur << " Tahun" << endl;
                index--;
            }
            index = mid + 1;
            while (index < jumlahHewan && dataHewan[index].habitat == habitat_cari) {
                cout << "Habitat: " << dataHewan[index].habitat << ", Nama: " << dataHewan[index].nama << ", Umur: " << dataHewan[index].umur << " Tahun" << endl;
                index++;
            }
            break;
        } else if (dataHewan[mid].habitat < habitat_cari) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    // Jika tidak ada data yang ditemukan
    if (!found) {
        cout << "Data Tidak Ditemukan Untuk Habitat: " << habitat_cari << endl;
    }
}

// Fungsi Untuk Menu Member #.17
int menu_member(string username) {
    string komentar;
    int pilihan_member, bintang;
    // Cek apakah member sudah ada di array
    bool member_exist = false;
    for (int i = 0; i < jumlahMember; ++i) {
        if (dataMember[i].username == username) {
            member_exist = true;
            break;
        }
    }
    if (!member_exist) {
        if (jumlahMember >= Maks_Member) {
            cout << "Kapasitas Data Member Telah Mencapai Batas Maksimum.\n"<<endl;
            return 0;
        }
        // Tambahkan member baru jika belum ada
        Member& newMember = dataMember[jumlahMember++];
        newMember.username = username;
        newMember.bintang = 0;
        newMember.komentar = "";
    }
    cout << "\n                  Selamat Datang " << username << endl;
    do {
        cout << "\n=========================Menu Member========================" << endl;
        cout << "|                     1. Tampilkan semua data              |" << endl;
        cout << "|                     2. Sorting                           |" << endl;
        cout << "|                     3. Searching                         |" << endl;
        cout << "|                     4. Keluar                            |" << endl;
        cout << "============================================================"<<endl;
        cout << "Silahkan Pilih-Pilihan Anda 1/2/3/4: ";
        cin >> pilihan_member;
        switch (pilihan_member) {
            case 1:
                tampilkan_seluruh_data_hewan();
                break;
            case 2:
                selection_sort_umur();
                break;
            case 3:
                binary_search_habitat();
                break;
            case 4:
                while(true){
                    cout << "Silahkan Berikan Bintang 1-5: ";
                    cin >> bintang;
                    if(bintang >= 1 && bintang <= 5){
                        break;
                    } else{  
                        cout << "Inputan Anda tidak valid, Harus Berupa Angka!\n" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                }
                cout << "Silahkan Masukkan Komentar: ";
                cin.ignore(); // Ignore newline character from previous input
                getline(cin, komentar);
                cout << "Terima Kasih Sudah Berkunjung"<< endl;
                cout << "\n"<<endl;
                for (int i = 0; i < jumlahMember; ++i) {
                    if (dataMember[i].username == username) {
                        dataMember[i].bintang = bintang;
                        dataMember[i].komentar = komentar;
                        break;
                    }
                }
                simpan_data_member_ke_file("datamember.csv"); // Simpan data member ke file
                return 0;
            default:
                cout << "Inputan Anda Tidak Valid, Silahkan Pilih 1/2/3/4\n"<<endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (true);
    return 0;
}

// Menu Utama #.18  
int main() {
    // Membaca data dari file CSV
    baca_data_dari_file("datahewan.csv");
    baca_data_member_dari_file("datamember.csv");
    while (true) {
        string pilihan;
        cout << "Selamat Datang DI Kebun Binatang Samarinda" <<endl;
        cout << "==========Menu Utama==========" << endl;
        cout << "|         1. Login           |" << endl;
        cout << "|         2. Keluar          |" << endl;
        cout << "=============================="<<endl;
        cout << "Masukkan Pilihan Anda 1/2: ";
        cin >> pilihan;
        bool valid = true;
        if (pilihan == "1") {
            string username;
            cout << "Masukkan Username: ";
            cin.ignore();
            getline(cin, username);
            bool valid = true;
            for (char c : username) {
                if (!isalpha(c)) {
                    valid = false;
                    break;
                }
            }
            if (!valid) {
                cout << "Inputan Harus Berupa Huruf,Silahkan coba lagi\n" <<endl;
                continue;
            }
            if (username == "admin") {
                if (login_admin()) {
                    menu_admin();
                }
            } else {
                menu_member(username);
            }
        } else if (pilihan == "2") {
            simpan_data_ke_file("datahewan.csv");  // Simpan data ke file sebelum keluar
            simpan_data_member_ke_file("datamember.csv"); // Simpan data member ke file sebelum keluar
            cout << "Terima Kasih Telah Berkunjung" << endl;
            break;
        } else {
            cout << "Masukkan Pilihan Yang Benar 1/2!\n"<<endl;
        }
    }
    return 0;
}