// ---- Consatants ----
#define MAX_NAME_CHAR 31
#define MAX_ID_CHAR 31
#define MAX_PWD_CHAR 31
#define MAX_CMD_CHAR 31

#define CH_MAX_NAME_CHAR "30"
#define CH_MAX_ID_CHAR "30"
#define CH_MAX_PWD_CHAR "30"
#define CH_MAX_CMD_CHAR "30"

#define PWDLENGTH 20 // password length for generation

#define FILENAME "PasswordManager.txt"
#define ENCRYPTFILENAME "PasswordManager"

#define PASSWORDLEN 128 // password length for opening
#define CH_PASSWORDLEN "127"
#define PWDFILE "pwdfile"

//#define WINDOWS 1
#define LINUX 1

// ---- Errors ----
#define BANNEDCHAR1 '|'

#define ERROR1 "ERROR1 : Dyanmic allocation do not success"
#define ERROR2 "ERROR2 : Wrong line number enter"
#define ERROR3 "ERROR3 : An error occurred opening a file"
#define ERROR4 "ERROR4 : An error occurred with linked lists"
#define ERROR5 "ERROR5 : Use of banned charter '|'"

// ---- Structures ----
typedef struct link {
    char name[MAX_NAME_CHAR];
    char id[MAX_ID_CHAR];
    char pwd[MAX_PWD_CHAR];
    struct link * nextLink;
} Link;

typedef struct linkedList {
    struct link * head;
    int size;
    struct link * tail;
} LinkedList;
