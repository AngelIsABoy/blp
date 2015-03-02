#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<curses.h>

#define MAX_STRING     80     /* Longest allowed response          */
#define MAX_ENTRY      2014   /* Longest allowed database entry    */

#define MESSAGE_LINE   6      /* Misc. message on this line        */
#define ERROR_LINE     22     /* Line to use for errors            */
#define Q_LINE         20     /* Line for questions                */
#define PROMPT_LINE    18     /* Line for prompting on             */

static char current_cd[MAX_STRING] = "\0";
static char current_cat[MAX_STRING];

const char *title_file = "title.cdb";
const char *tracks_file = "tracks.cdb";
const char *temp_file = "cdb.tmp";

void clear_all_screen(void);
void get_return(void);
int  get_confirm(void);
int  getchoice(*char *greet, char *choices[]);
void draw_menu(char *options[], int highlight, int start_row, int start_col);
void insert_title(char *cdtitle);
void get_string(char *string);
void add_record(void);
void count_cds(void);
void find_cd(void);
void list_tracks(void);
void remove_tracks(void);
void remove_cd(void);
void update_cd(void);

char *main_menu[] = {
    "add new CD",
    "fine CD",
    "count CDs and tracks in the catalog",
    "quit",
    0,
}

char *extended_menu[] = {
    "add new CD",
    "find CD",
    "count CDs and tracks in the catalog",
    "list tracks on current CD",
    "remove current CD",
    "update track information",
    "quit",
    0,
}

int main(){
    int choice;
    initscr();
    do {
        choice = get choice("Options:", current_cd[0] ? ectend_menu : main_menu);
        switch(choice) {
            case 'q':
                break;
            case 'a':
                add_record();
                break;
            case 'c':
                count_cds();
                break;
            case 'f':
                find_cd();
                break;
            case 'l';
                lisk_tracks();
                break;
            case 'r':
                remove_cd();
                break;
            case 'u':
                update_cd();
                break;
        }
    } while (choice != 'q');
    endwin();
    exit(EXIT_SUCCESS);
}

int getchoice(char *greet, char *choices[]) {
    static int selected_row = 0;
    int max_row = 0;
    int start_screenrow = MESSAGE_LINE, start_screencol = 10;
    char **option;
    int selected;
    int key = 0;

    option = choices;
    while (*option) {
        max_row++;
        option++;
    }
/* protect against menu getting shorter when CD deleted */
    if (selected_row >= max_row)
        selected_row = 0;
    clear_all_screen();
    mvprintw(start_screenrow - 2, start_screencol, greet);
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    key = 0;
    while (key != 'q' && key != KEY_ENTER && key != '\n') {
        if (key == KEY_UP) {
            if (selected_row == 0) 
                selected_row = max_row - 1;
            else
                selected_row--;
        } 
        if (key == KEY_DOWN) {
            if (selected_row == (max_row - 1))
                selected_row = 0;
            else
                selected_row++;
        }
        selected = *choices[selected_row];
        draw_menu(choices, selected_row, start_screenrow, start_screencol);
        
        key = getch();
    }
    keypad(stdscr, FALSE);
    nocbreak();
    echo();

    if (key == 'q')
        selected = 'q';
    
    return (selected);
}




























