/**
 * @file modAlphaCipher.cpp
 * @brief Реализация методов шифрования методом Гронсвельда
 */
 
#include "modAlphaCipher.h"
#include <locale>
/**
 * @brief Конструктор класса `modAlphaCipher`
 * 
 * @param skey Ключ для шифрования
 * @throw cipher_error Если ключ слабый (содержит слишком много нулей)
 */
modAlphaCipher::modAlphaCipher(const std::string& skey) {

    // Инициализация алфавита
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    // Преобразование ключа и проверка на слабость ключа
    key = convert(getValidKey(skey));
    int n = 0;
    for (auto e : key) {
        if (e == 0)
            n++;
    }
    if (2 * n > key.size())
        throw cipher_error("WeakKey");
}

/**
 * @brief Метод для шифрования текста
 * 
 * @param open_text Исходный текст для шифрования
 * @return Зашифрованный текст
 */
std::string modAlphaCipher::encrypt(const std::string& open_text) {

    std::vector<int> work = convert(getValidOpenText(open_text));
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

/**
 * @brief Метод для дешифрования текста
 * 
 * @param cipher_text Зашифрованный текст для дешифрования
 * @return Расшифрованный текст
 */
std::string modAlphaCipher::decrypt(const std::string& cipher_text) {

    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

/**
 * @brief Преобразует строку символов в вектор чисел по алфавиту
 * 
 * @param s Строка для преобразования
 * @return Вектор чисел, соответствующих символам из алфавита
 */
inline std::vector<int> modAlphaCipher::convert(const std::string& s) {

    std::vector<int> result;
    for (auto c : s) {
        result.push_back(alphaNum[c]);
    }
    return result;
}

/**
 * @brief Преобразует вектор чисел в строку символов алфавита
 * 
 * @param v Вектор чисел для преобразования
 * @return Строка символов, соответствующих числам из вектора
 */
inline std::string modAlphaCipher::convert(const std::vector<int>& v) {

    std::string result;
    for (auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}

/**
 * @brief Проверяет и возвращает корректный ключ для шифрования
 * 
 * @param s Исходный ключ
 * @throw cipher_error Если ключ пустой или содержит недопустимые символы
 * @return Корректный ключ для использования в шифровании
 */
inline std::string modAlphaCipher::getValidKey(const std::string & s) {

    if (s.empty())
        throw cipher_error("Empty key");

    std::string tmp(s);
    for (auto& c : tmp) {
        if (!isalpha(c))
            throw cipher_error(std::string("Invalid key"));
        if (islower(c))
            c = toupper(c);
    }
    return tmp;
}

/**
 * @brief Проверяет и преобразует исходный текст в корректный для шифрования
 * 
 * @param s Исходный текст
 * @throw cipher_error Если текст пустой или содержит недопустимые символы
 * @return Корректный текст для шифрования (только буквы алфавита в верхнем регистре)
 */
inline std::string modAlphaCipher::getValidOpenText(const std::string & s) {

    std::string tmp;
    for (auto c : s) {
        if (isalpha(c)) {
            if (islower(c))
                tmp.push_back(toupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Empty open text");
    return tmp;
}

/**
 * @brief Проверяет и преобразует зашифрованный текст в корректный формат
 * 
 * @param s Зашифрованный текст
 * @throw cipher_error Если текст пустой или содержит недопустимые символы
 * @return Корректный зашифрованный текст (только буквы алфавита в верхнем регистре)
 */
inline std::string modAlphaCipher::getValidCipherText(const std::string & s) {

    if (s.empty())
        throw cipher_error("Empty cipher text");

    for (auto c : s) {
        if (!isupper(c))
            throw cipher_error(std::string("Invalid cipher text"));
    }
    return s;
}
