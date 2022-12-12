// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <fcntl.h>
// #include <sys/stat.h>
// #include <dirent.h>
// typedef struct list{
//     char* name;
//     struct list* next;
//     struct stat filestat; 
// }list;

// int my_strcmp(char* p1,char* p2){

//     int i=0;

//       while( (p1[i] == p2[i]) && (p1[i] != '\0') && (p2[i] != '\0') ){
//         i++;
//     }

//     return p1[i]-p2[i];

// }
//  void my_list_print(list* nodes, int flag){

//      while(nodes){

//         if(flag == 2 || !flag){

//             if(nodes->name[0] != '.')
//             printf("%s\n", nodes->name);

//         }else{
//             printf("%s\n", nodes->name);
//         }
//         nodes = nodes->next;
//     }
//  }

// list* my_first_addLast_(list *node, char * name,struct stat filestat){
   
//     list *new_node = malloc(sizeof(list));
//     new_node->name = name;
//     new_node->next = NULL;
//     new_node->filestat = filestat;
//     if(node == NULL)    
//         node = new_node;
//     else
//     {
//         list *last_node = node;
//         while (last_node->next != NULL) {
//             last_node = last_node->next;
//         }
//         last_node->next = new_node;
//     }
//     return node;
// }
// void my_swap(list*  head, list* N_next){
//    char* swap = (char*)malloc(25);
//             struct stat filestat;
//             swap = head->name;
//             head->name =N_next->name;
//             N_next->name = swap;
//             filestat = head->filestat;
//             head->filestat = N_next->filestat;
//             N_next->filestat = filestat;
// }

//   list* sort_time_a(list* node,int flag){
//     list* headers = node;
//     while(headers->next != NULL){
//         list* N_next = headers->next;      
//         while(N_next != NULL){
//             if(flag == 2|| flag == 3){
//                 if(headers->filestat.st_mtim.tv_sec == N_next->filestat.st_mtim.tv_sec){
//                     if(headers->filestat.st_mtim.tv_nsec <= N_next->filestat.st_mtim.tv_nsec){
//                         my_swap(headers, N_next);
//                     }
//                 }else if(headers->filestat.st_mtim.tv_sec <= N_next->filestat.st_mtim.tv_sec ){
//                     my_swap(headers, N_next);
//                 }
//             }else{
//                 if(my_strcmp(headers->name, N_next->name)>= 0){
//                     my_swap(headers, N_next);
//                 }
//             }
//             N_next = N_next->next;
//         }
//         headers = headers->next;
//     }
//     return node;
// }
// void open_dir_file(int flag){
//      DIR *dir;
//     struct dirent *entry;
//     struct stat fs;
//     list *node = (list*)malloc(sizeof(list));
//     node=NULL;
//     dir = opendir(".");
//     if(dir == NULL)
//         perror("Unable to read directory");
//     while((entry= readdir(dir))){
//         stat(entry->d_name, &fs);
//         node = my_first_addLast_(node, entry->d_name, fs);
//     }
//     node = sort_time_a(node, flag);
//     my_list_print(node, flag);
    
//     closedir(dir);
// }

// list* sort_g(){


//     list* nodes_1 =(list*)malloc(sizeof(list));
//     list* nodes_2 =(list*)malloc(sizeof(list));
//     list* nodes_3 =(list*)malloc(sizeof(list));
//     nodes_2->name = "/";
//     nodes_2->next = NULL;
//     nodes_3->name = "/tmp/"; 
//     nodes_3->next = NULL;
//     nodes_1->name = ".";
//     nodes_1->next = nodes_2;
//     nodes_2->next = nodes_3;
//     return nodes_1;
// }
// void exet_note_(list* node_x, int flag){

//     int i=0;
//     while(i > flag){
//         i++;
//     }
//     struct stat ft;
//     list* file_node = (list*)malloc(sizeof(list));
//     file_node = NULL;
//     list* dir_node = (list*)malloc(sizeof(list));
//     dir_node = NULL;
//     int fd, count_f = 0, count_d = 0;
//     while(node_x){
//         fd = open(node_x->name, O_RDONLY);
//         if(fd >= 0){
//             stat(node_x->name,&ft);
//             if(!S_ISDIR(ft.st_mode)){ 

//                 file_node =  my_first_addLast_(file_node, node_x->name, ft);
//                 count_f++; 

//             }else{
//                 dir_node = my_first_addLast_(dir_node, node_x->name, ft);
//                 if(my_strcmp(node_x->name, "/") == 0){
//                     dir_node = sort_g();
//                 }
//                 count_d++;
//             }
//         }else{
//            printf("ls: cannot access '%s': No such file or directory\n", node_x->name); 
//         }
//         node_x = node_x->next;
//     }
//     if(count_f > 0){
//         file_node = sort_time_a(file_node,  flag);
//         while(file_node){
//             printf("%s\n", file_node->name);
//             file_node = file_node->next;
//         }
//     }
//     if(count_d > 0){
//         DIR* dir;
//         struct dirent *entry;
//         struct stat ft;

//         while(dir_node){

//             list* place_node = (list*)malloc(sizeof(list));
//             place_node = NULL;
//             dir = opendir(dir_node->name);
//             while((entry = readdir(dir))){
//                 stat(entry->d_name, &ft);

//                 place_node = my_first_addLast_(place_node, entry->d_name, ft);
                
//             }
//             place_node = sort_time_a(place_node, flag);

//             if(count_d > 1){
//                 printf("%s:\n",dir_node->name);
//             }

//             my_list_print(place_node, flag);
//             if(dir_node->next != NULL){
//                 putchar('\n');
//             }
//             dir_node = dir_node->next;
//         }
//     }
// }

// void my_ls(int ac,char** av){
//       int  flag=0;
//     struct stat fs;
//     list *list_else = malloc(sizeof(list));
//     list_else = NULL;
//     int  a = 0, t = 0, at=0;
//     int len = 0;

//     for(int i = 1; i < ac; i++){
//         if(my_strcmp(av[i], "-a")== 0)  a = 1;
//         else if(my_strcmp(av[i] , "-t")== 0) t = 1;
//         else if(my_strcmp(av[i], "-at")==0 || my_strcmp(av[i], "-ta")==0) at=1;
//         else{
//             len++;
//             stat(av[i], &fs);
//             list_else = my_first_addLast_(list_else, av[i], fs);
//         }
//     }

//     if(t==1 && a==1) flag = 3;
//     else if(at==1) flag=3;
//     else if(t==1) flag = 2;
//     else if(a==1) flag = 1;
    
//     if(len == 0){

//        open_dir_file(flag);
       
//     }
//     else{

//         exet_note_(list_else, flag);

//     }
// }
// int main(int ac,char** av){

//     my_ls(ac,av);

// }
