#include <iostream>
using namespace std;

void menara_hanoi(int banyak, string kiri, string kanan, string tengah) {
    
    if (banyak == 1) {
        cout << "Pindah piringan 1 dari " << kiri << " ke menara " << kanan << endl;
        return;
    }

    menara_hanoi(banyak - 1, kiri, tengah, kanan);
    cout << "Pindah piringan " << banyak << " dari menara " << kiri << " ke menara " << kanan << endl;
    menara_hanoi(banyak - 1, tengah, kanan, kiri);
}

int main() {
    
    int banyak;
    cout << "Masukkan jumlah piringan : ";
    cin >> banyak;
    printf("Alur perpindahan :\n");
    menara_hanoi(banyak, "kiri", "kanan", "tengah");
    return 0;

}