#include<stdio.h>
#include<stdlib.h>

int main()
{
    int c;
    while((c=fgetc(stdin))!=EOF) {
        switch(c) {
            case 0xb4:
            case 0xb8:
            case 0x60:
            case '^':
            case ':':
                break;
            case 0x92:
                printf("'");
                break;
            case 0x94:
                printf("\"");
                break;
            default:
                printf("%c", c);
        }
    }
    return 0;
}
