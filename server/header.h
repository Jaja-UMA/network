#define BUF_SIZE 1000000
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



int myprint(const char *);
char* fileToOut(const char*);

char *countStrlen(const char *message);

void subst(char *s, char from, char to);

int split(char *str, char *ret[], char separator, int nitems);

struct profile *add_profile(struct profile *p, char *line);

void command_quit(void);

void command_check(void);

int  print_profile(struct profile *p,char *);

void print_profile_csv(FILE *fp, struct profile *p);

void command_print(struct profile *p, int num);

void command_read(struct profile *p, char *filename);

void command_write(struct profile *p, char *filename);

void make_id_string(int id, char *str);

void make_birth_string(struct date *birth, char *str);

void command_find(struct profile *p, char *keyword);

int sort_by_id(struct profile *p1, struct profile *p2);

int sort_by_name(struct profile *p1, struct profile *p2);

int sort_by_birthday(struct profile *p1, struct profile *p2);

int sort_by_home(struct profile *p1, struct profile *p2);

int sort_by_comment(struct profile *p1, struct profile *p2);

void quick_sort(struct profile *p, int start, int end, int (*compare_func)(struct profile *p1, struct profile *p2));

void command_sort(struct profile *p, int column);

void exec_command(char command, char *parameter);

int parse_input(char *);
