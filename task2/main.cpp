/**
 * @file main.cpp
 * @brief Пример использования класса Shifr для шифрования и дешифрования текста
 */

#include <iostream>
#include "shifr.h"

/**
 * @brief Функция для шифрования, дешифрования и проверки работы класса Shifr
 * 
 * @param Text Исходный текст для шифрования и последующего дешифрования
 * @param key Ключ для шифрования
 * @param destructCipherText  параметр для "порчи" зашифрованного текста
 */
void check(const std::wstring& Text, const int key, const bool destructCipherText = false) {
    try {
        std::wstring cipherText;
        std::wstring decryptedText;
        Shifr cipher(key);
        cipherText = cipher.encrypt(Text);
        if (destructCipherText) { // надо "портить"?
            cipherText += L'и';
        }
        decryptedText = cipher.decrypt(cipherText);
        std::wcout << L"key=" << key << std::endl;
        std::wcout << Text << std::endl;
        std::wcout << cipherText << std::endl;
        std::wcout << decryptedText << std::endl;
    } catch (const cipher_error & e) {
        std::wcerr << L"Error: " << e.what() << std::endl;
    }
}

/**
 * @brief Использование функции check для проверки шифрования
 * 
 * @return Код завершения программы
 */
int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int columns;
    std::wcout << L"Enter the number of columns in the table: ";
    std::wcin >> columns;
    std::wcin.ignore();
    
    std::wstring text;
    std::wcout << L"Enter the encryption text: ";
    getline(std::wcin, text);
    check(text, columns, true);
    return 0;
}
