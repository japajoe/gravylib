#ifndef GRAVY_TOKENIZER_HPP
#define GRAVY_TOKENIZER_HPP

#include <iostream>
#include <string>
#include <vector>

namespace Gravy::System::Text
{
    enum class TokenType : int
    {
        WhiteSpace = 0, // Basically an unused type
        Identifier,
        IntegerLiteral,
        FloatingPointLiteral,
        StringLiteral,
        Operator,
        StringEscapeSequence,
        Comment,
        PotentialFloatingPoint,
        PotentialComment
    };

    template<typename T>
    struct Token
    {
        T type;
        std::string text;
        uint64_t lineNumber;
    };

    using TokenList = std::vector<Token<TokenType>>;

    class Tokenizer
    {
    public:
        Tokenizer() { }

        std::vector<Token<TokenType>> Parse(const std::string& source)
        {
            std::vector<Token<TokenType>> tokens;
            Token<TokenType> currentToken;

            currentToken.type = TokenType::WhiteSpace;
            currentToken.lineNumber = 1;

            for(char currentChar : source)
            {
                if(currentToken.type == TokenType::StringEscapeSequence)
                {
                    switch(currentChar)
                    {
                        case 'n':
                            AppendCharacter(currentToken, '\n');
                            break;
                        case 'r':
                            AppendCharacter(currentToken, '\r');
                            break;
                        case 't':
                            AppendCharacter(currentToken, '\t');
                            break;
                        case '\\':
                            AppendCharacter(currentToken, '\\');
                            break;
                        default:
                            std::cout << "Unknown escape sequence: \\" << currentChar << " on line " << currentToken.lineNumber << '\n';
                    }
                    currentToken.type = TokenType::StringLiteral;
                    continue;
                }

                else if(currentToken.type == TokenType::PotentialComment && currentChar != ';')
                {
                    currentToken.type = TokenType::Operator;
                    EndToken(currentToken, tokens);
                    continue;
                }

                switch(currentChar)
                {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        if(currentToken.type == TokenType::WhiteSpace)
                        {
                            currentToken.type = TokenType::IntegerLiteral;
                            AppendCharacter(currentToken, currentChar);
                        }
                        else if(currentToken.type == TokenType::PotentialFloatingPoint)
                        {
                            currentToken.type = TokenType::FloatingPointLiteral;
                            AppendCharacter(currentToken, currentChar);
                        }
                        else
                        {
                            AppendCharacter(currentToken, currentChar);
                        }
                        break;
                    
                    case '.':
                        if(currentToken.type == TokenType::WhiteSpace)
                        {
                            currentToken.type = TokenType::PotentialFloatingPoint;
                            AppendCharacter(currentToken, currentChar);
                        }
                        else if(currentToken.type == TokenType::IntegerLiteral)
                        {
                            currentToken.type = TokenType::FloatingPointLiteral;
                            AppendCharacter(currentToken, currentChar);
                        }
                        else if(currentToken.type == TokenType::StringLiteral)
                        {
                            AppendCharacter(currentToken, currentChar);
                        }
                        else
                        {
                            EndToken(currentToken, tokens);
                            currentToken.type = TokenType::Operator;
                            AppendCharacter(currentToken, currentChar);
                            EndToken(currentToken, tokens);
                        }
                        break;

                    case '{':
                    case '}':
                    case '(':
                    case ')':
                    case '[':
                    case ']':
                    case '=':
                    case '-':
                    case '+':
                    case '*':
                    case '%':
                    case '&':
                    case '!':
                    case ',':
                    case ':':
                        if(currentToken.type != TokenType::StringLiteral)
                        {
                            EndToken(currentToken, tokens);
                            currentToken.type = TokenType::Operator;
                            currentToken.text += currentChar;
                            EndToken(currentToken, tokens);
                        }
                        else
                        {
                            AppendCharacter(currentToken, currentChar);
                        }
                        break;

                    case ' ':
                    case '\t':
                        if(currentToken.type == TokenType::StringLiteral || currentToken.type == TokenType::Comment)
                        {
                            AppendCharacter(currentToken, currentChar);
                        }
                        else
                        {
                            EndToken(currentToken, tokens);
                        }
                        break;

                    case '\r':
                    case '\n':
                        EndToken(currentToken, tokens);
                        ++currentToken.lineNumber;
                        break;

                    case '"':
                        if(currentToken.type != TokenType::StringLiteral)
                        {
                            EndToken(currentToken, tokens);
                            currentToken.type = TokenType::StringLiteral;
                        }
                        else if(currentToken.type == TokenType::StringLiteral)
                        {
                            EndToken(currentToken, tokens);
                        }
                        break;

                    case '\\':
                        if(currentToken.type == TokenType::StringLiteral)
                        {
                            currentToken.type = TokenType::StringEscapeSequence;
                        }
                        else
                        {
                            EndToken(currentToken, tokens);
                            currentToken.type = TokenType::Operator;
                            AppendCharacter(currentToken, currentChar);
                            EndToken(currentToken, tokens);
                        }
                        break;

                    case ';':
                        if(currentToken.type == TokenType::StringLiteral)
                        {
                            AppendCharacter(currentToken, currentChar);
                        }
                        else if(currentToken.type == TokenType::PotentialComment)
                        {
                            currentToken.type = TokenType::Comment;
                            currentToken.text = "";
                        }
                        else
                        {
                            EndToken(currentToken, tokens);
                            currentToken.type = TokenType::PotentialComment;
                            AppendCharacter(currentToken, currentChar);
                        }
                        break;

                    default:
                        if(currentToken.type == TokenType::WhiteSpace || currentToken.type == TokenType::IntegerLiteral || currentToken.type == TokenType::FloatingPointLiteral)
                        {
                            if(currentToken.type == TokenType::IntegerLiteral)
                            {
                                switch(currentChar)
                                {
                                    case 'x':
                                    case 'a':
                                    case 'A':
                                    case 'b':
                                    case 'B':
                                    case 'c':
                                    case 'C':
                                    case 'd':
                                    case 'D':
                                    case 'e':
                                    case 'E':
                                    case 'f':
                                    case 'F':
                                        currentToken.type = TokenType::IntegerLiteral;
                                        AppendCharacter(currentToken, currentChar);
                                        break;
                                    default:
                                        EndToken(currentToken, tokens);
                                        currentToken.type = TokenType::Identifier;
                                        AppendCharacter(currentToken, currentChar);
                                        break;
                                }

                            }
                            else
                            {
                                EndToken(currentToken, tokens);
                                currentToken.type = TokenType::Identifier;
                                AppendCharacter(currentToken, currentChar);
                            }
                        }
                        else
                        {
                            AppendCharacter(currentToken, currentChar);
                        }
                        break;
                }
            }
            
            EndToken(currentToken, tokens);

            return tokens;
        }

    private:
        void EndToken(Token<TokenType>& token, std::vector<Token<TokenType>>& tokens)
        {
            if(token.type == TokenType::Comment)
            {
                //Console.WriteLine("Ignoring comment: " + token.text);
            }
            else if(token.type != TokenType::WhiteSpace)
            {
                tokens.push_back(token);
            }
            if(token.type == TokenType::PotentialFloatingPoint)
            {
                if(token.text == ".")
                {
                    token.type = TokenType::Operator;
                }
                else
                {
                    token.type = TokenType::FloatingPointLiteral;
                }
            }


            token.type = TokenType::WhiteSpace;
            token.text = "";
        }

        void AppendCharacter(Token<TokenType>& token, char c)
        {
            token.text += c;
        }    
    };
};
#endif