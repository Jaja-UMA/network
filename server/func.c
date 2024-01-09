#include"libs.h"
#include"header.h"

/* グローバル変数 ********************************************************** */
struct profile profile_data[10000];
int    nprofiles = 0;
char   sending[BUF_SIZE];

int myprint(const char *text){
    int n,textLen;
    char tmpText[BUF_SIZE];

    textLen = strlen(text);
    n=0;
    while(n<=textLen){
        strncpy(tmpText,text+n,BUF_SIZE);
        write(1,tmpText,BUF_SIZE);
        n+=BUF_SIZE;
    }
    putchar('\n');
    return 1;
}
//recvでもらった文字列からGETやPOSTを判断
char * bufToFile(const char *path)
{
    char method[10];
    char data[BUF_SIZE];

    // Use sscanf to extract the method and data
    if (sscanf(path, "%s %s", method, data) != 2) {
        fprintf(stderr, "Invalid request format: %s\n", path);
        return;
    }

    // Process the request based on the method
    if (strcmp(method, "POST") == 0) {
        printf("Processing POST request with data: %s\n", data);

    } else if (strcmp(method, "GET") == 0) {
        printf("Processing GET request for: %s\n", data);
        // Add your GET request handling code here
    } else {
        fprintf(stderr, "Unsupported method: %s\n", method);
    }

    return '0';

}

char* countStrlen(const char *messege)
{
    char len[10];

}


void subst (char *s, char from, char to) {
  int n;

  for (n = 0; s[n] != '\0'; n++) {
    if (s[n] == from) {
      s[n] = to;
    }
  }
}

/* ************************************************************************* *
 * 文字列strを区切り文字separatorで最大nitems個に分割して、分割した文字列の
 * それぞれの先頭アドレスを配列retに代入する関数
 * ************************************************************************* */
int split (char *str, char *ret[], char separator, int nitems) {
  int count = 0, n;

  ret[count++] = str;

  for (n = 0; str[n] != '\0' && count < nitems; n++) {
    if (str[n] == separator) {
      str[n] = '\0';
      ret[count++] = str + n + 1;
    }
  }
  return count;
}

/* ************************************************************************* *
 * 入力文字列lineを解析してデータを登録する関数
 * ************************************************************************* */
struct profile* add_profile (struct profile *p,
	     char           *line) {
  char *data[5], *birth[3];
  printf("プロフィール登録\n");
  split(line, data, ',', 5);

  p->id = atoi(data[0]);
  strcpy(p->name, data[1]);
  strcpy(p->home, data[3]);
  p->comment = (char *) malloc(sizeof(char) * (strlen(data[4])+1));
  strcpy(p->comment, data[4]);


  split(data[2], birth, '-', 3);
  p->birthday.y = atoi(birth[0]);
  p->birthday.m = atoi(birth[1]);
  p->birthday.d = atoi(birth[2]);

  return p;
}

/* 終了コマンド(%Q) ******************************************************** */
void command_quit (void) {
  exit(0);
}

/* チェックコマンド(%C) **************************************************** */
void command_check (void) {
  printf ("%d profile(s)\n", nprofiles);
  sprintf(sending,"%d profile(s)\n", nprofiles);
}

/* ************************************************************************* *
 * 登録データを１つ表示する関数
 * ************************************************************************* */
void print_profile (struct profile	*p) {
  printf("Id    : %d\n", p->id);
  printf("Name  : %s\n", p->name);
  printf("Birth : %04d-%02d-%02d\n",p->birthday.y,p->birthday.m,p->birthday.d);
  printf("Addr  : %s\n", p->home);
  printf("Com.  : %s\n", p->comment);
}
/* ************************************************************************* *
 * データをCSV形式で出力する関数
 * ************************************************************************* */
void print_profile_csv (FILE *fp, struct profile *p) {
  fprintf(fp, "%d,", p->id);
  fprintf(fp, "%s,", p->name);
  fprintf(fp, "%04d-%02d-%02d,",p->birthday.y,p->birthday.m,p->birthday.d);
  fprintf(fp, "%s,", p->home);
  fprintf(fp, "%s\n", p->comment);
}

/* プリントコマンド(%P) **************************************************** */
void command_print (struct profile	*p,
	       int		num) {
  int	start = 0, end = nprofiles;
  int	n;

  if (num > 0 && num < nprofiles) {
    end = num;
  } else if (num < 0 && num + end > 0) {
    start = num + end;
  }
  for (n = start; n < end; n++) {
    print_profile(&p[n]);
    printf("\n");
  }
}

/* 読み込みコマンド(%R) **************************************************** */
void command_read (struct profile	*p,
	      char		*filename) {
  FILE *fp = fopen(filename, "r");

  if (fp == NULL){
    fprintf(stderr, "%R: file open error %s.\n", filename);
  } else {
    while (parse_input(fp));
    fclose(fp);
  }
}

/* 書き出しコマンド(%W) **************************************************** */
void command_write (struct profile	*p,
	       char		*filename) {
  int  n;
  FILE *fp = fopen(filename, "w");

  if (fp == NULL){
    fprintf(stderr, "%W: file write error %s.\n", filename);
  } else {
    for (n = 0; n < nprofiles; n++) {
      print_profile_csv(fp, &p[n]);
    }
    fclose(fp);
  }
}

/* ************************************************************************* *
 * IDの値を文字列に変換する関数
 * ************************************************************************* */
void make_id_string (int  id,
		char *str) {
  sprintf (str, "%d", id);
}

/* ************************************************************************* *
 * Date構造体の値を-区切りの文字列に変換する関数
 * ************************************************************************* */
void make_birth_string (struct date *birth,
		   char        *str) {
  sprintf (str, "%04d-%02d-%02d", birth->y, birth->m, birth->d);
}

/* 検索コマンド(%F) ******************************************************** */
void command_find (struct profile	*p,
	      char		*keyword) {
  char            id[8], birth[11];
  int             n;

  for (n = 0; n < nprofiles; n++) {
    make_id_string (p[n].id, id);
    make_birth_string (&p[n].birthday, birth);
    if (strcmp (id, keyword) == 0        ||
	strcmp (birth, keyword) == 0     ||
	strcmp (p[n].name, keyword) == 0 ||
	strcmp (p[n].home, keyword) == 0) {
      print_profile (&p[n]);
      printf ("\n");
    }
  }
}

/* ************************************************************************* *
 * 各項目でのソート関数
 * ************************************************************************* */
int sort_by_id (struct profile	*p1,
	    struct profile	*p2) {
  return p1->id - p2->id;
}

int sort_by_name (struct profile	*p1,
	      struct profile	*p2) {
  return strcmp (p1->name, p2->name);
}

int sort_by_birthday (struct profile	*p1,
		  struct profile	*p2) {
  if (p1->birthday.y != p2->birthday.y) return p1->birthday.y - p2->birthday.y;
  if (p1->birthday.m != p2->birthday.m) return p1->birthday.m - p2->birthday.m;
  if (p1->birthday.d != p2->birthday.d) return p1->birthday.d - p2->birthday.d;

  return 0;
}

int sort_by_home (struct profile	*p1,
	      struct profile	*p2) {
  return strcmp (p1->home, p2->home);
}

int sort_by_comment (struct profile	*p1,
		 struct profile	*p2) {
  return strcmp (p1->comment, p2->comment);
}

/* ************************************************************************* *
 * クイックソート
 * ************************************************************************* */
void quick_sort (struct profile	*p,
	    int			start,
	    int			end,
	    int			(*compare_func) (struct profile	*p1,
						 struct profile	*p2)) {
  struct profile	tmp, key;
  int			left, right;

  /* キーを決める */
  key = p[(start + end) / 2];

  /* 交換するデータを交換する */
  left = start;
  right = end;

  while (1) {
    while (compare_func(&key, &p[left])  > 0)  left++;
    while (compare_func(&key, &p[right]) < 0) right--;
    if (left >= right) break;
    tmp = p[left];
    p[left]  = p[right];
    p[right] = tmp;
  }
  /* 左部分をさらにソート */
  if (start < left - 1) quick_sort(p, start, left - 1, compare_func);

  /* 右部分をさらにソート */
  if (end > right + 1)  quick_sort(p, right + 1, end, compare_func);
}

/* ************************************************************************* *
 * ソート関数の配列
 * ************************************************************************* */
int (*compare_function[]) (struct profile	*p1,struct profile	*p2) =
{
  sort_by_id,
  sort_by_name,
  sort_by_birthday,
  sort_by_home,
  sort_by_comment
};

/* 整列コマンド(%S) ******************************************************** */
void command_sort (struct profile    *p,
	      int               column) {
  quick_sort(profile_data, 0, nprofiles-1, compare_function[column-1]);
}

/* ************************************************************************* *
 * コマンド分岐関数
 * ************************************************************************* */
void exec_command (char	command,
	      char	*parameter) {
  switch (command) {
  case 'Q':
    command_quit();
    break;
  case 'C':
    command_check();
    break;
  case 'P':
    command_print(profile_data, atoi(parameter));
    break;
  case 'R':
    command_read(profile_data, parameter);
    break;
  case 'W':
    command_write(profile_data, parameter);
    break;
  case 'F':
    command_find(profile_data, parameter);
    break;
  case 'S':
    command_sort(profile_data, atoi(parameter));
    break;
  default:
    printf("Invalid command '%c' was found.\n", command);
    break;
  }
}

/* ************************************************************************* *
 * 入力文字列の解析
 * ************************************************************************* */
int parse_input (char *line) {

  subst(line, '\n', '\0');
  if (line[0] == '%') {
    printf("上来た\n");
    exec_command(line[1], &line[3]);
  } else {
    printf("下来た\n");
    add_profile(&profile_data[nprofiles], line);
    nprofiles++;
  }
  return 1;
}
