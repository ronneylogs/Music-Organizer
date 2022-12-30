#include <iostream>
#include <string>
#include <cmath>
#include <ctype.h>
#include <stdexcept>
#include <string.h>
#include "PlayList.h"
#include "Song.h"

using std::cout;
using std::endl;
using std::cin;


int main(void){
    int quit = 0;
	int ans;
	string song;
	string artist;
	PlayList* pl = new PlayList();
	printf("Menu:\n");
	printf("1 - Enter a song in the play list at a given position\n");
	printf("2 - Remove a song from the play list at a given position\n");
	printf("3 - Swap two songs in the play list\n");
	printf("4 - Print all the songs in the play list\n");
	printf("5 - Quit!\n");
	printf("\n");
	printf("Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ");
    while(quit != 1){
		cin>>ans;
		//using switch for menu input
		switch(ans){
    		//quit
			case 5:{
            	quit = 1;
				break;
			}
			//insert
			case 1:{
                int len;
				unsigned int position = 0;
				cin.ignore(888,'\n');
				printf("Song name: ");
				getline(cin,song);
				//if users enter empty space
				while(song == ""){
					printf("Please enter a valid song name: ");
					getline(cin,song);
				}

				printf("Artist: ");
				getline(cin,artist);
				//if users enter empty space
				while(artist == ""){
					printf("Input is empty. Please enter something valid: ");
					getline(cin,artist);
				}
			
				printf("Length(in seconds): ");
			
				
				cin>>len;
				//if user enters non-digit input
				while(cin.fail()){
					printf("You have entered an invalid input. Please try again.\n");
					printf("Length(in seconds): ");
					cin.clear();
					cin.ignore(888,'\n');
					cin>>len;
				}

				//if playlist is empty to start with
				if(pl->size()==0){
					
					cout<<"Position"<<"(1): ";
				}
				// //if there are already items in playlist
				if(pl->size()>=1){
					
					cout<<"Position"<<"(1 to "<<pl->size()+1<<"): ";
				}
				cin>>position;
				// //loops until the input is valid
				while(position<0||position-1>pl->size()){
					cout<<"Please re-enter position as the position you entered is invalid.\n";
					cin.clear();
					cin.ignore(888,'\n');
					
					if(pl->size()==0){
						cout<<"Position"<<"(1): ";
						cin>>position;
					}
					else if(pl->size()>0){
						cout<<"Position"<<"(1 to "<<pl->size()<<"): ";
						cin>>position;
					}
					else{
						cout<<"Please enter a valid input: ";
						cin>>position;
					}
				}
				cout<<"You entered "<<song<<" at position "<<position<<" in the play list."<<endl;
				printf("\n");
				pl->insert(Song(song,artist,len),position-1);
				printf("Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ");
				break;
			}

			//remove
			case 2:{
				int boo = 0;
				if(pl->size()==0){
					printf("No songs to remove. Please add songs before trying to remove.\n");
					boo = 1;
				}
				if(boo==0){
					cout<<"Position"<<"(1 to "<<pl->size()<<"): ";
					unsigned int rem;
					cin>>rem;
					//loops until input is valid
					while(rem<0||rem>pl->size()){
						printf("Your input is out of range, please try again.\n");
						cout<<"Position"<<"(1 to "<<pl->size()<<"): ";
						cin>>rem;
					}
					cout<<"You removed "<<pl->get(rem-1).getName()<<" from the play list.\n";
					//removes node
					pl->remove(rem-1);
				}
				printf("Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ");
				break;
				


			}
			//swap
			case 3:{
				int boo2 = 0;
				// only one song or no song so cannot swap with anything
				if(pl->size()==1||pl->size()==0){
					printf("Not enough songs to swap, please add more songs before trying to swap.\n");
					boo2 = 1;
					
				}
				if(boo2==0){
					cout<<"Swap song at position (1 to "<<pl->size()<<"): ";
					unsigned int pos1;
					cin>>pos1;
					//loops until input is valid
					while(pos1<=0||pos1>pl->size()){
						printf("Your input is out of range, please try again.\n");
						cout<<"Position"<<"(1 to "<<pl->size()<<"): ";
						cin>>pos1;
					}
					cout<<"with the song at position (1 to "<<pl->size()<<"): ";
					unsigned int pos2;
					cin>>pos2;
					//loops until input is valid
					while(pos2<=0||pos2>pl->size()){
						printf("Your input is out of range, please try again.\n");
						cout<<"Position"<<"(1 to "<<pl->size()<<"): ";
						cin>>pos2;
					}
					cout<<"You swapped the songs at position "<<pos1<<" and "<<pos2<<".\n";
					pl->swap(pos1-1,pos2-1);
					}
				printf("Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ");
				break;

			}
			// //print
			case 4: {
				//loops through everything in playlist and prints its items

				if(pl->size()==0){
					printf("You have no songs in the play list to print.\n");
				}
				else{
					for(unsigned int i = 0;i <pl->size();i++){
						cout<<i+1<<" ";
						cout<<pl->get(i).getName()<<" ";
						cout<<"("<<pl->get(i).getArtist()<<") ";
						cout<<pl->get(i).getLength()<<"s\n";
						}
				}
				printf("Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ");
				break;
				
				

			}
			default:
					printf("Enter 1 (insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ");
		 
	

    	}
	}
	//freeing playlist
	delete pl;
	printf("You have chosen to quit the program\n");
    return 0;
}
