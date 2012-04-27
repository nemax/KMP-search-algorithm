#include <string.h>
#include <stdio.h>

static int next[20]={0};

/*This is the worst one I think,the next value dosen`t tell
  you where the pattern_index should be put then,but it can
  work out by the value.
*/
void get_next_array_origin(char * pattern){
	//Get pattern length
	int length = strlen(pattern);

	int k = 1,value=0;
	//It`s a rule to set next[0] with value -1
	next[0]=-1;

	while(k < length){
		//Keep the next value of last unmatch character
		value = next[k-1];
		/*value>=0 means there is some overlays was discovered,
	 	  the second condition means the overlay was stop here
		*/
		while(value >= 0 && pattern[k] != pattern[value+1]){
			value = next[value];
		}
		/*It means we discoverd an overlay and pattern[k] is the
		  first(value equals -1) or subsequent char(value >= 0).
		*/
		if(pattern[k] == pattern[value+1]){
			next[k] = value+1;
		}
		//Other condition
		else{
			next[k]=-1;
		}
		k++;
		//printf("next[%d] = %d\n",k-1,next[k-1]);
	}
}

/*This is the second next value caculate algorithm,it`s 
  convenient.Because the next value tell you what the  
  next value of pattern_index.
*/

void get_next_array(char * pattern){
	int length = strlen(pattern) ;
	int k = 0,value=-1;
	next[k]=-1;

	while(k < length){
		while(value >= 0 && pattern[k] != pattern[value]){
			value = next[value];
		}

		k++;
		value++;
		next[k] = value;
	}
}

/*It`s an improvement algrithm for get_next_array().Former just
  tell you where to set you pattern_index,but not to concerned 
  about is the next char equal to the mismatch one,this algori-
  thm fix this problem.
*/
void get_next_array_enhanced(char * pattern){
	int length = strlen(pattern) ;
	int k = 0,value = -1;
	next[k]=value;

	while(k < length){
		while(value>=0 && pattern[k]!=pattern[value]){
			value = next[value];
		}
		/*Once the next char is equal to the current one,also
		  the mismatch one,we do this.Although they are equal
		  characters,but the next value of former one has been
		  work out,so it`s an available next value for the seond
		  one. 
		*/
		if(pattern[k] == pattern[value]){
			next[k] = next[value];
		}
		k++;
		value++;
		next[k] = value;
	}
}

void KMP_search_origin(char * main,char * pattern){
	get_next_array_origin(pattern);
	int main_index = 0,pattern_index = 0;
	int main_length = strlen(main);
	int pattern_length = strlen(pattern);
	int flag=-1;
	while(main_index<main_length){
		//printf("main_index:%d\n",main_index);
		if(main[main_index] == pattern[pattern_index]){
			//printf("%c = %c\n",main[main_index],pattern[pattern_index]);
			if(pattern_index == pattern_length-1){
				printf("find in place %d\n",main_index - pattern_length+1);
				flag=1;
				/*Once the last char equals the first char in pattern,
				  that means current char in main string can match the
				  first char in pattern,so we do this to avoiding miss
				  the comparision.
				*/
				if(pattern[0] == pattern[pattern_index]){
					main_index--;
				}
				pattern_index = -1;
			}
			main_index++;
			pattern_index++;
		}
		else{
			//printf("%c != %c\n",main[main_index],pattern[pattern_index]);
			if(pattern_index == 0){
				main_index++;
			}
			else{
				/*caculate the next position to be compare according
				  to the next value
				*/
				pattern_index = next[pattern_index-1]+1;
			}
		}
	}
	if(flag == -1){
		printf("Sorry,we find nothing.");
	}
}

void KMP_search(char * main,char * pattern){
	get_next_array(pattern);
	int main_index = 0,pattern_index = 0;
	int main_length = strlen(main);
	int pattern_length = strlen(pattern);
	int flag=-1;
	while(main_index<main_length){
		//printf("main_index:%d\n",main_index);
		if(main[main_index] == pattern[pattern_index]){
			//printf("%c = %c\n",main[main_index],pattern[pattern_index]);
			if(pattern_index == pattern_length-1){
				printf("find in place %d\n",main_index - pattern_length+1);
				flag=1;
				if(pattern[0] == pattern[pattern_index]){
					main_index--;
				}
				pattern_index = -1;
			}
			main_index++;
			pattern_index++;
		}
		else{
			//printf("%c != %c\n",main[main_index],pattern[pattern_index]);
			if(pattern_index == 0){
				main_index++;
			}
			else{
				/*It`s easier than before,the next value is
				  just where to put next time.
				*/
				pattern_index = next[pattern_index];
			}
		}
	}
	if(flag == -1){
		printf("Sorry,we find nothing.");
	}
}


void KMP_search_enhanced(char * main,char * pattern){
	get_next_array(pattern);
	int main_index = 0,pattern_index = 0;
	int main_length = strlen(main);
	int pattern_length = strlen(pattern);
	int flag=-1;
	while(main_index<main_length){
		//printf("main_index:%d\n",main_index);
		if(main[main_index] == pattern[pattern_index]){
			//printf("%c = %c\n",main[main_index],pattern[pattern_index]);
			if(pattern_index == pattern_length-1){
				printf("find in place %d\n",main_index - pattern_length+1);
				flag=1;
				if(pattern[0] == pattern[pattern_index]){
					main_index--;
				}
				pattern_index = -1;
			}
			main_index++;
			pattern_index++;
		}
		else{
			//printf("%c != %c\n",main[main_index],pattern[pattern_index]);
			/*next value equals -1 means the condition we mismatch at the 
			  first char,so we match again from the next char in main string
			*/
			if(next[pattern_index] == -1){
				main_index++;
				pattern_index = 0;
			}
			else{
				pattern_index = next[pattern_index];
			}
		}
	}
	if(flag == -1){
		printf("Sorry,we find nothing.");
	}
}