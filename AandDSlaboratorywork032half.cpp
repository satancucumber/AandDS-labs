//
// Created by Админ on 16.04.2023.
//

#include "AandDSlaboratorywork032half.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <time.h>
#include <chrono>
#include <fstream>

using namespace std;

// Моя любимая сортировка пузырьком
unordered_map<int, char> bubbleSort(unordered_map<int, char> list) {
    int listLength = list.size();
    while (listLength--) {
        bool swapped = false;

        for (int i = 0; i < listLength; i++) {
            if (list[i] > list[i + 1]) {
                swap(list[i], list[i + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }
    return list;
}


// Добавление A к B (merge)
unordered_map<int, char> MERGE(unordered_map<int, char> B, unordered_map<int, char> A) {
    int stop = A.size() + B.size();
    for (int i = B.size(); i < stop; i++) {
        B[i] = A[i - stop + A.size()];
    }
    B = bubbleSort(B);
    return B;
}

// Вычитание из A B (EXCL)
unordered_map<int, char> EXCL(unordered_map<int, char> A, unordered_map<int, char> B) {
    unordered_map<int, char> C;
    int k = 0;
    for (int i = 0; i < A.size(); i++) {
        bool ok = true;
        for (int j = 0; j < B.size(); j++) {
            if (B[j] == A[i]) {
                ok = false;
            }
        }
        if (ok) {
            C[k] = A[i];
            k++;
        }
    }
    return C;
}

// Убираем элементы с индекса p1 по p2 (ERASE)
unordered_map<int, char> ERASE(unordered_map<int, char> A, int p1, int p2) {
    unordered_map<int, char> C;
    int buff;
    int k = 0;
    // Если p1 и p2 не по возрастнию - меняем их местами
    if (p2 < p1) {
        buff = p1;
        p1 = p2;
        p2 = buff;
    }
    for (int i = 0; i < A.size(); i++) {
        if (i < p1 || i > p2) {
            C[k] = A[i];
            k++;
        }
    }
    return C;
}

int main() {
    ofstream fout;
    setlocale(0, "");
    srand((unsigned) time(NULL));
    int n;
    int choose = 0; // выбор действий
    int choose_auto = 0; // выбор - тест или ручной ввод

    cout << "0 - работа с множествами\n1 - работа с последовательностями\n";
    cin >> choose;
    cout << "0 - тестирование\n1 - ручной ввод\n";
    cin >> choose_auto;

    if (choose == 0) {
        /* Множества */
        auto begin_global = std::chrono::steady_clock::now();
        int stop = 1;
        if (choose_auto != 1) {
            stop = 500;
        }
        for (int ii = 0; ii < stop; ii++) {
            set<char> A, B, C, D, E, result;
            auto begin = chrono::steady_clock::now();
            if (choose_auto == 1) {
                cout << "Мощность множества = 26, только латинские строчные символы\n";
                cout << "Введите количество элементов A: ";
                cin >> n;
            } else {
                n = 10 + rand() % (100 - 10 + 1);
            }
            for (int i = 1; i <= n; i++) {
                char input;
                if (choose_auto == 1) {
                    cin >> input;
                } else {
                    input = char('a' + rand() % ('z' - 'a'));
                }
                if (!isalpha(input)) { input = 'a'; }
                A.insert(input);
            }
            if (choose_auto == 1) {
                cout << "Введите количество элементов B: ";
                cin >> n;
            } else {
                n = 10 + rand() % (100 - 10 + 1);
            }
            for (int i = 1; i <= n; i++) {
                char input;
                if (choose_auto == 1) {
                    cin >> input;
                } else {
                    input = char('a' + rand() % ('z' - 'a'));
                }
                if (!isalpha(input)) { input = 'a'; }
                B.insert(input);
            }

            if (choose_auto == 1) {
                cout << "Введите количество элементов C: ";
                cin >> n;
            } else {
                n = 10 + rand() % (100 - 10 + 1);
            }
            for (int i = 1; i <= n; i++) {
                char input;
                if (choose_auto == 1) {
                    cin >> input;
                } else {
                    input = char('a' + rand() % ('z' - 'a'));
                }
                if (!isalpha(input)) { input = 'a'; }
                C.insert(input);
            }

            if (choose_auto == 1) {
                cout << "Введите количество элементов D: ";
                cin >> n;
            } else {
                n = 10 + rand() % (100 - 10 + 1);
            }
            for (int i = 1; i <= n; i++) {
                char input;
                if (choose_auto == 1) {
                    cin >> input;
                } else {
                    input = char('a' + rand() % ('z' - 'a'));
                }
                if (!isalpha(input)) { input = 'a'; }
                D.insert(input);
            }

            if (choose_auto == 1) {
                cout << "Введите количество элементов E: ";
                cin >> n;
            } else {
                n = 10 + rand() % (100 - 10 + 1);
            }
            for (int i = 1; i <= n; i++) {
                char input;
                if (choose_auto == 1) {
                    cin >> input;
                } else {
                    input = char('a' + rand() % ('z' - 'a'));
                }
                if (!isalpha(input)) { input = 'a'; }
                E.insert(input);
            }

            if (choose_auto == 1) {
                cout << "result = A SUB (B AND C) OR D XOR E \n";
            }
            set_intersection(B.begin(), B.end(), C.begin(), C.end(),
                             inserter(result, result.end())); // B AND C = result
            if (choose_auto == 1) {
                cout << "B AND C = result \n";
                for (auto i: result) cout << i << " ";
            }
            set_difference(A.begin(), A.end(), result.begin(), result.end(),
                           inserter(result, result.end())); // A - result = result
            if (choose_auto == 1) {
                cout << "\nA - result = result \n";
                for (auto i: result) cout << i << " ";
            }
            set_union(result.begin(), result.end(), D.begin(), D.end(),
                      inserter(result, result.end())); // result OR D = result
            if (choose_auto == 1) {
                cout << "\nresult OR D = result \n";
                for (auto i: result) cout << i << " ";
            }
            set_symmetric_difference(result.begin(), result.end(), E.begin(), E.end(),
                                     inserter(result, result.end())); // result XOR E = result
            if (choose_auto == 1) {
                cout << "\nresult XOR E = result \n";
            }
            if (choose_auto == 1) {
                for (auto i: result) cout << i << " ";
                cout << "\n";
            }
            if (choose_auto != 1) {
                auto end = std::chrono::steady_clock::now();
                auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
                fout.open("AandDSlaboratorywork032half_sets.txt", ios::app);
                fout << to_string(ii) + ") Power of the set: " + to_string(n) + ". The time: " << elapsed_ms.count()
                     << " ms\n";
                fout.close();
            }
        }
        if (choose_auto != 1) {
            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms_global = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin_global);
            fout.open("AandDSlaboratorywork032half_sets.txt", ios::app);
            fout << "Number of iterations: " + to_string(stop) + ". The global time: " << elapsed_ms_global.count()
                 << " ms\n";
            fout.close();
        }

    } else {
        /* Последовательности */
        auto begin_global = std::chrono::steady_clock::now();
        int stop = 1;
        if (choose_auto != 1) {
            stop = 500;
        }

        for (int ii = 0; ii < stop; ii++) {
            auto begin = std::chrono::steady_clock::now();
            string mode = " "; // Название действия с последовательностью (merge, erase ...)
            unordered_map<int, char> F, G;
            if (choose_auto == 1) {
                cout << "Введите количество элементов F: ";
                cin >> n;
            } else {
                n = 10 + rand() % (100 - 10 + 1);
            }

            for (int i = 0; i < n; i++) {
                char a;
                if (choose_auto == 1) {
                    cout << i << ") ";
                    cin >> a;
                } else {
                    a = char('a' + rand() % ('z' - 'a'));
                }
                F[i] = a;  // добавляем новые элементы
            }

            if (choose_auto == 1) {
                cout << "Введите количество элементов G: ";
                cin >> n;
            } else {
                n = 10 + rand() % (100 - 10 + 1);
            }

            for (int i = 0; i < n; i++) {
                char a;
                if (choose_auto == 1) {
                    cout << i << ") ";
                    cin >> a;
                } else {
                    a = char('a' + rand() % ('z' - 'a'));
                }
                G[i] = a;  // добавляем новые элементы
            }
            if (choose_auto == 1) {
                cout << "0 - MERGE\n1 - EXCL\n2 - ERASE\n";
                cin >> choose;
            } else {
                choose = 999;
            }

            if (choose == 0) {
                F = MERGE(G, F);
                cout << "\nF.MERGE(G) = F \n";
            } else if (choose == 1) {
                F = EXCL(F, G);
                cout << "\nF.EXCL(G) = F \n";
            } else if (choose == 2) {
                int p1, p2;
                cout << "Введите p1:\n";
                cin >> p1;
                cout << "Введите p2:\n";
                cin >> p2;
                F = ERASE(F, p1, p2);
                cout << "\nF.ERASE(p1, p2) = F \n";
            } else {
                MERGE(G, F);
                EXCL(F, G);
                int p1 = rand() % (F.size() - 1);
                int p2 = rand() % (F.size() - 1);
                ERASE(F, p1, p2);
            }

            if (choose_auto == 1) {
                for (auto &item: F) {
                    cout << item.first << ") " << item.second << endl; // Вывод ключей и значений
                }
            } else {
                auto end = std::chrono::steady_clock::now();
                auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
                fout.open("AandDSlaboratorywork032half_sequences.txt", ios::app);
                fout << to_string(ii) + ") Power of the set: " + to_string(n) + ". The time: "
                     << elapsed_ms.count()
                     << " ms\n";
                fout.close();
            }
        }
        if (choose_auto != 1) {
            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms_global = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin_global);
            fout.open("AandDSlaboratorywork032half_sequences.txt", ios::app);
            fout << "Number of iterations: " + to_string(stop) + ". The global time: " << elapsed_ms_global.count()
                 << " ms\n";
            fout.close();
        }
    }

    system("pause");
    return 0;
}


