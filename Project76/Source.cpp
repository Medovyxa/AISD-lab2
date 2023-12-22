#include <iostream>
#include <cstdlib>


struct Student {
    std::string lastName;
    std::string firstName;
    int course;
    float average;

    Student(const std::string& last, const std::string& first, int crs, float avg)
        : lastName(last), firstName(first), course(crs), average(avg) {}

    friend std::ostream& operator<<(std::ostream& os, const Student& student) {
        os << "Студент: " << student.lastName << " " << student.firstName << ", Курс: " << student.course << ", Ср.балл: " << student.average;
        return os;
    }
};

template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(const T& value, Node* previous = nullptr, Node* nextNode = nullptr)
        : data(value), prev(previous), next(nextNode) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr) {
        Node<T>* otherCurrent = other.head;
        while (otherCurrent != nullptr) {
            push_tail(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }

    ~LinkedList() {
        while (head != nullptr) {
            pop_head();
        }
    }

    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            while (head != nullptr) {
                pop_head();
            }

            Node<T>* otherCurrent = other.head;
            while (otherCurrent != nullptr) {
                push_tail(otherCurrent->data);
                otherCurrent = otherCurrent->next;
            }
        }
        return *this;
    }

    void push_tail(const T& value) {
        Node<T>* newNode = new Node<T>(value, tail, nullptr);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    void push_tail(const LinkedList& other)
    {
        Node<T>* otherCurrent = other.head;
        while (otherCurrent != nullptr)
        {
            push_tail(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }
    }

    void push_head(const T& value) {
        Node<T>* newNode = new Node<T>(value, nullptr, head);
        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        }
        else {
            head->prev = newNode;
            head = newNode;
        }
    }
    bool is_empty() const
    {
        return head == nullptr;
    }

    void push_head(const LinkedList& other)
    {
        Node<T>* otherCurrent = other.head;
        LinkedList<T> temp;

        while (otherCurrent != nullptr)
        {
            temp.push_head(otherCurrent->data);
            otherCurrent = otherCurrent->next;
        }

        while (!temp.is_empty())
        {
            push_head(temp[0]);
            temp.pop_head();
        }
    }

    void pop_head() {
        if (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            else {
                tail = nullptr;
            }
            delete temp;
        }
    }

    void pop_tail() {
        if (head != nullptr) {
            Node<T>* temp = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            else {
                head = nullptr;
            }
            delete temp;
        }
    }

    void delete_node(const T& value) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                }
                else {
                    tail = current->prev;
                }
                delete current;
                return;
            }
            current = current->next;
        }
    }

    const T& operator[](int index) const {
        Node<T>* current = head;
        int i = 0;
        while (current != nullptr && i < index) {
            current = current->next;
            ++i;
        }

        if (current == nullptr) {
            throw std::out_of_range("Index out of range");
        }

        return current->data;
    }

    T& operator[](int index) {
        Node<T>* current = head;
        int i = 0;
        while (current != nullptr && i < index) {
            current = current->next;
            ++i;
        }

        if (current == nullptr) {
            throw std::out_of_range("Index out of range");
        }

        return current->data;
    }

    int countStudents() const {
        int count = 0;
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data.course >= 4 && current->data.average > 4.5) {
                count++;
            }
            current = current->next;
        }
        return count;
    }

    void print() const {
        Node<T>* current = head;
        while (current != nullptr) {
            std::cout << current->data << std::endl;
            current = current->next;
        }
        std::cout << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "Rus");
    LinkedList<Student> studentList;

    studentList.push_tail(Student("Андреев", "Даниил", 3, 4.8));
    studentList.push_tail(Student("Данилов", "Петр", 4, 4.8));
    studentList.push_tail(Student("Петров", "Максим", 5, 2.4));
    studentList.push_tail(Student("Максимов", "Александр", 4, 4.6));
    studentList.push_tail(Student("Александров", "Федор", 4, 4.7));

    int count = studentList.countStudents();
    std::cout << std::endl;
    studentList.print();
    std::cout << "Количество студентов удовлетворяющих требованиям: " << count << std::endl;

    count = 0;
    studentList.pop_tail();
    studentList.push_tail(Student("Федоров", "Артем", 4, 4.9));
    studentList.pop_head();
    studentList.push_head(Student("Артемов", "Владимир", 5, 3.1));
    count = studentList.countStudents();
    std::cout << std::endl;
    studentList.print();
    std::cout << "Количество студентов удовлетворяющих требованиям: " << count << std::endl;

    return 0;
}
