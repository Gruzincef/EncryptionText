#include <iostream>
#include <Windows.h>
#include <string>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

wstring replacementEncryption(wstring text, map<wchar_t, wchar_t>*& key) {
    int count = wcslen(text.c_str())+1;
    wchar_t* original =new wchar_t[count];
    wchar_t* encrypt = new wchar_t[count];
    const wchar_t* dt = text.c_str();
    wcsncpy_s(original, count, dt, count - 1);
    wcsncpy_s(encrypt, count, dt, count - 1);
    map<wchar_t, wchar_t>::iterator it;
    for (it = key->begin(); it != key->end(); ++it)
    {
        for (int j = 0; j < count; j++)
        {
            if (original[j] == it->first) encrypt[j] = it->second;
        }
    }
    wstring s(encrypt);
    delete[] encrypt;
    delete[] original;
    return s;
}
wstring replacementDecryption(wstring text, map<wchar_t, wchar_t>*& key) {
    int count = wcslen(text.c_str())+1;
    wchar_t* original = new wchar_t[count];
    wchar_t* decrypt = new wchar_t[count];
    const wchar_t* dt = text.c_str();
    wcsncpy_s(original, count, dt, count-1);
    wcsncpy_s(decrypt, count, dt, count - 1);
    map<wchar_t, wchar_t>::iterator it;
    for (it = key->begin(); it != key->end(); ++it)
    {
        for (int j = 0; j < count; j++)
        {
            if (original[j] == it->second) decrypt[j] = it->first;
        }
    }
    wstring s(decrypt);
    delete[] decrypt;
    delete[] original;
    return s;
}

bool notDouble(map<wchar_t, wchar_t>*& key, wchar_t ch) {
    map<wchar_t, wchar_t>::iterator it;
    for (it = key->begin(); it != key->end(); ++it)
    {
        if (it->second == ch)
        {
            return true;
        }
    }
    return false;
}

void generatedEncryptionKey(wstring text, map<wchar_t, wchar_t>*& key) {
    bool isDuplicate;
    int randomNumber;
    std::sort(text.begin(), text.end());
    auto newEnd = std::unique(text.begin(), text.end());
    text.erase(newEnd, text.end());
    int len = text.length();
    const wchar_t* dt = text.c_str();
    wchar_t* data = new wchar_t[len + 1];
    wcsncpy_s(data, len + 1, dt, len);
    srand(time(NULL));
    for (int i = 0; i < len; i++)
    {
        do {
            isDuplicate = false;
            randomNumber = rand() % len;

        } while (notDouble(key, data[randomNumber]));
        key->insert(pair<wchar_t, wchar_t>(data[i], data[randomNumber]));
    }
    delete[] data;
}

int main()
{
    wcout.imbue(locale("rus_rus.866"));
    wcin.imbue(locale("rus_rus.866"));
    map <wchar_t, wchar_t>* key = new  map <wchar_t, wchar_t>;
    std::wstring text;
    std::wcout << L"введите текст для шифрования:" << endl;
    getline(wcin, text);
    generatedEncryptionKey(text, key);
    wstring encrypt = replacementEncryption(text, key);
    wstring decrypt = replacementDecryption(encrypt, key);
    wcout << L"Исходный текст:"+ text << endl <<L"Зашифрованный текст:"+ encrypt << endl << L"Дешифрованный текст:" + decrypt << endl;
    return 0;
}

