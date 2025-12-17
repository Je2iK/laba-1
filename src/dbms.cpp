#include "json.hpp"
#include "include/brt.h"
#include "include/array.h"
#include "include/stack.h"
#include "include/queue.h"
#include "include/sll.h"
#include "include/dll.h"
#include <iostream>
#include <fstream>
#include <sstream>

using json = nlohmann::json;
using namespace std;

class DBMS {
private:
    Array<string> arrayNames{100};
    Array<Array<string>*> arrayData{100};
    Array<string> stackNames{100};
    Array<Stack<string>*> stackData{100};
    Array<string> queueNames{100};
    Array<Queue<string>*> queueData{100};
    Array<string> slistNames{100};
    Array<SinglyLinkedList<string>*> slistData{100};
    Array<string> dlistNames{100};
    Array<DoublyLinkedList<string>*> dlistData{100};
    Array<string> treeNames{100};
    Array<BRT> treeData{100};
    string filename;

    int findArray(const string& name) {
        for (size_t i = 0; i < arrayNames.size; i++) {
            if (arrayNames.arrayGet(arrayNames, i) == name) return i;
        }
        return -1;
    }
    
    Array<string>* getArray(const string& name) {
        int idx = findArray(name);
        if (idx == -1) {
            arrayNames.arrayAddEnd(arrayNames, name);
            Array<string>* newArr = new Array<string>(100);
            arrayData.arrayAddEnd(arrayData, newArr);
            return newArr;
        }
        return arrayData.arrayGet(arrayData, idx);
    }

    int findStack(const string& name) {
        for (size_t i = 0; i < stackNames.size; i++) {
            if (stackNames.arrayGet(stackNames, i) == name) return i;
        }
        return -1;
    }
    
    Stack<string>* getStack(const string& name) {
        int idx = findStack(name);
        if (idx == -1) {
            stackNames.arrayAddEnd(stackNames, name);
            Stack<string>* newStack = new Stack<string>();
            newStack->create(100);
            stackData.arrayAddEnd(stackData, newStack);
            return newStack;
        }
        return stackData.arrayGet(stackData, idx);
    }

    int findQueue(const string& name) {
        for (size_t i = 0; i < queueNames.size; i++) {
            if (queueNames.arrayGet(queueNames, i) == name) return i;
        }
        return -1;
    }
    
    Queue<string>* getQueue(const string& name) {
        int idx = findQueue(name);
        if (idx == -1) {
            queueNames.arrayAddEnd(queueNames, name);
            Queue<string>* newQueue = new Queue<string>();
            newQueue->create(100);
            queueData.arrayAddEnd(queueData, newQueue);
            return newQueue;
        }
        return queueData.arrayGet(queueData, idx);
    }

    int findSList(const string& name) {
        for (size_t i = 0; i < slistNames.size; i++) {
            if (slistNames.arrayGet(slistNames, i) == name) return i;
        }
        return -1;
    }
    
    SinglyLinkedList<string>* getSList(const string& name) {
        int idx = findSList(name);
        if (idx == -1) {
            slistNames.arrayAddEnd(slistNames, name);
            SinglyLinkedList<string>* newSList = new SinglyLinkedList<string>();
            slistData.arrayAddEnd(slistData, newSList);
            return newSList;
        }
        return slistData.arrayGet(slistData, idx);
    }

    int findDList(const string& name) {
        for (size_t i = 0; i < dlistNames.size; i++) {
            if (dlistNames.arrayGet(dlistNames, i) == name) return i;
        }
        return -1;
    }
    
    DoublyLinkedList<string>* getDList(const string& name) {
        int idx = findDList(name);
        if (idx == -1) {
            dlistNames.arrayAddEnd(dlistNames, name);
            DoublyLinkedList<string>* newDList = new DoublyLinkedList<string>();
            dlistData.arrayAddEnd(dlistData, newDList);
            return newDList;
        }
        return dlistData.arrayGet(dlistData, idx);
    }

    int findTree(const string& name) {
        for (size_t i = 0; i < treeNames.size; i++) {
            if (treeNames.arrayGet(treeNames, i) == name) return i;
        }
        return -1;
    }
    
    BRT* getTree(const string& name) {
        int idx = findTree(name);
        if (idx == -1) {
            treeNames.arrayAddEnd(treeNames, name);
            BRT newTree;
            treeData.arrayAddEnd(treeData, newTree);
            idx = treeData.size - 1;
        }
        static BRT temp;
        temp = treeData.arrayGet(treeData, idx);
        return &temp;
    }
    
    void updateTree(const string& name, const BRT& tree) {
        int idx = findTree(name);
        if (idx != -1) {
            treeData.arraySet(treeData, idx, tree);
        }
    }

public:
    DBMS(const string& file) : filename(file) {
        loadFromFile();
    }

    void saveToFile() {
        json data;
        json arraysJson;
        for (size_t i = 0; i < arrayNames.size; i++) {
            string name = arrayNames.arrayGet(arrayNames, i);
            Array<string>* arr = arrayData.arrayGet(arrayData, i);
            json values;
            for (size_t j = 0; j < arr->size; j++) {
                values.push_back(arr->arrayGet(*arr, j));
            }
            arraysJson[name] = values;
        }
        data["arrays"] = arraysJson;

        // Stacks
        json stacksJson;
        for (size_t i = 0; i < stackNames.size; i++) {
            string name = stackNames.arrayGet(stackNames, i);
            Stack<string>* stack = stackData.arrayGet(stackData, i);
            json values;
            Stack<string> temp;
            while (!stack->isEmpty()) {
                string val = stack->pop();
                values.push_back(val);
                temp.push(val);
            }
            while (!temp.isEmpty()) {
                stack->push(temp.pop());
            }
            stacksJson[name] = values;
        }
        data["stacks"] = stacksJson;

        // Queues
        json queuesJson;
        for (size_t i = 0; i < queueNames.size; i++) {
            string name = queueNames.arrayGet(queueNames, i);
            Queue<string>* queue = queueData.arrayGet(queueData, i);
            json values;
            Queue<string> temp;
            while (!queue->isEmpty()) {
                string val = queue->pop();
                values.push_back(val);
                temp.push(val);
            }
            while (!temp.isEmpty()) {
                queue->push(temp.pop());
            }
            queuesJson[name] = values;
        }
        data["queues"] = queuesJson;

        // Singly Linked Lists
        json slistsJson;
        for (size_t i = 0; i < slistNames.size; i++) {
            string name = slistNames.arrayGet(slistNames, i);
            SinglyLinkedList<string>* slist = slistData.arrayGet(slistData, i);
            json values;
            // Iterate through singly linked list
            auto* current = slist->head;
            while (current) {
                values.push_back(current->value);
                current = current->next;
            }
            slistsJson[name] = values;
        }
        data["slists"] = slistsJson;

        // Doubly Linked Lists
        json dlistsJson;
        for (size_t i = 0; i < dlistNames.size; i++) {
            string name = dlistNames.arrayGet(dlistNames, i);
            DoublyLinkedList<string>* dlist = dlistData.arrayGet(dlistData, i);
            json values;
            // Iterate through doubly linked list
            auto* current = dlist->head;
            while (current) {
                values.push_back(current->value);
                current = current->next;
            }
            dlistsJson[name] = values;
        }
        data["dlists"] = dlistsJson;

        // Trees
        json treesJson;
        for (size_t i = 0; i < treeNames.size; i++) {
            string name = treeNames.arrayGet(treeNames, i);
            BRT tree = treeData.arrayGet(treeData, i);
            json values = tree.toJson();
            treesJson[name] = values;
        }
        data["trees"] = treesJson;
        
        ofstream file(filename);
        file << data.dump(2);
    }

    void loadFromFile() {
        ifstream file(filename);
        if (!file.good()) return;
        
        json data;
        try {
            file >> data;
            if (data.contains("arrays")) {
                for (auto& item : data["arrays"].items()) {
                    arrayNames.arrayAddEnd(arrayNames, item.key());
                    Array<string>* arr = new Array<string>(100);
                    for (const auto& val : item.value()) {
                        arr->arrayAddEnd(*arr, val);
                    }
                    arrayData.arrayAddEnd(arrayData, arr);
                }
            }
            
            if (data.contains("stacks")) {
                for (auto& item : data["stacks"].items()) {
                    stackNames.arrayAddEnd(stackNames, item.key());
                    Stack<string>* stack = new Stack<string>();
                    for (auto it = item.value().rbegin(); it != item.value().rend(); ++it) {
                        stack->push(*it);
                    }
                    stackData.arrayAddEnd(stackData, stack);
                }
            }
            
            if (data.contains("queues")) {
                for (auto& item : data["queues"].items()) {
                    queueNames.arrayAddEnd(queueNames, item.key());
                    Queue<string>* queue = new Queue<string>();
                    for (const auto& val : item.value()) {
                        queue->push(val);
                    }
                    queueData.arrayAddEnd(queueData, queue);
                }
            }
            
            if (data.contains("slists")) {
                for (auto& item : data["slists"].items()) {
                    slistNames.arrayAddEnd(slistNames, item.key());
                    SinglyLinkedList<string>* slist = new SinglyLinkedList<string>();
                    for (const auto& val : item.value()) {
                        slist->addTail(val);
                    }
                    slistData.arrayAddEnd(slistData, slist);
                }
            }
            
            if (data.contains("dlists")) {
                for (auto& item : data["dlists"].items()) {
                    dlistNames.arrayAddEnd(dlistNames, item.key());
                    DoublyLinkedList<string>* dlist = new DoublyLinkedList<string>();
                    for (const auto& val : item.value()) {
                        dlist->addTail(val);
                    }
                    dlistData.arrayAddEnd(dlistData, dlist);
                }
            }
            
            if (data.contains("trees")) {
                for (auto& item : data["trees"].items()) {
                    treeNames.arrayAddEnd(treeNames, item.key());
                    BRT tree;
                    tree.fromJson(item.value());
                    treeData.arrayAddEnd(treeData, tree);
                }
            }
        } catch (...) {}
    }

    void executeQuery(const string& query) {
        stringstream ss(query);
        string cmd, name;
        ss >> cmd >> name;
        
        // Array commands
        if (cmd == "MPUSHI") {
            string value;
            int index;
            ss >> value >> index;
            Array<string>* arr = getArray(name);
            if (index >= 0 && (size_t)index <= arr->size) {
                arr->arrayAddIndex(*arr, index, value);
                cout << value << endl;
            }
        }
        else if (cmd == "MPUSHEND") {
            string value;
            ss >> value;
            Array<string>* arr = getArray(name);
            arr->arrayAddEnd(*arr, value);
            cout << value << endl;
        }
        else if (cmd == "MDELI") {
            int index;
            ss >> index;
            Array<string>* arr = getArray(name);
            if (index >= 0 && (size_t)index < arr->size) {
                arr->arrayDeleteIndex(*arr, index);
            }
        }
        else if (cmd == "MDELEND") {
            Array<string>* arr = getArray(name);
            if (arr->size > 0) {
                arr->arrayDeleteEnd(*arr);
            }
        }
        else if (cmd == "MGET") {
            int index;
            ss >> index;
            Array<string>* arr = getArray(name);
            if (index >= 0 && (size_t)index < arr->size) {
                cout << arr->arrayGet(*arr, index) << endl;
            }
        }
        else if (cmd == "MSET") {
            string value;
            int index;
            ss >> value >> index;
            Array<string>* arr = getArray(name);
            if (index >= 0 && (size_t)index < arr->size) {
                arr->arraySet(*arr, index, value);
            }
        }
        else if (cmd == "MLEN") {
            Array<string>* arr = getArray(name);
            cout << arr->arrayLength(*arr) << endl;
        }
        else if (cmd == "MREAD") {
            Array<string>* arr = getArray(name);
            arr->arrayRead(*arr);
        }
        
        // SLL commands
        else if (cmd == "SLLADDH") {
            string value;
            ss >> value;
            SinglyLinkedList<string>* sll = getSList(name);
            sll->addHead(value);
            cout << value << endl;
        }
        else if (cmd == "SLLADDT") {
            string value;
            ss >> value;
            SinglyLinkedList<string>* sll = getSList(name);
            sll->addTail(value);
            cout << value << endl;
        }
        else if (cmd == "SLLADDF") {
            string value, target;
            ss >> value >> target;
            SinglyLinkedList<string>* sll = getSList(name);
            sll->addBefore(target, value);
            cout << value << endl;
        }
        else if (cmd == "SLLADDB") {
            string value, target;
            ss >> value >> target;
            SinglyLinkedList<string>* sll = getSList(name);
            sll->addAfter(target, value);
            cout << value << endl;
        }
        else if (cmd == "SLLDELH") {
            SinglyLinkedList<string>* sll = getSList(name);
            sll->deleteHead();
        }
        else if (cmd == "SLLDELT") {
            SinglyLinkedList<string>* sll = getSList(name);
            sll->deleteTail();
        }
        else if (cmd == "SLLDELF") {
            string target;
            ss >> target;
            SinglyLinkedList<string>* sll = getSList(name);
            sll->deleteBefore(target);
        }
        else if (cmd == "SLLDELB") {
            string target;
            ss >> target;
            SinglyLinkedList<string>* sll = getSList(name);
            sll->deleteAfter(target);
        }
        else if (cmd == "SLLDELV") {
            string value;
            ss >> value;
            SinglyLinkedList<string>* sll = getSList(name);
            sll->deleteValue(value);
        }
        else if (cmd == "SLLREAD") {
            SinglyLinkedList<string>* sll = getSList(name);
            sll->read();
        }
        else if (cmd == "SLLFINDV") {
            string value;
            ss >> value;
            SinglyLinkedList<string>* sll = getSList(name);
            cout << (sll->search(value) ? "TRUE" : "FALSE") << endl;
        }
        
        // DLL commands
        else if (cmd == "DLLADDH") {
            string value;
            ss >> value;
            DoublyLinkedList<string>* dll = getDList(name);
            dll->addHead(value);
            cout << value << endl;
        }
        else if (cmd == "DLLADDT") {
            string value;
            ss >> value;
            DoublyLinkedList<string>* dll = getDList(name);
            dll->addTail(value);
            cout << value << endl;
        }
        else if (cmd == "DLLADDF") {
            string value, target;
            ss >> value >> target;
            DoublyLinkedList<string>* dll = getDList(name);
            dll->addBeforeValue(target, value);
            cout << value << endl;
        }
        else if (cmd == "DLLADDB") {
            string value, target;
            ss >> value >> target;
            DoublyLinkedList<string>* dll = getDList(name);
            dll->addAfterValue(target, value);
            cout << value << endl;
        }
        else if (cmd == "DLLDELH") {
            DoublyLinkedList<string>* dll = getDList(name);
            dll->deleteHead();
        }
        else if (cmd == "DLLDELT") {
            DoublyLinkedList<string>* dll = getDList(name);
            dll->deleteTail();
        }
        else if (cmd == "DLLDELF") {
            string target;
            ss >> target;
            DoublyLinkedList<string>* dll = getDList(name);
            dll->deleteBeforeValue(target);
        }
        else if (cmd == "DLLDELB") {
            string target;
            ss >> target;
            DoublyLinkedList<string>* dll = getDList(name);
            dll->deleteAfterValue(target);
        }
        else if (cmd == "DLLDELV") {
            string value;
            ss >> value;
            DoublyLinkedList<string>* dll = getDList(name);
            dll->deleteValue(value);
        }
        else if (cmd == "DLLREADF") {
            DoublyLinkedList<string>* dll = getDList(name);
            dll->readForward();
        }
        else if (cmd == "DLLREADB") {
            DoublyLinkedList<string>* dll = getDList(name);
            dll->readBackward();
        }
        else if (cmd == "DLLFINDV") {
            string value;
            ss >> value;
            DoublyLinkedList<string>* dll = getDList(name);
            cout << (dll->search(value) ? "TRUE" : "FALSE") << endl;
        }
        
        // BRT commands
        else if (cmd == "BRTINSERT") {
            int value;
            ss >> value;
            BRT* tree = getTree(name);
            tree->brtInsert(value);
            updateTree(name, *tree);
            cout << value << endl;
        }
        else if (cmd == "BRTDEL") {
            int value;
            ss >> value;
            BRT* tree = getTree(name);
            tree->brtRemove(value);
            updateTree(name, *tree);
        }
        else if (cmd == "BRTREAD") {
            BRT* tree = getTree(name);
            tree->inorder();
        }
        
        // Stack commands
        else if (cmd == "STPUSH") {
            string value;
            ss >> value;
            Stack<string>* stack = getStack(name);
            stack->push(value);
            cout << value << endl;
        }
        else if (cmd == "STPOP") {
            Stack<string>* stack = getStack(name);
            if (!stack->isEmpty()) {
                cout << stack->pop() << endl;
            }
        }
        else if (cmd == "STREAD") {
            Stack<string>* stack = getStack(name);
            stack->read();
        }
        
        // Queue commands
        else if (cmd == "QPUSH") {
            string value;
            ss >> value;
            Queue<string>* queue = getQueue(name);
            queue->push(value);
            cout << value << endl;
        }
        else if (cmd == "QPOP") {
            Queue<string>* queue = getQueue(name);
            if (!queue->isEmpty()) {
                cout << queue->pop() << endl;
            }
        }
        else if (cmd == "QREAD") {
            Queue<string>* queue = getQueue(name);
            queue->read();
        }
        
        saveToFile();
    }
};

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Usage: ./dbms --file file.data --query 'COMMAND ...'" << endl;
        return 1;
    }

    string filename, query;
    for (int i = 1; i < argc; ++i) {
        if (string(argv[i]) == "--file" && i + 1 < argc) {
            filename = argv[++i];
        }
        else if (string(argv[i]) == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }

    DBMS dbms(filename);
    dbms.executeQuery(query);
    return 0;
}
