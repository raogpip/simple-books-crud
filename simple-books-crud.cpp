#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "windows.h"




const int size = 180;

std::string bookAuthor[size] = {}; //book author
std::string bookName[size] = {}; //book name
std::string bookID[size] = {}; //book ID

void sortItem();        void addItem();    void printList();
void openFile();        void deleteItem(std::string search);
void saveToFile();      void updateItem(std::string search);


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::cout << "***ВАША ДОМАШНЯ БІБЛІОТЕКА***\n";
    int choice;
    std::string bookID; 
    openFile();

    do
    {
        std::cout << "1 - Додати Книгу\n";
        std::cout << "2 - Змінити інформацію про книгу\n";
        std::cout << "3 - Видалити книгу\n";
        std::cout << "4 - Відсортувати книги\n";
        std::cout << "5 - Вевести список книг на екран\n";
        std::cout << "6 - Зберегти та вийти\n";
        std::cout << "********************************\n";
        std::cout << "Оберіть опцію >> ";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            addItem();
            std::system("CLS");
            break;
        case 2:
            std::cin.ignore();
            std::cout << "Введіть ID книги для редагування: ";
            getline(std::cin, bookID);
            updateItem(bookID);
            break;
        case 3:
            std::cin.ignore();
            std::cout << "Введіть ID книги для видалення: ";
            getline(std::cin, bookID);
            deleteItem(bookID);
            break;
        case 4:
            sortItem();
            break;
        case 5:
            printList();
            break;
        default:
            break;
        }
    } while (choice != 6);

    saveToFile();
    std::cout << "Вихід...Збереження у файл.\n";

    return 0;
}



void addItem() {
    char name[50];
    char bookNumber[5];
    char author[50];

    std::cin.ignore();

    std::cout << "ID книги >> ";
    std::cin.getline(bookNumber, 5);

    std::cout << "Назва книги >> ";
    std::cin.getline(name, 50);

    std::cout << "Автор книги >> ";
    std::cin.getline(author, 50);

    for (int i = 0; i < size; i++)
    {
        if (bookID[i] == "\0")
        {
            bookID[i] = bookNumber;
            bookName[i] = name;
            bookAuthor[i] = author;
            break;
        }
    }
}


void printList() {
    std::system("CLS");
    std::cout << "Поточний список книг(и)\n";
    std::cout << "====================================================================================================\n";

    int counter = 0;
    std::cout << " No. |  ID  |               НАЗВА                  |                   АВТОР                       |" << "\n" << "----------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < size; i++)
    {
        if (bookID[i] != "\0")
        {
            counter++;
            std::cout << "  " << counter << "     " << bookID[i] << std::setw(38) << bookName[i]<< "  |" << std::setw(45) << bookAuthor[i]<<"  |" << "\n";
        }
    }
    if (counter == 0)
    {
        std::cout << "Немає книг в списку\n";
    }
    std::cout << "====================================================================================================\n";
}

void updateItem(std::string search) {
    char name[50];
    char author[50];
    char bookNumber[5];

    int counter = 0;
    for (int i = 0; i < size; i++)
    {
        if (bookID[i] == search)
        {
            counter++;
            std::cout << "Назва книги >>";
            std::cin.getline(name, 50);
            std::cout << "Автор книги >>";
            std::cin.getline(author, 50);

            bookName[i] = name;
            bookAuthor[i] = author;
            std::cout << "Редагування успішне!\n";
            break;
        }
    }
    if (counter == 0)
    {
        std::cout << "Такого ID не існує...\n";
    }
    std::cout << "=======================================\n";
}

void deleteItem(std::string search) {
    int counter = 0;
    for (int i = 0; i < size; i++)
    {
        if (bookID[i] == search)
        {
            counter++;
            bookID[i] = "";
            bookName[i] = "";
            bookAuthor[i] = "";
            std::cout << "Видалення успішне!\n";
            break;
        }
    }
    if (counter == 0)
    {
        std::cout << "Такого ID не існує...\n";
    }
    std::cout << "=======================================\n";
}

void openFile() {
    std::string line;
    std::ifstream myfile("C:\\lib\\library.txt");
    if (myfile.is_open())
    {
        int i = 0;
        while (getline(myfile, line))
        {
            int length = line.length();
            bookID[i] = line.substr(0, 3);
            bookName[i] = line.substr(line.find("Name:") + 5, line.find("Author:") - 12);
            bookAuthor[i] = line.substr(line.find("Author:") + 7, 100);
            i++;
        }
    }
    else
        std::cout << "Не вдалося відкрити файл\n";
}

void saveToFile() {
    std::ofstream myfile;
    myfile.open("C:\\lib\\library.txt");
    for (int i = 0; i < size; i++)
    {
        if (bookID[i] == "\0")
        {
            break;
        }
        else
            myfile << bookID[i] + ", Name:" + bookName[i] + ", Author:" + bookAuthor[i] << "\n";
    }
}

void sortItem() {
    int k = 0;
    std::string tmp{};
    std::string tmp_1{};
    std::string tmp_2{};
    for (int i = 0; i < size; i++)
    {
        k = i;
        for (int j = i; j < size; j++)
        {
            if (bookName[k] > bookName[j])
                k = j;
        }
        tmp = bookName[i];
        tmp_1 = bookID[i];
        tmp_2 = bookAuthor[i];
        bookName[i] = bookName[k];
        bookID[i] = bookID[k];
        bookAuthor[i] = bookAuthor[k];
        bookName[k] = tmp;
        bookID[k] = tmp_1;
        bookAuthor[k] = tmp_2;
    }
}