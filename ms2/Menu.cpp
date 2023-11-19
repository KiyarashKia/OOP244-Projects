#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Menu.h"

using namespace std;
namespace sdds {

    Menu::Menu(const char* content) {
        numOptions = 0;
        isValid = false;
        options = nullptr;

        if (content != nullptr) {
            for (int i = 0; i < strlen(content); i++) {
                if (content[i] == '\t') numOptions++;
            }

            if (numOptions <= maxNumOptions) {
                options = new char[strlen(content) + 1];
                strcpy(options, content);
                isValid = true;
            }
        }
    }



	// RO3
	Menu::~Menu() {
        delete[] options;
        options = nullptr;
	}

 
    unsigned int Menu::run() const {
        int userInput = 0;
        int index = 1;

        if (options) {  // Start of the 'if' block
            cout << index << "- ";
            for (size_t i = 0; i < strlen(options); i++) {
                if (options[i] == '\t') {
                    cout << endl;
                    cout << ++index << "- ";
                }
                else {
                    cout << options[i];
                }
            }
            cout << endl << "---------------------------------" << endl << "0- Exit" << endl << "> ";

            do {
                cin >> userInput;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid Integer, retry: ";
                    cin.clear();
                    userInput = false;
                }
                else if (userInput < 0 || userInput > index) {
                    cout << "Value out of range [0<=val<=" << index << "]: ";
                    cin.clear();
                }
            } while (userInput < 0 || userInput > index);

            return userInput;
        }
        else { 
            cout << "Invalid Menu!" << endl;
            return 0;
        }
    }



}