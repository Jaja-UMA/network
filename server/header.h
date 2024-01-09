#define BUF_SIZE 1024
#define PORT 61001
/* 個人データ用構造体 ****************************************************** */
struct date {
  int y;
  int m;
  int d;
};

struct profile {
  int         id;
  char        name[70];
  struct date birthday;
  char        home[70];
  char       *comment;
};

/* グローバル変数 ********************************************************** */
struct profile profile_data[10000];
int    nprofiles = 0;

int myprint(const char *);
char* fileToOut(const char*);
char* countStrlen(const char *);
