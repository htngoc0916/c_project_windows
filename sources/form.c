#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
//#include "addressbook.h"
//#include "form.h"
#include "../headers/addressbook.h"
#include "../headers/form.h"

void FormForAllView(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);
    int length;
    
    system("cls");
    length=sprintf(buffer,"\n");
    length+=sprintf(buffer+length, "%25s %s","", "�ּҷ� - ��ü����\n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    length+=sprintf(buffer+length,"%-5s %-15s %-15s %-15s %s \n", "Line", "Name", "Address", "Phone", "Email");
    for(int i=0; i < LINES; i++){
        length+=sprintf(buffer +length, "%-5d %-15s %-15s %-15s %s \n", (i+1), addressBook->personal[i].names, addressBook->personal[i].addresses, addressBook->personal[i].phoneNumbers, addressBook->personal[i].emailAddresses);
    }
    length+=sprintf(buffer+length, "-----------------------------------------------------------------------------\n");
    length+=sprintf(buffer+length, "�� ȭ�鿡 ���ư��ϴ�. \n");
    length+=sprintf(buffer+length, "=> EnterŰ ��������. \n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    printf("%s", buffer);
    free(buffer); 
    getchar();
    //char c = getc(stdin); 
}
void FormRecording(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);

    int length;
    char name[11];
    char emailAddress[255];
    char address[256];
    char phoneNumber[18];
    int line = -1; //result = -1: ������ ����, result > 0 ����
    char ynFlag;
    int flag = 1;

    while(flag){
        //system("cls"); //windows
        system("cls"); //macbook
        length=sprintf(buffer,"\n");
        length+=sprintf(buffer + length, "%25s %s","", "�����ϴ� \n");
        length+=sprintf(buffer + length, "%24s %s","", "[���� ����] \n");
        length+=sprintf(buffer + length, "====================================================================\n");
        printf("%s",buffer);
        //�̸���
        do{
            printf("\n ������ �̸����� �Է�: ");
            fgets(emailAddress, sizeof(emailAddress), stdin);   //scanf ���� '\n' ���� �����ϱ� ������ �ȵ˴ϴ�. fgets() ?Ǿߵ˴ϴ.
            emailAddress[strcspn(emailAddress, "\n")] = '\0'; // enter ����
            printf("\n �����Ͻ� �̸����� �����ϱ�? (y/n) : ");
            scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����      
            getchar();
        }while (toupper(ynFlag) != 'Y');
        printf("--------------------------------------------------------------------\n");

        //�̸��� �ߺ�
        if(toupper(ynFlag) == 'Y'){
            line = FindByEmail(addressBook, emailAddress);
            if(line >=0){
                system("cls"); //macbook
                length=sprintf(buffer,"\n");
                length+=sprintf(buffer + length, "%25s %s","", "�����ϴ� \n");
                length+=sprintf(buffer + length, "%24s %s","", "[���� ����] \n");
                length+=sprintf(buffer + length, "====================================================================\n\n");
                length+=sprintf(buffer + length, "%5s �Է��� �� %s �̸����� �ߺ��Ǿ����ϴ�.\n","", emailAddress);
                length+=sprintf(buffer + length, "====================================================================\n");
                length+=sprintf(buffer + length, "%5s %s","", "N�� �ڷ� ���ư���.\n");
                printf("%s",buffer);
                printf("%5s %s","", "��� �Է��ϰڽ��ϱ�? (y/n): ");
                scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����      
                getchar();
                if(toupper(ynFlag) != 'Y'){
                    return;
                }else{
                    continue;
                }
            }
        }

        //�̸�
        do{
            printf("\n ������ ������ �Է�: ");
            //scanf("%s",name); scanf ���� '\n' ���� �����ϱ� ������ �ȵ˴ϴ�. fgets() ?Ǿߵ˴ϴ.
            fgets(name, sizeof(name), stdin);   
            name[strcspn(name, "\n")] = '\0'; // enter ����
            printf("\n �����Ͻ� ������ �����ϱ�? (y/n) : ");
            scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����      
            getchar();
        }while (toupper(ynFlag) != 'Y');
        printf("--------------------------------------------------------------------\n");

        //�ּ�
        do{
            printf("\n ������ �ּҸ� �Է�: ");
            fgets(address, sizeof(address), stdin);   //scanf ���� '\n' ���� �����ϱ� ������ �ȵ˴ϴ�. fgets() ?Ǿߵ˴ϴ.
            address[strcspn(address, "\n")] = '\0'; // enter ����
            printf("\n �����Ͻ� ���Ұ� �����ϱ�? (y/n) : ");
            scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����          
            getchar();
        }while (toupper(ynFlag) != 'Y');
        printf("--------------------------------------------------------------------\n");

        //��ȭ��ȣ
        do{
            printf("\n ������ ��ȭ��ȣ�� �Է�: ");
            fgets(phoneNumber, sizeof(phoneNumber), stdin);   //scanf ���� '\n' ���� �����ϱ� ������ �ȵ˴ϴ�. fgets() ?Ǿߵ˴ϴ.
            phoneNumber[strcspn(phoneNumber, "\n")] = '\0'; // enter ����
            printf("\n �����Ͻ� ��ȭ��ȣ�� �����ϱ�? (y/n) : ");
            scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����        
            getchar();
        }while (toupper(ynFlag) != 'Y');
        printf("--------------------------------------------------------------------\n");

        line = Record(addressBook, name, address, phoneNumber, emailAddress);

        if(line != -1){
            //getchar(); 
            system("cls"); //macbook
            length=sprintf(buffer,"\n");
            length+=sprintf(buffer + length, "%25s %s","", "�����ϴ� \n");
            length+=sprintf(buffer + length, "%24s %s","", "[���� ����] \n");
            length+=sprintf(buffer + length, "====================================================================\n");
            length+=sprintf(buffer + length, "%3s %s \n\n","", "���� �����ǿ����ϴ�.");
            length+=sprintf(buffer + length, "%s \n","�Է�����");
            length+=sprintf(buffer + length, "%5s %-10s : %s \n","","����",name);
            length+=sprintf(buffer + length, "%5s %-10s : %s \n","","����", address);
            length+=sprintf(buffer + length, "%5s %-10s : %s \n","","��ȭ��ȣ", phoneNumber);
            length+=sprintf(buffer + length, "%5s %-10s : %s \n","","�̸���", emailAddress);
            length+=sprintf(buffer + length, "--------------------------------------------------------------------\n");
            length+=sprintf(buffer + length, "%15s: %d/%d \n\n","����� ����", line, LINES);
            length+=sprintf(buffer + length, "%s: %d %s \n\n", "�Է��Ͻ� ������", line, "�ٿ� �����Ͽ����ϴ�.");
            length += sprintf(buffer+length, "%3s %-5s %-8s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
            length+=sprintf(buffer + length, "%3s %-5d %-8s %-15s %-15s %s\n", "", line, name, address, phoneNumber, emailAddress);
            length+=sprintf(buffer + length, "--------------------------------------------------------------------\n");
            printf("%s", buffer);   
            printf("��� �Է��ϰڽ��ϱ�? (y/n): ");
            scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ���� 
            getchar();
            if(toupper(ynFlag) != 'Y') flag = 0;
        } else { 
            getchar(); 
            system("cls"); //macbook
            length=sprintf(buffer,"\n");
            length+=sprintf(buffer + length, "%25s %s","", "�����ϴ� \n");
            length+=sprintf(buffer + length, "%24s %s","", "[���� ����] \n");
            length+=sprintf(buffer + length, "====================================================================\n\n");
            length+=sprintf(buffer + length, "%1s %s","", "������ ������ �����ϴ�. \n");
            length+=sprintf(buffer + length, "--------------------------------------------------------------------\n\n");
            length+=sprintf(buffer + length, "%1s %s","", "������ ������ �����ϴ�. \n\n");
            length+=sprintf(buffer + length, "%3s %s","", "�ָ޴��� �̵��մϴ�. \n");
            length+=sprintf(buffer + length, "%3s %s","", "=> EnterŰ�� ��������. \n");
            printf("%s", buffer);   
            getchar();
            free(buffer);
            return;
        }
    }
    free(buffer);
}
void FormForFinding(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);
    int length;
    int flag = 1;
    int options;

    while (flag){
        //system("cls");
        system("cls");
        length=sprintf(buffer,"\n");
        length+=sprintf(buffer+length, "%30s %s","", "ã��\n");
        length+=sprintf(buffer+length, "%28s %s","", "�޴� - ����\n");
        length+=sprintf(buffer+length, "=============================================================================\n\n");
        length+=sprintf(buffer+length, "%24s %s","", "1. �������� ã��.\n");
        length+=sprintf(buffer+length, "%24s %s","", "2. �̸��Ϸ� ã��.\n");
        length+=sprintf(buffer+length, "%24s %s","", "0. �ڷ� ���ư���.\n");
        length+=sprintf(buffer+length, "\n\n");
        length+=sprintf(buffer+length, "=============================================================================\n\n");
        printf("%s", buffer);
        printf("�޴��� �����ϼ���: ");
        scanf("%d", &options);
        getchar();
        switch(options){
            case 1:
                //����
                FormForByName(addressBook);
                break;
            case 2:
                //�̸���
                FormForByEmailAddressses(addressBook);
                break;
            case 0:
                flag = 0;
                break;
        }
    }
    free(buffer); 
}
void FormForErasing(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);
    int length;
    char name[11];
    int line, count, maxLine;
    int lines[LINES];
    int flag = 1;
    char checkLine = 'N'; //������ȣ�� �ȸ�����
    char ynFlag;

    while(flag){
        system("cls");
        length=sprintf(buffer,"\n");
        length+=sprintf(buffer+length, "%30s %s","", "�����\n");
        length+=sprintf(buffer+length, "=============================================================================\n");
        printf("%s", buffer);
        printf("%3s %s", "", "����� ���� ������ �Է����ּ���. \n");
        printf("%s", "-----------------------------------------------------------------------------\n");
        
        do{
            printf("%10s %s", "", "����: ");
            fgets(name, sizeof(name), stdin);   
            name[strcspn(name, "\n")] = '\0'; // enter ����
            printf("\n");
            printf("ã���ðڽ��ϱ�? (y/n): ");
            scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����  
            getchar();    
            printf("-----------------------------------------------------------------------------\n");
        } while (toupper(ynFlag) != 'Y');
        
        count = FindByName(addressBook, name, lines);
        if(count > 0){
            while (checkLine != '\0'){
                system("cls");
                if(checkLine == 'N'){
                    length += sprintf(buffer + length, "�˻� ���: \n");
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer+length,"%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    for(int i=0; i<count; i++){
                        maxLine = i + 1;
                        length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", maxLine, addressBook->personal[lines[i]].names, addressBook->personal[lines[i]].addresses, addressBook->personal[lines[i]].phoneNumbers, addressBook->personal[lines[i]].emailAddresses);
                    }
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer + length, "���� �� ��ȣ�� �Է����ּ��� (%d ~ %d  ������ ���ڸ� �Է��ϼ���). \n\n", 1, count);
                }else{
                    length = sprintf(buffer, "\n");
                    length += sprintf(buffer + length, "%30s %s","", "�����\n");
                    length += sprintf(buffer + length, "=============================================================================\n");
                    length += sprintf(buffer + length, "%s", "���� �� ��ȣ�� ��ȿ���� �ʽ��ϴ�. \n");
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer + length,"%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    for(int i=0; i<count; i++){
                        maxLine = i+1;
                        length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", maxLine, addressBook->personal[lines[i]].names, addressBook->personal[lines[i]].addresses, addressBook->personal[lines[i]].phoneNumbers, addressBook->personal[lines[i]].emailAddresses);
                    }
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer + length, "���� �� ��ȣ�� �ٽ� �Է����ּ���. (%d ~ %d  ������ ���ڸ� �Է��ϼ���). \n\n", 1, count);
                }
                printf("%s", buffer);
                do{
                    printf("��: ");
                    scanf("%d",&line);
                    getchar();

                    printf("����� �� ��ȣ�� �½��ϱ�? (y/n): ");
                    scanf("%c",&ynFlag);
                    getchar();
                }
                while(toupper(ynFlag) != 'Y');

                //���� �߸��Է� üũ
                system("cls");
                if(line <= 0 || line > maxLine){
                    //��ȣ �߸�������
                    checkLine = 'Y';
                }else{
                    //��ȣ ����
                    checkLine = 'N';
                    count = Erase(addressBook, lines[line - 1]);
                    length = sprintf(buffer, "\n");
                    length += sprintf(buffer + length, "%30s %s","", "�����\n");
                    length += sprintf(buffer + length, "=============================================================================\n\n");
                    length += sprintf(buffer + length, "%d��? ���� �����Ǿ����ϴ�. \n", count + 1);
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
                    printf("%s", buffer);
                    printf("N�� ������ ���θ޴��� ���ư��ϴ�. \n");
                    printf("��� ����ðڽ��ϱ�? (y/n): ");
                    scanf("%c",&ynFlag);
                    getchar();
                    if(toupper(ynFlag) != 'Y'){
                        ynFlag = '\0';
                        return;
                    }else{
                        //�ݺ�������
                        ynFlag = '\0';
                        break;
                    }
                }
            }
        }else{
            system("cls");
            length += sprintf(buffer + length, "%3s %s��(��) �� ã�ҽ��ϴ�.\n", "", name);
            length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
            printf("%s", buffer);
            printf("N�� �Է��Ͻø� ���θ޴��� ���ư��ϴ�. \n �ٽ� �Է��Ͻðڽ��ϱ�? (y/n): ");
            scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����  
            getchar();    
            printf("-----------------------------------------------------------------------------\n");
            if(toupper(ynFlag) != 'Y'){
                return;
            }
        }
    }
}
void FormForCorrecting(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);
    int length;
    char name[11];
    char address[256];
    char phoneNumber[18];
    char emailAddress[256];
    int lines[LINES];
    int line;
    char ynFlag;
    int count, maxLine;
    int flag = 1;
    char checkLine = 'N';
    
    while (flag){
        system("cls");
        length=sprintf(buffer,"\n");
        length+=sprintf(buffer+length, "%30s %s","", "��ġ��\n");
        length+=sprintf(buffer+length, "=============================================================================\n");
        printf("%s", buffer);
        printf("%3s %s", "", "��ġ�� ���� ������ �Է����ּ���. \n");
        printf("%s", "-----------------------------------------------------------------------------\n");
        do{
            printf("%10s %s", "", "����: ");
            fgets(name, sizeof(name), stdin);   
            name[strcspn(name, "\n")] = '\0'; // enter ����
            printf("\n");
            printf("��ġ ������ �½��ϱ�? (y/n): ");
            scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����  
            getchar();    
            printf("-----------------------------------------------------------------------------\n");
            if(ynFlag == '0') return;
        } while (toupper(ynFlag) != 'Y');

        count = FindByName(addressBook, name, lines);
        if(count > 0){
            while (checkLine != '\0'){
                system("cls");
                if(checkLine == 'N'){
                    length += sprintf(buffer + length, "��ĥ %s��(��) %d�� ã�ҽ��ϴ�.\n", name, count);
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
                    length += sprintf(buffer+length,"%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    for(int i=0; i<count; i++){
                        maxLine = i+1; //line �Է� üũ �� �ʿ�
                        length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", maxLine, addressBook->personal[lines[i]].names, addressBook->personal[lines[i]].addresses, addressBook->personal[lines[i]].phoneNumbers, addressBook->personal[lines[i]].emailAddresses);
                    }
                }
                else{
                    length = sprintf(buffer, "\n");
                    length += sprintf(buffer + length, "%30s %s","", "�����\n");
                    length += sprintf(buffer + length, "=============================================================================\n");
                    length += sprintf(buffer + length, "%s", "���� �� ��ȣ�� ��ȿ���� �ʽ��ϴ�. \n");
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer + length,"%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    for(int i=0; i<count; i++){
                        maxLine = i+1; //line �Է� üũ �� �ʿ�
                        length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", maxLine, addressBook->personal[lines[i]].names, addressBook->personal[lines[i]].addresses, addressBook->personal[lines[i]].phoneNumbers, addressBook->personal[lines[i]].emailAddresses);
                    }
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer + length, "���� �� ��ȣ�� �ٽ� �Է����ּ���. (%d ~ %d  ������ ���ڸ� �Է��ϼ���). \n\n", 1, count);
                }
                length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                printf("%s", buffer);
                do{
                    
                    printf("��ĥ �� ��ȣ�� �Է����ּ���. \n");
                    printf("��: ");
                    scanf("%d",&line);
                    getchar();

                    printf("��ĥ �� ��ȣ�� �½��ϱ�? (y/n): ");
                    scanf("%c",&ynFlag);
                    getchar();
                    printf("\n");
                    printf("-----------------------------------------------------------------------------\n");
                }
                while(toupper(ynFlag) != 'Y');

                //���� �߸��Է� üũ
                system("cls");
                if(line <= 0 || line > maxLine){
                    //��ȣ �߸�������
                    checkLine = 'Y';
                }else{
                    //��ȣ ����
                    checkLine = 'N';
                    length = sprintf(buffer, "\n");
                    length += sprintf(buffer + length, "%30s %s","", "��ġ��\n");
                    length += sprintf(buffer + length, "=============================================================================\n\n");
                    length += sprintf(buffer + length, "��ĥ �� ��ȣ: %d \n\n", line);
                    length += sprintf(buffer + length, "%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    length += sprintf(buffer + length, "%3s %-5d %-15s %-15s %-15s %s \n", "", line, addressBook->personal[lines[line - 1]].names, addressBook->personal[lines[line - 1]].addresses, addressBook->personal[lines[line - 1]].phoneNumbers, addressBook->personal[lines[line - 1]].emailAddresses);
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    printf("%s", buffer);
                    //�ּ�
                    do{
                        printf("%10s %s", "", "�ּ�: ");
                        fgets(address, sizeof(address), stdin);   
                        address[strcspn(address, "\n")] = '\0'; // enter ����
                        printf("\n");
                        printf("��ġ �ּҰ� �½��ϱ�? (y/n): ");
                        scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����  
                        getchar();    
                        printf("-----------------------------------------------------------------------------\n");
                        if(ynFlag == '0') return;
                    } while (toupper(ynFlag) != 'Y');
                    //��ȭ��ȣ
                    do{
                        printf("%10s %s", "", "��ȭ��ȣ: ");
                        fgets(phoneNumber, sizeof(phoneNumber), stdin);   
                        phoneNumber[strcspn(phoneNumber, "\n")] = '\0'; // enter ����
                        printf("\n");
                        printf("��ġ ��ȭ��ȣ�� �½��ϱ�? (y/n): ");
                        scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����  
                        getchar();    
                        printf("-----------------------------------------------------------------------------\n");
                        if(ynFlag == '0') return;
                    } while (toupper(ynFlag) != 'Y');
                    //�̸���
                    do{
                        printf("%10s %s", "", "�̸���: ");
                        fgets(emailAddress, sizeof(emailAddress), stdin);   
                        emailAddress[strcspn(emailAddress, "\n")] = '\0'; // enter ����
                        printf("\n");
                        printf("��ġ �̸����� �½��ϱ�? (y/n): ");
                        scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����  
                        getchar();    
                        printf("-----------------------------------------------------------------------------\n");
                        if(ynFlag == '0') return;
                    } while (toupper(ynFlag) != 'Y');

                    system("cls");
                    length = sprintf(buffer, "\n");
                    length += sprintf(buffer + length, "%30s %s","", "��ġ��\n");
                    length += sprintf(buffer + length, "=============================================================================\n\n");
                    length += sprintf(buffer + length, "��ĥ �� ��ȣ: %d \n", line);
                    length += sprintf(buffer + length, "%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                    length += sprintf(buffer + length, "%3s %-5d %-15s %-15s %-15s %s \n", "", line, addressBook->personal[lines[line - 1]].names, addressBook->personal[lines[line - 1]].addresses, addressBook->personal[lines[line - 1]].phoneNumbers, addressBook->personal[lines[line - 1]].emailAddresses);
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    length += sprintf(buffer + length, "%5s �ּ�: %s \n","", address);
                    length += sprintf(buffer + length, "%5s ��ȭ��ȣ: %s \n","", phoneNumber);
                    length += sprintf(buffer + length, "%5s �̸���: %s \n","", emailAddress);
                    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                    printf("%s", buffer);
                    printf("��ġ�ðڽ��ϱ�? (y/n): ");
                    scanf("%c",&ynFlag);
                    getchar();
                    if(toupper(ynFlag) != 'Y'){
                         //�ݺ�������
                        break;
                    }else{
                        system("cls");
                        count = Correct(addressBook, lines[line-1], address, phoneNumber, emailAddress);
                        length = sprintf(buffer, "\n");
                        length += sprintf(buffer + length, "%30s %s","", "��ġ��\n");
                        length += sprintf(buffer + length, "=============================================================================\n\n");
                        length += sprintf(buffer + length, "%d���� ���ƽ��ϴ�. \n", count + 1);
                        length += sprintf(buffer + length, "%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
                        length += sprintf(buffer + length, "%3s %-5d %-15s %-15s %-15s %s \n", "", count + 1, addressBook->personal[count].names, addressBook->personal[count].addresses, addressBook->personal[count].phoneNumbers, addressBook->personal[count].emailAddresses);
                        length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n");
                        printf("%s",buffer);
                        //��
                        printf("��� ��ġ�ðڽ��ϱ�? (y/n): ");
                        scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����  
                        getchar();    
                        if(toupper(ynFlag) == 'Y'){
                            break;
                        }
                        else{
                            return;
                        }
                    }
                }
            }
        }
        else{
            system("cls");
            length += sprintf(buffer + length, "%3s %s��(��) �� ã�ҽ��ϴ�.\n", "", name);
            length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
            printf("%s", buffer);
            printf("EnterŰ �Է��ϼ���.");
            scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����  
        }
    }
    free(buffer); 
}
void FormForArranging(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);
    int length;

    //system("cls");
    system("cls");
    Arrange(addressBook);
    length=sprintf(buffer,"\n");
    length+=sprintf(buffer+length, "%25s %s","", "�����ϱ� \n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    length+=sprintf(buffer+length,"%-5s %-15s %-15s %-15s %s \n", "Line", "Name", "Address", "Phone", "Email");
    for(int i=0; i < LINES; i++){
        length+=sprintf(buffer +length, "%-5d %-15s %-15s %-15s %s \n", (i+1), addressBook->personal[i].names, addressBook->personal[i].addresses, addressBook->personal[i].phoneNumbers, addressBook->personal[i].emailAddresses);
    }
    length+=sprintf(buffer+length, "-----------------------------------------------------------------------------\n");
    length+=sprintf(buffer+length, "�� ȭ�鿡 ���ư��ϴ�. \n");
    length+=sprintf(buffer+length, "=> EnterŰ ��������. \n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    printf("%s", buffer);
    getchar();
    free(buffer); 
}
void FormForByEmailAddressses(AddressBook *addressBook){
   char* buffer = (char*) malloc(1024);
    int length;
    char email[256];
    char ynFlag;
    int count;
    int flag = 1;
    //system("cls");
    system("cls");
    length=sprintf(buffer,"\n");
    length+=sprintf(buffer+length, "%30s %s","", "ã��\n");
    length+=sprintf(buffer+length, "%22s %s","", "[�̸������� ã��]\n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    printf("%s", buffer);
    while (flag)
    {
        printf("%20s %s", "", "�̸���: ");
        fgets(email, sizeof(email), stdin);   
        email[strcspn(email, "\n")] = '\0'; // enter ����
        printf("\n");
        printf("ã���ðڽ��ϱ�? (y/n): ");
        scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����      
        getchar();
        printf("-----------------------------------------------------------------------------\n");
        if(toupper(ynFlag) == 'N'){
            return;
        }else if(toupper(ynFlag) == 'Y'){
            flag = 0; 
        }
    }

    system("cls");
    length += sprintf(buffer + length,"\n");
    count = FindByEmail(addressBook, email);
    if(count >= 0){
        length += sprintf(buffer + length, "%3s %s��(��) ã�ҽ��ϴ�.\n", "", email);
        length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
        length += sprintf(buffer + length, "%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
        length += sprintf(buffer + length, "%3s %-5d %-15s %-15s %-15s %s \n", "", (count + 1), addressBook->personal[count].names, addressBook->personal[count].addresses, addressBook->personal[count].phoneNumbers, addressBook->personal[count].emailAddresses);
    }else{
        length += sprintf(buffer + length, "%3s %s��(��) �� ã�ҽ��ϴ�.\n", "", email);
    }
    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
    length += sprintf(buffer + length, "%s \n", "ã�� �޴��� ���ư��ϴ�.");
    length += sprintf(buffer + length, "%s \n", " => EnterŰ �����ּ���...");
    printf("%s", buffer);
    free(buffer); 
    getchar();
}
void FormForByName(AddressBook *addressBook){
    char* buffer = (char*) malloc(1024);
    int length;
    char name[11];
    char ynFlag;
    int count;
    int lines[LINES];
    int flag = 1;
    //system("cls");
    system("cls");
    length=sprintf(buffer,"\n");
    length+=sprintf(buffer+length, "%30s %s","", "ã��\n");
    length+=sprintf(buffer+length, "%22s %s","", "[�������� ã��]\n");
    length+=sprintf(buffer+length, "=============================================================================\n");
    printf("%s", buffer);
    while (flag)
    {
        printf("%20s %s", "", "����:");
        fgets(name, sizeof(name), stdin);   
        name[strcspn(name, "\n")] = '\0'; // enter ����
        printf("\n");
        printf("ã���ðڽ��ϱ�? (y/n): ");
        scanf("%c", &ynFlag);    // ���ڸ� �Է¹޾Ƽ� ������ ����      
        getchar();
        printf("-----------------------------------------------------------------------------\n");
        if(toupper(ynFlag) == 'N'){
            return;
        }else if(toupper(ynFlag) == 'Y'){
            flag = 0; 
        }
    }

    system("cls");
    length += sprintf(buffer + length,"\n");
    count = FindByName(addressBook, name,lines);
    if(count > 0){
        length += sprintf(buffer + length, "%3s %s��(��) %d�� ã�ҽ��ϴ�.\n", "", name, count);
        length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
        length += sprintf(buffer+length,"%3s %-5s %-15s %-15s %-15s %s \n", "", "Line", "Name", "Address", "Phone", "Email");
        for(int i=0; i<count; i++){
            length+=sprintf(buffer +length, "%3s %-5d %-15s %-15s %-15s %s \n", "", lines[i]+1, addressBook->personal[lines[i]].names, addressBook->personal[lines[i]].addresses, addressBook->personal[lines[i]].phoneNumbers, addressBook->personal[lines[i]].emailAddresses);
        }
    }else{
        length += sprintf(buffer + length, "%3s %s��(��) �� ã�ҽ��ϴ�.\n", "", name);
    }
    length += sprintf(buffer + length, "-----------------------------------------------------------------------------\n\n");
    length += sprintf(buffer + length, "%s \n", "ã�� �޴��� ���ư��ϴ�.");
    length += sprintf(buffer + length, "%s \n", " => EnterŰ �����ּ���...");
    printf("%s", buffer);
    free(buffer); 
    getchar();
}