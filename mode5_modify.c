#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Macro define
#define MAX_PATIENT 30
#define MAX_PASSWORD_TRY 3
#define MAX_ACCOUNTS 5
#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20

//struct define
struct Patient{
    char ID_Card[20];
    char Name[30];
    int Is_Double_Positive;
    int Is_COVID_Recover;
    char Visit_time[15];
    char Recover_time[15];
    char Double_Visit_time[15];
}Patient_list[MAX_PATIENT];
int Patient_exist[MAX_PATIENT];
int list_current, all = 0;

//  Doctor struct
struct Account{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
}accounts[MAX_ACCOUNTS];
int numAccounts = 0;

//Three function which include B(before) and function num(N)
//  1 Doctor Function
//      B Search empty
int Empty_Search(){
    int i;
    for(i = 0; i < MAX_PATIENT; ++i)
        if(Patient_exist[i] == 0) return i;
    return -1;
}

//      B Judge empty
int Empty(){
    int i;
    int flag = 0;
    for(i = 0;i < MAX_PATIENT ; ++i)
        if(Patient_exist[i] == 1) flag = 1;
    if(flag) return 0;
    else return 1;
}

//      B translate 1/0 to True/False
char* TOF(int result){
    static char true[] = {'T','r','u','e','\0'};
    static char false[] = {'F','a','l','s','e','\0'};
    static char error[] = {'E','r','r','o','r','\0'};

    if(result == 1) return true;
    else if(result == 0) return false;
    else return error;
}

//      1 Append Patient data
void Append_Main(int op, int place){
    int check;
    while (1){
        printf("       Tips: Please enter the Patient Data with the format while input 0 for no:\n");
        printf("       姓名Name: \n\t");
        fgets(Patient_list[place].Name, sizeof(Patient_list[place].Name), stdin);
        Patient_list[place].Name[strcspn(Patient_list[place].Name, "\n")] = '\0'; // Remove trailing newline
        if(op){
            printf("       身份证号ID_Card: \n\t");
            fgets(Patient_list[place].ID_Card, sizeof(Patient_list[place].ID_Card), stdin);
            Patient_list[place].ID_Card[strcspn(Patient_list[place].ID_Card, "\n")] = '\0'; // Remove trailing newline
        }
        printf("       是否阳康Is_COVID_Recover: \n\t");
        scanf("%d", &Patient_list[place].Is_COVID_Recover);
        scanf("%*c"); // Consume the newline character left in the buffer
        
        printf("       是否二阳Is_Double_Positive: \n\t");
        scanf("%d", &Patient_list[place].Is_Double_Positive);
        scanf("%*c"); // Consume the newline character left in the buffer
        
        printf("       第一次来访时间Visit_time(e.g. 2023-06-15): \n\t");
        fgets(Patient_list[place].Visit_time, sizeof(Patient_list[place].Visit_time), stdin);
        Patient_list[place].Visit_time[strcspn(Patient_list[place].Visit_time, "\n")] = '\0'; // Remove trailing newline
        
        printf("       第一次阳康时间Recover_time(e.g. 2023-06-16): \n\t");
        fgets(Patient_list[place].Recover_time, sizeof(Patient_list[place].Recover_time), stdin);
        Patient_list[place].Recover_time[strcspn(Patient_list[place].Recover_time, "\n")] = '\0'; // Remove trailing newline

        printf("       二阳来访时间Double_Visit_time(e.g. 2023-06-16): \n\t");
        fgets(Patient_list[place].Double_Visit_time, sizeof(Patient_list[place].Double_Visit_time), stdin);
        Patient_list[place].Double_Visit_time[strcspn(Patient_list[place].Double_Visit_time, "\n")] = '\0'; // Remove trailing newline

        printf("       Tips: Please cheak whether the Data appended are right!\n");
        int i = place;
        printf("       Tips: ICR - Is_COVID19_Recover || IDP = Is_DoubleCOVID19_Positive.\n");
        printf("       Title: Num    Name\t      ID_Card\t     ICR   IDP     Visit_time\t Recover_time\t Double_Visit_time\n");
        printf("               %d    %-12s %-18s  ", i+1, Patient_list[i].Name, Patient_list[i].ID_Card);
        printf("%-5s %-5s   ", TOF(Patient_list[i].Is_COVID_Recover), TOF(Patient_list[i].Is_Double_Positive));
        printf("%-10s    %-10s      %-10s\n", Patient_list[i].Visit_time, Patient_list[i].Recover_time, Patient_list[i].Double_Visit_time);

        printf("       Input: Check with Y-1 or N-0:");
        scanf("%d", &check);
        if(check == 1){
            Patient_exist[place] = 1;
            ++list_current;
            return ;
        }
        else getchar();
    }
}

int Append_Data_Doc(){
    getchar();
    int place;
    if((place = Empty_Search()) == -1){
        printf("       Tips: Full list ! Please Enhance MAX_PATIENT.\n");
        return -1;
    }
    Append_Main(1, place);
}

//      2/5 Show Patient Info/Search patient data OP 0/1
void List_Info(int i){
    printf("               %d    %-12s %-18s  ", i+1, Patient_list[i].Name, Patient_list[i].ID_Card);
    printf("%-5s %-5s   ", TOF(Patient_list[i].Is_COVID_Recover), TOF(Patient_list[i].Is_Double_Positive));
    printf("%-10s    %-10s      %-10s\n", Patient_list[i].Visit_time, Patient_list[i].Recover_time, Patient_list[i].Double_Visit_time);
}

int List_Main(int op){
    int i, flag = 1;
    char name[30];
    if(op){
        printf("       Input: Please enter the name to search :");
        scanf("%s", name);
    }
    printf("       Tips: ICR - Is_COVID19_Recover || IDP = Is_DoubleCOVID19_Positive.\n");
    printf("       Title: Num    Name\t      ID_Card\t     ICR   IDP     Visit_time\t Recover_time\t Double_Visit_time\n");
    for(i = 0; i < MAX_PATIENT; ++i){
        if(Patient_exist[i]){
            if(strcmp(Patient_list[i].Name, name) == 0 && op){
                List_Info(i);
                return 0;
            }
            else if(!op){
                flag = 0;
                List_Info(i);
            }
        }
    }
    if(flag && !op) printf("\n       Tips: 数据库为空! None people here.\n");
    else if(op) printf("       Tips: No such person!\n");
    return -1;
}

//      3 Delete petient data
int Delete_Data_Doc(){
    int i;
    char name[30];
    printf("       Input: Please enter the name to delete:");
    scanf("%s", name);
    for(i = 0; i <MAX_PATIENT ; ++i){
        if(Patient_exist[i]){
            if(strcmp(Patient_list[i].Name, name) == 0 ){
                Patient_exist[i] = 0;
                --list_current;
                if(!Empty()) List_Info(0);
                else printf("       Tips: List Empty.\n");
                return 0;
            }
        }
    }
    printf("       Tips: No such person!\n");
    return -1;
}

//      4 Revise patient data
void Revise_Info(struct Patient Pat){
    printf("\n       Title: Patient Data:\n");
    printf("         1. 姓名 Name: %s\n", Pat.Name);
    printf("         2. 身份证号 ID_Card: %s\n", Pat.ID_Card);
    printf("         3. 是否阳康 Is_COVID_Recover: %s\n", TOF(Pat.Is_COVID_Recover));
    printf("         4. 是否二阳 Is_Double_Positive: %s\n", TOF(Pat.Is_Double_Positive));
    printf("         5. 第一次来访时间 Visit_time: %s\n", Pat.Visit_time);
    printf("         6. 第一次阳康时间 Recover_time: %s\n", Pat.Recover_time);
    printf("         7. 二阳来访时间 Double_Visit_time (e.g. 2023-06-16): %s\n", Pat.Double_Visit_time);
}

void Revise_Main(int place){
    int choice, check;
    while(1){
        Revise_Info(Patient_list[place]);
        printf("       Input: Enter the number corresponding to the attribute you want to revise (0 to exit): ");
        scanf("%d", &choice);
        getchar();
        if(choice == 0){
            printf("       Tips: Exit Success.\n");
            return;
        }
        char new_value[100];
        printf("\n       Input: Enter the new value for the attribute: ");
        fgets(new_value, sizeof(new_value), stdin);
        new_value[strcspn(new_value, "\n")] = '\0'; // Remove trailing newline

        struct Patient tmp = Patient_list[place];
        switch(choice){
            case 1: strcpy(tmp.Name, new_value); break;
            case 2: strcpy(tmp.ID_Card, new_value); break;
            case 3: tmp.Is_COVID_Recover = atoi(new_value); break;
            case 4: tmp.Is_Double_Positive = atoi(new_value); break;
            case 5: strcpy(tmp.Visit_time, new_value); break;
            case 6: strcpy(tmp.Recover_time, new_value); break;
            case 7: strcpy(tmp.Double_Visit_time, new_value); break;
            default: printf("       Tips: Invalid attribute number. Please try again.\n"); continue;
        }
        system("cls");
        Revise_Info(tmp);
        printf("       Input: Do you want to continue revising? (1-Yes, 0-No): ");
        scanf("%d", &check);

        if(check == 0) continue;
        else{
            switch(choice){
                case 1: strcpy(Patient_list[place].Name, new_value); break;
                case 2: strcpy(Patient_list[place].ID_Card, new_value); break;
                case 3: Patient_list[place].Is_COVID_Recover = atoi(new_value); break;
                case 4: Patient_list[place].Is_Double_Positive = atoi(new_value); break;
                case 5: strcpy(Patient_list[place].Visit_time, new_value); break;
                case 6: strcpy(Patient_list[place].Recover_time, new_value); break;
                case 7: strcpy(Patient_list[place].Double_Visit_time, new_value); break;
                default: printf("       Tips: Invalid attribute number. Please try again.\n"); continue;
            }
        }
    }
}

int Revise_Data_Doc() {
    int i;
    char name[30];
    printf("       Input: Please enter the name to search: ");
    scanf("%s", name);
    for(i = 0; i < MAX_PATIENT; ++i)
        if(Patient_exist[i] && strcmp(Patient_list[i].Name, name) == 0){
            Revise_Main(i);
            return 0;
        }
    printf("       Tips: No such person!\n");
    getchar();
    return -1;
}

//      6/7 Sort by Visit time
int Compare_Patients_Visit(const void *a, const void *b) {
    const struct Patient *patient1 = (const struct Patient *)a;
    const struct Patient *patient2 = (const struct Patient *)b;
    
    return strcmp(patient1->Visit_time, patient2->Visit_time);
}

//          Sort with 2 mode
void Sort_Patients_Visit(int order) {
    qsort(Patient_list, all, sizeof(struct Patient), Compare_Patients_Visit);
    if (order == 1) {
        struct Patient temp;
        int i, j;
        for (i = 0, j = all - 1; i < j; i++, j--) {
            temp = Patient_list[i];
            Patient_list[i] = Patient_list[j];
            Patient_list[j] = temp;
        }
    }
    List_Main(0);
}
      
//      B Calculate the time difference
void Time_Differ(const char* date1, const char* date2, char* result) {
    struct tm tm1, tm2;
    memset(&tm1, 0, sizeof(struct tm));
    memset(&tm2, 0, sizeof(struct tm));

    int year, month, day;
    sscanf(date1, "%d-%d-%d", &year, &month, &day);
    tm1.tm_year = year - 1900;
    tm1.tm_mon = month - 1;
    tm1.tm_mday = day;
    sscanf(date2, "%d-%d-%d", &year, &month, &day);
    tm2.tm_year = year - 1900;
    tm2.tm_mon = month - 1;
    tm2.tm_mday = day;

    time_t timestamp1 = mktime(&tm1);
    time_t timestamp2 = mktime(&tm2);
    time_t diff = timestamp2 - timestamp1;

    struct tm* tm_diff = gmtime(&diff);
    strftime(result, 15, "%Y-%m-%d", tm_diff);
}

//      8/9 Sort by Visit time
int Compare_Patients_Positive(const void* a, const void* b) {
    const struct Patient* patient1 = (const struct Patient*)a;
    const struct Patient* patient2 = (const struct Patient*)b;

    char result1[15];
    char result2[15];

    Time_Differ(patient1->Recover_time, patient1->Visit_time, result1);
    Time_Differ(patient1->Recover_time, patient2->Visit_time, result2);

    return strcmp(result1, result2);
}

//          Sort with 2 mode
void Sort_Patients_Positive(int order) {
    qsort(Patient_list, all, sizeof(struct Patient), Compare_Patients_Positive);
    if (order == 1) {
        struct Patient temp;
        int i, j;
        for (i = 0, j = all - 1; i < j; i++, j--) {
            temp = Patient_list[i];
            Patient_list[i] = Patient_list[j];
            Patient_list[j] = temp;
        }
    }
    List_Main(0);
}


//      A/B Sort by Visit time
int Compare_Patients_DoublePositive(const void* a, const void* b) {
    const struct Patient* patient1 = (const struct Patient*)a;
    const struct Patient* patient2 = (const struct Patient*)b;

    char result1[15];
    char result2[15];

    Time_Differ(patient1->Double_Visit_time, patient1->Visit_time, result1);
    Time_Differ(patient1->Double_Visit_time, patient2->Visit_time, result2);

    return strcmp(result1, result2);
}

//          Sort with 2 mode
void Sort_Patients_DoublePositive(int order) {
    qsort(Patient_list, all, sizeof(struct Patient), Compare_Patients_DoublePositive);
    if (order == 1) {
        struct Patient temp;
        int i, j;
        for (i = 0, j = all - 1; i < j; i++, j--) {
            temp = Patient_list[i];
            Patient_list[i] = Patient_list[j];
            Patient_list[j] = temp;
        }
    }
    List_Main(0);
}

//      C/E Read File
void ReadFile(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("       Tips: Failed to open file: %s\n", filename);
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

//      D/F Modify File
void ModifyFile(const char* filename){
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("       Tips: Failed to open file: %s\n", filename);
        return;
    }
    printf("       Input: Enter new content (Enter 'exit' to finish):\n");
    char line[100];

    while (fgets(line, sizeof(line), stdin) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, "exit") == 0) {
            break;
        }
        fputs(line, file);
        fputc('\n', file); 
    }
    fclose(file);
    printf("       Tips: File modified successfully.\n");
}

//      W Function to write data to a file
void File_Write() {
    FILE *file;
    int i;
    file = fopen("saveData.dat", "w");
    if (file == NULL) {
        printf("       Tips: Failed to open the file.\n");
        return;
    }
    fwrite(&list_current, sizeof(int), 1, file);
    for (i = 0; i < MAX_PATIENT; i++) {
        if (Patient_exist[i]) {
            fwrite(&Patient_list[i], sizeof(struct Patient), 1, file);
        }
    }
    fclose(file);
    printf("       Tips: Data saved successfully.\n");
}

//      R Function to read data from a file
void File_Read(){
    FILE *file;
    int i;
    file = fopen("saveData.dat", "r");
    if (file == NULL) {
        printf("       Tips: Failed to open the file.\n");
        return;
    }
    fread(&list_current, sizeof(int), 1, file);
    for (i = 0; i < MAX_PATIENT; i++) {
        if (fread(&Patient_list[i], sizeof(struct Patient), 1, file) != 1) {
            break;
        }
        Patient_exist[i] = 1;
        all++;
    }
    fclose(file);
    printf("       Tips: Patient Data loaded successfully.\n");
}

//      Doctor Info
void Print_Info(int id){
    printf("\n\n\nSet initialization...\n");
    printf("       Tips: 欢迎值班医生%s登录\n",accounts[id].username);
    printf("\n             患 者 信 息 管 理    \n");
	printf("       ============================= \n");
	printf("\n         一、记录"); 
    printf("\n       (1) 追加记录\n       (2) 列表记录\n       (3) 删除记录 ");
    printf("\n       (4) 修改记录\n       (5) 搜索记录 \n");
    printf("\n         二、排序"); 
    printf("\n       (6) 按就诊时间降序排序\n       (7) 按就诊时间升序排序 ");
    printf("\n       (8) 按患病时长降序排序\n       (9) 按患病时长升序排序 ");
    printf("\n       (A) 按二次患病时长降序排序\n       (B) 按二次患病时长升序排序 \n");
    printf("\n         三、公告"); 
    printf("\n       (C) 查看《防疫小贴士》公告\n       (D) 修改《防疫小贴士》内容 ");
    printf("\n       (E) 查看《拨打120正确话术》公告\n       (F) 修改《拨打120正确话术》内容 \n");
 	printf("\n       (W) 写入文件\n       (R) 从文件重读取\n       (0) 退出 ");
    printf("\n\n       Input: 请输入你的选择:");
}

void Doc_Info(int id){
    char Doc_Info_choice;
    getchar();
    Print_Info(id);
    scanf("%c",&Doc_Info_choice);
    while(Doc_Info_choice != '0'){
        switch(Doc_Info_choice){
            case '1': Append_Data_Doc(); break;
            case '2': List_Main(0); break;
            case '3': Delete_Data_Doc(); break;
            case '4': Revise_Data_Doc(); break;
            case '5': List_Main(1); break;
            case '6': Sort_Patients_Visit(1); break;
            case '7': Sort_Patients_Visit(0); break;
            case '8': Sort_Patients_Positive(1); break;
            case '9': Sort_Patients_Positive(0); break;
            case 'A': Sort_Patients_DoublePositive(1); break;
            case 'B': Sort_Patients_DoublePositive(0); break;
            case 'C': ReadFile("tips.txt"); break;
            case 'D': ModifyFile("tips.txt"); break;
            case 'E': ReadFile("hotline.txt"); break;
            case 'F': ModifyFile("hotline.txt"); break;
            case 'W': File_Write(); break;
            case 'R': File_Read(); break;
        }
        printf("       ");
        system("Pause");
        system("cls");
        Print_Info(id);
        if(Doc_Info_choice != '4' && Doc_Info_choice != 'D' && Doc_Info_choice != 'F') getchar();
        scanf("%c",&Doc_Info_choice);
    }
}

//      Patient Info
void Pinfo(int place){
    printf("\n\n       %s患者您好! 以下为您在本院登记的个人信息：\n",Patient_list[place].Name);
    printf("\n       (1)身份证号             (2)就诊时间 \n");
    printf("          %-18s      %s\n", Patient_list[place].ID_Card, Patient_list[place].Visit_time);
    printf("       (3)是否为二阳           (4)现是否阳康    \n");
    printf("          %-18s      %s\n", TOF(Patient_list[place].Is_Double_Positive), TOF(Patient_list[place].Is_COVID_Recover));
    printf("       (5)阳康时间             (6)二阳就诊时间  \n");
    printf("          %-18s      %s\n", Patient_list[place].Recover_time, Patient_list[place].Double_Visit_time);
    printf("\n\n       =================================   \n");
    printf("\n       (1) 修改记录\n       (2) 查看《防疫小贴士》公告\n       (3) 查看《拨打120正确话术》公告\n");
    printf("\n       Input: 请输入选项 Enter choice:");
}

void Pat_Info(){
    char Pat_Info_Choice = '0';
    int place;
    int i;
    char name[30];
    printf("       Input: Please enter the name to search:");
    scanf("%s", name);
    for(i = 0; i <MAX_PATIENT ; ++i){
        if(Patient_exist[i]){
            if(strcmp(Patient_list[i].Name, name) == 0 ){
                Pat_Info_Choice = '1';
                place = i;
            }
        }
    }
    if(Pat_Info_Choice == '0') printf("       Tips: No such person!\n");
    getchar();
    do{
        if(Pat_Info_Choice == '0'){
            //若不能在记录中搜索到信息，则跳转，显示如下界面：
            printf("\n       Input: 请输入您的身份证号码ID_Card:\n       ");
            place = Empty_Search();
            fgets(Patient_list[place].ID_Card, sizeof(Patient_list[place].ID_Card), stdin);
            Patient_list[place].ID_Card[strcspn(Patient_list[place].ID_Card, "\n")] = '\0'; // Remove trailing newline
            printf("\n       Tips: 身份证号码为 %s 的用户请注册:\n\n ",Patient_list[place].ID_Card); 
            Append_Main(0, place);
            Pat_Info_Choice = '1';
            getchar();
        }
        else if(Pat_Info_Choice == '1'){
            Pinfo(place);
            scanf("%c",&Pat_Info_Choice);
            getchar();
            while(Pat_Info_Choice != '0'){
                switch(Pat_Info_Choice){
                    case '1': Revise_Main(place); break;
                    case '2': ReadFile("tips.txt"); break;
                    case '3': ReadFile("hotline.txt"); break;
                }
                printf("       ");
                system("Pause");
                system("cls");
                Pinfo(place);
                scanf("%c",&Pat_Info_Choice);
                getchar();
            }
        }
    }while(Pat_Info_Choice != '0');
}

//  702813 Administrator function
//      B load account from file
void loadAccountsFromFile(){
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    FILE *file = fopen("accounts.dat", "r");
    if(file == NULL){
        printf("       Tips: Fail to read doctor information.\n");
        return;
    }
    numAccounts = 0;

    while(fscanf(file, "%s %s", username, password) == 2){
        if (numAccounts == MAX_ACCOUNTS) {
            printf("       Tips: Data Oversize.\n");
            break;
        }
        strcpy(accounts[numAccounts].username, username);
        strcpy(accounts[numAccounts].password, password);
        numAccounts++;
    }

    fclose(file);
    printf("       Tips: Doctor data Success all.\n");
}

//      B Admin login
int login(){
	int i;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    
    printf("       Input: 请输入账号 Account:");
    scanf("%s", username);
    printf("       Input: 请输入密码 Password:");
    scanf("%s", password);
    
    for (i = 0; i < numAccounts; i++) {
        if (strcmp(accounts[i].username, username) == 0 && strcmp(accounts[i].password, password) == 0) {
            return i;
        }
    }
    return -1;
}

//      1 Doctor Account Create
void createAccount(){
    if (numAccounts == MAX_ACCOUNTS) {
        printf("       Tips: 已达到账号上限 Account full.\n");
        return;
    }
    struct Account newAccount;

    printf("       Input: 请输入账号 Account:");
    scanf("%s", newAccount.username);
    printf("       Input: 请输入密码 Password:");
    scanf("%s", newAccount.password);

    accounts[numAccounts] = newAccount;
    numAccounts++;
    printf("       Tips: 账号创建成功 Account exist.\n");
}

//      2 delete account
void deleteAccountFromFile() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char currUsername[MAX_USERNAME_LENGTH];
    char currPassword[MAX_PASSWORD_LENGTH];
    int found = 0;    

    printf("       Input: 请输入要删除的账号 Delete Account:");
    scanf("%s", username);
    printf("       Input: 请输入要删除的账号密码 Delete Password:");
    scanf("%s", password);

    FILE *file = fopen("accounts.dat", "r");
    if (file == NULL) {
        printf("       Tips: Read fail.\n");
        return;
    }
    FILE *tempFile = fopen("temp.txt", "w");  // 创建临时文件用于存储未删除的账号密码
    if (tempFile == NULL) {
        printf("       Tips: Temp open fail.\n");
        fclose(file);
        return;
    }

    while (fscanf(file, "%s %s", currUsername, currPassword) == 2)  // 逐行读取文件，将未匹配的账号密码写入临时文件
        if (strcmp(currUsername, username) == 0 && strcmp(currPassword, password) == 0) found = 1;
        else fprintf(tempFile, "%s %s\n", currUsername, currPassword);
    fclose(file);
    fclose(tempFile);

    if (remove("accounts.dat") != 0){  // 删除原文件并将临时文件重命名为原文件名
        printf("       Tips: Delete error.\n");
        return;
    }
    if (rename("temp.txt", "accounts.dat") != 0){
        printf("       Tips: Rename error.\n");
        return;
    }

    if (found) printf("       Tips: Remove success.\n");
    else printf("       Tips: No match account-password.\n");
}

//      3 Display all accounts
void displayAllAccounts(){
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    FILE *file = fopen("accounts.dat", "r");
    if (file == NULL) {
        printf("       Tips: Read fail.\n");
        return;
    }

    printf("       Tips: Account & Password\n");
    while(fscanf(file, "%s %s", username, password) == 2)
        printf("       账号：%s  密码：%s\n", username, password);

    fclose(file);
}

//      4 Save account to file
void saveAccountsToFile() {
	int i;
    FILE *file = fopen("accounts.dat", "w");
    if(file == NULL){
        printf("       Tips: Write fail.\n");
        return;
    }

    for(i = 0; i < numAccounts; i++)
        fprintf(file, "%s %s\n", accounts[i].username, accounts[i].password);
    fclose(file);
    printf("       Tips: Save success.\n");
}

//      B Administrator continue
int Continue(){
    int choice;
    printf("       Input: Do you want to try again?(Y-1/N-0):");
    scanf(" %d", &choice);
    getchar();
    return choice;
}

//      Admin Info
void Admin_Mode(){
    int choice;
    while (1){
        printf("\n       管理员模式Admin Mode\n");
        printf("       0. 退出模式 Exit\n");
        printf("       1. 创建账号 Create\n");
        printf("       2. 删除账号 Delete\n");
        printf("       3. 显示所有账号 ShowInfo\n");
        printf("       4. 写入文件 Write\n");
        printf("       Input: Please enter the choice:");
        scanf("%d", &choice);
        printf("\n\n");
        switch(choice){
            case 0: return;
            case 1: createAccount(); break;
            case 2: deleteAccountFromFile(); break;
            case 3: displayAllAccounts(); break;
            case 4: saveAccountsToFile(); break;
            default: printf("       Tips: Choose error.\n");
        }
        printf("       ");
        system("Pause");
        system("cls");
    }
}

//MainInfo include Patient\Doctor\Administrator Part
int MainInfo(){
    int identity = 2, id;
    info:  //goto's termination (only to quit multiple nest) 
    do{
        system("cls");  //Main display
        printf("Display Main Info...\n\n");
        printf("              程序设计与实践    实验（五） 新冠疫情常态化防控阶段医生与患者信息管理系统\n");
        printf("        Welcome to Doctor/Patient MIS in NPC(Normal prevention and control) stage of COVID-19\n");
        printf("\n");
        printf("                                22计科C1班 张昕悦 黄翊轩   2023.06.19\n\n");
        printf("                  启动说明Begin tip : Continue with identity Doctor(1) or Patient(2)\n");
        printf("        ======================================================================================\n");
        printf("                            (1)医生                      (2)患者\n"); 
        printf("\n        请选择正确身份登录：");
        scanf("%d",&identity);
        if(identity == 1){  //Doctor Mode
            printf("       Input: Please enter the Account-Password order for log-in:\n");
            int try;
            char password[30];
            do{
                try = 1;
                do{
                    printf("        (%d - %d)\n", try, MAX_PASSWORD_TRY);
                    if((id = login()) != -1){
                        Doc_Info(id);
                        goto info;  //0 function to the begin
                    }
                    ++try;
                }while(try <= MAX_PASSWORD_TRY);
                printf("        Tips: Authority Denied for your %d try(s).\n",MAX_PASSWORD_TRY);
            }while(Continue() == 1);
        }
        else if(identity == 2) Pat_Info();  //Patient Mode
        else if(identity == 702813){  //Administrator Mode
            int try;
            char password[10];
            char right[10] = {'8','5','0','2','4','5'};
            do{
                try = 1;
                do{
                    printf("        Input: Please enter the Admin Password(%d - %d):", try, MAX_PASSWORD_TRY);
                    scanf("%s",password);
                    if(strncmp(password, right, 6) == 0){
                        Admin_Mode();
                        goto info;
                    }
                    ++try;
                }while(try <= MAX_PASSWORD_TRY);
                printf("        Input: Authority Denied for your %d try(s).\n",MAX_PASSWORD_TRY);
            }while(Continue() == 1);
        }
        else if(identity == 0) ;
        else printf("        Tips: Input error Please try again.\n        ");
    }while(identity);
}

int main(){
    printf("Set initialization...\n");  //Reset the flag and read files
    memset(Patient_exist, 0, sizeof(int) * MAX_PATIENT);
    list_current = 0;
    File_Read();
    loadAccountsFromFile();
    system("Pause");
	MainInfo();  //Main Display here
    printf("        Thanks for using.\n        ");  //at the end
    system("Pause");
	return 0;
}