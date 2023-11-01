#pragma once

#include <optional>
#include <string>

namespace typy {
struct Token {
    public:
        enum Type {
            // Character tokens
            LPAREN,
            RPAREN,
            COMMA,
            DOT,
            SEMICOLON,
            COLON,
            PLUS,
            MINUS,
            SLASH,
            STAR,
            STAR_STAR,
            LESS,
            LESS_LESS,
            GREATER,
            GREATER_GREATER,
            CARET,
            VBAR,
            VBAR_VBAR,
            AMPER,
            AMPER_AMPER,
            EQ,
            PLUS_EQ,
            MINUS_EQ,
            SLASH_EQ,
            STAR_EQ,
            STAR_STAR_EQ,
            LESS_EQ,
            LESS_LESS_EQ,
            GREATER_EQ,
            GREATER_GREATER_EQ,
            CARET_EQ,
            VBAR_EQ,
            AMPER_EQ,
            RARROW,
            ELLIPSIS,
            // Literals
            IDENT,
            INT,
            FLOAT,
            STRING,
            // Keywords
            PASS,
            BREAK,
            CONTINUE,
            RETURN,
            DEL,
            TYPE,
            ASSERT,
            DEF,
            STRUCT,
            ENUM,
            IF,
            ELIF,
            ELSE,
            WHILE,
            FOR,
            TRUE,
            FALSE,
            // Other
            NEWLINE,
            INDENT,
            DEDENT,
            UNKNOWN,
            ENDMARKER,
        };

        Token(Type token_t, std::optional<std::string> text, int line,
              int startcol, int endcol);

        std::string stringify();
        static std::string stringify_token_t(Type token_t);
        static std::optional<Type> match_symbol(const std::string &str);
        static std::optional<Type> match_keyword(const std::string &str);

    public:
        Type m_token_t;
        std::optional<std::string> m_text;
        int m_line;
        int m_startcol;
        int m_endcol;
};
} // namespace typy
