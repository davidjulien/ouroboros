#include <stdio.h>
#include <ctype.h>
#include "char_filter.h"

int islatin1(int c)
{
    return isalnum(c) || (c>=224 && c<254);
}

int islatin1_or_space(int c)
{
    return islatin1(c) || isspace(c) || c == '\'';
}

int everything(int c)
{
    return (unsigned char)c;
}

unsigned char stable_transform(int c)
{
    return (unsigned char )c;
}

unsigned char latin1_to_ascii(int c)
{
    /* TODO : gérer les majuscules accentuées */
    switch(c) {
        case '\t':
        case '\'':
        case 247:
        case 248:
            return ' ';
        case 192: /* à maj */
        case 193:
        case 194:
        case 195: /* ~a */
        case 196:
        case 197:
        case 224: /* à */
        case 225: /* a' */
        case 226: /* â */
        case 227: /* a~ */
        case 228: /* ä */
        case 229: /* °a */
        case 230:
            return 'a';
        case 200:
        case 201 : /* é maj */
        case 202: /* Ê */
        case 203:
        case 232: /* è */
        case 233: /* é */
        case 234: /* ê */
        case 235: /* ë */
            return 'e';
        case 204:
        case 205:
        case 206: /* î maj */
        case 207:
        case 236: /* `i */
        case 237: /* 'i */
        case 238: /* î */
        case 239: /* 'ï': */
            return 'i';
        case 240:
        case 242: 
        case 243: 
        case 244: /* 'ô': */
        case 245:
        case 246:
            return 'o';
        case 217:
        case 218:
        case 219:
        case 220:
        case 249: /* 'ù' */
        case 250:
        case 251: /* 'û': */
        case 252:
            return 'u';
        case 231: /* ç */
            return 'c';
        case 253:
        case 255:
            return 'y';
        case 209:
        case 241:
            return 'n';
        default:
            if (c>127) {
                printf("Code %d : %c\n", c, c);
            }
            return tolower(c);
    }
}
