#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../headers/addressbook.h"

//���� Form
void OnMenu(){
    //char buffer[1024];
    char* buffer = (char*) malloc(1024);
    int length;
    int menuOptions = 7;
    int count = 0;
    char *menu[20] = {"�����ϱ�", "ã��", "��ġ��", "�����", "�����ϱ�", "��ü����", "������"}; 
   
    //system("cls"); windows
    system("cls"); //macbook
    length=sprintf(buffer,"\n");
    length+=sprintf(buffer+length, "%31s %s","", "�ּҷ� v.01\n");
    length+=sprintf(buffer+length, "=============================================================================\n\n");
    for(int i=0; i< menuOptions; i++){
        count++;
        if(count == menuOptions) count =0; //0. ������ ����
        length+=sprintf(buffer + length,"%32d . %s\n", count, menu[i]);
    }
    length+=sprintf(buffer+length,"\n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    printf("%s",buffer);
    free(buffer);
}
//����
void Create(AddressBook *addressBook){
    #if 1
        addressBook->personal =(PersonalInformation(*))malloc(sizeof(PersonalInformation)*LINES);
        memset(addressBook->personal, 0, sizeof(PersonalInformation)*LINES);
    #endif
        //addressBook->personal = (PersonalInformation(*))calloc(LINES, sizeof(PersonalInformation));

    if(addressBook->personal !=NULL){
        addressBook->count = 0;
    }
}
//�޸� ����
void Destroy(AddressBook *addressBook){
    if(addressBook->personal != NULL){
        free(addressBook->personal);
        addressBook->count = 0;
    }
}
//����
void Arrange(AddressBook *addressBook){
    int i, j;
    PersonalInformation temp;
    for (i = 1; i < LINES; i++) {
        if (addressBook->personal[i].names[0] == '\0') {
            continue; //bo qua dong rong
        }
        temp = addressBook->personal[i];
        j = i - 1;
        while (j >= 0 && strcmp(addressBook->personal[j].names, temp.names) > 0) {
            addressBook->personal[j + 1] = addressBook->personal[j];
            j--;
        }
        addressBook->personal[j + 1] = temp;
    }
}
//������
int TakeOut(AddressBook *addressBook){
    int count=0;
    
    FILE *fp = fopen(path,"rb");
    if(fp != NULL){
        while (fread(&addressBook->personal[count], sizeof(PersonalInformation), 1, fp) > 0){
            count++;
        }
        fclose(fp);
    }

    addressBook->count = count;
    return count;
}
//�ִ�.
int TakeIn(AddressBook *addressBook){
    int i=0;
    int count=0;
    
    //������ ������ ���� ������ ���� �ִ� txt ���Ͽ� ���� ������ ��µ�.
    FILE *fp = fopen(path,"wb");
    if(fp != NULL){
        while (i<LINES && strcmp(addressBook->personal[i].names,"\0")!=0){
            count++;
            i++;
        }
        
        if(count>0){
            if(fp != NULL){
                fwrite(addressBook->personal, sizeof(PersonalInformation), count, fp);
            }
        }
        fclose(fp);
    }
    return count;
}
//�����ϴ�
int Record(AddressBook *addressBook, char *name, char *address, char *phoneNumber, char *emailAddress){
    int line;
    line = addressBook->count;
    if(line >= 0 && line < LINES){
        strcpy(addressBook->personal[line].names, name);
        strcpy(addressBook->personal[line].addresses, address);
        strcpy(addressBook->personal[line].phoneNumbers, phoneNumber);
        strcpy(addressBook->personal[line].emailAddresses, emailAddress);
        addressBook->count++;
        line++;
    }else{
        line = -1;
    }
    return line;
}
//�������� ã��
int FindByName(AddressBook *addressBook, char(*name), int(*lines)){
    int count=0;
    int i=0;

    while (i<LINES && strcmp(addressBook->personal[i].names,"\0")!=0){ 
        if(strcmp(addressBook->personal[i].names,name)==0){ 
            lines[count]=i; 
            count++;
        }
        i++;
    }
    
    return count;
}
//�̸��Ϸ� ã��
int FindByEmail(AddressBook *addressBook, char(*emailAddress)){
    int line = -1;
    int i=0;

    while(i<LINES && strcmp(addressBook->personal[i].names,"\0")!=0 && strcmp(addressBook->personal[i].emailAddresses,emailAddress)!=0){
        i++;
    }
    if(i<LINES && strcmp(addressBook->personal[i].names,"\0")!=0){
        line = i;
    }
    
    return line;
}
//��ġ��
int Correct(AddressBook *addressBook, int correctLine, char (*address), char (*phoneNumber), char (*emailAddress)){
    int line =-1;

    if(0 <= correctLine && correctLine < LINES && strcmp(addressBook->personal[correctLine].names,"")!=0){
        line=correctLine;
        strcpy(addressBook->personal[line].addresses,address);
        strcpy(addressBook->personal[line].phoneNumbers,phoneNumber);
        strcpy(addressBook->personal[line].emailAddresses,emailAddress);
    }
    return line;
}
//�����
int Erase(AddressBook *addressBook, int eraseLine){
    int i=0;
    int line=-1;
    int j;

    if(0 <= eraseLine && eraseLine < LINES && strcmp(addressBook->personal[eraseLine].names,"")!=0){
        line= eraseLine;
        i=line;
        //��ü ������ �Ǻ�
        while(i<LINES && strcmp(addressBook->personal[i].names,"\0")!=0){
            i++;
        }   
        //���� ������� �ϴ� �ٿ� ���� �ٿ� ������ �ִ��� ������ �Ǻ�
        if(line < LINES && strcmp(addressBook->personal[line].names,"\0")!=0){
            //���� ������ȣ�� �ƴϴ� �ڿ� ������ ������ ����´�.
            for(j=line; j<i; j++){
                strcpy(addressBook->personal[j].names, addressBook->personal[j+1].names);
                strcpy(addressBook->personal[j].addresses, addressBook->personal[j+1].addresses);
                strcpy(addressBook->personal[j].phoneNumbers, addressBook->personal[j+1].phoneNumbers);
                strcpy(addressBook->personal[j].emailAddresses, addressBook->personal[j+1].emailAddresses);
            }
        }
        //���� ������� �ϴ� ���� ���� �����̴� ���� �����Ѵ�.
        strcpy(addressBook->personal[i-1].names,"");
        strcpy(addressBook->personal[i-1].addresses,"");
        strcpy(addressBook->personal[i-1].phoneNumbers,"");
        strcpy(addressBook->personal[i-1].emailAddresses,"");
        addressBook->count--;
    }
    return line;
}