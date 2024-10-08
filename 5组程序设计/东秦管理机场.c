#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include <process.h>
/*�������õ�C���Ա�׼��ͷ�ļ���
1. `<stdio.h>`: ��׼�������ͷ�ļ��������������ļ����������������������ȹ��ܵĺ������������磬`printf`��`scanf`��`fopen`��`fclose` �Ⱥ��������������ͷ�ļ��С�
2. `<string.h>`: �ַ�������ͷ�ļ������������ڴ����ַ��������ַ������ơ����ӡ��Ƚϵȣ��ĺ������������磬`strcpy`��`strcmp`��`strlen` �Ⱥ��������������ͷ�ļ��С�
3. `<conio.h>`: ����̨�������ͷ�ļ����������ڿ���̨������ʹ�õĺ�������`getch()`����Щ�����ڱ�׼�����������ͨ�����ṩ��
4. `<unistd.h>`: ͳһϵͳ����ͷ�ļ�����������ϵͳ������صĺ�����������`sleep`��
5. `<process.h>`: ���̿���ͷ�ļ�������������̿�����صĺ�����������`exit`��
*/
 
// ����ȫ�ֱ���
FILE *fp;
int i, end_of_file, pw_tries=0;
/*�����˼���ȫ�ֱ�����
1. `FILE *fp`: ����һ���ļ�ָ�룬����ָ��򿪵��ļ�����C�����У��ļ�����ͨ����Ҫʹ���ļ�ָ�롣���ָ���ڳ���Ĳ�ͬ���ֱ�������ȡ��д���ļ���
2. `int i`: ����һ�����ͱ�����ͨ������ѭ�����ƻ��������������������ṩ�Ĵ���Ƭ���У���û�б���ȷ�������κ��ض��Ĺ��ܣ������ܱ���������������������;��
3. `int end_of_file`: ����һ�����ͱ�����ͨ�������ļ������С����ļ���ȡ���������ļ�ĩβʱ����������ᱻ����Ϊ�ض�ֵ����-1������ָʾ�ļ�������
4. `int pw_tries=0`: ����һ�����ͱ��������ڸ����û����Ե�¼�Ĵ���������������û���֤������ʹ�ã��������û����Ե�¼�Ĵ�����
*/ 

// �ṹ�嶨��
struct variables {
    char name[10], dep[16], des[16], deptime[8], destime[8];
    long long num;
    int refno, noofseats;
}booking[25];
/* `struct variables` �ṹ�壬���ڴ洢��Ʊ����ص����ݡ�����ṹ����������ֶΣ�
- `name`: �ÿ͵����ϣ�����Ϊ16���ַ���
- `dep`: �����أ�����Ϊ4���ַ���
- `des`: Ŀ�ĵأ�����Ϊ4���ַ���
- `deptime`: ����ʱ�䣬����Ϊ8���ַ���
- `destime`: ����ʱ�䣬����Ϊ8���ַ���
- `num`: �ÿ͵���ϵ�绰������Ϊ10�����֡�
- `refno`: Ʊ��ο��š�
- `noofseats`: Ԥ������λ����
����ṹ�屻����Ϊ���� `booking[25]`����ζ�ſ��Դ洢25��Ʊ���¼��ÿ����¼���������ֶΣ����ڴ洢�����ÿ͵�Ʊ����Ϣ��
*/ 

// ��������
extern void authentication();// �����û���֤�ĺ���//տ 
extern void loader(char value[10]);// ��ʾ���ض����ĺ���//տ 
extern void options();// ��ʾ����ѡ��ĺ���//տ 
extern void bookticket();// ����Ԥ��Ʊ��ĺ��� //�� 
extern int count_digits_in_num(long long number);// ���������е�λ���ĺ���//�� 
extern void flight_time(char dep[3], char des[3]);// ���ݳ����غ�Ŀ�ĵ��ṩ����ʱ��ĺ���//�� 
extern void list_booked_tickets();// ��ʾ����Ԥ����Ʊ��ĺ���//�� 
extern void search_ticket();// ͨ���ο�������Ʊ��ĺ���//տ 
extern void edit_ticket();// ͨ���ο��ű༭Ʊ��ĺ���//�� 
extern void cancel_ticket();// ͨ���ο���ȡ��Ʊ��ĺ���//�� 
void exit_terminal();// �˳�����ĺ���//�� 

//տ���� 
extern int main() {
    // ����������������
    // ����ʼʱִ����֤
    authentication();
    
    // ������ѭ��
    while(1) {
        // ��ʾ����ѡ��
        options();
        
        // �����û�ѡ��ִ����Ӧ����
        switch(getch()) {
            case '1':
                bookticket();
                break;
            case '2':
                list_booked_tickets();
                break;
            case '3':
                search_ticket();
                break;
            case '4':
                edit_ticket();
                break;
            case '5':
                cancel_ticket();
                break;
            case '6':
                exit_terminal();
                return 0; // �˳�����
            default:
                printf("��Чѡ�������ѡ��\n");
        }
    }
    return 0;
}

// �����û���֤�ĺ���
extern void authentication() {
    // �������
    char username[50], password[10], input;

    // �ı����̨�������������ɫ��ͨ�����������û�����
    system("COLOR 0E"); // �ı䱳��Ϊ��ɫ������Ϊǳ��ɫ 

    // �������Ա�Ϊ�û���֤�����ṩһ���ɾ�����ʼ��
    system("cls");

    // ��ӡ����¼ҳ�棬��ʾ�û������û���������
    printf("---------------------------------------------------------------\n");
    printf("************** |  ���ػ��� | ***************\n");
    printf("---------------------------------------------------------------\n");
    printf("\n\n\t\t\t| ��¼ҳ�� |\n\n");
    printf("\n\n\t\t| ��ȷ�û��������ص�һ���� |\n\n");
    printf("\n\n\t\t| ��ȷ���룺5201314 |\n\n");
    printf("\n\t\t�û���:\t");
    scanf("%s", &username);
    int pass = 0;
    printf("\n\n\t\t����:\t");

    // ѭ�����û���������
    while (1) {
        password[pass] = getch(); // ��ȡ��������
        if (password[pass] == 13) // ������� Enter �������ж�ѭ��
            break;
        else if (password[pass] == 8 && pass != 0) // ��������˸�������ڳ����в����˸��
        {
            printf("\b"); // ����һ���ַ�
            printf(" "); // ��ӡһ���ո������ǻ��˵��ַ�
            printf("\b"); // �ٴλ���һ���ַ���ʹ���ص�ԭ����λ��
            pass--; // ���������ַ����ĳ���
        }
        else
        {
            printf("*"); // ��������ʱ��ʾ*
            pass++; // ���������ַ����ĳ���
        }
    }
    password[pass] = '\0'; // ����ַ���������

    // ����û����������Ƿ���ȷ
    if (strcmp(username, "���ص�һ����") == 0 && strcmp(password, "5201314") == 0) {
        // ������ȷ��ִ�к�������
        pw_tries = 0; // �������볢�Դ���
        loader("loading"); // ��ʾ���ض���
        options(); // ��ʾ����ѡ��
    } else if (pw_tries == 3) { // ������Դ�������3��
        system("cls"); // ����
        system("COLOR 0C"); // �ı䱳��Ϊ��ɫ������Ϊǳ��ɫ
        printf("\t\t |---------------------------------------------------------------|\n");
        printf("\t\t |************** |  ��ӭ�������ػ���  | ***************|\n");
        printf("\t\t |---------------------------------------------------------------|\n");
        printf("\n\n\t\t\t\t\t  ��¼����\n\n");
        printf("\t|----------------------------------------------------------------------------------|\n");
        printf("\a\t\t\t\t���ѵ�¼ʧ�� 3 ��.\n\n"); // ��¼ʧ����Ϣ�����о�������
        printf("\t\t\t\t������ȷ���û���������\n\t\t\n");
        printf("\t|----------------------------------------------------------------------------------|\n");
        printf("\n\nEnter any key to exit.");
        getch(); // �ȴ�����
        exit(0); // �˳�����
    } else { // ����û������������
    	pw_tries++; // �������볢�Դ���
        system("cls"); // ����
        system("COLOR 0C"); // �ı䱳��Ϊ��ɫ������Ϊǳ��ɫ
        printf("---------------------------------------------------------------\n");
        printf("************** |  ��ӭ�������ػ��� | ***************\n");
        printf("---------------------------------------------------------------\n");
        printf("\n\n\t\t\t��¼����\n\n");
        printf("  |--------------------------------------------------------|\n");
        printf("\a\n\t     �û��������벻��ȷ!!!\n\n\t     �밴��Enter��������.\n\n"); // ������Ϣ�����о�������
        printf("  |--------------------------------------------------------|\n");
        input = getch(); // �ȴ�����
        if (input == 13) {
            main(); // �������������¿�ʼ
        } else {
            exit(0); // �˳�����
        }
    }
}
/*���� `authentication`�������������Ҫ��������֤�û�������û����������Ƿ���ȷ�������������������ϸ���ͣ�
1. ������ʼʱ��ʹ�� `system("COLOR 0E")` �������ı����̨�������������ɫ����ͨ�����������û����档
2. ʹ�� `system("cls")` �����������Ļ���Ա�Ϊ�û���֤�����ṩһ���ɾ�����ʼ�㡣
3. �������������ӡ����¼���棬��ʾ�û������û��������롣
4. ʹ�� `scanf("%s",&username)` ��������ȡ�û�������ʹ�� `getch()` ��������ȡ�������룬�Ա�����������Ļ����ʾ��
5. ����û��������붼�� "admin" �� "captcha"�����û��ɹ���¼����ʱ���������볢�Դ��� `pw_tries`�������� `loader("loading")` ������ʾ���ض�����Ȼ����� `options()` ������ʾ����ѡ�
6. ������볢�Դ����ﵽ3�Σ�����ʾ������Ϣ�������û��Ѿ������������Ȼ���˳�����
7. ����û�������������������볢�Դ��� `pw_tries`������ʾ������Ϣ�������û�������û��������벻��ȷ��Ȼ��ȴ��û�����������û����� Enter �����򷵻������� `main()`�����¿�ʼ����
*/ 

// ��ʾ���ض����ĺ���
void loader(char value[10]) {
    int loader;
    if (value == "loading") {
        printf("\n\n\n\n\t  ������...");
    } else if (value == "updating") {
        printf("\n\n\t\t������...");
    } else if (value == "deleting") {
        printf("\n\n\n\t\tɾ����...");
    } else if (value == "loggingout") {
        printf("\n\n\t\tע����...");
    }
    for (loader=1; loader<=25; loader++) {
        printf (".");
        Sleep(80); // ���ض����ӳ�
    }
}
/*`loader` �������ú���������ʾһ���򵥵ļ��ض����������������������ϸ���ͣ�
1. ��������һ���ַ������� `value`������������԰�����ͬ��ֵ����ָʾ���ض����������ġ����磬��� `value` ���� "loading"������ʾ "Loading..."��������� "updating"������ʾ "Updating..."���������ơ�
2. ��� `value` ���� "loading"�����ӡ "Loading..."��
3. ��� `value` ���� "updating"�����ӡ "Updating..."��
4. ��� `value` ���� "deleting"�����ӡ "Deleting..."��
5. ��� `value` ���� "loggingout"�����ӡ "Logging out..."��
6. ʹ��һ��ѭ������ѭ����1��25��ÿ��ѭ����ӡһ�� "." �ַ���Ȼ����ͣ80���롣���ѭ��ģ���˼��ع��̣�ͨ���ӳ�����������Ч����
*/ 

// ��ʾ����ѡ��ĺ���
void options()                                                                  //function to display options of program
{
	char choice;
	system("cls"); //to clear the screen
	system("COLOR 0B"); //changes bg to black and fg to light aqua
	printf("        ________                 __________ \n");
	printf("|\\   |  |          |       |     |        |     \n");
	printf("| \\  |  |_______   |       |     |        |        \n");
	printf("|  \\ |  |          |       |     |     \\  |        \n");
	printf("|   \\|  |_______   |_______|     |______\\_|             ���չ�˾...\n");
    printf("                                         \\  \n\n\n\n");
	printf("-------------------------- �������--------------------------\n\n\n");
	printf("1.	��Ʊ\n\n2.	�鿴��Ԥ������Ʊ�б�\n\n3.	ͨ���ο�������Ʊ����Ϣ\n\n"); //to print the options
	printf("4.	ͨ���ο��ű༭Ʊ������\n\n5.	ͨ���ο���ȡ��Ʊ��\n\n6.	�˳�ϵͳ\n\n\n");	
	printf("��������ѡ��.\n\n");
	choice: 
	choice = getch();
	switch(choice)
	{
		system("cls"); 
		case '1' : bookticket();
		break;
		case '2' : list_booked_tickets();
		break;
		case '3' : search_ticket();
		break;
		case '4' : edit_ticket();
		break;	
		case '5' : cancel_ticket();
		break;
		case '6' : exit_terminal();
		break;
		default: 
		printf ("\t\tѡ���ѡ����Ч�����ѡ���ᵽ��ѡ�\n\n���ٴ���������ѡ��\n");
		goto choice; //goes to choice 
	}
}
/*
`options` �������ú���������ʾ�����ѡ��˵��������������������ϸ���ͣ�
1. ������ʼʱ��ʹ�� `system("cls")` �����������Ļ���Ա�Ϊѡ��˵��ṩһ���ɾ�����ʼ�㡣
2. ʹ�� `system("COLOR 0B")` �������ı����̨�������������ɫ��ͨ�����������û����档
3. �������������ӡ������ѡ��Ĳ˵�������Ԥ��Ʊ�񡢲鿴��Ԥ����Ʊ���б�ͨ���ο�������Ʊ����Ϣ���༭Ʊ�����顢ȡ��Ʊ����˳�ϵͳ��
4. ʹ�� `getch()` �����ȡ�û�������ѡ��Ȼ��ʹ�� `switch` ����������û������롣
5. �����û������룬����������Ӧ�ĺ�����ִ����Ӧ�Ĳ������� `bookticket()` ����Ԥ��Ʊ��`list_booked_tickets()` ���ڲ鿴��Ԥ����Ʊ���б�`search_ticket()` ����ͨ���ο�������Ʊ����Ϣ��`edit_ticket()` ���ڱ༭Ʊ�����飬`cancel_ticket()` ����ȡ��Ʊ��`exit_terminal()` �����˳�ϵͳ��
6. ����û���������Ч��ѡ��������ʾ������Ϣ�������û�ֻ��ѡ���ᵽ��ѡ������û���������ѡ������û��ٴ�������Чѡ�������ظ���ʾ������Ϣ��ֱ���û�������Ч��ѡ��Ϊֹ��
*/

// ͨ���ο�������Ʊ��ĺ���
void search_ticket() {
    system("cls"); // ����
    system("COLOR 0E"); // �ı䱳����ɫ
    fp = fopen("ticket_details.txt", "r"); // ���ļ����ڶ�ȡ
    if (fp == NULL) { // ����ļ��Ƿ�Ϊ��
        printf("\t\t\t\t��û�л�Ʊ��Ԥ��.");
        getch(); // �ȴ�����
        options(); // ����ѡ��˵�
        return; // ��������
    }
    int ref_no, p, j = 1;
    printf("---------------------------------------------------------------------------------------------\n");
    printf("*****************************  | ���ο��������Ʊ֤ |  *****************************\n");
    printf("---------------------------------------------------------------------------------------------\n\n\n");
    printf("����ο����: \t");
    scanf("%d", &ref_no);
    while (1) { // ѭ����ȡ�ļ�����
        end_of_file = fscanf(fp, "%d %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].name, &booking[j].num,
        booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
        if (end_of_file == -1) { // �ļ�����
            break;
        }
        j++;
    }
    fclose(fp); // �ر��ļ�
    for (p = 1; p < j; p++) { // ѭ���������Ĳο���
        if (booking[p].refno == ref_no) { // �ҵ�ƥ��Ĳο���
            printf("\n\n\n�ο���\t\t:\t%d\n\n����\t\t:\t%s\n\n�绰����\t:\t%lli\n\n������\t\t:\t%s\n\n",
            booking[p].refno, booking[p].name, booking[p].num, booking[p].dep);
            printf("Ŀ�ĵ�\t\t:\t%s\n\n����ʱ��\t:\t%s\n\n����ʱ��\t:\t%s\n\n��λ����\t:\t%d",
            booking[p].des, booking[p].deptime, booking[p].destime, booking[p].noofseats);
            getch(); // �ȴ�����
            options(); // ����ѡ��˵�
            return; // ��������
        }
    }
    printf("\n��ȷ��������Ĳο��������Ʊ�б���.\n"); // δ�ҵ�ƥ��Ĳο���
    getch(); // �ȴ�����
    options(); // ����ѡ��˵�
}
/*
 `search_ticket` �������ú�������ͨ���ο�������Ʊ����Ϣ�������������������ϸ���ͣ�
1. ������ʼʱ��ʹ�� `system("cls")` �����������Ļ���Ա�Ϊ����Ʊ������ṩһ���ɾ�����ʼ�㡣
2. ʹ�� `system("COLOR 0E")` �������ı����̨�������������ɫ��ͨ�����������û����档
3. �� `ticket_details.txt` �ļ��Զ�ȡģʽ������ļ�Ϊ�գ���ʾһ����Ϣ������ѡ��˵���
4. ��ʾ�û�����Ҫ������Ʊ��ο��š�
5. ѭ����ȡ�ļ����ݣ���Ʊ���¼�洢�� `booking` �����С�
6. �ر��ļ���
7. ѭ���������Ĳο��ţ�����ҵ�ƥ��ļ�¼�����ӡ��Ʊ����Ϣ��
8. ����ѡ��˵���

*/

//���� 
// ����Ԥ��Ʊ��ĺ���
void bookticket() {
    // �������
    int j, digits_in_num;
	char request, ans;
	book_ticket:
	j=1;
    // �������ı䱳����ɫ
    system("cls");
    system("COLOR 0E"); // �ı䱳����ɫΪ��ɫ������Ϊǳ��ɫ
    // ���ļ��Զ�ȡ����Ʊ���¼�������ļ���׷���¼�¼
    fp = fopen("ticket_details.txt", "r"); // ���ļ��Զ�ȡģʽ
    while (fp != NULL) { // ѭ����ȡ�ļ�����
        end_of_file = fscanf(fp, "%d %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].name, &booking[j].num,
        booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
        if (end_of_file == -1) { // �ļ�����
            break; // ����ѭ��
        }
        j++; // ���Ӽ�¼��
    }
    fclose(fp); // �ر��ļ�
    // ���ļ���׷��ģʽ
    fp = fopen("ticket_details.txt", "a+");
    // ��ʾ�û�����Ԥ��Ʊ�����ϸ��Ϣ
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("**********************************   |   �ڶ��ػ���Ԥ����Ʊ  |   *********************************\n");
    printf("----------------------------------------------------------------------------------------------------------------\n\n\n");
    printf("��������������:\n\n");
    printf("\n����:\t");
    scanf("%s", booking[i].name); // �����ÿ͵�����
    enter_number:
    printf("\n��ϵ�绰��ʮλ����:\t");
    scanf("%lli", &booking[i].num); // �����ÿ͵���ϵ�绰
    digits_in_num = count_digits_in_num(booking[i].num); // ������ϵ�绰��λ��
    if (digits_in_num != 10) { // �����ϵ�绰�Ƿ�Ϊ10λ��
        printf("\t\t������Ч����������ȷ����ϵ����.");
        goto enter_number; // ��ת��������ϵ�绰��ѭ��
    }
    // �����µĲο���
    booking[i].refno = booking[j-1].refno + 1;
    // ��������غ�Ŀ�ĵ�
    dep_des:
    printf("\n�������ĳ����غ�Ŀ�ĵ�\n\t\t\n");
    printf("\t ����\n\t �Ϻ�\n\t ���\n\t ����\n\n");
    printf("������  -\t");
    scanf("%s", booking[i].dep);
    printf("Ŀ�ĵ�  -\t");
    scanf("%s", booking[i].des);
    // �������غ�Ŀ�ĵ��Ƿ���ͬ
    if (strcmp(booking[i].dep, booking[i].des) == 0) {
        printf ("������ĳ����غ�Ŀ�ĵ���ͬ�����ٴ����롣\n");
        goto dep_des; // ��ת��������������غ�Ŀ�ĵص�ѭ��
    }
    // �������غ�Ŀ�ĵ��Ƿ���Ч
    if ((strcmp(booking[i].dep, "����") != 0) && (strcmp(booking[i].dep, "�Ϻ�") != 0) && (strcmp(booking[i].dep, "���") != 0) && (strcmp(booking[i].dep, "����") != 0)) {
        printf("\n����ĳ����ػ�Ŀ�ĵس���");
        goto dep_des; // ��ת��������������غ�Ŀ�ĵص�ѭ��
    }
    if ((strcmp(booking[i].des, "����") != 0) && (strcmp(booking[i].des, "�Ϻ�") != 0) && (strcmp(booking[i].des, "���") != 0) && (strcmp(booking[i].des, "����") != 0)) {
        printf("\n����ĳ����ػ�Ŀ�ĵس���");
        goto dep_des; // ��ת��������������غ�Ŀ�ĵص�ѭ��
    }
    // ��ʾ������Ϣ
    system("cls");
    printf ("----------------------------------------------------------------------------------------------------------------\n");
    printf ("****************************************   |  ������Ϣȷ�� |   ****************************************\n");
    printf ("----------------------------------------------------------------------------------------------------------------\n\n\n");
    printf("\nDear %s,\n\t���ĺ������ %d.\n\n��������Ҫ�󣬺���ʱ����:\n", booking[i].name, booking[i].refno);
    flight_time(booking[i].dep, booking[i].des);
    printf("\n���ʱ��:\t%s\n����ʱ��:\t%s\n", booking[i].deptime, booking[i].destime);
    // ȷ��Ʊ����Ϣ
    ticket_confirmation:
    printf("\n\n��ȷ�����Ļ�Ʊ�𣿣�����'y'��'n'��\t");
    scanf(" %c", &request);
    if (request == 'Y' || request == 'y') {
        // Ԥ����λ��
        no_of_tickets:
        printf("\n ����Ԥ��������λ?\t");
        scanf("%d", &booking[i].noofseats);
        if (booking[i].noofseats == 0) // ����Ƿ���Ԥ��0����λ
        {
            printf ("\n\t\t���޷�Ԥ��0��Ʊ�����ٴ�����Ʊ��.");
            goto no_of_tickets; // ��ת������������λ����ѭ��
        }
        printf("\n��ȷ��%d ����λ", booking[i].noofseats);
        // ��Ԥ����Ϣ׷�ӵ��ļ���
        fprintf (fp, "%d %s %lli %s %s %s %s %d\n", booking[i].refno, booking[i].name, booking[i].num, booking[i].dep,
        booking[i].des, booking[i].deptime, booking[i].destime, booking[i].noofseats);
        fclose(fp); // �ر��ļ�
    } else if (request == 'N' || request == 'n') {
        // ���ȡ��ȷ�ϣ��򷵻�ѡ��˵�
        printf("\n\n\t\t������3���ڱ��ض���ѡ��ҳ��.");
        sleep(3); // �ȴ�3��
        options();
    } else {
        // ���������Ч��������ȷ��
        printf("\nEnter either Y or N.\n���ٴ���������ȷ��.");
        goto ticket_confirmation; // ��ת������ȷ�ϵ�ѭ��
    }
    // ѯ���û��Ƿ���Ҫ����Ԥ��
    more_data:
    printf ("\n\n���Ƿ���Ҫ����Ԥ��?������'y'��'n'��\t");
    scanf (" %c", &ans);
    if (ans == 'y' || ans == 'Y') {
        // �����Ҫ����Ԥ�����򷵻غ�����ʼ
        goto book_ticket; // ��ת����ʼԤ����ѭ��
    } else if (ans == 'n' || ans == 'N') {
        // �������Ҫ����Ԥ�����򱣴����ݲ�����ѡ��˵�
        printf("\n �����ѳɹ�����.\n\n\t\t�����������ѡ��ҳ...");
        getch(); // �ȴ�����
    } else {
        // ���������Ч��������ѯ��
        printf("\nEnter either Y or N.\n���ٴ���������ȷ����Ϣ.");
        goto more_data; // ��ת������ѯ�ʵ�ѭ��
    }
    options(); // ����ѡ��˵�
}

/*
 `bookticket` �������ú�������Ԥ��Ʊ�������������������ϸ���ͣ�
1. ������ʼʱ��ʹ�� `system("cls")` �����������Ļ���Ա�ΪԤ��Ʊ������ṩһ���ɾ�����ʼ�㡣
2. ʹ�� `system("COLOR 0E")` �������ı����̨�������������ɫ��ͨ�����������û����档
3. ���ļ� `ticket_details.txt` �Զ�ȡ����Ʊ���¼�������ļ���׷���¼�¼��
4. ��ȡ `ticket_details.txt` �ļ��е�Ʊ���¼���������Ǵ洢�� `booking` �����С�����ļ�������������ѭ����
5. �ر��ļ���
6. ��ʾ�û�����Ԥ��Ʊ�����ϸ��Ϣ��������������ϵ��ʽ�������غ�Ŀ�ĵء�
7. ����������ϵ��ʽ�Ƿ�Ϊ10λ����������ǣ�����ʾ�û��������롣
8. �����µĲο��ţ�����ʾ�û���������غ�Ŀ�ĵء�
9. �������غ�Ŀ�ĵ��Ƿ���ͬ������ǣ�����ʾ�û��������롣
10. �������غ�Ŀ�ĵ��Ƿ���Ч��������ǣ�����ʾ�û��������롣
11. ѯ���û��Ƿ�ȷ��Ԥ�������ȷ�ϣ�����Ԥ������Ϣ׷�ӵ� `ticket_details.txt` �ļ��У����ر��ļ���
12. ѯ���û��Ƿ���Ҫ����Ԥ���������Ҫ���򷵻� `bookticket` ���������¿�ʼԤ�����̡�
*/

// ���������е�λ���ĺ���
int count_digits_in_num(long long number) {
    int digits_in_num = 0;
    while (number != 0) {
        number = number / 10;
        digits_in_num++;
    }
    return digits_in_num;
}
//��������Ĺ���ԭ����ͨ�����ϵؽ���������ֳ���10��Ȼ��ݼ���ֱ�����ֱ�Ϊ0��ÿ�γ���10���൱���Ƴ����ֵ����һλ����ˣ��ݼ��Ĵ����������ֵ�λ���� 

// ��ʾ����Ԥ����Ʊ��ĺ���
void list_booked_tickets() {
    system("cls"); // ����
    system("COLOR 0E"); // �ı䱳����ɫ
    fp = fopen("ticket_details.txt", "r"); // ���ļ����ڶ�ȡ
    if (fp == NULL) { // ����ļ��Ƿ�Ϊ��
        printf("\t\t\t\t��û��Ʊ yet.");
        getch(); // �ȴ�����
        options(); // ����ѡ��˵�
        return; // ��������
    }
    int j = 1;
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("******************************************   LIST OF BOOKED TICKETS   ******************************************\n");
    printf("----------------------------------------------------------------------------------------------------------------\n\n\n");
    printf("�ο���\t| ����\t\t| �绰����\t| ������\t| Ŀ�ĵ�\t| ����ʱ��\t| ����ʱ��\t| ��λ����\n");
    printf("----------------------------------------------------------------------------------------------------------------\n\n");
    while (1) { // ѭ����ȡ�ļ�����
        end_of_file = fscanf(fp, "%d %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].name, &booking[j].num,
        booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
        if (end_of_file == -1) { // �ļ�����
            break;
        }
        printf("   %d\t| %s\t\t| %lli\t| %s\t\t| %s\t\t| %s\t| %s\t|\t%d\n\n", booking[j].refno,booking[j].name, booking[j].num,
        booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, booking[j].noofseats);
        j++;
    }
    fclose(fp); // �ر��ļ�
    getch(); // �ȴ�����
    options(); // ����ѡ��˵�
}
/* `list_booked_tickets` �������ú���������ʾ������Ԥ����Ʊ����Ϣ�������������������ϸ���ͣ�
1. ������ʼʱ��ʹ�� `system("cls")` �����������Ļ���Ա�Ϊ��ʾƱ���б�����ṩһ���ɾ�����ʼ�㡣
2. ʹ�� `system("COLOR 0E")` �������ı����̨�������������ɫ��ͨ�����������û����档
3. �� `ticket_details.txt` �ļ��Զ�ȡģʽ������ļ�Ϊ�գ���ʾһ����Ϣ������ѡ��˵���
4. ��ӡ��Ʊ���б�ı��⡣
5. ѭ����ȡ�ļ����ݣ���Ʊ���¼�洢�� `booking` �����У�����ӡ��ÿ����¼����Ϣ��
6. �ر��ļ���
7. �ȴ��û�������
8. ����ѡ��˵���
*/ 


// ͨ���ο��ű༭Ʊ��ĺ���
void edit_ticket()                                                             
{
	int digits_in_num;
	system ("cls");
	system ("COLOR 0E");
	printf ("---------------------------------------------------------------------------------------------\n");
	printf ("******************************  | ͨ���ο��ű༭Ʊ�� |  ******************************\n");
	printf ("---------------------------------------------------------------------------------------------\n\n\n");
	fp = fopen ("ticket_details.txt", "r+"); //open file pointer in read+ mode
	if (fp == NULL) //condition to check if file is empty and displpay msg accordingly
	{
		printf ("\t\t\t\t ��û�ж�Ʊ.");
		getch();
		options();
	}
	int ref_no, j=1, p, d;
	while (1)
	{
		end_of_file = fscanf (fp,"%d %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].name, &booking[j].num, 
		booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
		if (end_of_file == -1){break;} //breaks loop at the end of file
		j++;
	}
	
	printf ("����Ҫ�༭�Ĳο����: \t");
	scanf("%d", &ref_no);

	rewind(fp); //to put the cursor in the beginning of file
	for (p=1; p<j; p++)
	{
		if (booking[p].refno == ref_no)
		{
			printf ("\n\n����\t[Old data: %s ]:\t", booking[p].name);
			scanf ("%s", booking[p].name);
			enter_number:
			printf ("\n�绰����\t[Old data: %lli ]:\t", booking[p].num);
			scanf ("%lli", &booking[p].num);
			digits_in_num = count_digits_in_num (booking[p].num); //calling of count_digits_in_num function 
			if (digits_in_num != 10) //condition if input number is of 10 digits or not
			{
				printf ("\t\t ������Ч����������ȷ����ϵ����.");
				goto enter_number; //goes to line number 459
			}
				
			dep_des:
			printf("\n�������ĳ����غ�Ŀ�ĵ�λ��.\n\t\tType\n");
			printf("\t ����\n\t �Ϻ�\n\t ���\n\t ����\n\n");
			printf ("������\t[Old data: %s ]:\t", booking[p].dep);
			scanf ("%s", booking[p].dep);
			printf ("Ŀ�ĵ�\t[Old data: %s ]:\t", booking[p].des);
			scanf ("%s", booking[p].des);
			if (strcmp(booking[p].dep, booking[p].des) == 0)
			{
				printf ("����������ͬ�ĳ����غ�Ŀ�ĵء����ٴ����롣\n");
				goto dep_des; //goes to line number 469
			}
			if ((strcmp(booking[p].dep,"����")!=0)&&(strcmp(booking[p].dep,"�Ϻ�")!=0)&&(strcmp(booking[p].dep,"���")!=0)&&(strcmp(booking[p].dep,"����")!=0))
			{
				printf("\n��Ч�ĳ����ػ�Ŀ�ĵ�.");
				goto dep_des; //goes to line number 469
			}
			if ((strcmp(booking[p].des,"����")!=0)&&(strcmp(booking[p].des,"�Ϻ�")!=0)&&(strcmp(booking[p].des,"���")!=0)&&(strcmp(booking[p].des,"����")!=0))
			{
				printf("\n��Ч�ĳ����ػ�Ŀ�ĵ�.");
				goto dep_des; //goes to line number 469
			}
			fflush(stdin);
			no_of_tickets:
			printf ("\nƱ��\t[Old data: %d ]:\t", booking[p].noofseats);
			scanf ("%d", &booking[p].noofseats);
			if (booking[p].noofseats == 0) 
			{ 
			printf ("\t\t���޷�Ԥ��0��Ʊ�����ٴ�����Ʊ��\n"); 
			goto no_of_tickets;
			}
			printf("\n\nDear %s,\n\t ��������Ҫ���µĺ���ʱ����:",booking[p].name);
			flight_time(booking[p].dep, booking[p].des);
			strcpy (booking[p].deptime, booking[i].deptime);
			strcpy (booking[p].destime, booking[i].destime);
			printf("\n����ʱ��:\t%s\n����ʱ��:\t%s\n\n", booking[p].deptime, booking[p].destime);
			loader("updating");
			printf ("\n\n�������ѳɹ�����.");
			
			for (p=1; p<j; p++)
			{
				fprintf (fp, "%d %s %lli %s %s %s %s %d\n",booking[p].refno, booking[p].name, booking[p].num, 
				booking[p].dep, booking[p].des, booking[p].deptime, booking[p].destime, booking[p].noofseats);
			}
			fclose (fp);
			getch();
			options();
		}
	}
	
	
	printf ("�������ѳɹ�����\nc.\n"); //message to display if the ref no is not found
	getch();
	options();
}

//������������������ı䱳����ɫ��Ȼ���Ʊ����Ϣ�ļ�������ļ�Ϊ�գ�������ʾһ����Ϣ������ѡ��˵�������ļ�����Ʊ����Ϣ�����������û�����һ���ο������༭��Ӧ��Ʊ�� 
/* `edit_ticket` �������ú�������ͨ���ο��ű༭Ʊ����Ϣ�������������������ϸ���ͣ�
1. ������ʼʱ��ʹ�� `system("cls")` �����������Ļ���Ա�Ϊ�༭Ʊ������ṩһ���ɾ�����ʼ�㡣
2. ʹ�� `system("COLOR 0E")` �������ı����̨�������������ɫ��ͨ�����������û����档
3. �� `ticket_details.txt` �ļ��Զ�ȡ��д��ģʽ������ļ�Ϊ�գ���ʾһ����Ϣ������ѡ��˵���
4. ��ʾ�û�����Ҫ�༭��Ʊ��ο��š�
5. ���ļ�ָ�����¶�λ���ļ���ʼ������ȡƱ���¼��
6. ѭ���������Ĳο��ţ�����ҵ�ƥ��ļ�¼������ʾ�û������µ�Ʊ����Ϣ������������ϵ��ʽ�������غ�Ŀ�ĵصȡ�
7. ��֤�������ϵ��ʽ�Ƿ�Ϊ10λ����������ǣ�����ʾ�û��������롣
8. �������غ�Ŀ�ĵ��Ƿ���ͬ������ǣ�����ʾ�û��������롣
9. �������غ�Ŀ�ĵ��Ƿ���Ч��������ǣ�����ʾ�û��������롣
10. ѯ���û��Ƿ�ȷ�ϸ���Ʊ����Ϣ�����ȷ�ϣ����µ�Ʊ����Ϣд�� `ticket_details.txt` �ļ��У����ر��ļ���
11. ��ʾ���³ɹ�����Ϣ������ʾ���ض�����
12. ����ѡ��˵���
 */ 



//�񶫲� 
// ���ݳ����غ�Ŀ�ĵ��ṩ����ʱ��ĺ���
void flight_time(char dep[3], char des[3]) {
    if (strcmp(dep, "����") == 0) {
        if (strcmp(des, "�Ϻ�") == 0) {
            strcpy(booking[i].deptime, "06:00am");
            strcpy(booking[i].destime, "06:30am");
        } else if (strcmp(des, "���") == 0) {
            strcpy(booking[i].deptime, "09:20am");
            strcpy(booking[i].destime, "10:15am");
        } else if (strcmp(des, "����") == 0) {
            strcpy(booking[i].deptime, "11:40pm");
            strcpy(booking[i].destime, "12:30pm");
        }
    } else if (strcmp(dep, "�Ϻ�") == 0) {
        if (strcmp(des, "����") == 0) {
            strcpy(booking[i].deptime, "01:20am");
            strcpy(booking[i].destime, "01:50am");
        } else if (strcmp(des, "���") == 0) {
            strcpy(booking[i].deptime, "02:35pm");
            strcpy(booking[i].destime, "04:40pm");
        } else if (strcmp(des, "����") == 0) {
            strcpy(booking[i].deptime, "07:00am");
            strcpy(booking[i].destime, "08:05am");
        }
    } else if (strcmp(dep, "���") == 0) {
        if (strcmp(des, "����") == 0) {
            strcpy(booking[i].deptime, "10:25am");
            strcpy(booking[i].destime, "11:20am");
        } else if (strcmp(des, "�Ϻ�") == 0) {
            strcpy(booking[i].deptime, "10:45am");
            strcpy(booking[i].destime, "12:50am");
        } else if (strcmp(des, "����") == 0) {
            strcpy(booking[i].deptime, "05:10pm");
            strcpy(booking[i].destime, "07:30pm");
        }
    } else if (strcmp(dep, "����") == 0) {
        if (strcmp(des, "����") == 0) {
            strcpy(booking[i].deptime, "08:00pm");
            strcpy(booking[i].destime, "08:50pm");
        } else if (strcmp(des, "�Ϻ�") == 0) {
            strcpy(booking[i].deptime, "01:00pm");
            strcpy(booking[i].destime, "02:05pm");
        } else if (strcmp(des, "���") == 0) {
            strcpy(booking[i].deptime, "08:35am");
            strcpy(booking[i].destime, "09:55am");
        }
    } else {
        printf("�����ػ�Ŀ�ĵ���Ч");
    }
}
/*
`flight_time` �������ú������ڸ��ݳ����غ�Ŀ�ĵ��ṩ����ʱ�䡣�����������������ϸ���ͣ�
1. �������������ַ������� `dep` �� `des`���ֱ��ʾ�����غ�Ŀ�ĵء�
2. ʹ�� `strcmp` �����Ƚ� `dep` �� `des` ��������ȷ������ĳ����غ�Ŀ�ĵء�
3. ���ݲ�ͬ�ĳ����غ�Ŀ�ĵ���ϣ������ṩ��Ӧ�ĺ���ʱ�䡣���磬����� ���� ������ �Ϻ����򺽰�ʱ��Ϊ 06:00am �� 06:30am��
4. ��������ػ�Ŀ�ĵ���Ч��������Ԥ������б��У�����������ӡһ��������Ϣ�������û�����ĳ����ػ�Ŀ�ĵ���Ч��
*/ 

// ͨ���ο���ȡ��Ʊ��ĺ���
void cancel_ticket() {
    char confirmation;
	system("cls"); // ����
    system("COLOR 0E"); // �ı䱳����ɫ
    fp = fopen("ticket_details.txt", "r+"); // ���ļ����ڶ�ȡ��д��
    if (fp == NULL) { // ����ļ��Ƿ�Ϊ��
        printf("\t\t\t\tδ���ڶ�Ʊ��");
        getch(); // �ȴ�����
        options(); // ����ѡ��˵�
        return; // ��������
    }
    int ref_no, j = 1, p, d;
    while (1) { // ѭ����ȡ�ļ�����
        end_of_file = fscanf(fp, "%d %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].name, &booking[j].num,
        booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
        if (end_of_file == -1) { // �ļ�����
            break;
        }
        j++;
    }
    printf("����Ҫȡ���Ĳο���: \t");
    scanf("%d", &ref_no);
    for (p=1; p<j; p++) //loop to find the entered ref number
		{
			if (booking[p].refno == ref_no) //condition when ref number is found
			{	
				printf("\n\n��ȷ��Ҫɾ��%d��Ʊ֤��ϸ��Ϣ��(����'y'��'n')\t", ref_no); //cancellation confirmation
				scanf (" %c", &confirmation);
				if ( confirmation == 'Y' || confirmation == 'y')
				{
					for (d=p; d<j; d++) //loop to replace the index number of entered ref number with preceeding structure
					{
						booking[d] = booking[d+1]; //preceeding structure replaces the place of the previous one
					}
					j--;
					loader("deleting"); //deleting animation
					printf ("\n\n\n�����ѳɹ�ɾ��.");
				
					fp = fopen ("ticket_details.txt", "w"); //to write the updated information after deletion in file
					for (p=1; p<j; p++)
					{
						fprintf (fp, "%d %s %lli %s %s %s %s %d\n", booking[p].refno, booking[p].name, booking[p].num, 
						booking[p].dep, booking[p].des, booking[p].deptime, booking[p].destime, booking[p].noofseats);
					}
					fclose (fp); //closes file pointer
					getch();
					options();
				}
				else if ( confirmation == 'N' || confirmation == 'n')
				{
					printf("\n\n\t\t������ 3 ���ڻص�ѡ��ҳ��.");
					sleep(3); //to wait for 3 seconds before executing the option function
					options();	
				}
				else 
				{
					printf ("\n\n�����롰Y����N������ȷ��.");
				}
			}
		}
	
    printf("\n��ȷ��������Ĳο�����Ʊ֤�б��С�\n"); // δ�ҵ�ƥ��Ĳο���
    getch(); // �ȴ�����
    options(); // ����ѡ��˵�
}
/*
 `cancel_ticket` �������ú�������ͨ���ο���ȡ��Ʊ�������������������ϸ���ͣ�
1. ������ʼʱ��ʹ�� `system("cls")` �����������Ļ���Ա�Ϊȡ��Ʊ������ṩһ���ɾ�����ʼ�㡣
2. ʹ�� `system("COLOR 0E")` �������ı����̨�������������ɫ��ͨ�����������û����档
3. �� `ticket_details.txt` �ļ��Զ�ȡ��д��ģʽ������ļ�Ϊ�գ���ʾһ����Ϣ������ѡ��˵���
4. ��ʾ�û�����Ҫȡ����Ʊ��ο��š�
5. ���ļ�ָ�����¶�λ���ļ���ʼ������ȡƱ���¼��
6. ѭ���������Ĳο��ţ�����ҵ�ƥ��ļ�¼������ʾһ����Ϣ��ʾƱ���ѳɹ�ȡ�����������ļ��е�Ʊ����Ϣ��
7. ����ѡ��˵���
*/ 

// �˳�����ĺ���
void exit_terminal() {
    system("cls"); // ����
    system("COLOR 0E"); // �ı䱳����ɫ
    printf("---------------------------------------------------------------------------------------------\n");
    printf("********************************************* | �˳����� | *********************************************\n");
    printf("---------------------------------------------------------------------------------------------\n\n\n");
    printf("��л��ʹ�ö�Ʊϵͳ���ټ���\n");
    getch(); // �ȴ�����
    // �ر����д򿪵��ļ�
    fclose(fp);
    // �˳�����
    exit(0);
}
/* 
 `exit_terminal` �������ú��������˳����������������������ϸ���ͣ�
1. ������ʼʱ��ʹ�� `system("cls")` �����������Ļ���Ա�Ϊ�˳���������ṩһ���ɾ�����ʼ�㡣
2. ʹ�� `system("COLOR 0E")` �������ı����̨�������������ɫ��ͨ�����������û����档
3. ��ʾһ����л��Ϣ�������û����򼴽��˳���
4. �ȴ��û�������
5. �ر����д򿪵��ļ��������ļ�ָ�� `fp`��
6. ʹ�� `exit(0)` �����˳�����
*/ 
