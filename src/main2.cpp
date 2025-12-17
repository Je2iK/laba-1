#include "include/dll.h"
#include "include/sll.h"
#include "include/stack.h"
#include "include/queue.h"
#include "include/array.h"
#include "include/brt.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    Array<string> arr{};
    SinglyLinkedList<string> sll;
    DoublyLinkedList<string> dll;
    Stack<string> st;
    Queue<string> q;
    BRT brt;
    if (argc < 3) {
        cerr << "Использование: ./dbms --query 'COMMAND ...'\n";
        return 1;
    }

    string query;
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "--query" && i + 1 < argc) {
            for (int j = i + 1; j < argc; ++j) {
                query += argv[j];
                if (j != argc - 1)
                    query += " ";
            }
            break;
        }
    }

    stringstream ss(query);
    string cmd;
    ss >> cmd;

    // Загрузка всех структур
    arr.loadFromFile();
    sll.loadFromFile();
    dll.loadFromFile();
    st.loadFromFile();
    q.loadFromFile("./txt/queue.txt");
    brt.loadFromFile();

    // array
    if (cmd == "MPUSHI") {
        string value;
        int index;
        ss >> value >> index;
        arr.arrayAddIndex(arr, index, value);
    }
    else if (cmd == "MPUSHEND") {
        string value;
        ss >> value;
        arr.arrayAddEnd(arr, value);
    }
    else if (cmd == "MDELI") {
        int index;
        ss >> index;
        arr.arrayDeleteIndex(arr, index);
    }
    else if (cmd == "MDELEND") {
        arr.arrayDeleteEnd(arr);
    }
    else if (cmd == "MGET") {
        int index;
        ss >> index;
    }
    else if (cmd == "MSET") {
        string value;
        int index;
        ss >> value >> index;
        arr.arraySet(arr, index, value);
    }
    else if (cmd == "MLEN") {
        cout << arr.arrayLength(arr) << endl;
    }
    else if (cmd == "MREAD") {
        arr.arrayRead(arr);
    }

    // sll
    else if (cmd == "SLLADDH") {
        string value;
        ss >> value;
        sll.addHead(value);
    }
    else if (cmd == "SLLADDT") {
        string value;
        ss >> value;
        sll.addTail(value);
    }
    else if (cmd == "SLLADDF") {
        string value, target;
        ss >> value >> target;
        sll.addBefore(target, value);
    }
    else if (cmd == "SLLADDB") {
        string value, target;
        ss >> value >> target;
        sll.addAfter(target, value);
    }
    else if (cmd == "SLLDELH") {
        sll.deleteHead();
    }
    else if (cmd == "SLLDELT") {
        sll.deleteTail();
    }
    else if (cmd == "SLLDELF") {
        string target;
        ss >> target;
        sll.deleteBefore(target);
    }
    else if (cmd == "SLLDELB") {
        string target;
        ss >> target;
        sll.deleteAfter(target);
    }
    else if (cmd == "SLLDELV") {
        string value;
        ss >> value;
        sll.deleteValue(value);
    }
    else if (cmd == "SLLREAD") {
        sll.read();
    }
    else if (cmd == "SLLFINDV") {
        string value;
        ss >> value;
    }

    // dll
    else if (cmd == "DLLADDH") {
        string value;
        ss >> value;
        dll.addHead(value);
    }
    else if (cmd == "DLLADDT") {
        string value;
        ss >> value;
        dll.addTail(value);
    }
    else if (cmd == "DLLADDF") {
        string value, target;
        ss >> value >> target;
        dll.addBeforeValue(target, value);
    }
    else if (cmd == "DLLADDB") {
        string value, target;
        ss >> value >> target;
        dll.addAfterValue(target, value);
    }
    else if (cmd == "DLLDELH") {
        dll.deleteHead();
    }
    else if (cmd == "DLLDELT") {
        dll.deleteTail();
    }
    else if (cmd == "DLLDELF") {
        string target;
        ss >> target;
        dll.deleteBeforeValue(target);
    }
    else if (cmd == "DLLDELB") {
        string target;
        ss >> target;
        dll.deleteAfterValue(target);
    }
    else if (cmd == "DLLDELV") {
        string value;
        ss >> value;
        dll.deleteValue(value);
    }
    else if (cmd == "DLLREADF") {
        dll.readForward();
    }
    else if (cmd == "DLLREADB") {
        dll.readBackward();
    }
    else if (cmd == "DLLFINDV") {
        string value;
        ss >> value;
        cout << value << "\" " << (dll.search(value) ? "найдено" : "не найдено") << endl;
    }

    // stack
    else if (cmd == "STPUSH") {
        string val;
        ss >> val;
        st.push(val);
    }
    else if (cmd == "STPOP") {
        if (!st.isEmpty()) {
            string val = st.pop();
            cout << "[STACK] Удаление: \"" << val << "\"" << endl;
            st.saveToFile();
        } else {
            cout << "[STACK] Попытка извлечения из пустого стека" << endl;
        }
    }
    else if (cmd == "STREAD") {
        st.read();
    }

    // queue
    else if (cmd == "QPUSH") {
        string val;
        ss >> val;
        q.push(val);
        cout << "[QUEUE] Вставка: \"" << val << "\"" << endl;
        q.saveToFile("./txt/queue.txt");
    }
    else if (cmd == "QPOP") {
        if (!q.isEmpty()) {
            string val = q.pop();
            cout << "[QUEUE] Удаление: \"" << val << "\"" << endl;
            q.saveToFile("./txt/queue.txt");
        } else {
            cout << "[QUEUE] Попытка извлечения из пустой очереди" << endl;
        }
    }
    else if (cmd == "QREAD") {
        q.read();
    }

    // brt
    else if (cmd == "BRTINSERT") {
        int i;
        ss >> i;
        brt.brtInsert(i);
    }
    else if (cmd == "BRTDEL") {
        int i;
        ss >> i;
        brt.brtRemove(i);
    }
    else if (cmd == "BRTREAD") {
        brt.inorder();
    }

    else {
        cerr << "Неизвестная команда: " << cmd << endl;
        return 1;
    }

    return 0;
}

