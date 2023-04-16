//
// Created by Админ on 16.04.2023.
//

#include "AandDSlaboratorywork032half.h"

#include <algorithm>
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

// Моя любимая сортировка пузырьком
unordered_map<int, char> bubbleSort(unordered_map<int, char> list)
{
    int listLength = list.size();
    while(listLength--)
    {
        bool swapped = false;

        for(int i = 0; i < listLength; i++)
        {
            if(list[i] > list[i + 1])
            {
                swap(list[i], list[i + 1]);
                swapped = true;
            }
        }

        if(swapped == false)
            break;
    }
    return list;
}


// Добавление A к B (merge)
unordered_map <int, char> MERGE(unordered_map <int, char> B, unordered_map <int, char> A) {
    int stop = A.size() + B.size();
    for (int i = B.size(); i < stop; i++) {
        B[i] = A[i - stop + A.size()];
    }
    B = bubbleSort(B);
    return B;
}

// Вычитание из A B (EXCL)
unordered_map<int, char> EXCL(unordered_map <int, char> A, unordered_map <int, char> B) {
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
            k ++;
        }
    }
    return C;
}

int main() {
    setlocale(0, "");
    int n;
    int choose = 0; // выбор действий

    cout << "0 - работа с множествами\n1 - работа с последовательностями\n";
    cin >> choose;
    if (choose == 0) {
        /* Множества */
        set<char> A, B, C, D, E, result;
        cout << "Мощность множества = 26, только латинские строчные символы\n";
        cout << "Введите количество элементов A: ";
        cin >> n;
        for (int i = 1; i <= n; i++) {
            char input;
            cin >> input;
            if (!isalpha(input)) { input = 'a'; }
            A.insert(input);
        }

        cout << "Введите количество элементов B: ";
        cin >> n;
        for (int i = 1; i <= n; i++) {
            char input;
            cin >> input;
            if (!isalpha(input)) { input = 'a'; }
            B.insert(input);
        }

        cout << "Введите количество элементов C: ";
        cin >> n;
        for (int i = 1; i <= n; i++) {
            char input;
            cin >> input;
            if (!isalpha(input)) { input = 'a'; }
            C.insert(input);
        }

        cout << "Введите количество элементов D: ";
        cin >> n;
        for (int i = 1; i <= n; i++) {
            char input;
            cin >> input;
            if (!isalpha(input)) { input = 'a'; }
            D.insert(input);
        }

        cout << "Введите количество элементов E: ";
        cin >> n;
        for (int i = 1; i <= n; i++) {
            char input;
            cin >> input;
            if (!isalpha(input)) { input = 'a'; }
            E.insert(input);
        }

        cout << "result = A SUB (B AND C) OR D XOR E \n";
        set_intersection(B.begin(), B.end(), C.begin(), C.end(), inserter(result, result.end())); // B AND C = result
        cout << "B AND C = result \n";
        for (auto i: result) cout << i << " ";
        set_difference(A.begin(), A.end(), result.begin(), result.end(),
                       inserter(result, result.end())); // A - result = result
        cout << "\nA - result = result \n";
        for (auto i: result) cout << i << " ";
        set_union(result.begin(), result.end(), D.begin(), D.end(),
                  inserter(result, result.end())); // result OR D = result
        cout << "\nresult OR D = result \n";
        for (auto i: result) cout << i << " ";
        set_symmetric_difference(result.begin(), result.end(), E.begin(), E.end(),
                                 inserter(result, result.end())); // result XOR E = result
        cout << "\nresult XOR E = result \n";
        for (auto i: result) cout << i << " ";
        cout << "\n";
    } else {
        /* Последовательности */

        unordered_map<int, char> F, G;

        cout << "Введите количество элементов F: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << i << ") ";
            char a;
            cin >> a;
            F[i] = a;  // добавляем новые элементы
        }

        cout << "Введите количество элементов G: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            cout << i << ") ";
            char a;
            cin >> a;
            G[i] = a;  // добавляем новые элементы
        }
        cout << "0 - MERGE\n1 - EXCL\n2 - ERASE\n";
        cin >> choose;

        if (choose == 0) {
            F = MERGE(G, F);
            cout << "\nF.MERGE(G) = F \n";
        } else if (choose == 1) {
            F = EXCL(F, G);
            cout << "\nF.EXCL(G) = F \n";
        } else {
            int p1, p2;
            cout << "Введите p1:\n";
            cin >> p1;
            cout << "Введите p2:\n";
            cin >> p2;
            F = ERASE(F, p1, p2);
            cout << "\nF.ERASE(p1, p2) = F \n";
        }

        for (auto &item: F) {
            cout << item.first << ") " << item.second << endl; // Вывод ключей и значений
        }
    }

    system("pause");
    return 0;
}


