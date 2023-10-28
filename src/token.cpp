#include "token.hpp"

#include <optional>
#include <string>

const std::unordered_map<std::string, Token::Type> SYMBOL_MAPPINGS = {
    {"(", Token::LPAREN},
    {")", Token::RPAREN},
    {",", Token::COMMA},
    {".", Token::DOT},
    {";", Token::SEMICOLON},
    {":", Token::COLON},
    {"+", Token::PLUS},
    {"-", Token::MINUS},
    {"/", Token::SLASH},
    {"*", Token::STAR},
    {"**", Token::STAR_STAR},
    {"<", Token::LESS},
    {"<<", Token::LESS_LESS},
    {">", Token::GREATER},
    {">>", Token::GREATER_GREATER},
    {"^", Token::CARET},
    {"|", Token::VBAR},
    {"||", Token::VBAR_VBAR},
    {"&", Token::AMPER},
    {"&&", Token::AMPER_AMPER},
    {"=", Token::EQ},
    {"+=", Token::PLUS_EQ},
    {"-=", Token::MINUS_EQ},
    {"/=", Token::SLASH_EQ},
    {"*=", Token::STAR_EQ},
    {"**=", Token::STAR_STAR_EQ},
    {"<=", Token::LESS_EQ},
    {"<<=", Token::LESS_LESS_EQ},
    {">=", Token::GREATER_EQ},
    {">>=", Token::GREATER_GREATER_EQ},
    {"^=", Token::CARET_EQ},
    {"|=", Token::VBAR_EQ},
    {"&=", Token::AMPER_EQ},
    {"->", Token::RARROW},
    {"...", Token::ELLIPSIS},
};

const std::unordered_map<std::string, Token::Type> KEYWORD_MAPPINGS = {
    {"pass", Token::PASS},
    {"break", Token::BREAK},
    {"continue", Token::CONTINUE},
    {"return", Token::RETURN},
    {"del", Token::DEL},
    {"type", Token::TYPE},
    {"assert", Token::ASSERT},
    {"def", Token::DEF},
    {"struct", Token::STRUCT},
    {"enum", Token::ENUM},
    {"if", Token::IF},
    {"elif", Token::ELIF},
    {"else", Token::ELSE},
    {"while", Token::WHILE},
    {"for", Token::FOR},
    {"True", Token::TRUE},
    {"False", Token::FALSE},
};

Token::Token(Type token_t, std::optional<std::string> lexeme, int line,
             int startcol, int endcol)
    : m_token_t(token_t), m_lexeme(lexeme), m_line(line), m_startcol(startcol),
      m_endcol(endcol) {}

std::string Token::stringify() {
    std::string str = Token::stringify_token_t(this->m_token_t);
    if (this->m_lexeme) {
        str.append(" " + m_lexeme.value());
    }
    return "(" + str + " LINE " + std::to_string(this->m_line + 1) + " COL " +
           std::to_string(this->m_startcol + 1) + " TO " +
           std::to_string(this->m_endcol + 1) + ")";
}

std::string Token::stringify_token_t(Type token_t) {
    switch (token_t) {
    case LPAREN:
        return "LPAREN";
    case RPAREN:
        return "RPAREN";
    case COMMA:
        return "COMMA";
    case DOT:
        return "DOT";
    case SEMICOLON:
        return "SEMICOLON";
    case COLON:
        return "COLON";
    case PLUS:
        return "PLUS";
    case MINUS:
        return "MINUS";
    case SLASH:
        return "SLASH";
    case STAR:
        return "STAR";
    case STAR_STAR:
        return "STAR_STAR";
    case LESS:
        return "LESS";
    case LESS_LESS:
        return "LESS_LESS";
    case GREATER:
        return "GREATER";
    case GREATER_GREATER:
        return "GREATER_GREATER";
    case CARET:
        return "CARET";
    case VBAR:
        return "VBAR";
    case VBAR_VBAR:
        return "VBAR_VBAR";
    case AMPER:
        return "AMPER";
    case AMPER_AMPER:
        return "AMPER_AMPER";
    case EQ:
        return "EQ";
    case PLUS_EQ:
        return "PLUS_EQ";
    case MINUS_EQ:
        return "MINUS_EQ";
    case SLASH_EQ:
        return "SLASH_EQ";
    case STAR_EQ:
        return "STAR_EQ";
    case STAR_STAR_EQ:
        return "STAR_STAR_EQ";
    case LESS_EQ:
        return "LESS_EQ";
    case LESS_LESS_EQ:
        return "LESS_LESS_EQ";
    case GREATER_EQ:
        return "GREATER_EQ";
    case GREATER_GREATER_EQ:
        return "GREATER_GREATER_EQ";
    case CARET_EQ:
        return "CARET_EQ";
    case VBAR_EQ:
        return "VBAR_EQ";
    case AMPER_EQ:
        return "AMPER_EQ";
    case RARROW:
        return "RARROW";
    case ELLIPSIS:
        return "ELLIPSIS";
    case IDENT:
        return "IDENT";
    case INT:
        return "INT";
    case FLOAT:
        return "FLOAT";
    case STRING:
        return "STRING";
    case PASS:
        return "PASS";
    case BREAK:
        return "BREAK";
    case CONTINUE:
        return "CONTINUE";
    case RETURN:
        return "RETURN";
    case DEL:
        return "DEL";
    case TYPE:
        return "TYPE";
    case ASSERT:
        return "ASSERT";
    case DEF:
        return "DEF";
    case STRUCT:
        return "STRUCT";
    case ENUM:
        return "ENUM";
    case IF:
        return "IF";
    case ELIF:
        return "ELIF";
    case ELSE:
        return "ELSE";
    case WHILE:
        return "WHILE";
    case FOR:
        return "FOR";
    case TRUE:
        return "TRUE";
    case FALSE:
        return "FALSE";
    case NEWLINE:
        return "NEWLINE";
    case INDENT:
        return "INDENT";
    case DEDENT:
        return "DEDENT";
    case UNKNOWN:
        return "UNKNOWN";
    case ENDMARKER:
        return "ENDMARKER";
    }
}

std::optional<Token::Type> Token::match_symbol(const std::string &str) {
    if (SYMBOL_MAPPINGS.count(str)) {
        return SYMBOL_MAPPINGS.at(str);
    }
    return {};
};

std::optional<Token::Type> Token::match_keyword(const std::string &str) {
    if (KEYWORD_MAPPINGS.count(str)) {
        return KEYWORD_MAPPINGS.at(str);
    }
    return {};
}