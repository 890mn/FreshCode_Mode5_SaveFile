//Include use
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
//  Patient struct
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
int list_current;
int all = 0;

//  Doctor struct
struct Account{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};
struct Account accounts[MAX_ACCOUNTS];
int numAccounts = 0;

//Three function which include B(before) and function num(N)
//  1 Doctor Function
//      B Search empty
int Empty_Search(){
    int i;
    for(i = 0; i < MAX_PATIENT; ++i){
        if(Patient_exist[i] == 0) return i;
    }
    return -1;
}

//      B Judge empty
int Empty(){
    int i;
    int flag = 0;
    for(i = 0;i < MAX_PATIENT ; ++i){
        if(Patient_exist[i] == 1) flag = 1;
    }
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
int Append_Data_Doc(){
    getchar();
    int place;
    int check;
    if((place = Empty_Search()) == -1){
        printf("       Tips: Full list ! Please Enhance MAX_PATIENT.\n");
        return -1;
    }
    while (1) {
        printf("       Tips: Please enter the Patient Data with the format while input 0 for no:\n");
    
        // Read patient name using fgets
        printf("       ����Name: \n\t");
        fgets(Patient_list[place].Name, sizeof(Patient_list[place].Name), stdin);
        Patient_list[place].Name[strcspn(Patient_list[place].Name, "\n")] = '\0'; // Remove trailing newline
        
        // Read other patient data
        printf("       ���֤��ID_Card: \n\t");
        fgets(Patient_list[place].ID_Card, sizeof(Patient_list[place].ID_Card), stdin);
        Patient_list[place].ID_Card[strcspn(Patient_list[place].ID_Card, "\n")] = '\0'; // Remove trailing newline
        
        printf("       �Ƿ�����Is_COVID_Recover: \n\t");
        scanf("%d", &Patient_list[place].Is_COVID_Recover);
        scanf("%*c"); // Consume the newline character left in the buffer
        
        // Read remaining patient data
        printf("       �Ƿ����Is_Double_Positive: \n\t");
        scanf("%d", &Patient_list[place].Is_Double_Positive);
        scanf("%*c"); // Consume the newline character left in the buffer
        
        printf("       ��һ������ʱ��Visit_time(e.g. 2023-06-15): \n\t");
        fgets(Patient_list[place].Visit_time, sizeof(Patient_list[place].Visit_time), stdin);
        Patient_list[place].Visit_time[strcspn(Patient_list[place].Visit_time, "\n")] = '\0'; // Remove trailing newline
        
        printf("       ��һ������ʱ��Recover_time(e.g. 2023-06-16): \n\t");
        fgets(Patient_list[place].Recover_time, sizeof(Patient_list[place].Recover_time), stdin);
        Patient_list[place].Recover_time[strcspn(Patient_list[place].Recover_time, "\n")] = '\0'; // Remove trailing newline

        printf("       ��������ʱ��Double_Visit_time(e.g. 2023-06-16): \n\t");
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
            return 0;
        }
    }
}

//      2 Show Patient Info
void List_Info(){
    int i;
    int flag = 1;
    printf("       Tips: ICR - Is_COVID19_Recover || IDP = Is_DoubleCOVID19_Positive.\n");
    printf("       Title: Num    Name\t      ID_Card\t     ICR   IDP     Visit_time\t Recover_time\t Double_Visit_time\n");
    for(i = 0; i < MAX_PATIENT; ++i){
        if(Patient_exist[i]){
            flag = 0;
            printf("               %d    %-12s %-18s  ", i+1, Patient_list[i].Name, Patient_list[i].ID_Card);
            printf("%-5s %-5s   ", TOF(Patient_list[i].Is_COVID_Recover), TOF(Patient_list[i].Is_Double_Positive));
            printf("%-10s    %-10s      %-10s\n", Patient_list[i].Visit_time, Patient_list[i].Recover_time, Patient_list[i].Double_Visit_time);
        }
    }
    if(flag) printf("\n       Tips: ���ݿ�Ϊ��! None people here.\n");
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
                if(!Empty()) List_Info();
                else printf("       Tips: List Empty.\n");
                return 0;
            }
        }
    }
    printf("       Tips: No such person!\n");
    return -1;
}

//      4 Revise patient data
int Revise_Data_Doc(){
    int i,check;
    char name[30];
    printf("       Input: Please enter the name to revise:");
    scanf("%s", name);
    getchar();
    for(i = 0; i <MAX_PATIENT ; ++i){
        if(Patient_exist[i]){
            if(strcmp(Patient_list[i].Name, name) == 0 ){
                int place = i;
                while (1) {
                    printf("       Input: Please enter the Patient Data with the format:\n");
                
                    // Read patient name using fgets
                    printf("       ����Name: \n\t");
                    fgets(Patient_list[place].Name, sizeof(Patient_list[place].Name), stdin);
                    Patient_list[place].Name[strcspn(Patient_list[place].Name, "\n")] = '\0'; // Remove trailing newline
                    
                    // Read other patient data
                    printf("       ���֤��ID_Card: \n\t");
                    fgets(Patient_list[place].ID_Card, sizeof(Patient_list[place].ID_Card), stdin);
                    Patient_list[place].ID_Card[strcspn(Patient_list[place].ID_Card, "\n")] = '\0'; // Remove trailing newline
                    
                    printf("       �Ƿ�����Is_COVID_Recover: \n\t");
                    scanf("%d", &Patient_list[place].Is_COVID_Recover);
                    scanf("%*c"); // Consume the newline character left in the buffer
                    
                    // Read remaining patient data
                    printf("       �Ƿ����Is_Double_Positive: \n\t");
                    scanf("%d", &Patient_list[place].Is_Double_Positive);
                    scanf("%*c"); // Consume the newline character left in the buffer
                    
                    printf("       ��һ������ʱ��Visit_time: \n\t");
                    fgets(Patient_list[place].Visit_time, sizeof(Patient_list[place].Visit_time), stdin);
                    Patient_list[place].Visit_time[strcspn(Patient_list[place].Visit_time, "\n")] = '\0'; // Remove trailing newline
                    
                    printf("       ��һ������ʱ��Recover_time: \n\t");
                    fgets(Patient_list[place].Recover_time, sizeof(Patient_list[place].Recover_time), stdin);
                    Patient_list[place].Recover_time[strcspn(Patient_list[place].Recover_time, "\n")] = '\0'; // Remove trailing newline

                    printf("       ��������ʱ��Double_Visit_time(e.g. 2023-06-16): \n\t");
                    fgets(Patient_list[place].Double_Visit_time, sizeof(Patient_list[place].Double_Visit_time), stdin);
                    Patient_list[place].Double_Visit_time[strcspn(Patient_list[place].Double_Visit_time, "\n")] = '\0'; // Remove trailing newline

                    printf("       Tips: Please cheak whether the Data appended are right!\n");

                    printf("       Tips: ICR - Is_COVID19_Recover || IDP = Is_DoubleCOVID19_Positive.\n");
                    printf("       Title: Num    Name\t      ID_Card\t     ICR   IDP     Visit_time\t Recover_time\t Double_Visit_time\n");
                    printf("               %d    %-12s %-18s  ", i+1, Patient_list[i].Name, Patient_list[i].ID_Card);
                    printf("%-5s %-5s   ", TOF(Patient_list[i].Is_COVID_Recover), TOF(Patient_list[i].Is_Double_Positive));
                    printf("%-10s    %-10s      %-10s\n", Patient_list[i].Visit_time, Patient_list[i].Recover_time, Patient_list[i].Double_Visit_time);

                    printf("       Input: Check with Y-1 or N-0:");
                    scanf("%d", &check);
                    if(check == 1){
                        Patient_exist[place] = 1;
                        return 0;
                    }
                }
            }
        }
    }
    printf("       Tips: No such person!\n");
    return -1;
}

//      5 Search patient data
int Search_Data_Doc(){
    int i;
    char name[30];
    printf("       Input: Please enter the name to search :");
    scanf("%s", name);
    for(i = 0; i <MAX_PATIENT ; ++i){
        if(Patient_exist[i]){
            if(strcmp(Patient_list[i].Name, name) == 0 ){
                printf("       Tips: ICR - Is_COVID19_Recover || IDP = Is_DoubleCOVID19_Positive.\n");
                printf("       Title: Num    Name\t      ID_Card\t     ICR   IDP     Visit_time\t Recover_time\t Double_Visit_time\n");
                printf("               %d    %-12s %-18s  ", i+1, Patient_list[i].Name, Patient_list[i].ID_Card);
                printf("%-5s %-5s   ", TOF(Patient_list[i].Is_COVID_Recover), TOF(Patient_list[i].Is_Double_Positive));
                printf("%-10s    %-10s      %-10s\n", Patient_list[i].Visit_time, Patient_list[i].Recover_time, Patient_list[i].Double_Visit_time);
                return 0;
            }
        }
    }
    printf("       Tips: No such person!\n");
    return -1;
}

//      6/7 Sort by Visit time
//          Compare Rule
int Compare_Patients_Visit(const void *a, const void *b) {
    const struct Patient *patient1 = (const struct Patient *)a;
    const struct Patient *patient2 = (const struct Patient *)b;
    
    return strcmp(patient1->Visit_time, patient2->Visit_time);
}

//          Sort with 2 mode
void Sort_Patients_Visit(int order) {
    qsort(Patient_list, all, sizeof(struct Patient), Compare_Patients_Visit);

    if (order == 1) {
        // Reverse the sorted array for descending order
        struct Patient temp;
        int i, j;
        for (i = 0, j = all - 1; i < j; i++, j--) {
            temp = Patient_list[i];
            Patient_list[i] = Patient_list[j];
            Patient_list[j] = temp;
        }
    }
    // Print the sorted list
    List_Info();
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
//          Compare Rule
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
        // Reverse the sorted array for descending order
        struct Patient temp;
        int i, j;
        for (i = 0, j = all - 1; i < j; i++, j--) {
            temp = Patient_list[i];
            Patient_list[i] = Patient_list[j];
            Patient_list[j] = temp;
        }
    }
    // Print the sorted list
    List_Info();
}


//      A/B Sort by Visit time
//          Compare Rule
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
        // Reverse the sorted array for descending order
        struct Patient temp;
        int i, j;
        for (i = 0, j = all - 1; i < j; i++, j--) {
            temp = Patient_list[i];
            Patient_list[i] = Patient_list[j];
            Patient_list[j] = temp;
        }
    }
    // Print the sorted list
    List_Info();
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
    fwrite(&list_current, sizeof(int), 1, file);  // Write the current list size
    // Write patient data for existing patients
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
    fread(&list_current, sizeof(int), 1, file);  // Read the current list size
    // Read patient data for existing patients
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
void Doc_Info(int id){
    getchar();
    printf("\n\n\nSet initialization...\n");
    printf("       Tips: ��ӭֵ��ҽ��%s��¼\n",accounts[id].username);
    char Doc_Info_choice;
    printf("\n             �� �� �� Ϣ �� ��    \n");
	printf("       ============================= \n");
	printf("\n         һ����¼"); 
    printf("\n       (1) ׷�Ӽ�¼ "); 
    printf("\n       (2) �б��¼ ");
    printf("\n       (3) ɾ����¼ ");
    printf("\n       (4) �޸ļ�¼ ");
    printf("\n       (5) ������¼ \n");
    printf("\n         ��������"); 
    printf("\n       (6) ������ʱ�併������ ");
    printf("\n       (7) ������ʱ���������� ");
    printf("\n       (8) ������ʱ���������� ");
    printf("\n       (9) ������ʱ���������� ");
    printf("\n       (A) �����λ���ʱ���������� ");
    printf("\n       (B) �����λ���ʱ���������� \n");
    printf("\n         ��������"); 
    printf("\n       (C) �鿴������С��ʿ������ ");
    printf("\n       (D) �޸ġ�����С��ʿ������ ");
    printf("\n       (E) �鿴������120��ȷ���������� ");
    printf("\n       (F) �޸ġ�����120��ȷ���������� \n");
 	printf("\n       (W) д���ļ� ");
    printf("\n       (R) ���ļ��ض�ȡ ");
    printf("\n       (0) �˳� ");
    printf("\n\n       Input: ���������ѡ��:");
    scanf("%c",&Doc_Info_choice);
    while(Doc_Info_choice != '0'){
        switch(Doc_Info_choice){
            case '1':
                Append_Data_Doc();
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case '2':
                List_Info();
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case '3':
                Delete_Data_Doc();
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case '4':
                Revise_Data_Doc();
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case '5':
                Search_Data_Doc();
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case '6':
                Sort_Patients_Visit(1);
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case '7':
                Sort_Patients_Visit(0);
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case '8':
                Sort_Patients_Positive(1);
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case '9':
                Sort_Patients_Positive(0);
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case 'A':
                Sort_Patients_DoublePositive(1);
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case 'B':
                Sort_Patients_DoublePositive(0);
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case 'C':
                ReadFile("tips.txt");
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case 'D':
                ModifyFile("tips.txt");
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case 'E':
                ReadFile("hotline.txt");
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case 'F':
                ModifyFile("hotline.txt");
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case 'W':
                File_Write();
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case 'R':
                File_Read();
                printf("       ");
                system("Pause");
                system("cls");
                break;
        }
        printf("\n             �� �� �� Ϣ �� ��    \n");
        printf("       =============================   \n");
        printf("\n         һ����¼"); 
        printf("\n       (1) ׷�Ӽ�¼ "); 
        printf("\n       (2) �б��¼ ");
        printf("\n       (3) ɾ����¼ ");
        printf("\n       (4) �޸ļ�¼ ");
        printf("\n       (5) ������¼ \n");
        printf("\n         ��������"); 
        printf("\n       (6) ������ʱ�併������ ");
        printf("\n       (7) ������ʱ���������� ");
        printf("\n       (8) ������ʱ���������� ");
        printf("\n       (9) ������ʱ���������� ");
        printf("\n       (A) �����λ���ʱ���������� ");
        printf("\n       (B) �����λ���ʱ���������� \n");
        printf("\n         ��������"); 
        printf("\n       (C) �鿴������С��ʿ������ ");
        printf("\n       (D) �޸ġ�����С��ʿ������ ");
        printf("\n       (E) �鿴������120��ȷ���������� ");
        printf("\n       (F) �޸ġ�����120��ȷ���������� \n");
        printf("\n       (W) д���ļ� ");
        printf("\n       (R) ���ļ��ض�ȡ ");
        printf("\n       (0) �˳� ");
        printf("\n\n       Input: ���������ѡ��:");
        if(Doc_Info_choice != 'D' && Doc_Info_choice != 'F') getchar();
        scanf("%c",&Doc_Info_choice);
    }
}

//  2 Patient Function
//      1 Revise patient data
int Revise_Data_Pat(int place){
    int check;
    while (1) {
        printf("       Input: Please enter the Data with the format:\n");
        // Read patient name using fgets
        printf("       ����Name: \n\t");
        fgets(Patient_list[place].Name, sizeof(Patient_list[place].Name), stdin);
        Patient_list[place].Name[strcspn(Patient_list[place].Name, "\n")] = '\0'; // Remove trailing newline
                    
        // Read other patient data
        printf("       ���֤��ID_Card: \n\t");
        fgets(Patient_list[place].ID_Card, sizeof(Patient_list[place].ID_Card), stdin);
        Patient_list[place].ID_Card[strcspn(Patient_list[place].ID_Card, "\n")] = '\0'; // Remove trailing newline
                    
        printf("       �Ƿ�����Is_COVID_Recover: \n\t");
        scanf("%d", &Patient_list[place].Is_COVID_Recover);
        scanf("%*c"); // Consume the newline character left in the buffer
                    
        // Read remaining patient data
        printf("       �Ƿ����Is_Double_Positive: \n\t");
        scanf("%d", &Patient_list[place].Is_Double_Positive);
        scanf("%*c"); // Consume the newline character left in the buffer
                    
        printf("       ��һ������ʱ��Visit_time(e.g. 2023-06-16): \n\t");
        fgets(Patient_list[place].Visit_time, sizeof(Patient_list[place].Visit_time), stdin);
        Patient_list[place].Visit_time[strcspn(Patient_list[place].Visit_time, "\n")] = '\0'; // Remove trailing newline
                    
        printf("       ��һ������ʱ��Recover_time(e.g. 2023-06-16): \n\t");
        fgets(Patient_list[place].Recover_time, sizeof(Patient_list[place].Recover_time), stdin);
        Patient_list[place].Recover_time[strcspn(Patient_list[place].Recover_time, "\n")] = '\0'; // Remove trailing newline

        printf("       ��������ʱ��Double_Visit_time(e.g. 2023-06-16): \n\t");
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
            return 0;
        }
    }
}

//      Patient Info
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
            //�������ڼ�¼����������Ϣ������ת����ʾ���½��棺
            printf("\n       Input: �������������֤����ID_Card:\n       ");
            place = Empty_Search();
            fgets(Patient_list[place].ID_Card, sizeof(Patient_list[place].ID_Card), stdin);
            Patient_list[place].ID_Card[strcspn(Patient_list[place].ID_Card, "\n")] = '\0'; // Remove trailing newline

            printf("\n       Tips: ���֤����Ϊ %s ���û���ע��:\n\n ",Patient_list[place].ID_Card); 

            // Read patient name using fgets
            printf("       ����Name: \n\t");
            fgets(Patient_list[place].Name, sizeof(Patient_list[place].Name), stdin);
            Patient_list[place].Name[strcspn(Patient_list[place].Name, "\n")] = '\0'; // Remove trailing newline
            
            printf("       �Ƿ�����Is_COVID_Recover: \n\t");
            scanf("%d", &Patient_list[place].Is_COVID_Recover);
            scanf("%*c"); // Consume the newline character left in the buffer
            
            // Read remaining patient data
            printf("       �Ƿ����Is_Double_Positive: \n\t");
            scanf("%d", &Patient_list[place].Is_Double_Positive);
            scanf("%*c"); // Consume the newline character left in the buffer

            printf("       ��һ������ʱ��Visit_time(e.g. 2023-06-15): \n\t");
            scanf("%*c"); // Consume the newline character left in the buffer
            fgets(Patient_list[place].Visit_time, sizeof(Patient_list[place].Visit_time), stdin);
            Patient_list[place].Visit_time[strcspn(Patient_list[place].Visit_time, "\n")] = '\0'; // Remove trailing newline

            printf("       ��һ������ʱ��Recover_time(e.g. 2023-06-16): \n\t");
            scanf("%*c"); // Consume the newline character left in the buffer
            fgets(Patient_list[place].Recover_time, sizeof(Patient_list[place].Recover_time), stdin);
            Patient_list[place].Recover_time[strcspn(Patient_list[place].Recover_time, "\n")] = '\0'; // Remove trailing newline

            printf("       ��������ʱ��Double_Visit_time(e.g. 2023-06-16): \n\t");
            scanf("%*c"); // Consume the newline character left in the buffer
            fgets(Patient_list[place].Double_Visit_time, sizeof(Patient_list[place].Double_Visit_time), stdin);
            Patient_list[place].Double_Visit_time[strcspn(Patient_list[place].Double_Visit_time, "\n")] = '\0'; // Remove trailing newline

            Patient_exist[place] = 1;
            ++list_current;
            Pat_Info_Choice = '1';
        }
        else if(Pat_Info_Choice == '1'){
            //�����ڼ�¼����������Ϣ������ת��Ӧ���ߵļ�¼��Ϣ����ʾ���½��棺
            printf("\n ");
            printf("\n       %s��������! ����Ϊ���ڱ�Ժ�Ǽǵĸ�����Ϣ��\n",Patient_list[place].Name);
            printf("\n       (1)���֤��             (2)����ʱ�� \n");
            printf("          %-18s      %s\n", Patient_list[place].ID_Card, Patient_list[place].Visit_time);
            printf("       (3)�Ƿ�Ϊ����           (4)���Ƿ�����    \n");
            printf("          %-18s      %s\n", TOF(Patient_list[place].Is_COVID_Recover), TOF(Patient_list[place].Is_Double_Positive));
            printf("       (5)����ʱ��             (6)��������ʱ��  \n");
            printf("          %-18s      %s\n", Patient_list[place].Recover_time, Patient_list[place].Double_Visit_time);
                
            printf("\n");
            printf("\n       =================================   \n");
            printf("\n       (1) �޸ļ�¼                          "); 
            printf("\n       (2) �鿴������С��ʿ������             ");
            printf("\n       (3) �鿴������120��ȷ����������        ");
            printf("\n");
            printf("\n       Input: ������ѡ�� Enter choice:");
            scanf("%c",&Pat_Info_Choice);
            getchar();
            while(Pat_Info_Choice != '0'){
                switch(Pat_Info_Choice){
                    case '1':
                        Revise_Data_Pat(place);
                        getchar();
                        printf("       ");
                        system("Pause");
                        system("cls");
                        break;
                    case '2':
                        ReadFile("tips.txt");
                        printf("       ");
                        system("Pause");
                        system("cls");
                        break;
                    case '3':
                        ReadFile("hotline.txt");
                        printf("       ");
                        system("Pause");
                        system("cls");
                        break;
                }
                printf("\n ");
                printf("\n       %s��������! ����Ϊ���ڱ�Ժ�Ǽǵĸ�����Ϣ��\n",Patient_list[place].Name);
                printf("\n       (1)���֤��             (2)����ʱ�� \n");
                printf("          %-18s      %s\n", Patient_list[place].ID_Card, Patient_list[place].Visit_time);
                printf("       (3)�Ƿ�Ϊ����           (4)���Ƿ�����    \n");
                printf("          %-18s      %s\n", TOF(Patient_list[place].Is_COVID_Recover), TOF(Patient_list[place].Is_Double_Positive));
                printf("       (5)����ʱ��             (6)��������ʱ��  \n");
                printf("          %-18s      %s\n", Patient_list[place].Recover_time, Patient_list[place].Double_Visit_time);
                    
                printf("\n");
                printf("\n       =================================   \n");
                printf("\n       (1) �޸ļ�¼                          "); 
                printf("\n       (2) �鿴������С��ʿ������             ");
                printf("\n       (3) �鿴������120��ȷ����������        ");
                printf("\n");
                printf("\n       Input: ������ѡ�� Enter choice:");
                scanf("%c",&Pat_Info_Choice);
                getchar();
            }
        }
    }while(Pat_Info_Choice != '0');
}

//  702813 Administrator function
//      B load account from file
void loadAccountsFromFile(){
    FILE *file = fopen("accounts.dat", "r");
    if(file == NULL){
        printf("       Tips: �޷����ļ����ж�ȡ Fail to read.\n");
        return;
    }
    numAccounts = 0;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    while(fscanf(file, "%s %s", username, password) == 2){
        if (numAccounts == MAX_ACCOUNTS) {
            printf("       Tips: �ļ��е��˺ų����������������� Oversize.\n");
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
    
    printf("       Input: �������˺� Account:");
    scanf("%s", username);
    
    printf("       Input: ���������� Password:");
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
        printf("       Tips: �Ѵﵽ�˺����� Account full.\n");
        return;
    }
    struct Account newAccount;

    printf("       Input: �������˺� Account:");
    scanf("%s", newAccount.username);
    printf("       Input: ���������� Password:");
    scanf("%s", newAccount.password);

    accounts[numAccounts] = newAccount;
    numAccounts++;
    printf("       Tips: �˺Ŵ����ɹ� Account exist.\n");
}

//      2 delete account
void deleteAccountFromFile() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("       Input: ������Ҫɾ�����˺� Delete Account:");
    scanf("%s", username);
    printf("       Input: ������Ҫɾ�����˺����� Delete Password:");
    scanf("%s", password);

    FILE *file = fopen("accounts.dat", "r");
    if (file == NULL) {
        printf("       Tips: �޷����ļ����ж�ȡ Read fail.\n");
        return;
    }
    // ������ʱ�ļ����ڴ洢δɾ�����˺�����
    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL) {
        printf("       Tips: �޷�����ʱ�ļ�����д�� Temp fail.\n");
        fclose(file);
        return;
    }
    int found = 0;
    char currUsername[MAX_USERNAME_LENGTH];
    char currPassword[MAX_PASSWORD_LENGTH];
    // ���ж�ȡ�ļ�����δƥ����˺�����д����ʱ�ļ�
    while (fscanf(file, "%s %s", currUsername, currPassword) == 2) {
        if (strcmp(currUsername, username) == 0 && strcmp(currPassword, password) == 0) {
            found = 1;  // ����ҵ�ƥ����˺�����
        } else {
            fprintf(tempFile, "%s %s\n", currUsername, currPassword);
        }
    }
    fclose(file);
    fclose(tempFile);
    // ɾ��ԭ�ļ�������ʱ�ļ�������Ϊԭ�ļ���
    if (remove("accounts.dat") != 0) {
        printf("       Tips: �޷�ɾ���ļ� Delete error.\n");
        return;
    }
    if (rename("temp.txt", "accounts.dat") != 0) {
        printf("       Tips: �޷��������ļ� Rename error.\n");
        return;
    }
    if (found) {
        printf("       Tips: �˺������Ѵ��ļ���ɾ�� Remove success.\n");
    } else {
        printf("       Tips: δ�ҵ�ƥ����˺����� No match.\n");
    }
}

//      3 Display all accounts
void displayAllAccounts() {
    FILE *file = fopen("accounts.dat", "r");
    if (file == NULL) {
        printf("       Tips: �޷����ļ����ж�ȡ Read fail.\n");
        return;
    }
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("       Tips: Account & Password\n");
    while (fscanf(file, "%s %s", username, password) == 2) {
        printf("       �˺ţ�%s  ���룺%s\n", username, password);
    }
    fclose(file);
}

//      4 Save account to file
void saveAccountsToFile() {
	int i;
    FILE *file = fopen("accounts.dat", "w");
    if (file == NULL) {
        printf("       Tips: �޷����ļ�����д�� Write fail.\n");
        return;
    }
    for (i = 0; i < numAccounts; i++) {
        fprintf(file, "%s %s\n", accounts[i].username, accounts[i].password);
    }
    fclose(file);
    printf("       Tips: �˺������ѱ��浽�ļ��� Save success.\n");
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
        printf("\n       ����ԱģʽAdmin Mode\n");
        printf("       0. �˳�ģʽ Exit\n");
        printf("       1. �����˺� Create\n");
        printf("       2. ɾ���˺� Delete\n");
        printf("       3. ��ʾ�����˺� ShowInfo\n");
        printf("       4. д���ļ� Write\n");
        printf("       Input: Please enter the choice:");
        scanf("%d", &choice);
        printf("\n\n");
        switch(choice){
            case 0:
                printf("       ");
                return;
            case 1:
                createAccount();
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case 2:
                deleteAccountFromFile();
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case 3:
                displayAllAccounts();
                printf("       ");
                system("Pause");
                system("cls");
                break;
            case 4:
                saveAccountsToFile();
                printf("       ");
                system("Pause");
                system("cls");
                break;
            default:
                printf("       Tips: ��Ч��ѡ�� Choose error.\n");
        }
    }
}

//MainInfo include Patient and Doctor
int MainInfo(){
    int identity;
    int id;
    scanf("%d",&identity);
    while(!(identity == 1 || identity == 2 || identity == 702813)){
        printf("        Tips: Input error Please try again.\n        ");
        scanf("%d",&identity);
    }
    if(identity == 1){  //Doctor Part
        printf("       Input: Please enter the Account-Password order for log-in:\n");
        int try;
        char password[30];
        
        do{
            try = 1;
            do{
                printf("        (%d - %d)\n", try, MAX_PASSWORD_TRY);
                if((id = login()) != -1){
                    Doc_Info(id);
                    return 0;
                }
                ++try;
            }while(try <= MAX_PASSWORD_TRY);
            printf("        Tips: Authority Denied for your %d try(s).\n",MAX_PASSWORD_TRY);
        }while(Continue() == 1);
    }
    else if(identity == 2){  //Patient Part
        Pat_Info();
    }
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
                    return 0;
                }
                ++try;
            }while(try <= MAX_PASSWORD_TRY);
            printf("        Input: Authority Denied for your %d try(s).\n",MAX_PASSWORD_TRY);
        }while(Continue() == 1);
    }
}

//Main Info
int main(){
    printf("Set initialization...\n");
    memset(Patient_exist, 0, sizeof(int) * MAX_PATIENT);
    File_Read();
    loadAccountsFromFile();
    list_current = 0;
	printf("\n");
	printf("Display Main Info...\n\n");
	printf("              ���������ʵ��    ʵ�飨�壩 �¹����鳣̬�����ؽ׶�ҽ���뻼����Ϣ����ϵͳ\n");
	printf("       Welcome to Doctor/Patient MIS in NPC(Normal prevention and control) stage of COVID-19\n");
    printf("\n");
	printf("                             22�ƿ�C1�� ����� �����   2023.06.19\n\n");
    printf("                  ����˵��Begin tip : Continue with identity Doctor(1) or Patient(2)\n");
	printf("       ======================================================================================\n");
    printf("                            (1)ҽ��                      (2)����\n"); 
    printf("\n       ��ѡ����ȷ��ݵ�¼��");
    MainInfo();
	return 0;
}
