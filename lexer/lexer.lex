%{
    #include <iostream>
%}

%option noyywrap
%option c++
%x comment

%{
   enum yytokentype {
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
%}

DIGIT       [0-9]+
ID          [a-zA-Z][a-zA-Z0-9]*


%%

"/*"                        BEGIN(comment);
<comment>[^*\n]*            /* eat anything that’s not a ’*’ */
<comment>"*"+[^*/\n]*       /* eat up ’*’s not followed by ’/’s */
<comment>\n                 {return NewLine;}
<comment>"*"+"/"            BEGIN(INITIAL);
[/][/].*\n                  {return NewLine;}


(?i:fun)            {
                        return Function;
                    }

(?i:if)             {
                        return If;
                    }

(?i:while)          {
                        return While;
                    }

(?i:return)         {
                        return Return;
                    }

(?i:val)            {
                        return Val;
                    }

(?i:var)            {
                        return Var;
                    }

(?i:Int)            {
                        return Var;
                    }

(?i:String)         {
                        return Var;
                    }

[\n]                {
                        return NewLine;
                    }

" "                 {
                        return WhiteSpace;
                    }

[(]                 {
                        return LeftParen;
                    }

[)]                 {
                        return RightParen;
                    }

[{]                 {
                        return LeftBrace;
                    }

[}]                 {
                        return RightBrace;
                    }

[+]                 {
                        return Plus;
                    }

[-]                 {
                        return Minus;
                    }

{ID}                {
                        return Identifier;
                    }


[/]                 {
                        return Div;
                    }

"*"                 {
                        return Mul;
                    }

"=="                {
                        return EqualEqual;
                    }

"="                 {
                        return Equal;
                    }

[>]                 {
                        return Greater;
                    }

[<]                 {
                        return Less;
                    }

[;]                 {
                        return SemiColon;
                    }

[:]                 {
                        return Colon;
                    }

[,]                 {
                        return Comma;
                    }
{DIGIT}             {
                        return NumericConstant;
                    }

{DIGIT}"."{DIGIT}   {
                        return NumericConstant;
                    }

\"(\\.|[^"\\])*\"   {
                        return StringConstant;
                    }


<<EOF>>             {
                        //yyterminate();
                        return Eof;
                    }

%%