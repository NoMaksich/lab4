/**
 * @file main.cpp
 * @brief Пример использования класса modAlphaCipher для шифрования и дешифрования текста
 */

#include <iostream>
#include "modAlphaCipher.h"
#include <locale>
#include <clocale>
#include <cwctype>
#include <cctype>

using namespace std;

/**
 * @brief Функция для шифрования, дешифрования и проверки работы класса modAlphaCipher
 * 
 * @param Text Исходный текст для шифрования и последующего дешифрования
 * @param key Ключ для шифрования
 * @param destructCipherText  параметр для "порчи" зашифрованного текста
 */
void check(const string& Text, const string& key, const bool destructCipherText = false) {
    try {
        string cipherText;
        string decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text);
        if (destructCipherText) { // надо "портить"?
            cipherText += 'd';
        }
        decryptedText = cipher.decrypt(cipherText);
        cout << "key=" << key << endl;
        cout << Text << endl;
        cout << cipherText << endl;
        cout << decryptedText << endl;
    } catch (const cipher_error & e) {
        cerr << "Error: " << e.what() << endl;
    }
}

/**
 * @brief Точка входа в программу
 * 
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 * @return Код завершения программы
 */
int main(int argc, char **argv) { 
    // Пример использования класса modAlphaCipher для шифрования и дешифрования текста
    check("METALNIKOV", "SECRET", true);
    return 0;
}
