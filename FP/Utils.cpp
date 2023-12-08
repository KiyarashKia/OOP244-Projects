/***********************************************************************
// Final project Milestone 1
// Module: Utils
// File: Utils.h
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name                 Date            Reason
***********************************************************************/
/*
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
Student : Kiarash Kia
Student ID: 108688235
Email: kkia2@myseneca.ca
Milestone 56 - Utils.cpp
Date : 12/08/2023
 */


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <cstring>
#include <iomanip>
#include "Utils.h"
using namespace std;
namespace sdds {
    Utils ut;
    void Utils::testMode(bool testmode) {
        m_testMode = testmode;
    }
    void Utils::getSystemDate(int* year, int* mon, int* day) {
        if (m_testMode) {
            if (day) *day = sdds_testDay;
            if (mon) *mon = sdds_testMon;
            if (year) *year = sdds_testYear;
        }
        else {
            time_t t = std::time(NULL);
            tm lt = *localtime(&t);
            if (day) *day = lt.tm_mday;
            if (mon) *mon = lt.tm_mon + 1;
            if (year) *year = lt.tm_year + 1900;
        }
    }
    int Utils::daysOfMon(int month, int year)const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    // Recommended methods for Utils

    void Utils::alocpy(char*& destination, const char* source) {

        if (destination != nullptr)
        {
            delete[] destination;
        }
        

        if (source != nullptr)
        {
            destination = new char[strlen(source) + 1];
            strcpy(destination, source);
        }
        else
        {
            destination = nullptr;
        }

    }

    int Utils::getint(const char* prompt) {

        int value;
        bool success = false;

        if (prompt != nullptr)
        {
            cout << prompt;
        }

        while (!success)
        {
            cin >> value;

            if (!cin)
            {
                cout << "Invalid Integer, retry: ";
                cin.clear();
                cin.ignore(2000, '\n');
            }
            else
            {
                success = true;
            }
        }
        return value;
    }

    int Utils::getint(int min, int max, const char* prompt, const char* errMes) {

        int value;
        bool InRange = false;


        if (prompt != nullptr)
        {
            cout << prompt;
        }

        while (!InRange)
        {
            value = getint();

            if (value < min || value > max)
            {
                if (errMes != nullptr)
                {
                    cout << errMes << ", retry: ";
                }
                else
                {
                    cout << "Value out of range [" << std::fixed << std::setprecision(2) << min << "<=val<=" << max << "]: ";
                }
            }
            else
            {
                InRange = true;
            }
        }
        return value;
    }

    double Utils::getdouble(const char* prompt) {
        double value;
        bool success = false;

        if (prompt != nullptr) {
            cout << prompt;
        }

        while (!success) {
            cin >> value;
            if (!cin) {
                cout << "Invalid number, retry: ";
                cin.clear();
                cin.ignore(2000, '\n');
            }
            else {
                success = true;
            }
        }
        return value;
    }



    double Utils::getdouble(double min, double max, const char* prompt, const char* errMes) {
        double value;
        bool InRange = false;

        if (prompt != nullptr) {
            cout << prompt;
        }

        while (!InRange) {
            value = getdouble();
            if (value < min || value > max) {
                if (errMes != nullptr) {
                    cout << errMes << ", retry: ";
                }
                else {
                    cout << "Value out of range [" << std::fixed << std::setprecision(2) << min << "<=val<=" << max << "]: ";
                }
            }
            else {
                InRange = true;
            }
        }
        return value;
    }

}