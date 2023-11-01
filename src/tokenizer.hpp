#pragma once

#include "token.hpp"

#include <cctype>
#include <optional>
#include <string>
#include <vector>

namespace typy {
class Tokenizer {
    public:
        Tokenizer(std::string source);
        void tokenize();
        void emit_token_stream(const std::string &outfile);

    public:
        std::string m_source;
        std::vector<Token> m_tokens;

    private:
        char peek() { return this->m_source[this->m_cur]; }
        char advance() { return this->m_source[this->m_cur++]; };

        void tokenize_newline();
        void tokenize_indent();
        void tokenize_num();
        void tokenize_ident();
        void tokenize_str();
        void tokenize_symbol();
        void tokenize_comment();

        static bool isalnum(char c) { return std::isalnum(c) || c == '_'; }
        static bool isnum(char c) { return std::isdigit(c) || c == '.'; }

    private:
        int m_line;
        int m_col;
        int m_linestart;
        int m_level;
        int m_cur;
};
} // namespace typy