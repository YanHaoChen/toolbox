#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	/* file */
	FILE *fr, *fw;
	fr = fopen(argv[1],"r");
	int tmp_name_len = strlen(argv[1])+4;
	char tmp_name[tmp_name_len];
	sprintf(tmp_name,"%s.tmp",argv[1]);
	fw = fopen(tmp_name,"w");
	/* word */
	char *origin, *to_be;
	size_t o_len, to_len;	
	origin = argv[2];
	o_len = strlen(origin);
	to_be = argv[3];
	to_len = strlen(to_be);
	/* status */
	char *line = NULL;
	size_t inital_len = 0;
	ssize_t line_len = 0;

	int i, j, z, line_count=0;
	
	int correct_count = 0;
	int first_flag = -1;

	while((line_len = getline(&line, &inital_len, fr)) != -1){
		printf("At line: %d\n",++line_count);
		if(line_len > o_len){
			for(i=0; i <= line_len - o_len;){
				correct_count = 0;				
				first_flag = -1;
				for(j=0; j< o_len;j++){
					if(origin[j] == line[i+j]){
						correct_count++;
						if(correct_count == o_len){
							printf("found!\n");
							fputs(to_be, fw);
							i += j + 1;
							break;
						}else if (first_flag == -1  && j > 0 && origin[0] == line[i+j]){
							first_flag = j;
						}
					}else{
						if(first_flag == -1){	
							for(z=0;z<=j;z++){
								fputc(line[i+z],fw);
							}
							i +=  j+ 1;
						}else{
							for(z=0;z<j;z++){
								fputc(line[i+z],fw);
							}
							i += first_flag;
						}
						break;
					}
				}
			}			
		}
		fputc('\n',fw);
	}
	if(line) free(line);
	fclose(fr);
	fclose(fw);
	return 0;
}
