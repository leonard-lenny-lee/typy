#include "token.hpp"

#include <optional>
#include <string>

const std::unordered_map<std::string, typy::Token::Type> SYMBOL_MAPPINGS = {
    {"(", typy::Token::LPAREN},
    {")", typy::Token::RPAREN},
    {",", typy::Token::COMMA},
    {".", typy::Token::DOT},
    {";", typy::Token::SEMICOLON},
    {":", typy::Token::COLON},
    {"+", typy::Token::PLUS},
    {"-", typy::Token::MINUS},
    {"/", typy::Token::SLASH},
    {"*", typy::Token::STAR},
    {"**", typy::Token::STAR_STAR},
    {"<", typy::Token::LESS},
    {"<<", typy::Token::LESS_LESS},
    {">", typy::Token::GREATER},
    {">>", typy::Token::GREATER_GREATER},
    {"^", typy::Token::CARET},
    {"|", typy::Token::VBAR},
    {"||", typy::Token::VBAR_VBAR},
    {"&", typy::Token::AMPER},
    {"&&", typy::Token::AMPER_AMPER},
    {"=", typy::Token::EQ},
    {"+=", typy::Token::PLUS_EQ},
    {"-=", typy::Token::MINUS_EQ},
    {"/=", typy::Token::SLASH_EQ},
    {"*=", typy::Token::STAR_EQ},
    {"**=", typy::Token::STAR_STAR_EQ},
    {"<=", typy::Token::LESS_EQ},
    {"<<=", typy::Token::LESS_LESS_EQ},
    {">=", typy::Token::GREATER_EQ},
    {">>=", typy::Token::GREATER_GREATER_EQ},
    {"^=", typy::Token::CARET_EQ},
    {"|=", typy::Token::VBAR_EQ},
    {"&=", typy::Token::AMPER_EQ},
    {"->", typy::Token::RARROW},
    {"...", typy::Token::ELLIPSIS},
};

const std::unordered_map<std::string, typy::Token::Type> KEYWORD_MAPPINGS = {
    {"pass", typy::Token::PASS},
    {"break", typy::Token::BREAK},
    {"continue", typy::Token::CONTINUE},
    {"return", typy::Token::RETURN},
    {"del", typy::Token::DEL},
    {"type", typy::Token::TYPE},
    {"assert", typy::Token::ASSERT},
    {"def", typy::Token::DEF},
    {"struct", typy::Token::STRUCT},
    {"enum", typy::Token::ENUM},
    {"if", typy::Token::IF},
    {"elif", typy::Token::ELIF},
    {"else", typy::Token::ELSE},
    {"while", typy::Token::WHILE},
    {"for", typy::Token::FOR},
    {"True", typy::Token::TRUE},
    {"False", typy::Token::FALSE},
};

typy::Token::Token(Type token_t, std::optional<std::string> text, int line,
                   int startcol, int endcol)
    : m_token_t(token_t), m_text(text), m_line(line), m_startcol(startcol),
      m_endcol(endcol) {}

std::string typy::Token::stringify() {
    std::string str = Token::stringify_token_t(m_token_t);
    if (m_text) {
        str.append(" " + m_text.value());
    }
    return "(" + str + " LINE " + std::to_string(m_line + 1) + " COL " +
           std::to_string(m_startcol + 1) + " TO " +
           std::to_string(m_endcol + 1) + ")";
}

std::string typy::Token::stringify_token_t(Type token_t) {
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

std::optional<typy::Token::Type>
typy::Token::match_symbol(const std::string &str) {
    if (SYMBOL_MAPPINGS.count(str)) {
        return SYMBOL_MAPPINGS.at(str);
    }
    return std::nullopt;
};

std::optional<typy::Token::Type>
typy::Token::match_keyword(const std::string &str) {
    if (KEYWORD_MAPPINGS.count(str)) {
        return KEYWORD_MAPPINGS.at(str);
    }
    return std::nullopt;
}