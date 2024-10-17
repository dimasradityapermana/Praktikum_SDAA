#include <iostream>
using namespace std;

struct Node
{
    string product_name;
    string merk;
    int price;
    int stock;
    Node *next;
};

Node *head = nullptr;
int many_product = 0;

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

void create_stationery(Node *&head, int &many_product)
{
    Node *new_node = new Node();
    cout << "Tambah produk baru:" << endl;
    cin.ignore();
    cout << "Masukkan nama produk: ";
    getline(cin, new_node->product_name);

    cout << "Masukkan merk: ";
    getline(cin, new_node->merk);

    while (true)
    {
        cout << "Masukkan harga: ";
        cin >> new_node->price;
        cin.ignore();

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input tidak valid, harap masukkan angka yang benar!" << endl;
        }
        else
        {
            cin.clear();
            break;
        }
    }

    while (true)
    {
        cout << "Masukkan stok: ";
        cin >> new_node->stock;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input tidak valid, harap masukkan angka yang benar!" << endl;
        }
        else
        {
            cin.clear();
            break;
        }
    }

    new_node->next = head;
    head = new_node;

    many_product++;
    cout << "Produk berhasil ditambahkan!" << endl;
}

void read_stationery(Node *head)
{
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    cout << "\nDaftar Produk:" << endl;
    Node *temp = head;
    int index = 1;

    while (temp != nullptr)
    {
        cout << "Produk " << index << ": "
             << temp->product_name << ", Merk: " << temp->merk
             << ", Harga: " << temp->price << ", Stok: " << temp->stock << endl;
        temp = temp->next;
        index++;
    }
}

void update_stationery(Node *head, int many_product)
{
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    int index;
    cout << "Pilih nomor produk yang ingin di-update: ";
    cin >> index;
    cin.ignore();

    if (index > 0 && index <= many_product)
    {
        Node *temp = head;
        for (int i = 1; i < index; i++)
        {
            temp = temp->next;
        }

        cout << "Masukkan nama produk baru: ";
        getline(cin, temp->product_name);

        cout << "Masukkan merk baru: ";
        getline(cin, temp->merk);

        while (true)
        {
            cout << "Masukkan harga: ";
            cin >> temp->price;
            cin.ignore();

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input tidak valid, harap masukkan angka yang benar!" << endl;
            }
            else
            {
                cin.clear();
                break;
            }
        }

        while (true)
        {
            cout << "Masukkan stok: ";
            cin >> temp->stock;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Input tidak valid, harap masukkan angka yang benar!" << endl;
            }
            else
            {
                cin.clear();
                break;
            }
        }

        cout << "Data berhasil di-update!" << endl;
    }
    else
    {
        cout << "Produk tidak ditemukan!" << endl;
    }
}

void delete_stationery(Node *&head, int &many_product)
{
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    int choice;
    cout << "1. Hapus produk pertama (dequeue)" << endl;
    cout << "2. Hapus produk terakhir (pop)" << endl;
    cout << "Pilih opsi penghapusan: ";
    cin >> choice;

    if (choice == 1)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        many_product--;
        cout << "Produk pertama berhasil dihapus!" << endl;
    }
    else if (choice == 2)
    {
        if (head->next == nullptr)
        {
            delete head;
            head = nullptr;
        }
        else
        {
            Node *temp = head;
            while (temp->next->next != nullptr)
            {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
        many_product--;
        cout << "Produk terakhir berhasil dihapus!" << endl;
    }
    else
    {
        cout << "Pilihan tidak valid!" << endl;
    }
}

Node *partition(Node *low, Node *high)
{
    int pivot = high->price;
    Node *i = low;
    Node *j = low;

    while (j != high)
    {
        if (j->price < pivot)
        {
            swap(i->price, j->price);
            swap(i->product_name, j->product_name);
            swap(i->merk, j->merk);
            swap(i->stock, j->stock);
            i = i->next;
        }
        j = j->next;
    }

    swap(i->price, high->price);
    swap(i->product_name, high->product_name);
    swap(i->merk, high->merk);
    swap(i->stock, high->stock);
    return i;
}

void quick_sort(Node *low, Node *high)
{
    if (low != nullptr && high != nullptr && low != high && low != high->next)
    {
        Node *p = partition(low, high);
        quick_sort(low, p->next);
        quick_sort(p->next, high);
    }
}

void shell_sort(Node *head)
{
    int gap = many_product / 2;
    while (gap > 0)
    {
        for (int i = gap; i < many_product; i++)
        {
            Node *temp = head;
            for (int j = 0; j < i; j++)
            {
                temp = temp->next;
            }

            int current_price = temp->price;
            string current_product = temp->product_name;
            string current_merk = temp->merk;
            int current_stock = temp->stock;

            Node *prev = temp;
            for (int j = i - gap; j >= 0; j -= gap)
            {
                Node *gap_node = head;
                for (int k = 0; k < j; k++)
                {
                    gap_node = gap_node->next;
                }

                if (gap_node->price >= current_price)
                {
                    break;
                }

                prev->price = gap_node->price;
                prev->product_name = gap_node->product_name;
                prev->merk = gap_node->merk;
                prev->stock = gap_node->stock;
                prev = gap_node;
            }

            prev->price = current_price;
            prev->product_name = current_product;
            prev->merk = current_merk;
            prev->stock = current_stock;
        }
        gap /= 2;
    }
}

void sort_stationery(Node *head)
{
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    int choice;
    cout << "1. Sorting Ascending (Quick Sort)" << endl;
    cout << "2. Sorting Descending (Shell Sort)" << endl;
    cout << "Pilih jenis sorting: ";
    cin >> choice;

    Node *last = head;
    while (last->next != nullptr)
    {
        last = last->next;
    }

    if (choice == 1)
    {
        quick_sort(head, last);
        cout << "Produk berhasil diurutkan secara ascending (Quick Sort)." << endl;
    }
    else if (choice == 2)
    {
        shell_sort(head);
        cout << "Produk berhasil diurutkan secara descending (Shell Sort)." << endl;
    }
    else
    {
        cout << "Pilihan tidak valid!" << endl;
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
        cout << "=              5. Urutkan produk            =" << endl;
        cout << "=              6. Keluar                    =" << endl;
        cout << "=============================================" << endl;
        cout << "Pilih menu: ";
        cin >> choice;
        cout << "---------------------------------------------" << endl;

        switch (choice)
        {
        case 1:
            create_stationery(head, many_product);
            break;
        case 2:
            read_stationery(head);
            break;
        case 3:
            update_stationery(head, many_product);
            break;
        case 4:
            delete_stationery(head, many_product);
            break;
        case 5:
            sort_stationery(head);
            break;
        case 6:
            cout << "Program dihentikan!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
        }
    } while (choice != 6);
}

int main()
{
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
