#include "tokenizer.hpp"

#include "constants.hpp"
#include "token.hpp"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

typy::Tokenizer::Tokenizer(std::string source)
    : m_source(source), m_tokens(std::vector<Token>()), m_line(0), m_col(0),
      m_linestart(0), m_level(0), m_cur(0) {}

void typy::Tokenizer::tokenize() {
    while (m_cur < m_source.length()) {
        char c = peek();
        if (std::isspace(c)) {
            if (c == '\n') {
                tokenize_newline();
            } else {
                m_col++;
            }
        } else if (Tokenizer::isalnum(c)) {
            if (std::isdigit(c)) {
                tokenize_num();
            } else {
                tokenize_ident();
            }
        } else if (c == '"' || c == '\'') {
            tokenize_str();
        } else if (c == '#') {
            tokenize_comment();
        } else if (std::ispunct(c)) {
            tokenize_symbol();
        } else {
        };
        m_cur++;
    }
};

void typy::Tokenizer::emit_token_stream(const std::string &outfile) {
    std::ofstream out(outfile);
    for (Token token : m_tokens) {
        out << token.stringify() << ' ';
        if (token.m_token_t == Token::NEWLINE) {
            out << '\n';
        }
    }
}

void typy::Tokenizer::tokenize_newline() {
    m_tokens.push_back(
        Token(Token::NEWLINE, std::nullopt, m_line, m_col, m_col + 1));
    m_line++;
    m_col = 0;
    m_linestart = m_cur;
    tokenize_indent();
}

void typy::Tokenizer::tokenize_indent() {
    assert(m_col == 0);
    m_cur++;
    while (std::isblank(peek())) {
        m_cur++;
        m_col++;
    }
    int indent_level = (m_col + 1) / constants::TAB_SIZE;
    Token::Type indent_token_t =
        indent_level > m_level ? Token::INDENT : Token::DEDENT;
    int increment = indent_token_t == Token::INDENT ? 1 : -1;
    int n_tokens = std::abs(m_level - indent_level);
    for (int i = 0; i < n_tokens; i++) {
        m_tokens.push_back(Token(indent_token_t, std::nullopt, m_line, m_col,
                                 m_col + constants::TAB_SIZE));
        m_level += increment;
    }
    m_cur--;
}

void typy::Tokenizer::tokenize_num() {
    std::string tok_buf;
    bool valid = true;
    int n_periods = 0;
    while (Tokenizer::isalnum(peek()) || peek() == '.') {
        char c = advance();
        tok_buf.push_back(c);
        if (!Tokenizer::isnum(c)) {
            valid = false;
        } else if (c == '.') {
            n_periods++;
        }
    }
    if (n_periods > 1)
        valid = false;
    Token::Type token_t = !valid          ? Token::UNKNOWN
                          : n_periods > 0 ? Token::FLOAT
                                          : Token::INT;
    m_tokens.push_back(
        Token(token_t, tok_buf, m_line, m_col, m_col + tok_buf.length()));
    m_col += tok_buf.length();
    m_cur--;
};

void typy::Tokenizer::tokenize_ident() {
    std::string tok_buf;
    while (Tokenizer::isalnum(peek())) {
        tok_buf.push_back(advance());
    }
    Token::Type token_t;
    std::optional<Token::Type> kw_token_t = Token::match_keyword(tok_buf);
    std::optional<std::string> lexeme;
    int tok_length = tok_buf.length();
    if (kw_token_t.has_value()) {
        token_t = kw_token_t.value();
        lexeme = std::nullopt;
    } else {
        token_t = Token::IDENT;
        lexeme = tok_buf;
    }
    m_tokens.push_back(
        Token(token_t, lexeme, m_line, m_col, m_col + tok_length));
    m_col += tok_length;
    m_cur--;
}

void typy::Tokenizer::tokenize_str() {
    char opening_char = advance();
    std::string tok_buf;
    tok_buf.push_back(opening_char);
    while (peek() != opening_char) {
        tok_buf.push_back(advance());
    }
    tok_buf.push_back(opening_char);
    int end_col = m_col + tok_buf.length();
    m_tokens.push_back(
        Token(Token::STRING, std::move(tok_buf), m_line, m_col, end_col));
    m_cur++;
    m_col += tok_buf.length();
}

void typy::Tokenizer::tokenize_symbol() {
    std::string tok_buf;
    while (std::ispunct(peek())) {
        tok_buf.push_back(advance());
    }
    std::optional<Token::Type> symbol = Token::match_symbol(tok_buf);
    while (!symbol.has_value()) {
        if (tok_buf.length() == 1) {
            m_tokens.push_back(Token(Token::UNKNOWN, tok_buf, m_line, m_col,
                                     m_col + tok_buf.length()));
            m_col++;
            return;
        }
        tok_buf.pop_back();
        m_cur--;
        symbol = Token::match_symbol(tok_buf);
    }
    m_tokens.push_back(Token(symbol.value(), std::nullopt, m_line, m_col,
                             m_col + tok_buf.length()));
    m_col += tok_buf.length();
    m_cur--;
}

void typy::Tokenizer::tokenize_comment() {
    assert(peek() == '#');
    advance();
    int comment_length = 1;
    while (peek() != '\n') {
        comment_length++;
        m_cur++;
    }
    m_col += comment_length;
    m_cur--;
}
