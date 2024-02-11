#include <stdio.h>
#include <ctype.h>
enum Statetype{Normal, Slash, Comment, Asterisk, charLit, stringLit, 
stringIgnore, charIgnore, slashDQ, slashSQ, slashDQIgnore, slashSQIgnore, 
commentIgnore, AsteriskIgnore};
enum Statetype;
/*Normal is the default state. Checks if c is a slash(may be a comment), 
a quote (could be a string/char literal), if it's none of those, prints 
it and remains in normal*/
enum Statetype handleNormalState(int c) {
    enum Statetype state;
    if (c == '/') {
        state = Slash;
    }
    else if (c == '\"') {
        putchar(c);
        state = stringLit;
    }
    else if (c == '\'') {
        putchar(c);
        state = charLit;
    }
    else {
        putchar(c);
        state = Normal;
    }
    return state;  
}
/*could be a comment or perhaps division. If it sees a *, opens comment
Also checks for quotes and a double /. If c isn't an asterisk, prints */
enum Statetype handleSlashState(int c) {
    enum Statetype state;
    if (c=='*') {
        state = Comment;
    }
    else if (c == '/') {
        putchar(c);
        state = Slash;
    }
    else if (c == '\"') {
        putchar(c);
        state = slashDQ;
    }
    else if (c == '\'') {
        putchar(c);
        state = slashSQ;
    }
    else {
        putchar(c);
        state = Normal;
    }
    return state;
}
/*runs through the comment until it ends. Checks for * to see when it ends,
checks for \ in case it has to ignore it. Does not print(goal is decomment)*/
enum Statetype handleCommentState(int c) {
    enum Statetype state;
    if (c=='*') {
        state = Asterisk;
    }
    if (c == '\\') {
        state = commentIgnore;
    }
    if (c == '\n') {
        putchar(c);
        state = Comment;
    }
    else {
        state = Comment;
    }
    return state;
}
/*may or may not be the close of a comment. Checks for **, \*, or random asterisks in 
a comment */
enum Statetype handleAsteriskState(int c) {
    enum Statetype state;
    if (c == '*') {
        state = Asterisk;
    }
    if (c == '\\') {
        state = AsteriskIgnore;
    }
    else if (c == '/') {
        /*only put space at very end of comment*/
        putchar(' ');
        state = Normal;
    }
    else {
        state = Comment;
    }
    return state;
}
/*anything in a string lit should not be treated as a comment.
This is double quotes purgatory. Checks for backslashes that may 
be a fake close quote and at the real close quote, sends it back to 
Normal. And prints everything*/
enum Statetype handlestringLitState(int c) {
    enum Statetype state;
    if (c == '\\') {
        putchar(c);
        state = stringIgnore;
    }
    else if (c == '\"') {
        putchar(c);
        state = Normal;
    }
    else {
        putchar(c);
        state = stringLit;
    }
    return state;
}
/*similar to stringLit, but for chars(single quotes)*/
enum Statetype handlecharLitState(int c) {
    enum Statetype state;
      if (c == '\\') {
        putchar(c);
        state = charIgnore;
    }
    else if (c == '\'') {
        putchar(c);
        state = Normal;
    }
    else {
        putchar(c);
        state = charLit;
    }
    return state;
}
/*handles \ in a string lit from normal*/
enum Statetype handlestringIgnoreState(int c) {
    enum Statetype state;
    putchar(c);
    state = stringLit;
    return state;
}
/*handles \ in a int lit from normal*/
enum Statetype handlecharIgnoreState(char c) {
    enum Statetype state;
    putchar(c);
    state = charLit;
    return state;
}
/* for the case where we have /', similar to charLit*/
enum Statetype handleslashSQState(char c) {
    enum Statetype state;
    if (c == '\\') {
        putchar(c);
        state = slashSQIgnore;
    }
    else if (c == '\'') {
        putchar(c);
        state = Normal;
    }
    else {
        putchar(c);
        state = slashSQ;
    }
    return state;
}
/*for the case where we have /", similar to stringLit*/
enum Statetype handleslashDQState(char c) {
    enum Statetype state;
    if (c == '\\') {
        putchar(c);
        state = slashDQIgnore;
    }
    else if (c == '\"') {
        putchar(c);
        state = Normal;
    }
    else {
        putchar(c);
        state = slashDQ;
    }
    return state;
}
/*ignores \ in a stringlit after a slash*/
enum Statetype handleslashDQIgnoreState(char c) {
    enum Statetype state;
    putchar(c);
    state = slashDQ;
    return state;
}
/*ignores \ in a charlit after a slash*/
enum Statetype handleslashSQIgnoreState(char c) {
    enum Statetype state;
    putchar(c);
    state = slashSQ;
    return state;
}
/*ignores \ in a comment*/
enum Statetype handlecommentIgnoreState(char c) {
    enum Statetype state;
    putchar(' ');
    state = Comment;
    return state;
}
/*ignores backslash following an asterisk in a comment*/
enum Statetype handlestateAsteriskIgnoreState(char c) {
    enum Statetype state;
    putchar(' ');
    state = Asterisk;
    return state;
}
int main(void) {
    int c;
    enum Statetype state = Normal;
    while ((c = getchar()) != EOF) {
        switch (state) {
            case Normal:
                state = handleNormalState(c);
                break;
            case Slash:
                state = handleSlashState(c);
                break;
            case Comment:
                state = handleCommentState(c);
                break;
            case Asterisk:
                state = handleAsteriskState(c);
                break;
            case charLit:
                state = handlecharLitState(c);
                break;
            case stringLit:
                state = handlestringLitState(c);
                break;
            case stringIgnore:
                state = handlestringIgnoreState(c);
                break;
            case charIgnore:
                state = handlecharIgnoreState(c);
                break;
            case  slashDQ:
                state = handleslashDQState(c);
                break;
            case slashSQ:
            state = handleslashSQState(c);
                break;
            case slashDQIgnore:
                 state = handleslashDQIgnoreState(c);
                 break;
            case slashSQIgnore:
             state = handleslashSQIgnoreState(c);
                break;
            case commentIgnore:
                state = handlecommentIgnoreState(c);
                break;
            case AsteriskIgnore:
                state = handleAsteriskState(c);
        }
    }
    return 0;
}