#include <stdio.h>
#include <arpa/inet.h>

void byteorder(){
    union{
        short value;
        char union_bytes[sizeof(short)];
    }test;

    test.value = 0x0102;
    if((test.union_bytes[0] == 1) && (test.union_bytes[1] == 2)){
        printf("big endian\n");
    }
    else if((test.union_bytes[0] == 2) && (test.union_bytes[1] == 1)){
        printf("little endian\n");
    }
    else{
        printf("unknown...\n");
    }
}

int main(){
    byteorder();
    //char* szValue1 = inet_pton("1.2.3.4");
    //char* szValue2 = inet_ntoa("10.194.71.60");
    //printf("address 1: %s\n",szValue1);
    //printf("address 2: %s\n",szValue2);
    return 0;
}
