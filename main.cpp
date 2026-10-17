
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Stack {
    vector<int> data;

public:
    void push(int value) {
        data.push_back(value);
        cout << "Pushed: " << value << "\n";
    }

    void pop() {
        if (data.empty()) {
            cout << "Stack is empty!\n";
            return;
        }
        cout << "Popped: " << data.back() << "\n";
        data.pop_back();
    }

    void display() {
        if (data.empty()) {
            cout << "Stack is empty!\n";
            return;
        }
        cout << "Stack (top to bottom): ";
        for (auto it = data.rbegin(); it != data.rend(); ++it)
            cout << *it << " ";
        cout << "\n";
    }
};

int binarySearch(const vector<int>& a, int target) {
    int low = 0, high = static_cast<int>(a.size()) - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (a[mid] == target)
            return mid;
        if (a[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

void bubbleSort(vector<int>& a) {
    for (int i = 0; i < static_cast<int>(a.size()) - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < static_cast<int>(a.size()) - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

void mergeParts(vector<int>& a, int left, int mid, int right) {
    vector<int> temp;
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (a[i] <= a[j])
            temp.push_back(a[i++]);
        else
            temp.push_back(a[j++]);
    }

    while (i <= mid)
        temp.push_back(a[i++]);

    while (j <= right)
        temp.push_back(a[j++]);

    for (int k = 0; k < static_cast<int>(temp.size()); k++)
        a[left + k] = temp[k];
}

void mergeSort(vector<int>& a, int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(a, left, mid);
    mergeSort(a, mid + 1, right);
    mergeParts(a, left, mid, right);
}

void showArray(const vector<int>& a) {
    if (a.empty()) {
        cout << "Array is empty.\n";
        return;
    }

    for (int value : a)
        cout << value << " ";
    cout << "\n";
}

int main() {
    vector<int> numbers;
    Stack stack;
    int choice;

    while (true) {
        cout << "\n========== ALGOVAULT ==========\n";
        cout << "1. Enter array\n";
        cout << "2. Bubble Sort\n";
        cout << "3. Merge Sort\n";
        cout << "4. Binary Search\n";
        cout << "5. Stack Operations\n";
        cout << "6. Display Array\n";
        cout << "7. Exit\n";
        cout << "Choose: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Exiting.\n";
            break;
        }

        if (choice == 1) {
            int n;
            cout << "Number of elements: ";
            if (!(cin >> n) || n < 0 || n > 100000) {
                cout << "Enter a size between 0 and 100000.\n";
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                }
                continue;
            }

            numbers.resize(n);
            cout << "Enter elements: ";
            bool valid = true;

            for (int& value : numbers) {
                if (!(cin >> value)) {
                    valid = false;
                    break;
                }
            }

            if (!valid) {
                cin.clear();
                cin.ignore(10000, '\n');
                numbers.clear();
                cout << "Invalid array input.\n";
            } else {
                cout << "Array saved: ";
                showArray(numbers);
            }
        } else if (choice == 2 || choice == 3) {
            if (numbers.empty()) {
                cout << "Enter a non-empty array first.\n";
                continue;
            }

            if (choice == 2)
                bubbleSort(numbers);
            else
                mergeSort(numbers, 0, static_cast<int>(numbers.size()) - 1);

            cout << "Sorted array: ";
            showArray(numbers);
        } else if (choice == 4) {
            if (numbers.empty()) {
                cout << "Enter a non-empty array first.\n";
                continue;
            }

            vector<int> sorted = numbers;
            sort(sorted.begin(), sorted.end());

            int target;
            cout << "Element to search: ";
            if (!(cin >> target)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input.\n";
                continue;
            }

            int index = binarySearch(sorted, target);

            if (index == -1)
                cout << "Element not found.\n";
            else
                cout << "Element found at sorted index " << index << ".\n";
        } else if (choice == 5) {
            int operation;
            cout << "1. Push  2. Pop  3. Display  4. Back\nChoose: ";

            if (!(cin >> operation)) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input.\n";
                continue;
            }

            if (operation == 1) {
                int value;
                cout << "Value: ";
                if (cin >> value)
                    stack.push(value);
                else {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid input.\n";
                }
            } else if (operation == 2) {
                stack.pop();
            } else if (operation == 3) {
                stack.display();
            } else if (operation != 4) {
                cout << "Invalid operation.\n";
            }
        } else if (choice == 6) {
            showArray(numbers);
        } else if (choice == 7) {
            cout << "Thanks for using AlgoVault!\n";
            break;
        } else {
            cout << "Choose a valid option.\n";
        }
    }

    return 0;
}
