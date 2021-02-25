#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>


char *getWord (char *text, int start, bool *isEnterFound) { /* returns a single word from text starts searching from start */
    char *word,*q; /* q = a helper string to make sure mallocing well */
    char token; /* token is the right now input char */
    int i = 0;
    int j = start;
    word = malloc(sizeof(char)*50);
    while (isalnum(token = text[j++]) || token == '\n') { 
        if (token == '\n')
        {
            (*isEnterFound) = true;
            break;
        }
        word[i++] = token;
        /*q = realloc(word, (strlen(word) + 2) * sizeof(char));
        if (!q) {
            fprintf(stderr, "Out of memory\n");
            exit(1);
        }
        word = q;*/
    }
    word[i] = '\0';
    return word;
}

void tolowerString (char *input) { /* Changes a string so all the letters in it will by lower */
    int i;
    for (i = 0; i < strlen(input); ++i)
    {
        input[i] = tolower(input[i]);
    }
}



/* Tree functions area */ 
typedef struct Node
{
    /* data */
    char *word;
    int lines[30];
    int linesLength;
    struct Node *ls;
    struct Node *rs;
    int count;

}Node;


Node* newNode(char* word, int line) { /* Return a new node with the vars given to the funcion */
    Node *p = (Node*) malloc (sizeof(Node)); 
    p->word = word;
    //p->lines = malloc(sizeof(int));
    p->lines[0] = line;
    p->linesLength = 1;
    p->ls = p->rs = NULL; 
    p->count=1;
    return p; 
}

void insert(Node **root, char *word, int line) { /* Insert node to tree using recursion */
    int *q;
    int i;
    if(!*root) {
        *root = newNode(word, line); 
        return; 
    }
    if(strcmp(word, (*root)->word) < 0)  /* In case word is smaller than the nodes word */
    { 
        insert(&((*root)->ls),word,line); 
    }
    else if (strcmp(word, (*root)->word) == 0) /* In case word already exist */
    {
        for (i = 0; i < (*root)->linesLength; ++i)
        {
            if ((*root)->lines[i] == line)
            {
                return;
            }
        }
        /*q = realloc((*root)->lines, (*root)->linesLength + 2);
        if (!q)
        {
            fprintf(stderr, "Out of memory!\n");
            exit(1);
        }*/

        //(*root)->lines = q;
        (*root)->lines[(*root)->linesLength] = line;
        (*root)->linesLength++;
        (*root)->count++;
        
        return;
    }
    else /* In case word is bigger than the nodes word */
    {
        insert(&((*root)->rs),word,line); 
    }
}

void printTreeRec(Node *root) { /* A recursive function which prints the tree by given root */
    int i;

    if(!root) {
        return; 
    }
    printTreeRec(root->ls);

    printf("The word: \"%s\" ",root->word); 
    if (strlen(root->word) < 15) {
        for (i = 0; i < 15 - strlen(root->word); ++i) {
            printf(" ");
        }
    }   
    printf("appears in ");
    if (root->linesLength == 1) {
        printf("line: ");
    }
    else {
        printf("lines: ");
    }
    for (i = 0;i < root->linesLength - 1; i++) {
        printf("%d, ", root->lines[i]);
    }
    printf("%d", root->lines[i]);
    printf(" with %d", root->count);
    printf("\n");

    printTreeRec(root->rs);
}

void freeTree(Node *root) { /* A function to free the tree recursively */
    if(!root)
        return; 
    freeTree(root->ls);
    freeTree(root->rs); 
    free(root->lines);
    free(root->word);
    free(root); 
}

    

int main(){
   
    FILE *fptr = fopen("vanban.txt","r");
    FILE *fptr1 = fopen("stopw.txt","r");

    char str[30][30];
    
    printf("aaaaaa");
    int i=0;
    char tmp[50];
    while(fscanf(fptr1,"%s\n",tmp)!=EOF){
        strcpy(str[i],tmp);
       
        i++;

    }
    int count =i;
    char *word;



    //printf("%s",text);
    char text[300];

      int line = 1; /* Line counter */
    bool foundEnter = false;
    bool *isEnterFound = &foundEnter;
    Node *root = NULL; /* First node of the tree */
     /* Pointer to what was the last thing readed in text string */
    while(fgets(text,300,fptr)!=NULL){
        printf("%s",text);
        int start = 0;


    while (start < strlen(text)) {
        word = getWord(text, start, isEnterFound); /* If getWord detected enter foundEnter will become true */
        tolowerString(word);
       
        start += strlen(word) + 1;
       
       
      
       
        if (strcmp(word, "") != 0 ) {
            int check =1;
          
            i=0;
            while (i<=count){
                
                if(strcmp(word,str[i])==0){
                    check =0;
                    //if(check==0) printf("co check\n");
                    break;
                }
                i++;
                
            }
            if(check ==1){
                
                insert(&root,word,line);
                }
            
           
        }

        if (foundEnter)
        {
            foundEnter = false;
            line++;
        }
       
       
    }
    }
    printTreeRec(root);

   
    
    
   //free(root);

    fclose(fptr1);
    fclose(fptr);


}