#include "quote.h"
#include <ctime>
#include <fstream>
#include <iostream>

bool Quote::Init(const char* filename)
{
    srand(time(NULL));

    std::ifstream ifs(filename);
    if (!ifs.is_open())
    {
        std::cerr << "[ERROR] Quote::Init failed: open file\n";
        return false;
    }

    std::string quote;
    while (getline(ifs, quote))
    {
        if (quote.size() > 0)
        {
            m_quote_list.push_back(quote);
        }
    }

    return true;
}

std::string Quote::GetRandomQuote()
{
    if (m_quote_list.size() == 0)
    {
        return "";
    }

    return m_quote_list[rand() % m_quote_list.size()];
}
