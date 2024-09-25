#include <iostream>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

class Ludyna {
private:
    string imya;
    int vik;

public:
    Ludyna(const string& imya = "�������", int vik = 0) : imya(imya), vik(vik) {}

    Ludyna(const Ludyna& other) = default;
    Ludyna& operator=(const Ludyna& other) = default;

    void print(ostream& out) const {
        out << "��'�: " << imya << ", ³�: " << vik << endl;
    }
};

class Kvartyra {
private:
    Ludyna* lyudy;
    int kilkistLyudey;

public:
    Kvartyra(int kilkistLyudey = 0) : kilkistLyudey(kilkistLyudey) {
        lyudy = new Ludyna[kilkistLyudey];
    }

    Kvartyra(const Kvartyra& other) : kilkistLyudey(other.kilkistLyudey) {
        lyudy = new Ludyna[kilkistLyudey];
        for (int i = 0; i < kilkistLyudey; ++i) {
            lyudy[i] = other.lyudy[i];
        }
    }

    Kvartyra& operator=(const Kvartyra& other) {
        if (this != &other) {
            delete[] lyudy;
            kilkistLyudey = other.kilkistLyudey;
            lyudy = new Ludyna[kilkistLyudey];
            for (int i = 0; i < kilkistLyudey; ++i) {
                lyudy[i] = other.lyudy[i];
            }
        }
        return *this;
    }

    ~Kvartyra() {
        delete[] lyudy;
    }

    void addLudyna(const Ludyna& ludyna, int index) {
        if (index < kilkistLyudey) {
            lyudy[index] = ludyna;
        }
    }

    void print(ostream& out) const {
        for (int i = 0; i < kilkistLyudey; ++i) {
            lyudy[i].print(out);
        }
    }
};

class Budynok {
private:
    Kvartyra* kvartyry;
    int kilkistKvartyr;

public:
    Budynok(int kilkistKvartyr = 40) : kilkistKvartyr(kilkistKvartyr) {
        kvartyry = new Kvartyra[kilkistKvartyr];
    }

    ~Budynok() {
        delete[] kvartyry;
    }

    void zaselytyLudy(int indexKvartyry, int kilkistLyudey) {
        if (indexKvartyry < kilkistKvartyr) {
            kvartyry[indexKvartyry] = Kvartyra(kilkistLyudey);
            for (int i = 0; i < kilkistLyudey; ++i) {
                string imya;
                int vik;
                cout << "������ ��'� �������� #" << i + 1 << " ��� �������� " << indexKvartyry + 1 << ": ";
                cin >> imya;
                cout << "������ �� �������� #" << i + 1 << ": ";
                while (!(cin >> vik) || vik < 0) {
                    cout << "���� �����, ������ ������ ��: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
                Ludyna ludyna(imya, vik);
                kvartyry[indexKvartyry].addLudyna(ludyna, i);
            }
        }
    }

    void print(ostream& out) const {
        for (int i = 0; i < kilkistKvartyr; ++i) {
            out << "�������� " << i + 1 << ":" << endl;
            kvartyry[i].print(out);
        }
    }
};

int main() {
    setlocale(LC_CTYPE, "ukr");
    Budynok budynok;

    int kilkistLyudey, kvartiraNum;
    char continueChoice = 'y';

    while (continueChoice == 'y') {
        cout << "������ ����� �������� (1-40), ��� ��������: ";
        cin >> kvartiraNum;

        if (kvartiraNum < 1 || kvartiraNum > 40) {
            cout << "������������ ����� ��������!" << endl;
            continue;
        }

        cout << "������ ������� ����� � ������� " << kvartiraNum << ": ";
        cin >> kilkistLyudey;

        while (kilkistLyudey < 0) {
            cout << "ʳ������ ����� �� ���� ���� ��'�����. ������ �����: ";
            cin >> kilkistLyudey;
        }

        budynok.zaselytyLudy(kvartiraNum - 1, kilkistLyudey);

        cout << "������ �������� �� ���� ��������? (y/n): ";
        cin >> continueChoice;
    }


    ofstream outFile("C:\\Users\\Student\\Desktop\\ResidentsInfo.txt");
    if (outFile.is_open()) {
        outFile << "���������� ��� ��� ��������� �������:" << endl;
        budynok.print(outFile);
        outFile.close();
        cout << "���������� ������ ��������� �� ������� ���." << endl;
    }
    else {
        cout << "�� ������� ������� ���� ��� ������." << endl;
    }

    return 0;
}
