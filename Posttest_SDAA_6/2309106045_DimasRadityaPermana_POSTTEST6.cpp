#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
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

Node *get_last(Node *head)
{
    while (head->next != nullptr)
    {
        head = head->next;
    }
    return head;
}

void quick_sort(Node *low, Node *high)
{
    if (low == nullptr || high == nullptr || low == high || low->next == high)
    {
        return;
    }

    Node *pivot = partition(low, high);
    quick_sort(low, pivot->next);
    quick_sort(pivot->next, high);
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

    Node *last = get_last(head);

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

void fibonacci_search(Node *head, int key)
{
    quick_sort(head, get_last(head));
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    vector<int> fib = {0, 1};
    int m = 1;
    while (fib[m] < many_product)
    {
        m++;
        fib.push_back(fib[m - 1] + fib[m - 2]);
    }

    int offset = -1;
    Node *current = head;
    bool found = false;

    while (fib[m] > 1)
    {
        int i = min(offset + fib[m - 2], many_product - 1);
        Node *curr = head;

        for (int j = 0; j < i && curr != nullptr; j++)
        {
            curr = curr->next;
        }

        if (curr == nullptr || curr->price > key)
        {
            m -= 2;
        }
        else if (curr->price < key)
        {
            offset = i;
            m -= 1;
        }
        else
        {
            cout << "Produk ditemukan: " << curr->product_name << ", Merk: " << curr->merk
                 << ", Harga: " << curr->price << ", Stok: " << curr->stock << endl;
            found = true;
            Node *next_product = curr->next;

            while (next_product != nullptr && next_product->price == key)
            {
                cout << "Produk ditemukan: " << next_product->product_name << ", Merk: " << next_product->merk
                     << ", Harga: " << next_product->price << ", Stok: " << next_product->stock << endl;
                next_product = next_product->next;
            }
            return;
        }
    }


    Node *last_check = head;
    for (int j = 0; j <= offset + 1 && last_check != nullptr; j++)
    {
        last_check = last_check->next;
    }

    if (last_check != nullptr && last_check->price == key)
    {
        cout << "Produk ditemukan: " << last_check->product_name << ", Merk: " << last_check->merk
             << ", Harga: " << last_check->price << ", Stok: " << last_check->stock << endl;
        found = true;
    }

    if (!found)
    {
        cout << "Produk tidak ditemukan." << endl;
    }
}

void jump_search(Node *head, int key)
{
    quick_sort(head, get_last(head));
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    int jump = sqrt(many_product);
    Node *temp = head;
    Node *prev = nullptr;
    bool found = false;

    while (temp != nullptr)
    {
        if (temp->price == key)
        {
            cout << "Produk ditemukan: " << temp->product_name << ", Merk: " << temp->merk
                 << ", Harga: " << temp->price << ", Stok: " << temp->stock << endl;
            found = true;
            temp = temp->next;
            while (temp != nullptr && temp->price == key)
            {
                cout << "Produk ditemukan: " << temp->product_name << ", Merk: " << temp->merk
                     << ", Harga: " << temp->price << ", Stok: " << temp->stock << endl;
                temp = temp->next;
            }
            return;
        }
        else if (temp->price < key)
        {
            prev = temp;
            for (int i = 0; i < jump; i++)
            {
                if (temp == nullptr)
                {
                    break;
                }
                prev = temp;
                temp = temp->next;
                if (temp == nullptr)
                {
                    break;
                }
            }
        }
        else
        {
            break;
        }
    }

    if (!found)
    {
        cout << "Produk tidak ditemukan." << endl;
    }
}

void boyer_moore_search(Node *head, string key)
{
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    Node *temp = head;
    vector<int> last_occurrence(256, -1);
    for (int i = 0; i < key.length(); i++)
    {
        last_occurrence[key[i]] = i;
    }

    bool found = false;
    while (temp != nullptr)
    {
        int i = key.length() - 1;
        int j = i;
        int k = i;
        while (j >= 0 && k >= 0 && temp != nullptr)
        {
            if (key[j] == temp->product_name[k])
            {
                j--;
                k--;
            }
            else
            {
                j = i;
                k = i;
                if (last_occurrence[temp->product_name[i]] != -1)
                {
                    k = last_occurrence[temp->product_name[i]];
                }
                temp = temp->next;
            }
        }

        if (j < 0)
        {
            cout << "Produk ditemukan: " << temp->product_name << ", Merk: " << temp->merk
                 << ", Harga: " << temp->price << ", Stok: " << temp->stock << endl;
            found = true;
            return;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "Produk tidak ditemukan." << endl;
    }
}

void search(Node *head)
{
    if (head == nullptr)
    {
        cout << "Tidak ada produk yang tersedia." << endl;
        return;
    }

    int choice;
    cout << "1. Fibonacci Search" << endl;
    cout << "2. Jump Search" << endl;
    cout << "3. Boyer-Moore Search" << endl;
    cout << "Pilih jenis pencarian: ";
    cin >> choice;

    if (choice == 1 || choice == 2)
    {
        int key;
        cout << "Masukkan harga produk yang dicari: ";
        cin >> key;

        if (choice == 1)
        {
            fibonacci_search(head, key);
        }
        else if (choice == 2)
        {
            jump_search(head, key);
        }
    }
    else if (choice == 3)
    {
        string key;
        cout << "Masukkan nama produk yang dicari: ";
        cin.ignore();
        getline(cin, key);
        boyer_moore_search(head, key);
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
        cout << "=              6. Search                    =" << endl;
        cout << "=              7. Keluar                    =" << endl;
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
            search(head);
            break;
        case 7:
            cout << "Program dihentikan!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
        }
    } while (choice != 7);
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
