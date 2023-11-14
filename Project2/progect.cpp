#include <iostream>
#include <time.h> 
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <ctime>
#include "compare_string.h"


enum ColorConsole {
    Blue = 1,
    Green = 2,
    Read = 12,
    White = 7,
};
class Node {
public:
	std::string date;
    std::string color;
	int score;
	Node* right;
	Node* left;
    Node* pref;
	Node(std::string date) {
        color = "White";
		this->date = date;
		right = nullptr;
		left = nullptr;
		score = 1;
	}
};

class BiTree {
	
    std::string found_str;
    char found_symbol;
    bool flag_found_str = 0;
    bool flag_found_symbol = 0;
	void add_more(std::string date, Node* Newroot);
	void remove_more(std::string date, Node * deleteNode);
    void paint_more_char(Node* left, Node* right);
    void paint_left_char(Node* left);
    void paint_right_char(Node* right);
    void paint_more_string(Node* left, Node* right);
    void paint_left_string(Node* left);
    void paint_right_string(Node* right);
    void found_more(Node* found, std::string str);
    struct Trunk
    {
        Trunk* prev;
        std::string str;

        Trunk(Trunk* prev, std::string str)
        {
            this->prev = prev;
            this->str = str;
        }
    };

    // Вспомогательная функция для печати ветвей бинарного дерева
    void showTrunks(Trunk* p)
    {
        if (p == nullptr) {
            return;
        }

        showTrunks(p->prev);
        std::cout << p->str;
    }

    void printTree(Node* root, Trunk* prev, bool isLeft)
    {
        if (root == nullptr) {
            return;
        }

        std::string prev_str = "    ";
        Trunk* trunk = new Trunk(prev, prev_str);

        printTree(root->right, trunk, true);

        if (!prev) {
            trunk->str = "---";
        }
        else if (isLeft)
        {
            trunk->str = ".---";
            prev_str = "   |";
        }
        else {
            trunk->str = "`---";
            prev->str = prev_str;
        }

        showTrunks(trunk);
        HANDLE hConsole;
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (root->color == "Green") {
            SetConsoleTextAttribute(hConsole, Green);
            std::cout << " " << root->date << std::endl;
            SetConsoleTextAttribute(hConsole, White);
        }
        else if (root->color == "Blue") {
            SetConsoleTextAttribute(hConsole, Blue);
            std::cout << " " << root->date << std::endl;
            SetConsoleTextAttribute(hConsole, White);
        }
        else if (root->color == "Read") {
            SetConsoleTextAttribute(hConsole, Read);
            std::cout << " " << root->date << std::endl;
            SetConsoleTextAttribute(hConsole, White);
        }
        else {
            SetConsoleTextAttribute(hConsole, White);
            std::cout << " " << root->date << std::endl;
        }
        if (prev) {
            prev->str = prev_str;
        }
        trunk->str = "   |";

        printTree(root->left, trunk, false);
    }

public:
    Node* root;
	void add(std::string date);
	void remove(std::string date);
	void show();
    void paint();
    void FoundStr(std::string str);
    void FoundSymbol(char symbol);
    void FoundElem(std::string str);
    int GetLevel(Node* find);
    int MaxDepth() {
        return height(root);
    }
    int height(Node* root);
	BiTree();
	~BiTree();
    Node* GetRoot()const {
        return root;
    }
};

#include "BiTree.h"

void BiTree::add(std::string date) {
	if (root == nullptr) {
		root = new Node(date);
		root->pref = nullptr;
	}
	else {
		add_more(date, root);
	}
}

void BiTree::add_more(std::string date, Node* newNode) {
	if (compare_string(date, newNode->date) == 0) {
		if (newNode->right != nullptr) {
			add_more(date, newNode->right);
		}
		else {
			newNode->right = new Node(date);
			newNode->right->pref = newNode;
		}
	}
	else if (compare_string(date, newNode->date) == 1) {
		if (newNode->left != nullptr) {
			add_more(date, newNode->left);
		}
		else {
			newNode->left = new Node(date);
			newNode->left->pref = newNode;
		}
	}
	else {
		newNode->score++;
	}
}

void BiTree::remove_more(std::string date, Node* deleteNode)
{
	if (date == deleteNode->date) {
		if (deleteNode->score == 1) {
			if (deleteNode->left == nullptr && deleteNode->right != nullptr) {
				if (deleteNode->pref->right = deleteNode) {
					deleteNode->pref->right = deleteNode->right;
					delete deleteNode;
				}
				else {
					deleteNode->pref->left = deleteNode->right;
					delete deleteNode;
				}
			}
			else if (deleteNode->right == nullptr && deleteNode->left != nullptr) {
				if (deleteNode->pref->right = deleteNode) {
					deleteNode->pref->right = deleteNode->left;
					delete deleteNode;
				}
				else {
					deleteNode->pref->left = deleteNode->left;
					delete deleteNode;
				}
			}
			else {
				Node* current = deleteNode->left;
				while (current->right != nullptr) {
					current = current->right;
				}
				if (current->left != nullptr) {
					deleteNode->date = current->date;
					deleteNode->score = current->score;
					current->pref->right = current->left;
					delete current;
				}
				else {
					deleteNode->date = current->date;
					deleteNode->score = current->score;
					if (current->pref->right->date == deleteNode->date) {
						current->pref->right = nullptr;
						delete current;
					}
					else {
						current->pref->left = nullptr;
						delete current;
					}
					
					

				}
			}
		}
		else {
			deleteNode->score--;
		}
	}
	else if (date > deleteNode->date) {
		if (deleteNode->right != nullptr) {
			remove_more(date, deleteNode->right);
		}
		else {
			std::cout << "node not found" << std::endl;
		}
	}
	else {
		if (deleteNode->left != nullptr) {
			remove_more(date, deleteNode->left);
		}
		else {
			std::cout << "node not found" << std::endl;
		}
	}
}




void BiTree::remove(std::string date) {
	if (root == nullptr) {
		std::cout << "tree is empty" << std::endl;
	}
	else {
		remove_more(date, root);
	}
}

void BiTree::show()
{
	paint();
	printTree(root, nullptr, false);

}
void BiTree::FoundStr(std::string str) {
	found_str = str;
	flag_found_str = 1;
	paint();
}

void BiTree::FoundSymbol(char symbol) {
	found_symbol = symbol;
	flag_found_symbol = 1;
	paint();
}
void BiTree::paint() {
	if (flag_found_str == 1) {
		if (root != nullptr) {
			if (root->date.find(found_str) != std::string::npos) {
				if (root->color == "Read") {

				}
				else if (root->color == "Blue") {
					root->color = "Read";
				}
				else {
					root->color = "Green";
				}
				
			}

			if (root->right == nullptr && root->left == nullptr) {
				return;
			}
			else if (root->right == nullptr) {
				paint_left_string(root->left);
			}
			else if (root->left == nullptr) {
				paint_right_string(root->left);
			}
			else {
				paint_more_string(root->right, root->left);
			}
		}
	}
	if (flag_found_symbol == 1) {
		if (root != nullptr) {
			if (root->date[0] == found_symbol) {
				if (root->color == "Read") {

				}
				else if (root->color == "Green") {
					root->color = "Read";
				}
				else {
					root->color = "Blue";
				}
			}
			if (root->right == nullptr && root->left == nullptr) {
				return;
			}
			else if (root->right == nullptr) {
				paint_left_char(root->left);
			}
			else if (root->left == nullptr) {
				paint_right_char(root->left);
			}
			else {
				paint_more_char(root->right, root->left);
			}
		}
	}
}

void BiTree::paint_more_string(Node* right, Node* left)
{
	if (right == nullptr && left == nullptr) {
		return;
	}
	else if (right == nullptr) {
		if (left->date.find(found_str) != std::string::npos) {
			if (left->color == "Read") {

			}
			else if (left->color == "Blue") {
				left->color = "Read";
			}
			else {
				left->color = "Green";
			}

		}
		return paint_left_string(left);
	}
	else if (left == nullptr) {
		if (right->date.find(found_str) != std::string::npos) {
			if (right->color == "Read") {

			}
			else if (right->color == "Blue") {
				right->color = "Read";
			}
			else {
				right->color = "Green";
			}
		}
		return paint_more_string(right->right, right->left);
	}
	else {
		if (right->date.find(found_str) != std::string::npos) {
			if (right->color == "Read") {

			}
			else if (right->color == "Blue") {
				right->color = "Read";
			}
			else {
				right->color = "Green";
			}
		}
		if (left->date.find(found_str) != std::string::npos) {
			if (left->color == "Read") {

			}
			else if (left->color == "Blue") {
				left->color = "Read";
			}
			else {
				left->color = "Green";
			}
		}
		return paint_more_string(right->right, right->left), paint_more_string(left->right, left->left);
	}
}


void BiTree::paint_right_string(Node* right)
{
	if (right->date.find(found_str) != std::string::npos) {
		if (right->color == "Read") {

		}
		else if (right->color == "Blue") {
			right->color = "Read";
		}
		else {
			right->color = "Green";
		}
	}
	if (right->right != nullptr && right->left != nullptr) {
		return paint_more_string(right->left, right->right);
	}
	else if (right->right != nullptr && right->left == nullptr) {
		return paint_right_string(right->right);
	}
	else if (right->right == nullptr && right->left != nullptr) {
		return paint_left_string(right->left);
	}
	else {

	}
}


void BiTree::paint_left_string(Node* left)
{
	if (left->date.find(found_str) != std::string::npos) {
		if (left->color == "Read") {

		}
		else if (left->color == "Blue") {
			left->color = "Read";
		}
		else {
			left->color = "Green";
		}
	}
	if (left->right != nullptr && left->left != nullptr) {
		return paint_more_string(left->left, left->right);
	}
	else if (left->right != nullptr && left->left == nullptr) {
		return paint_right_string(left->right);
	}
	else if (left->right == nullptr && left->left != nullptr) {
		return paint_left_string(left->left);
	}
	else {

	}
}

void BiTree::paint_more_char(Node* right, Node* left) {

	if (right == nullptr && left == nullptr) {
		return;
	}
	else if (right == nullptr) {
		if (left->date[0] == found_symbol) {
			if (left->color == "Read") {

			}
			else if (left->color == "Green") {
				left->color = "Read";
			}
			else {
				left->color = "Blue";
			}
		}
		return paint_left_char(left);
	}
	else if (left == nullptr) {
		if (right->date[0] == found_symbol) {
			if (right->color == "Read") {

			}
			else if (right->color == "Green") {
				right->color = "Read";
			}
			else {
				right->color = "Blue";
			}
			
		}
		return paint_more_char(right->right, right->left);
	}
	else {
		if (right->date[0] == found_symbol) {
			if (right->color == "Read") {

			}
			else if (right->color == "Green") {
				right->color = "Read";
			}
			else {
				right->color = "Blue";
			}

		}
		if (left->date[0] == found_symbol) {
			if (left->color == "Read") {

			}
			else if (left->color == "Green") {
				left->color = "Read";
			}
			else {
				left->color = "Blue";
			}
		}
		return paint_more_char(right->right, right->left), paint_more_char(left->right, left->left);
	}
}

void BiTree::paint_right_char(Node* right) {
	if (right->date[0] == found_symbol) {
		if (right->color == "Read") {

		}
		else if (right->color == "Green") {
			right->color = "Read";
		}
		else {
			right->color = "Blue";
		}

	}
	if (right->right != nullptr && right->left != nullptr) {
		return paint_more_char(right->left, right->right);
	}
	else if (right->right != nullptr && right->left == nullptr) {
		return paint_right_char(right->right);
	}
	else if (right->right == nullptr && right->left != nullptr) {
		return paint_left_char(right->left);
	}
	else {

	}
}

void BiTree::paint_left_char(Node* left) {
	if (left->date[0] == found_symbol) {
		if (left->color == "Read") {

		}
		else if (left->color == "Green") {
			left->color = "Read";
		}
		else {
			left->color = "Blue";
		}
	}
	if (left->right != nullptr && left->left != nullptr) {
		return paint_more_char(left->left, left->right);
	}
	else if (left->right != nullptr && left->left == nullptr) {
		return paint_right_char(left->right);
	}
	else if (left->right == nullptr && left->left != nullptr) {
		return paint_left_char(left->left);
	}
	else {

	}
}

void BiTree::FoundElem(std::string str) {
	found_more(root, str);
}

int BiTree::GetLevel(Node* find)
{
	int score = 0;
	if (root != nullptr) {
		Node* temp = root;
		if (find->date == temp->date) {
			return 0;
		}
		else {
			while(find->date != temp->date){
				if (compare_string(find->date, temp->date) == 0) {
					if (temp->right != nullptr) {
						temp = temp->right;
						score++;
					}
					else {
						std::cout << "Node not found" << std::endl;
					}
					
					
				}
				else if (compare_string(find->date, temp->date) == 1) {
					if (temp->right != nullptr) {
						temp = temp->left;
						score++;
					}
					else {
						std::cout << "Node not found" << std::endl;
					}
				}
			}
			return score;
		}
	}
	
}

int BiTree::height(Node* root)
{
	// базовый случай: пустое дерево имеет высоту 0
	if (root == nullptr) {
		return 0;
	}

	// повторяем для левого и правого поддерева и учитываем максимальную глубину
	return 1 + max(height(root->left), height(root->right));
}


void BiTree::found_more(Node* found, std::string str) {
	if (compare_string(found->date, str) == 1) {
		std::cout << found->date << std::endl;
		return found_more(found->right, str);
	}
	else if (compare_string(found->date, str) == 0) {
		std::cout << found->date << std::endl;
		return found_more(found->left, str);
	}
	else if(found->date == str){
		std::cout << found->date << std::endl;
		return;
	}
	else {
		std::cout << "Node didn't found" << std::endl;
	}
}

/*void BiTree::clear()
{
	if (root != nullptr) {
		if (root->right != nullptr && root->left != nullptr) {
			Node* temp_right = root->right;
			Node* temp_left = root->left;
			delete root;
			temp_left->pref = nullptr;
			temp_right->pref = nullptr;
			return clear_more(temp_right, temp_left);
		}
		else if (root->left == nullptr && root->right != nullptr) {
			Node* temp_right = root->right;
			delete root;
			temp_right->pref = nullptr;
			return clear_side(temp_right);
		}
		else if (root->left != nullptr && root->right == nullptr) {
			Node* temp_left = root->left;
			delete root;
			temp_left->pref = nullptr;
			return clear_more(temp_left);
		}
		else {
			return;
		}
	}
}*/

BiTree::BiTree()
{

}


BiTree ::~BiTree() {

}
#include <string>

bool compare_string(std::string left, std::string right);

#include "compare_string.h"
bool compare_string(std::string left, std::string right) {
	int size_right = right.size();
	int size_left = right.size();
	if (size_right > size_left) {
		for (int i = 0; i < size_left; ++i) {
			if (left[i] > right[i]) {
				return 0;
			}
			else if (left[i] < right[i]) {
				return 1;
			}
			else {

			}
		}
	}
	else {
		for (int i = 0; i < size_right; ++i) {
			if (left[i] > right[i]) {
				return 0;
			}
			else if (left[i] < right[i]) {
				return 1;
			}
			else {

			}
		}
	}
}
