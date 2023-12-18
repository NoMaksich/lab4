/**
 * @file shifr.cpp
 * @brief Файл реализации класса Shifr для шифрования текста методом сдвига по колонкам
 */

#include "shifr.h"
#include <iostream>
#include <locale>
#include <algorithm>

/**
 * @brief Конструктор класса Shifr
 * @param columns Количество столбцов для шифрования
 * @throw cipher_error Если ключ меньше или равен единице
 */
Shifr::Shifr(int columns) : key(columns) {
    if (key <= 1) {
        throw cipher_error("Invalid key");
    }
}

/**
 * @brief Метод для шифрования текста
 * @param open_text Исходный текст для шифрования
 * @return Зашифрованный текст
 */
std::wstring Shifr::encrypt(const std::wstring& open_text) {
    std::wstring tmp = getValidOpenText(open_text);

    // Преобразование всех символов в верхний регистр
    std::transform(tmp.begin(), tmp.end(), tmp.begin(), [](wchar_t c) {
        return std::towupper(c);
    });

    int length = tmp.length();
    int rows = (length + key - 1) / key;

    std::wstring ciphertext;

    for (int i = key - 1; i >= 0; --i) {
        for (int j = 0; j < rows; ++j) {
            int index = j * key + i;
            if (index < length) {
                ciphertext += tmp[index];
            } else {
                ciphertext += ' ';
            }
        }
    }

    return ciphertext;
}

/**
 * @brief Метод для дешифрования текста
 * @param cipher_text Зашифрованный текст для дешифрования
 * @return Расшифрованный текст
 */
std::wstring Shifr::decrypt(const std::wstring& cipher_text) {
    std::wstring tmp = getValidCipherText(cipher_text);

    int length = tmp.length();
    int rows = (length + key - 1) / key;

    std::wstring text;

    for (int i = 0; i < rows; ++i) {
        for (int j = key - 1; j >= 0; --j) {
            int index = i + j * rows;
            if (index < length) {
                text += tmp[index];
            } else {
                text += ' ';
            }
        }
    }

    return text;
}

/**
 * @brief Метод для проверки и получения корректного ключа
 * @param key Исходный ключ для проверки
 * @throw cipher_error Если ключ меньше или равен единице или является буквой
 * @return Корректный ключ для использования в шифровании
 */
int Shifr::getValidKey(int key) {
    if (key <= 1 || iswalpha(key)) {
        throw cipher_error("Invalid key");
    }
    return key;
}

/**
 * @brief Метод для проверки и получения корректного открытого текста
 * @param s Исходный открытый текст
 * @throw cipher_error Если текст содержит недопустимые символы или является пустым
 * @return Корректный открытый текст для шифрования
 */
std::wstring Shifr::getValidOpenText(const std::wstring &s) {
    std::wstring tmp;
    for (size_t i = 0; i < s.size(); i++) {
        wchar_t c = s[i];
        if ((c >= L'А' && c <= L'Я') || (c >= L'а' && c <= L'я') || c == L'ё' || c == L'Ё' || c == L' ') {
            tmp.push_back(std::towupper(c));
        }
    }
    if (tmp.empty()) {
        throw cipher_error("Invalid open text");
    }
    return tmp;
}

/**
 * @brief Метод для проверки и получения корректного зашифрованного текста
 * @param s Исходный зашифрованный текст
 * @throw cipher_error Если текст содержит недопустимые символы, пуст или содержит символы в нижнем регистре
 * @return Корректный зашифрованный текст для дешифрования
 */
std::wstring Shifr::getValidCipherText(const std::wstring &s) {
    std::wstring tmp;
    for (auto c : s) {
        if (iswupper(c)) {
            tmp.push_back(c);
        } else if (c == L' ') {
            tmp.push_back(L' ');
        } else {
            throw cipher_error("Invalid cipher text");
        }
    }

    if (tmp.empty()) {
        throw cipher_error("Empty cipher text");
    }
    return tmp;
}
