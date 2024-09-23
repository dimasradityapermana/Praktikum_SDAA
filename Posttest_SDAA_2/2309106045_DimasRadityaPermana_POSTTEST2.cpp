#include <iostream>
using namespace std;

struct db_stationery {
    string product_name;
    string merk;
    int price;
    int stock;
};

db_stationery database[100];
int many_product = 3;

bool login(string username, string password)
{
    string correct_uname = "admin";
    string correct_pass = "123";

    if (username == correct_uname && password == correct_pass)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void create_stationery(db_stationery database[], int &many_product)
{
    cout << "Tambah produk baru:" << endl;
    cout << "Masukkan nama produk: ";
    cin >> database[many_product].product_name;
    cout << "Masukkan merk: ";
    cin >> database[many_product].merk;
    cout << "Masukkan harga: ";
    cin >> database[many_product].price;
    cout << "Masukkan stok: ";
    cin >> database[many_product].stock;
    many_product++;
    cout << "Produk berhasil ditambahkan!" << endl;
}

void read_stationery(db_stationery database[], int many_product)
{
    cout << "\nDaftar Produk:" << endl;
    db_stationery *ptr = database;
    for (int i = 0; i < many_product; i++)
    {
        cout << "Produk " << i + 1 << ": "
             << ptr->product_name << ", Merk: " << ptr->merk
             << ", Harga: " << ptr->price << ", Stok: " << ptr->stock << endl;
        ptr++;
    }
}

void update_stationery(db_stationery database[], int many_product)
{
    int index;
    cout << "Pilih nomor produk yang ingin di-update: ";
    cin >> index;
    if (index > 0 && index <= many_product)
    {
        index--;
        cout << "Masukkan nama produk baru: ";
        cin >> database[index].product_name;
        cout << "Masukkan merk baru: ";
        cin >> database[index].merk;
        cout << "Masukkan harga baru: ";
        cin >> database[index].price;
        cout << "Masukkan stok baru: ";
        cin >> database[index].stock;
        cout << "Data berhasil di-update!" << endl;
    }
    else
    {
        cout << "Produk tidak ditemukan!" << endl;
    }
}

void delete_stationery(db_stationery database[], int &many_product)
{
    int index;
    cout << "Pilih nomor produk yang ingin dihapus: ";
    cin >> index;
    if (index > 0 && index <= many_product)
    {
        index--;
        for (int i = index; i < many_product - 1; i++)
        {
            database[i] = database[i + 1];
        }
        many_product--;
        cout << "Produk berhasil dihapus!" << endl;
    }
    else
    {
        cout << "Produk tidak ditemukan!" << endl;
    }
}

void choice()
{
    int choice;
    do
    {
        cout << "=============================================" << endl;
        cout << "=         Admin Toko Dim's Stationery       =" << endl;
        cout << "=============================================" << endl;
        cout << "=                [ MENU UTAMA ]             =" << endl;
        cout << "=              1. Tambah produk             =" << endl;
        cout << "=              2. Lihat produk              =" << endl;
        cout << "=              3. Update produk             =" << endl;
        cout << "=              4. Hapus produk              =" << endl;
        cout << "=              5. Keluar                    =" << endl;
        cout << "=============================================" << endl;
        cout << "Pilih menu: ";
        cin >> choice;
        cout << "---------------------------------------------" << endl;
        switch (choice)
        {
        case 1:
            create_stationery(database, many_product);
            break;
        case 2:
            read_stationery(database, many_product);
            break;
        case 3:
            update_stationery(database, many_product);
            break;
        case 4:
            delete_stationery(database, many_product);
            break;
        case 5:
            cout << "Program dihentikan!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
        }
    } while (choice != 5);
}

int main(){

    database[0] = {"Binder", "Bantex", 20000, 10};
    database[1] = {"Sarasa", "Zebra", 14000, 4};
    database[2] = {"Kokoro", "Zebra", 6000, 10};

    string username;
    string password;
    int attempt = 0;
    bool success = false;

    while (attempt < 3 && !success)
    {
        cout << "Masukkan username: ";
        getline(cin, username);
        
        cout << "Masukkan password: ";
        getline(cin, password);

        if (login(username, password))
        {
            cout << "Login berhasil!" << endl;
            success = true;
            choice();
        }
        else
        {
            attempt++;
            cout << "Login gagal! Username atau password salah." << endl;
            if (attempt < 3)
            {
                cout << "Anda memiliki " << 3 - attempt << " kesempatan lagi." << endl;
            }
        }
    }

    if (!success)
    {
        cout << "Anda telah gagal login 3 kali. Program dihentikan." << endl;
    }

    return 0;
}