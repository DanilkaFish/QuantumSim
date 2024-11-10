
#include <string>
#include <map>
#include <stdexcept>

constexpr char AND='^';
constexpr char OR='v';
const std::string X = "x";
constexpr char NUMBER = '3';
constexpr char NAME = 'n';
constexpr char END = 'e';
constexpr char NOT = '!';

void error(std::string s){
    throw std::runtime_error("ParserError : " + s);
}

struct Token{
    Token(){}
    Token(char k): kind{k}, value{0}{}
    Token(char k, int val): kind{k}, value{val}{}
    Token(char k, std::string& name): kind{k}, name{name}{}
    char kind;
    int value;
    std::string name;
};



class TokenStream{
public:
    TokenStream(std::string& s): s{s}, pos{s.begin()}{}
    Token get();
    char next(){
        if (pos == s.end()){
            return END;
        }
        char temp = *pos;
        pos++;
        return temp;
    }
    void putback(Token t);
private:
    bool is_full = false;
    Token buffer;
    std::string s;
    std::string::iterator pos;
};


void TokenStream::putback(Token t){
    if (is_full) 
        error("Already full buffer");
    is_full = true;
    buffer = t;
}

Token TokenStream::get(){
    if (is_full){
        is_full = false;
        return buffer;
    }
    char temp = next();
    if (isalpha(temp)){
        std::string s;
        s += temp;
        while (next() && (isalpha(temp) || isdigit(temp)))
                s += temp;
            return Token{NAME, s};
    }
    switch (temp)
    {
    case END: 
    case AND: 
    case  OR: 
    case NOT: 
    case '(': 
    case ')': 
        return Token{temp};
    case '0': case '1': case '2':case '3':case '4':
    case '5': case '6':case '7':case '8':case '9':
        int val = int(temp) - int('0');
        temp = next();
        while(isdigit(temp)){
            val = val*10 + int(temp) - int('0');
            temp = next();
        }
        return Token{NUMBER, val};
    default:
        error("Bad Token {" + std::string(1, temp) + "}");
    }
    return Token{};
}

double Expression();
double Term_and();
double Term_not();
double Primary();



struct BoolNum{
    BoolNum(int n): num{n} {
        for(;n > 0; n/10){
            s.push_back(char(n%10) + '0');
        }
    }
    int num;
    std::string s;
};

template<class T>
class Parser{
public:
    Parser(std::strgin s): ts{s}{};
    virtual T andop(T& lv, T& rv);
    virtual T orop(T& lv, T& rv);
    virtual T fromnum(int n);
    virtual ~ParserInterface() = 0;
    T evaluate(std::string& s){return Expression(s.begin())};
    T Expression(){
        T left = Term();
        Token t = ts.get();
        while (true){
            switch (t.kind)
            {
            case OR:
                left = orop(left, Term_and());
                break;
            default:
                ts.putback();
                return left;
            }
        }
    }
    T Term_and(){
        T left = Term_not();
        Token t = ts.get();
        while (true){
            switch (t.kind)
            {
            case AND:
                left = andop(left, Term_not());
                break;
            default:
                ts.putback();
                return left;
            }
        }
    }
    T Term_not(){
        T left = Primary();
        Token t = ts.get();
        while (true){
            switch (t.kind)
            {
            case NOT:
                left = notop(left, Primary());
                break;
            default:
                ts.putback();
                return left;
            }
        }
    }
    T Primary(std::string::iterator pos){
        Token t = ts.get();
        while (true){
            switch (t.kind)
            {
            case '(':
                Expression();
                break;
            case 
            default:
                error("Primary");
            }
        }
    }
private:
    T obj;
    TokenStream ts;
};

