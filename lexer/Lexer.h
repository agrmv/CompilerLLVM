//
// Created by agrmv on 14.09.2019.
//
#pragma once

#include <string>
#include <unordered_map>
#include <cstring>
#include <FlexLexer.h>

enum Token {
    WhiteSpace = 258,
    NewLine,
    Identifier,
    NumericConstant,
    Plus,
    Minus,
    Div,
    Mul,
    LeftBrace,
    RightBrace,
    LeftParen,
    RightParen,
    Int,
    String,
    StringConstant,
    Var,
    Val,
    EqualEqual,
    Equal,
    Greater,
    Less,
    Return,
    Function,
    If,
    While,
    SemiColon,
    Comma,
    Colon,
    Eof
};

class Lexer {
    std::pair<uint16_t, uint16_t> tokenPosition;
    std::unique_ptr<yyFlexLexer> flex;
    const std::string filename;
    const std::unordered_map<uint16_t , std::string> keywords = {
            {WhiteSpace,        "whitespace"},
            {NewLine,           "newline"},
            {Identifier,        "identifier"},
            {NumericConstant,   "numeric_constant"},
            {LeftParen,         "left_paren"},
            {RightParen,        "right_paren"},
            {LeftBrace,         "left_brace"},
            {RightBrace,        "right_brace"},
            {Plus,              "plus"},
            {Minus,             "minus"},
            {Div,               "div"},
            {Mul,               "mul"},
            {Int,               "int"},
            {String,            "string"},
            {StringConstant,    "string_constant"},
            {Val,               "val"},
            {Var,               "var"},
            {EqualEqual,        "equal_equal"},
            {Equal,             "equal"},
            {Greater,           "greater"},
            {Less,              "less"},
            {Return,            "return"},
            {Function,          "function"},
            {While,             "while"},
            {SemiColon,         "semi"},
            {Comma,             "comma"},
            {Colon,             "colon"},
            {Eof,               "eof"}
    };
public:
    Lexer(std::istream &file, std::string filename) : filename(std::move(filename)), tokenPosition(1,1) {
        flex = std::make_unique<yyFlexLexer>(&file);
    }

    void tokenize() {
        while (uint16_t token = flex->yylex()) {
            if (token == Eof) {
                printToken(keywords.at(token), getTokenPosition(token));
                break;
            }
            tokenSearch(token);
        }
    }

    std::pair<uint16_t, uint16_t> getTokenPosition(const uint16_t& token) {
        static uint16_t tokenLength = 0;

        if (token == NewLine) {
            tokenLength = 0;
            tokenPosition.first += 1;
            return tokenPosition;
        }

        if (token == WhiteSpace) {
            tokenLength += 1;
            return tokenPosition;
        }

        if (tokenLength == 0) {
            tokenLength += strlen(flex->YYText());
            return std::make_pair(tokenPosition.first,1);
        }

        tokenPosition.second = tokenLength;
        tokenLength += strlen(flex->YYText());;
        return tokenPosition;
    }

    void tokenSearch(const uint16_t& token) {
        if (keywords.find(token) != keywords.end()) {
            printToken(keywords.at(token), getTokenPosition(token));
        }
    }

    void printToken(const std::string &token, const std::pair<uint16_t, uint16_t>& position) const {
        if (token != "whitespace" && token != "newline") {
            std::cout << "Scanner: " << token << " '" << flex->YYText() << "'";
            std::cout << "\t\tLocation: " << filename << "[" << position.first << ":" << position.second << "]" << std::endl;
        }
    }
};