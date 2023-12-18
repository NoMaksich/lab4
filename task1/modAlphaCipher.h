/**
 * @file modAlphaCipher.h
 * @brief Шифрование методом Гронсвельда
 */
 
#pragma once
#include <vector>
#include <string>
#include <map>
#include <locale>

class modAlphaCipher {
private:
    std::string numAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; // алфавит по порядку
    std::map<char, int> alphaNum; // ассоциативный массив "номер по символу"
    std::vector<int> key; // ключ

    /**
     * @brief Преобразует строку в вектор чисел по алфавиту
     * @param s Строка для преобразования
     * @return Вектор чисел, соответствующих символам из алфавита
     */
    std::vector<int> convert(const std::string& s);

    /**
     * @brief Преобразует вектор чисел в строку по алфавиту
     * @param v Вектор чисел для преобразования
     * @return Строка символов, соответствующих числам из вектора
     */
    std::string convert(const std::vector<int>& v);

    /**
     * @brief Возвращает корректный ключ (только буквы алфавита в верхнем регистре)
     * @param s Исходный ключ
     * @return Корректный ключ для использования в шифровании
     */
    std::string getValidKey(const std::string & s);

    /**
     * @brief Проверяет и преобразует исходный текст в корректный для шифрования
     * @param s Исходный текст
     * @return Корректный текст для шифрования (только буквы алфавита в верхнем регистре)
     */
    std::string getValidOpenText(const std::string & s);

    /**
     * @brief Проверяет и преобразует зашифрованный текст в корректный формат
     * @param s Зашифрованный текст
     * @return Корректный зашифрованный текст (только буквы алфавита в верхнем регистре)
     */
    std::string getValidCipherText(const std::string & s);

public:
    /**
     * @brief Конструктор с ключом для шифрования
     * @param skey Ключ для шифрования
     */
    modAlphaCipher(const std::string& skey);

    /**
     * @brief Метод для шифрования текста
     * @param open_text Исходный текст для шифрования
     * @return Зашифрованный текст
     */
    std::string encrypt(const std::string& open_text);

    /**
     * @brief Метод для дешифрования текста
     * @param cipher_text Зашифрованный текст для дешифрования
     * @return Расшифрованный текст
     */
    std::string decrypt(const std::string& cipher_text);
};

/**
 * @brief Класс для обработки ошибок шифрования
 */
class cipher_error : public std::invalid_argument {
public:
    /**
     * @brief Конструктор с сообщением об ошибке
     * @param what_arg Сообщение об ошибке
     */
    explicit cipher_error(const std::string& what_arg) : std::invalid_argument(what_arg) {}

    /**
     * @brief Конструктор с сообщением об ошибке (символьный массив)
     * @param what_arg Сообщение об ошибке в виде символьного массива
     */
    explicit cipher_error(const char* what_arg) : std::invalid_argument(what_arg) {}
};
