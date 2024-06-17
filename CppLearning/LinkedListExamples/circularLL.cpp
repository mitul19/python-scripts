#include <iostream>
#include <vector>
#include <algorithm> // for std::random_shuffle

class Node
{
public:
    int data;
    Node *next;

    Node(int data)
    {
        this->data = data;
        this->next = nullptr;
    }
};

class CLL
{
private:
    Node *head;
    Node *tail;

public:
    CLL()
    {
        head = nullptr;
        tail = nullptr;
    }

    void append(int data)
    {
        Node *new_node = new Node(data);
        if (!head)
        {
            head = new_node;
            tail = head;
            head->next = head;
            return;
        }

        tail->next = new_node;
        new_node->next = head;
        tail = new_node;
    }

    void print()
    {
        if (!head)
        {
            return;
        }

        Node *cur = head;
        do
        {
            std::cout << cur->data << "->";
            cur = cur->next;
        } while (cur != head);
        std::cout << "..." << std::endl;
    }
};

int main()
{
    std::vector<int> elements = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    // std::random_shuffle(elements.begin(), elements.end());

    CLL cll;
    for (int e : elements)
    {
        cll.append(e);
    }
    cll.print();

    return 0;
}
