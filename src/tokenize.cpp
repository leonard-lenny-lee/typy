#include "tokenize.hpp"

#include "constants.hpp"
#include "token.hpp"

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

Tokenizer::Tokenizer(std::string source)
    : m_source(source), m_tokens(std::vector<Token>()), m_line(0), m_col(0),
      m_linestart(0), m_level(0), m_cur(0) {}

void Tokenizer::tokenize() {
    while (this->m_cur < this->m_source.length()) {
        char c = this->peek();
        if (std::isspace(c)) {
            if (c == '\n') {
                this->tokenize_newline();
            } else {
                this->m_col++;
            }
        } else if (Tokenizer::isalnum(c)) {
            if (std::isdigit(c)) {
                this->tokenize_num();
            } else {
                this->tokenize_ident();
            }
        } else if (c == '"' || c == '\'') {
            this->tokenize_str();
        } else if (c == '#') {
            this->tokenize_comment();
        } else if (std::ispunct(c)) { // Must be symbol
            this->tokenize_symbol();
        } else {
        };
        this->m_cur++;
    }
};

void Tokenizer::emit_token_stream(const std::string &outfile) {
    std::ofstream out(outfile);
    for (Token token : this->m_tokens) {
        out << token.stringify() << ' ';
        if (token.m_token_t == Token::NEWLINE) {
            out << '\n';
        }
    }
}

void Tokenizer::tokenize_newline() {
    this->m_tokens.push_back(Token(Token::NEWLINE, std::nullopt, this->m_line,
                                   this->m_col, this->m_col + 1));
    this->m_line++;
    this->m_col = 0;
    this->m_linestart = this->m_cur;
    this->tokenize_indent();
}

void Tokenizer::tokenize_indent() {
    assert(this->m_col == 0);
    this->m_cur++;
    while (std::isblank(this->peek())) {
        this->m_cur++;
        this->m_col++;
    }
    int indent_level = (this->m_col + 1) / constants::TAB_SIZE;
    Token::Type indent_token_t =
        indent_level > this->m_level ? Token::INDENT : Token::DEDENT;
    int increment = indent_token_t == Token::INDENT ? 1 : -1;
    int n_tokens = std::abs(this->m_level - indent_level);
    for (int i = 0; i < n_tokens; i++) {
        this->m_tokens.push_back(Token(indent_token_t, std::nullopt,
                                       this->m_line, this->m_col,
                                       this->m_col + constants::TAB_SIZE));
        this->m_level += increment;
    }
    this->m_cur--;
}

void Tokenizer::tokenize_num() {
    std::string tok_buf;
    bool valid = true;
    int n_periods = 0;
    while (Tokenizer::isalnum(this->peek()) || this->peek() == '.') {
        char c = this->advance();
        tok_buf.push_back(c);
        if (!Tokenizer::isnum(c))
            valid = false;
        else if (c == '.')
            n_periods++;
    }
    if (n_periods > 1)
        valid = false;
    Token::Type token_t;
    if (!valid)
        token_t = Token::UNKNOWN;
    else if (n_periods > 0)
        token_t = Token::FLOAT;
    else
        token_t = Token::INT;
    this->m_tokens.push_back(Token(token_t, std::move(tok_buf), this->m_line,
                                   this->m_col,
                                   this->m_col + tok_buf.length()));
    this->m_col += tok_buf.length();
    this->m_cur--;
};

void Tokenizer::tokenize_ident() {
    std::string tok_buf;
    while (Tokenizer::isalnum(this->peek()))
        tok_buf.push_back(this->advance());
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
    this->m_tokens.push_back(Token(token_t, lexeme, this->m_line, this->m_col,
                                   this->m_col + tok_length));
    this->m_col += tok_length;
    this->m_cur--;
}

void Tokenizer::tokenize_str() {
    char opening_char = this->advance();
    std::string tok_buf;
    tok_buf.push_back(opening_char);
    while (this->peek() != opening_char) {
        tok_buf.push_back(this->advance());
    }
    tok_buf.push_back(opening_char);
    this->m_tokens.push_back(Token(Token::STRING, std::move(tok_buf),
                                   this->m_line, this->m_col,
                                   this->m_col + tok_buf.length()));
    this->m_cur++;
    this->m_col += tok_buf.length();
}

void Tokenizer::tokenize_symbol() {
    std::string tok_buf;
    while (std::ispunct(this->peek())) {
        tok_buf.push_back(this->advance());
    }
    std::optional<Token::Type> symbol = Token::match_symbol(tok_buf);
    while (!symbol.has_value()) {
        if (tok_buf.length() == 1) {
            this->m_tokens.push_back(Token(Token::UNKNOWN, tok_buf,
                                           this->m_line, this->m_col,
                                           this->m_col + tok_buf.length()));
            this->m_col++;
            return;
        }
        tok_buf.pop_back();
        this->m_cur--;
        symbol = Token::match_symbol(tok_buf);
    }
    this->m_tokens.push_back(Token(symbol.value(), std::nullopt, this->m_line,
                                   this->m_col,
                                   this->m_col + tok_buf.length()));
    this->m_col += tok_buf.length();
    this->m_cur--;
}

void Tokenizer::tokenize_comment() {
    assert(this->peek() == '#');
    this->advance();
    int comment_length = 1;
    while (this->peek() != '\n') {
        comment_length++;
        this->m_cur++;
    }
    this->m_col += comment_length;
    this->m_cur--;
}
