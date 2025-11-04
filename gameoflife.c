#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void get_cell_data(int game_area[12][12]){
        FILE *file = fopen("cells.txt", "r");
        if(file == NULL){
                perror("[!] Error opening file!");
                return;
        }

        int ch;
        int o=1;
        int i=1;

        for(int outer=0; outer<12; outer++){
                for(int inner=0; inner<12; inner++){
                        game_area[outer][inner]=0;
                }
        }

        while ((ch = fgetc(file)) != EOF) {
                if(ch!=10){

                        game_area[o][i] = ch;
                        printf("[%d,%d]",o,i);
                        i++;

                        if(i>10){
                                i=1;
                                o++;
                                printf("\n");
                        }
                        if(o>10){
                                o=1;
                        }
                }
        }

        fclose(file);

        return;

}

void print_cell_data(int game_area[12][12]){

        for(int outer=1; outer<11; outer++){
                for(int inner=1; inner<11; inner++){
                        if(game_area[outer][inner]==48){
                                printf(" ");
                        }
                        else{
                                printf("*");
                        }
                }
                printf("\n");
        }
}

void update_cell_data(int game_area[12][12]){
        int grid_size=12;
        int adj_living = 0;
        int self_living = 0;
        int ref_in = 1;
        int ref_out = 1;

        for(int x = 1; x < (grid_size-1); x++){

                for(int y = 1; y < (grid_size-1); y++){

                        for(int a = (x - 1); a < (x + 2); a++){

                                for(int b = (y - 1); b < (y + 2); b++){

                                        if((a==x) && (b==y)){
                                                self_living++;
                                        }
                                        else{
                                                if(game_area[a][b]==49){
                                                        adj_living++;
                                                }
                                        }

                                }
                        }

                        if(game_area[ref_in][ref_out] == 49){
                                if(adj_living < 2){
                                        game_area[ref_in][ref_out] = 48;
                                }

                                if(adj_living > 3){
                                        game_area[ref_in][ref_out] = 48;
                                }
                        }
                        if(game_area[ref_in][ref_out] == 48){
                                if(adj_living == 3){
                                        game_area[ref_in][ref_out] = 49;
                                }

                        }

                        ref_out++;

                        if(ref_out > 10){
                                ref_out = 1;
                                ref_in++;
                        }

                        adj_living=0;
                        self_living=0;
                }
        }
}

int main(void){

        int grid_size = 12;
        int grid_chk = 1;
        int adj_living = 0;
        int self_living = 0;
        int game_area[12][12];

        get_cell_data(game_area);

        print_cell_data(game_area);
        printf("\n");

        for(int z=0; z<100; z++){
                system("clear");
                update_cell_data(game_area);
                print_cell_data(game_area);
                sleep(1);
        }

}
