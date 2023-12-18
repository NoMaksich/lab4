/**
 * @file shifr.h
 * @brief Заголовочный файл с описанием класса Shifr для шифрования текста
 */

#pragma once
#include <string>
#include <stdexcept>
#include <cctype>

/**
 * @class Shifr
 * @brief Класс для шифрования текста методом сдвига по колонкам
 */
class Shifr {
public:
    /**
     * @brief Конструктор класса Shifr
     * @param columns Количество столбцов для шифрования
     */
    Shifr(int columns);

    /**
     * @brief Метод для шифрования текста
     * @param plaintext Исходный текст для шифрования
     * @return Зашифрованный текст
     */
    std::wstring encrypt(const std::wstring& plaintext);

    /**
     * @brief Метод для дешифрования текста
     * @param ciphertext Зашифрованный текст для дешифрования
     * @return Расшифрованный текст
     */
    std::wstring decrypt(const std::wstring& ciphertext);

    /**
     * @brief Метод для проверки и получения корректного ключа
     * @param key Исходный ключ для проверки
     * @return Корректный ключ для использования в шифровании
     */
    int getValidKey(int key);

    /**
     * @brief Метод для проверки и получения корректного открытого текста
     * @param s Исходный открытый текст
     * @return Корректный открытый текст для шифрования
     */
    std::wstring getValidOpenText(const std::wstring &s);

    /**
     * @brief Метод для проверки и получения корректного зашифрованного текста
     * @param s Исходный зашифрованный текст
     * @return Корректный зашифрованный текст для дешифрования
     */
    std::wstring getValidCipherText(const std::wstring &s);

private:
    int key; /**< Ключ для шифрования */
};

/**
 * @class cipher_error
 * @brief Класс для обработки ошибок шифрования
 */
class cipher_error : public std::invalid_argument {
public:
    /**
     * @brief Конструктор класса cipher_error с сообщением об ошибке
     * @param what_arg Сообщение об ошибке
     */
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}

    /**
     * @brief Конструктор класса cipher_error с сообщением об ошибке (символьный массив)
     * @param what_arg Сообщение об ошибке в виде символьного массива
     */
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};
