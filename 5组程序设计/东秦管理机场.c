#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <unistd.h>
#include <process.h>
/*几个常用的C语言标准库头文件：
1. `<stdio.h>`: 标准输入输出头文件，包含了用于文件操作、输入输出、错误处理等功能的函数声明。例如，`printf`、`scanf`、`fopen`、`fclose` 等函数都定义在这个头文件中。
2. `<string.h>`: 字符串处理头文件，包含了用于处理字符串（如字符串复制、连接、比较等）的函数声明。例如，`strcpy`、`strcmp`、`strlen` 等函数都定义在这个头文件中。
3. `<conio.h>`: 控制台输入输出头文件，包含了在控制台环境中使用的函数，如`getch()`，这些函数在标准输入输出库中通常不提供。
4. `<unistd.h>`: 统一系统调用头文件，包含了与系统调用相关的函数声明，如`sleep`。
5. `<process.h>`: 进程控制头文件，包含了与进程控制相关的函数声明，如`exit`。
*/
 
// 定义全局变量
FILE *fp;
int i, end_of_file, pw_tries=0;
/*声明了几个全局变量：
1. `FILE *fp`: 这是一个文件指针，用于指向打开的文件。在C语言中，文件操作通常需要使用文件指针。这个指针在程序的不同部分被用来读取或写入文件。
2. `int i`: 这是一个整型变量，通常用于循环控制或其他计数操作。在您提供的代码片段中，它没有被明确地用于任何特定的功能，但可能被用于数组索引或其他用途。
3. `int end_of_file`: 这是一个整型变量，通常用于文件操作中。当文件读取操作到达文件末尾时，这个变量会被设置为特定值（如-1），以指示文件结束。
4. `int pw_tries=0`: 这是一个整型变量，用于跟踪用户尝试登录的次数。这个变量在用户认证函数中使用，以限制用户尝试登录的次数。
*/ 

// 结构体定义
struct variables {
    char name[10], dep[16], des[16], deptime[8], destime[8];
    long long num;
    int refno, noofseats;
}booking[25];
/* `struct variables` 结构体，用于存储与票务相关的数据。这个结构体包含以下字段：
- `name`: 旅客的姓氏，长度为16个字符。
- `dep`: 出发地，长度为4个字符。
- `des`: 目的地，长度为4个字符。
- `deptime`: 出发时间，长度为8个字符。
- `destime`: 到达时间，长度为8个字符。
- `num`: 旅客的联系电话，长度为10个数字。
- `refno`: 票务参考号。
- `noofseats`: 预订的座位数。
这个结构体被声明为数组 `booking[25]`，意味着可以存储25个票务记录。每个记录包含上述字段，用于存储单个旅客的票务信息。
*/ 

// 函数声明
extern void authentication();// 用于用户认证的函数//湛 
extern void loader(char value[10]);// 显示加载动画的函数//湛 
extern void options();// 显示程序选项的函数//湛 
extern void bookticket();// 用于预订票务的函数 //凌 
extern int count_digits_in_num(long long number);// 计算数字中的位数的函数//凌 
extern void flight_time(char dep[3], char des[3]);// 根据出发地和目的地提供航班时间的函数//柴 
extern void list_booked_tickets();// 显示所有预订的票务的函数//凌 
extern void search_ticket();// 通过参考号搜索票务的函数//湛 
extern void edit_ticket();// 通过参考号编辑票务的函数//凌 
extern void cancel_ticket();// 通过参考号取消票务的函数//柴 
void exit_terminal();// 退出程序的函数//柴 

//湛传斌 
extern int main() {
    // 主函数：程序的入口
    // 程序开始时执行认证
    authentication();
    
    // 进入主循环
    while(1) {
        // 显示程序选项
        options();
        
        // 根据用户选择执行相应操作
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
                return 0; // 退出程序
            default:
                printf("无效选项，请重新选择。\n");
        }
    }
    return 0;
}

// 用于用户认证的函数
extern void authentication() {
    // 定义变量
    char username[50], password[10], input;

    // 改变控制台背景和字体的颜色，通常用于美化用户界面
    system("COLOR 0E"); // 改变背景为黑色，字体为浅黄色 

    // 清屏，以便为用户认证界面提供一个干净的起始点
    system("cls");

    // 打印出登录页面，提示用户输入用户名和密码
    printf("---------------------------------------------------------------\n");
    printf("************** |  东秦机场 | ***************\n");
    printf("---------------------------------------------------------------\n");
    printf("\n\n\t\t\t| 登录页面 |\n\n");
    printf("\n\n\t\t| 正确用户名：东秦第一深情 |\n\n");
    printf("\n\n\t\t| 正确密码：5201314 |\n\n");
    printf("\n\t\t用户名:\t");
    scanf("%s", &username);
    int pass = 0;
    printf("\n\n\t\t密码:\t");

    // 循环让用户输入密码
    while (1) {
        password[pass] = getch(); // 获取密码输入
        if (password[pass] == 13) // 如果按下 Enter 键，则中断循环
            break;
        else if (password[pass] == 8 && pass != 0) // 如果按下退格键，则在程序中操作退格键
        {
            printf("\b"); // 回退一个字符
            printf(" "); // 打印一个空格来覆盖回退的字符
            printf("\b"); // 再次回退一个字符，使光标回到原来的位置
            pass--; // 减少密码字符串的长度
        }
        else
        {
            printf("*"); // 输入密码时显示*
            pass++; // 增加密码字符串的长度
        }
    }
    password[pass] = '\0'; // 添加字符串结束符

    // 检查用户名和密码是否正确
    if (strcmp(username, "东秦第一深情") == 0 && strcmp(password, "5201314") == 0) {
        // 密码正确，执行后续操作
        pw_tries = 0; // 重置密码尝试次数
        loader("loading"); // 显示加载动画
        options(); // 显示程序选项
    } else if (pw_tries == 3) { // 如果尝试次数超过3次
        system("cls"); // 清屏
        system("COLOR 0C"); // 改变背景为黑色，字体为浅红色
        printf("\t\t |---------------------------------------------------------------|\n");
        printf("\t\t |************** |  欢迎来到东秦机场  | ***************|\n");
        printf("\t\t |---------------------------------------------------------------|\n");
        printf("\n\n\t\t\t\t\t  登录界面\n\n");
        printf("\t|----------------------------------------------------------------------------------|\n");
        printf("\a\t\t\t\t您已登录失败 3 次.\n\n"); // 登录失败信息，带有警告铃声
        printf("\t\t\t\t请检查正确的用户名和密码\n\t\t\n");
        printf("\t|----------------------------------------------------------------------------------|\n");
        printf("\n\nEnter any key to exit.");
        getch(); // 等待按键
        exit(0); // 退出程序
    } else { // 如果用户名或密码错误
    	pw_tries++; // 增加密码尝试次数
        system("cls"); // 清屏
        system("COLOR 0C"); // 改变背景为黑色，字体为浅红色
        printf("---------------------------------------------------------------\n");
        printf("************** |  欢迎来到东秦机场 | ***************\n");
        printf("---------------------------------------------------------------\n");
        printf("\n\n\t\t\t登录界面\n\n");
        printf("  |--------------------------------------------------------|\n");
        printf("\a\n\t     用户名或密码不正确!!!\n\n\t     请按“Enter”键重试.\n\n"); // 错误信息，带有警告铃声
        printf("  |--------------------------------------------------------|\n");
        input = getch(); // 等待按键
        if (input == 13) {
            main(); // 返回主函数重新开始
        } else {
            exit(0); // 退出程序
        }
    }
}
/*函数 `authentication`。这个函数的主要功能是验证用户输入的用户名和密码是否正确。以下是这个函数的详细解释：
1. 函数开始时，使用 `system("COLOR 0E")` 命令来改变控制台背景和字体的颜色，这通常用于美化用户界面。
2. 使用 `system("cls")` 命令来清除屏幕，以便为用户认证界面提供一个干净的起始点。
3. 接下来，程序打印出登录界面，提示用户输入用户名和密码。
4. 使用 `scanf("%s",&username)` 命令来获取用户名，并使用 `getch()` 命令来获取密码输入，以避免密码在屏幕上显示。
5. 如果用户名和密码都是 "admin" 和 "captcha"，则用户成功登录。此时，重置密码尝试次数 `pw_tries`，并调用 `loader("loading")` 函数显示加载动画，然后调用 `options()` 函数显示程序选项。
6. 如果密码尝试次数达到3次，则显示错误信息，告诉用户已经三次输入错误，然后退出程序。
7. 如果用户名或密码错误，增加密码尝试次数 `pw_tries`，并显示错误信息，告诉用户输入的用户名或密码不正确。然后等待用户按键，如果用户按下 Enter 键，则返回主函数 `main()`，重新开始程序。
*/ 

// 显示加载动画的函数
void loader(char value[10]) {
    int loader;
    if (value == "loading") {
        printf("\n\n\n\n\t  加载中...");
    } else if (value == "updating") {
        printf("\n\n\t\t更新中...");
    } else if (value == "deleting") {
        printf("\n\n\n\t\t删除中...");
    } else if (value == "loggingout") {
        printf("\n\n\t\t注销中...");
    }
    for (loader=1; loader<=25; loader++) {
        printf (".");
        Sleep(80); // 加载动画延迟
    }
}
/*`loader` 函数，该函数用于显示一个简单的加载动画。以下是这个函数的详细解释：
1. 函数接受一个字符串参数 `value`，这个参数可以包含不同的值，以指示加载动画的上下文。例如，如果 `value` 包含 "loading"，则显示 "Loading..."；如果包含 "updating"，则显示 "Updating..."，依此类推。
2. 如果 `value` 包含 "loading"，则打印 "Loading..."。
3. 如果 `value` 包含 "updating"，则打印 "Updating..."。
4. 如果 `value` 包含 "deleting"，则打印 "Deleting..."。
5. 如果 `value` 包含 "loggingout"，则打印 "Logging out..."。
6. 使用一个循环，该循环从1到25，每次循环打印一个 "." 字符，然后暂停80毫秒。这个循环模拟了加载过程，通过延迟来创建动画效果。
*/ 

// 显示程序选项的函数
void options()                                                                  //function to display options of program
{
	char choice;
	system("cls"); //to clear the screen
	system("COLOR 0B"); //changes bg to black and fg to light aqua
	printf("        ________                 __________ \n");
	printf("|\\   |  |          |       |     |        |     \n");
	printf("| \\  |  |_______   |       |     |        |        \n");
	printf("|  \\ |  |          |       |     |     \\  |        \n");
	printf("|   \\|  |_______   |_______|     |______\\_|             航空公司...\n");
    printf("                                         \\  \n\n\n\n");
	printf("-------------------------- 管理面板--------------------------\n\n\n");
	printf("1.	订票\n\n2.	查看已预订的门票列表\n\n3.	通过参考号搜索票务信息\n\n"); //to print the options
	printf("4.	通过参考号编辑票务详情\n\n5.	通过参考号取消票务\n\n6.	退出系统\n\n\n");	
	printf("输入您的选择.\n\n");
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
		printf ("\t\t选择的选项无效。请仅选择提到的选项。\n\n请再次输入您的选择：\n");
		goto choice; //goes to choice 
	}
}
/*
`options` 函数，该函数用于显示程序的选项菜单。以下是这个函数的详细解释：
1. 函数开始时，使用 `system("cls")` 命令来清除屏幕，以便为选项菜单提供一个干净的起始点。
2. 使用 `system("COLOR 0B")` 命令来改变控制台背景和字体的颜色，通常用于美化用户界面。
3. 接下来，程序打印出程序选项的菜单，包括预订票务、查看已预订的票务列表、通过参考号搜索票务信息、编辑票务详情、取消票务和退出系统。
4. 使用 `getch()` 命令获取用户的输入选择，然后使用 `switch` 语句来处理用户的输入。
5. 根据用户的输入，程序会调用相应的函数来执行相应的操作，如 `bookticket()` 用于预订票务，`list_booked_tickets()` 用于查看已预订的票务列表，`search_ticket()` 用于通过参考号搜索票务信息，`edit_ticket()` 用于编辑票务详情，`cancel_ticket()` 用于取消票务，`exit_terminal()` 用于退出系统。
6. 如果用户输入了无效的选项，程序会显示错误信息，告诉用户只能选择提到的选项，并让用户重新输入选择。如果用户再次输入无效选项，程序会重复显示错误信息，直到用户输入有效的选项为止。
*/

// 通过参考号搜索票务的函数
void search_ticket() {
    system("cls"); // 清屏
    system("COLOR 0E"); // 改变背景颜色
    fp = fopen("ticket_details.txt", "r"); // 打开文件用于读取
    if (fp == NULL) { // 检查文件是否为空
        printf("\t\t\t\t还没有机票被预订.");
        getch(); // 等待按键
        options(); // 返回选项菜单
        return; // 函数结束
    }
    int ref_no, p, j = 1;
    printf("---------------------------------------------------------------------------------------------\n");
    printf("*****************************  | 按参考编号搜索票证 |  *****************************\n");
    printf("---------------------------------------------------------------------------------------------\n\n\n");
    printf("输入参考编号: \t");
    scanf("%d", &ref_no);
    while (1) { // 循环读取文件内容
        end_of_file = fscanf(fp, "%d %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].name, &booking[j].num,
        booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
        if (end_of_file == -1) { // 文件结束
            break;
        }
        j++;
    }
    fclose(fp); // 关闭文件
    for (p = 1; p < j; p++) { // 循环检查输入的参考号
        if (booking[p].refno == ref_no) { // 找到匹配的参考号
            printf("\n\n\n参考号\t\t:\t%d\n\n姓名\t\t:\t%s\n\n电话号码\t:\t%lli\n\n出发地\t\t:\t%s\n\n",
            booking[p].refno, booking[p].name, booking[p].num, booking[p].dep);
            printf("目的地\t\t:\t%s\n\n出发时间\t:\t%s\n\n到达时间\t:\t%s\n\n座位数量\t:\t%d",
            booking[p].des, booking[p].deptime, booking[p].destime, booking[p].noofseats);
            getch(); // 等待按键
            options(); // 返回选项菜单
            return; // 函数结束
        }
    }
    printf("\n请确保您输入的参考编号在门票列表中.\n"); // 未找到匹配的参考号
    getch(); // 等待按键
    options(); // 返回选项菜单
}
/*
 `search_ticket` 函数，该函数用于通过参考号搜索票务信息。以下是这个函数的详细解释：
1. 函数开始时，使用 `system("cls")` 命令来清除屏幕，以便为搜索票务界面提供一个干净的起始点。
2. 使用 `system("COLOR 0E")` 命令来改变控制台背景和字体的颜色，通常用于美化用户界面。
3. 打开 `ticket_details.txt` 文件以读取模式。如果文件为空，显示一条信息并返回选项菜单。
4. 提示用户输入要搜索的票务参考号。
5. 循环读取文件内容，将票务记录存储在 `booking` 数组中。
6. 关闭文件。
7. 循环检查输入的参考号，如果找到匹配的记录，则打印出票务信息。
8. 返回选项菜单。

*/

//凌勇 
// 用于预订票务的函数
void bookticket() {
    // 定义变量
    int j, digits_in_num;
	char request, ans;
	book_ticket:
	j=1;
    // 清屏并改变背景颜色
    system("cls");
    system("COLOR 0E"); // 改变背景颜色为黑色，字体为浅黄色
    // 打开文件以读取现有票务记录，并打开文件以追加新记录
    fp = fopen("ticket_details.txt", "r"); // 打开文件以读取模式
    while (fp != NULL) { // 循环读取文件内容
        end_of_file = fscanf(fp, "%d %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].name, &booking[j].num,
        booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
        if (end_of_file == -1) { // 文件结束
            break; // 跳出循环
        }
        j++; // 增加记录数
    }
    fclose(fp); // 关闭文件
    // 打开文件以追加模式
    fp = fopen("ticket_details.txt", "a+");
    // 提示用户输入预订票务的详细信息
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("**********************************   |   在东秦机场预订机票  |   *********************************\n");
    printf("----------------------------------------------------------------------------------------------------------------\n\n\n");
    printf("请输入以下详情:\n\n");
    printf("\n姓名:\t");
    scanf("%s", booking[i].name); // 输入旅客的姓氏
    enter_number:
    printf("\n联系电话（十位数）:\t");
    scanf("%lli", &booking[i].num); // 输入旅客的联系电话
    digits_in_num = count_digits_in_num(booking[i].num); // 计算联系电话的位数
    if (digits_in_num != 10) { // 检查联系电话是否为10位数
        printf("\t\t号码无效。请输入正确的联系号码.");
        goto enter_number; // 跳转到输入联系电话的循环
    }
    // 生成新的参考号
    booking[i].refno = booking[j-1].refno + 1;
    // 输入出发地和目的地
    dep_des:
    printf("\n输入您的出发地和目的地\n\t\t\n");
    printf("\t 北京\n\t 上海\n\t 天津\n\t 深圳\n\n");
    printf("出发地  -\t");
    scanf("%s", booking[i].dep);
    printf("目的地  -\t");
    scanf("%s", booking[i].des);
    // 检查出发地和目的地是否相同
    if (strcmp(booking[i].dep, booking[i].des) == 0) {
        printf ("您输入的出发地和目的地相同，请再次输入。\n");
        goto dep_des; // 跳转到重新输入出发地和目的地的循环
    }
    // 检查出发地和目的地是否有效
    if ((strcmp(booking[i].dep, "北京") != 0) && (strcmp(booking[i].dep, "上海") != 0) && (strcmp(booking[i].dep, "天津") != 0) && (strcmp(booking[i].dep, "深圳") != 0)) {
        printf("\n输入的出发地或目的地出错");
        goto dep_des; // 跳转到重新输入出发地和目的地的循环
    }
    if ((strcmp(booking[i].des, "北京") != 0) && (strcmp(booking[i].des, "上海") != 0) && (strcmp(booking[i].des, "天津") != 0) && (strcmp(booking[i].des, "深圳") != 0)) {
        printf("\n输入的出发地或目的地出错");
        goto dep_des; // 跳转到重新输入出发地和目的地的循环
    }
    // 显示航班信息
    system("cls");
    printf ("----------------------------------------------------------------------------------------------------------------\n");
    printf ("****************************************   |  订单信息确认 |   ****************************************\n");
    printf ("----------------------------------------------------------------------------------------------------------------\n\n\n");
    printf("\nDear %s,\n\t您的航班号是 %d.\n\n根据您的要求，航班时间是:\n", booking[i].name, booking[i].refno);
    flight_time(booking[i].dep, booking[i].des);
    printf("\n起飞时间:\t%s\n到达时间:\t%s\n", booking[i].deptime, booking[i].destime);
    // 确认票务信息
    ticket_confirmation:
    printf("\n\n您确认您的机票吗？（输入'y'或'n'）\t");
    scanf(" %c", &request);
    if (request == 'Y' || request == 'y') {
        // 预订座位数
        no_of_tickets:
        printf("\n 你想预订几个座位?\t");
        scanf("%d", &booking[i].noofseats);
        if (booking[i].noofseats == 0) // 检查是否尝试预订0个座位
        {
            printf ("\n\t\t您无法预订0张票。请再次输入票号.");
            goto no_of_tickets; // 跳转到重新输入座位数的循环
        }
        printf("\n已确认%d 个座位", booking[i].noofseats);
        // 将预订信息追加到文件中
        fprintf (fp, "%d %s %lli %s %s %s %s %d\n", booking[i].refno, booking[i].name, booking[i].num, booking[i].dep,
        booking[i].des, booking[i].deptime, booking[i].destime, booking[i].noofseats);
        fclose(fp); // 关闭文件
    } else if (request == 'N' || request == 'n') {
        // 如果取消确认，则返回选项菜单
        printf("\n\n\t\t您将在3秒内被重定向到选项页面.");
        sleep(3); // 等待3秒
        options();
    } else {
        // 如果输入无效，则重新确认
        printf("\nEnter either Y or N.\n请再次输入您的确认.");
        goto ticket_confirmation; // 跳转到重新确认的循环
    }
    // 询问用户是否需要继续预订
    more_data:
    printf ("\n\n您是否需要继续预订?（输入'y'或'n'）\t");
    scanf (" %c", &ans);
    if (ans == 'y' || ans == 'Y') {
        // 如果需要继续预订，则返回函数开始
        goto book_ticket; // 跳转到开始预订的循环
    } else if (ans == 'n' || ans == 'N') {
        // 如果不需要继续预订，则保存数据并返回选项菜单
        printf("\n 数据已成功保存.\n\n\t\t按任意键进入选项页...");
        getch(); // 等待按键
    } else {
        // 如果输入无效，则重新询问
        printf("\nEnter either Y or N.\n请再次输入您的确认信息.");
        goto more_data; // 跳转到重新询问的循环
    }
    options(); // 返回选项菜单
}

/*
 `bookticket` 函数，该函数用于预订票务。以下是这个函数的详细解释：
1. 函数开始时，使用 `system("cls")` 命令来清除屏幕，以便为预订票务界面提供一个干净的起始点。
2. 使用 `system("COLOR 0E")` 命令来改变控制台背景和字体的颜色，通常用于美化用户界面。
3. 打开文件 `ticket_details.txt` 以读取现有票务记录，并打开文件以追加新记录。
4. 读取 `ticket_details.txt` 文件中的票务记录，并将它们存储在 `booking` 数组中。如果文件结束，则跳出循环。
5. 关闭文件。
6. 提示用户输入预订票务的详细信息，包括姓名、联系方式、出发地和目的地。
7. 检查输入的联系方式是否为10位数，如果不是，则提示用户重新输入。
8. 生成新的参考号，并提示用户输入出发地和目的地。
9. 检查出发地和目的地是否相同，如果是，则提示用户重新输入。
10. 检查出发地和目的地是否有效，如果不是，则提示用户重新输入。
11. 询问用户是否确认预订，如果确认，则将新预订的信息追加到 `ticket_details.txt` 文件中，并关闭文件。
12. 询问用户是否需要继续预订，如果需要，则返回 `bookticket` 函数，重新开始预订过程。
*/

// 计算数字中的位数的函数
int count_digits_in_num(long long number) {
    int digits_in_num = 0;
    while (number != 0) {
        number = number / 10;
        digits_in_num++;
    }
    return digits_in_num;
}
//这个函数的工作原理是通过不断地将输入的数字除以10，然后递减，直到数字变为0。每次除以10都相当于移除数字的最后一位。因此，递减的次数就是数字的位数。 

// 显示所有预订的票务的函数
void list_booked_tickets() {
    system("cls"); // 清屏
    system("COLOR 0E"); // 改变背景颜色
    fp = fopen("ticket_details.txt", "r"); // 打开文件用于读取
    if (fp == NULL) { // 检查文件是否为空
        printf("\t\t\t\t还没订票 yet.");
        getch(); // 等待按键
        options(); // 返回选项菜单
        return; // 函数结束
    }
    int j = 1;
    printf("----------------------------------------------------------------------------------------------------------------\n");
    printf("******************************************   LIST OF BOOKED TICKETS   ******************************************\n");
    printf("----------------------------------------------------------------------------------------------------------------\n\n\n");
    printf("参考号\t| 姓名\t\t| 电话号码\t| 出发地\t| 目的地\t| 出发时间\t| 到达时间\t| 座位数量\n");
    printf("----------------------------------------------------------------------------------------------------------------\n\n");
    while (1) { // 循环读取文件内容
        end_of_file = fscanf(fp, "%d %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].name, &booking[j].num,
        booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
        if (end_of_file == -1) { // 文件结束
            break;
        }
        printf("   %d\t| %s\t\t| %lli\t| %s\t\t| %s\t\t| %s\t| %s\t|\t%d\n\n", booking[j].refno,booking[j].name, booking[j].num,
        booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, booking[j].noofseats);
        j++;
    }
    fclose(fp); // 关闭文件
    getch(); // 等待按键
    options(); // 返回选项菜单
}
/* `list_booked_tickets` 函数，该函数用于显示所有已预订的票务信息。以下是这个函数的详细解释：
1. 函数开始时，使用 `system("cls")` 命令来清除屏幕，以便为显示票务列表界面提供一个干净的起始点。
2. 使用 `system("COLOR 0E")` 命令来改变控制台背景和字体的颜色，通常用于美化用户界面。
3. 打开 `ticket_details.txt` 文件以读取模式。如果文件为空，显示一条信息并返回选项菜单。
4. 打印出票务列表的标题。
5. 循环读取文件内容，将票务记录存储在 `booking` 数组中，并打印出每条记录的信息。
6. 关闭文件。
7. 等待用户按键。
8. 返回选项菜单。
*/ 


// 通过参考号编辑票务的函数
void edit_ticket()                                                             
{
	int digits_in_num;
	system ("cls");
	system ("COLOR 0E");
	printf ("---------------------------------------------------------------------------------------------\n");
	printf ("******************************  | 通过参考号编辑票务 |  ******************************\n");
	printf ("---------------------------------------------------------------------------------------------\n\n\n");
	fp = fopen ("ticket_details.txt", "r+"); //open file pointer in read+ mode
	if (fp == NULL) //condition to check if file is empty and displpay msg accordingly
	{
		printf ("\t\t\t\t 还没有订票.");
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
	
	printf ("输入要编辑的参考编号: \t");
	scanf("%d", &ref_no);

	rewind(fp); //to put the cursor in the beginning of file
	for (p=1; p<j; p++)
	{
		if (booking[p].refno == ref_no)
		{
			printf ("\n\n姓名\t[Old data: %s ]:\t", booking[p].name);
			scanf ("%s", booking[p].name);
			enter_number:
			printf ("\n电话号码\t[Old data: %lli ]:\t", booking[p].num);
			scanf ("%lli", &booking[p].num);
			digits_in_num = count_digits_in_num (booking[p].num); //calling of count_digits_in_num function 
			if (digits_in_num != 10) //condition if input number is of 10 digits or not
			{
				printf ("\t\t 号码无效。请输入正确的联系号码.");
				goto enter_number; //goes to line number 459
			}
				
			dep_des:
			printf("\n输入您的出发地和目的地位置.\n\t\tType\n");
			printf("\t 北京\n\t 上海\n\t 天津\n\t 深圳\n\n");
			printf ("出发地\t[Old data: %s ]:\t", booking[p].dep);
			scanf ("%s", booking[p].dep);
			printf ("目的地\t[Old data: %s ]:\t", booking[p].des);
			scanf ("%s", booking[p].des);
			if (strcmp(booking[p].dep, booking[p].des) == 0)
			{
				printf ("您输入了相同的出发地和目的地。请再次输入。\n");
				goto dep_des; //goes to line number 469
			}
			if ((strcmp(booking[p].dep,"北京")!=0)&&(strcmp(booking[p].dep,"上海")!=0)&&(strcmp(booking[p].dep,"天津")!=0)&&(strcmp(booking[p].dep,"深圳")!=0))
			{
				printf("\n无效的出发地或目的地.");
				goto dep_des; //goes to line number 469
			}
			if ((strcmp(booking[p].des,"北京")!=0)&&(strcmp(booking[p].des,"上海")!=0)&&(strcmp(booking[p].des,"天津")!=0)&&(strcmp(booking[p].des,"深圳")!=0))
			{
				printf("\n无效的出发地或目的地.");
				goto dep_des; //goes to line number 469
			}
			fflush(stdin);
			no_of_tickets:
			printf ("\n票数\t[Old data: %d ]:\t", booking[p].noofseats);
			scanf ("%d", &booking[p].noofseats);
			if (booking[p].noofseats == 0) 
			{ 
			printf ("\t\t您无法预订0张票。请再次输入票号\n"); 
			goto no_of_tickets;
			}
			printf("\n\nDear %s,\n\t 根据您的要求，新的航班时间是:",booking[p].name);
			flight_time(booking[p].dep, booking[p].des);
			strcpy (booking[p].deptime, booking[i].deptime);
			strcpy (booking[p].destime, booking[i].destime);
			printf("\n出发时间:\t%s\n到达时间:\t%s\n\n", booking[p].deptime, booking[p].destime);
			loader("updating");
			printf ("\n\n新数据已成功更新.");
			
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
	
	
	printf ("新数据已成功更新\nc.\n"); //message to display if the ref no is not found
	getch();
	options();
}

//这个函数首先清屏并改变背景颜色，然后打开票务信息文件。如果文件为空，它将显示一条信息并返回选项菜单。如果文件中有票务信息，它将允许用户输入一个参考号来编辑相应的票。 
/* `edit_ticket` 函数，该函数用于通过参考号编辑票务信息。以下是这个函数的详细解释：
1. 函数开始时，使用 `system("cls")` 命令来清除屏幕，以便为编辑票务界面提供一个干净的起始点。
2. 使用 `system("COLOR 0E")` 命令来改变控制台背景和字体的颜色，通常用于美化用户界面。
3. 打开 `ticket_details.txt` 文件以读取和写入模式。如果文件为空，显示一条信息并返回选项菜单。
4. 提示用户输入要编辑的票务参考号。
5. 将文件指针重新定位到文件开始，并读取票务记录。
6. 循环检查输入的参考号，如果找到匹配的记录，则提示用户输入新的票务信息，如姓名、联系方式、出发地和目的地等。
7. 验证输入的联系方式是否为10位数，如果不是，则提示用户重新输入。
8. 检查出发地和目的地是否相同，如果是，则提示用户重新输入。
9. 检查出发地和目的地是否有效，如果不是，则提示用户重新输入。
10. 询问用户是否确认更新票务信息，如果确认，则将新的票务信息写入 `ticket_details.txt` 文件中，并关闭文件。
11. 显示更新成功的信息，并显示加载动画。
12. 返回选项菜单。
 */ 



//柴东博 
// 根据出发地和目的地提供航班时间的函数
void flight_time(char dep[3], char des[3]) {
    if (strcmp(dep, "北京") == 0) {
        if (strcmp(des, "上海") == 0) {
            strcpy(booking[i].deptime, "06:00am");
            strcpy(booking[i].destime, "06:30am");
        } else if (strcmp(des, "天津") == 0) {
            strcpy(booking[i].deptime, "09:20am");
            strcpy(booking[i].destime, "10:15am");
        } else if (strcmp(des, "深圳") == 0) {
            strcpy(booking[i].deptime, "11:40pm");
            strcpy(booking[i].destime, "12:30pm");
        }
    } else if (strcmp(dep, "上海") == 0) {
        if (strcmp(des, "北京") == 0) {
            strcpy(booking[i].deptime, "01:20am");
            strcpy(booking[i].destime, "01:50am");
        } else if (strcmp(des, "天津") == 0) {
            strcpy(booking[i].deptime, "02:35pm");
            strcpy(booking[i].destime, "04:40pm");
        } else if (strcmp(des, "深圳") == 0) {
            strcpy(booking[i].deptime, "07:00am");
            strcpy(booking[i].destime, "08:05am");
        }
    } else if (strcmp(dep, "天津") == 0) {
        if (strcmp(des, "北京") == 0) {
            strcpy(booking[i].deptime, "10:25am");
            strcpy(booking[i].destime, "11:20am");
        } else if (strcmp(des, "上海") == 0) {
            strcpy(booking[i].deptime, "10:45am");
            strcpy(booking[i].destime, "12:50am");
        } else if (strcmp(des, "深圳") == 0) {
            strcpy(booking[i].deptime, "05:10pm");
            strcpy(booking[i].destime, "07:30pm");
        }
    } else if (strcmp(dep, "深圳") == 0) {
        if (strcmp(des, "北京") == 0) {
            strcpy(booking[i].deptime, "08:00pm");
            strcpy(booking[i].destime, "08:50pm");
        } else if (strcmp(des, "上海") == 0) {
            strcpy(booking[i].deptime, "01:00pm");
            strcpy(booking[i].destime, "02:05pm");
        } else if (strcmp(des, "天津") == 0) {
            strcpy(booking[i].deptime, "08:35am");
            strcpy(booking[i].destime, "09:55am");
        }
    } else {
        printf("出发地或目的地无效");
    }
}
/*
`flight_time` 函数，该函数用于根据出发地和目的地提供航班时间。以下是这个函数的详细解释：
1. 函数接受两个字符串参数 `dep` 和 `des`，分别表示出发地和目的地。
2. 使用 `strcmp` 函数比较 `dep` 和 `des` 参数，以确定航班的出发地和目的地。
3. 根据不同的出发地和目的地组合，函数提供相应的航班时间。例如，如果从 北京 出发到 上海，则航班时间为 06:00am 到 06:30am。
4. 如果出发地或目的地无效（即不在预定义的列表中），函数将打印一条错误信息，告诉用户输入的出发地或目的地无效。
*/ 

// 通过参考号取消票务的函数
void cancel_ticket() {
    char confirmation;
	system("cls"); // 清屏
    system("COLOR 0E"); // 改变背景颜色
    fp = fopen("ticket_details.txt", "r+"); // 打开文件用于读取和写入
    if (fp == NULL) { // 检查文件是否为空
        printf("\t\t\t\t未存在订票。");
        getch(); // 等待按键
        options(); // 返回选项菜单
        return; // 函数结束
    }
    int ref_no, j = 1, p, d;
    while (1) { // 循环读取文件内容
        end_of_file = fscanf(fp, "%d %s %lli %s %s %s %s %d", &booking[j].refno, booking[j].name, &booking[j].num,
        booking[j].dep, booking[j].des, booking[j].deptime, booking[j].destime, &booking[j].noofseats);
        if (end_of_file == -1) { // 文件结束
            break;
        }
        j++;
    }
    printf("输入要取消的参考号: \t");
    scanf("%d", &ref_no);
    for (p=1; p<j; p++) //loop to find the entered ref number
		{
			if (booking[p].refno == ref_no) //condition when ref number is found
			{	
				printf("\n\n您确定要删除%d的票证详细信息吗？(输入'y'或'n')\t", ref_no); //cancellation confirmation
				scanf (" %c", &confirmation);
				if ( confirmation == 'Y' || confirmation == 'y')
				{
					for (d=p; d<j; d++) //loop to replace the index number of entered ref number with preceeding structure
					{
						booking[d] = booking[d+1]; //preceeding structure replaces the place of the previous one
					}
					j--;
					loader("deleting"); //deleting animation
					printf ("\n\n\n数据已成功删除.");
				
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
					printf("\n\n\t\t您将在 3 秒内回到选择页面.");
					sleep(3); //to wait for 3 seconds before executing the option function
					options();	
				}
				else 
				{
					printf ("\n\n请输入“Y”或“N”进行确认.");
				}
			}
		}
	
    printf("\n请确保您输入的参考号在票证列表中。\n"); // 未找到匹配的参考号
    getch(); // 等待按键
    options(); // 返回选项菜单
}
/*
 `cancel_ticket` 函数，该函数用于通过参考号取消票务。以下是这个函数的详细解释：
1. 函数开始时，使用 `system("cls")` 命令来清除屏幕，以便为取消票务界面提供一个干净的起始点。
2. 使用 `system("COLOR 0E")` 命令来改变控制台背景和字体的颜色，通常用于美化用户界面。
3. 打开 `ticket_details.txt` 文件以读取和写入模式。如果文件为空，显示一条信息并返回选项菜单。
4. 提示用户输入要取消的票务参考号。
5. 将文件指针重新定位到文件开始，并读取票务记录。
6. 循环检查输入的参考号，如果找到匹配的记录，则显示一条信息表示票务已成功取消，并更新文件中的票务信息。
7. 返回选项菜单。
*/ 

// 退出程序的函数
void exit_terminal() {
    system("cls"); // 清屏
    system("COLOR 0E"); // 改变背景颜色
    printf("---------------------------------------------------------------------------------------------\n");
    printf("********************************************* | 退出程序 | *********************************************\n");
    printf("---------------------------------------------------------------------------------------------\n\n\n");
    printf("感谢您使用订票系统。再见！\n");
    getch(); // 等待按键
    // 关闭所有打开的文件
    fclose(fp);
    // 退出程序
    exit(0);
}
/* 
 `exit_terminal` 函数，该函数用于退出程序。以下是这个函数的详细解释：
1. 函数开始时，使用 `system("cls")` 命令来清除屏幕，以便为退出程序界面提供一个干净的起始点。
2. 使用 `system("COLOR 0E")` 命令来改变控制台背景和字体的颜色，通常用于美化用户界面。
3. 显示一条感谢信息，告诉用户程序即将退出。
4. 等待用户按键。
5. 关闭所有打开的文件，包括文件指针 `fp`。
6. 使用 `exit(0)` 命令退出程序。
*/ 
