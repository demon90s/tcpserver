#include <vector>
#include <string>

class Quote
{
public:
    bool Init(const char* filename);

    std::string GetRandomQuote();

private:
    std::vector<std::string> m_quote_list;
};
