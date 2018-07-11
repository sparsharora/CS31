//
//  main.cpp
//  P5
//
//  Created by Sparsh Arora on 11/11/15.
//  Copyright © 2015 Sparsh Arora. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdlib>
#include "utilities.h"

using namespace std;

const int MAXWORDS=9000; //maximum number of words in an array as a global constant

int manageOneRound(const char words[][7], int nWords, int wordnum);

int manageOneRound(const char words[][7], int nWords, int wordnum)
{
    if(nWords<0 || wordnum<0 || wordnum>=nWords)  //checking if nowrds is positive and the number for secret word is between 0
    return -1;                                    //and nWords
    char probe[100],a[100],b[100];
  
    int ctr=0,rocks=0;
     do //loop until probe word and secret word are same
     {
         strcpy(a,words[wordnum]); //using a temporary c string array

         int j,k,chk=0;
         ctr++;           // for number of tries
         cout<<"Probe word: ";
         cin.getline(probe,100);
         strcpy(b,probe); //using a temporary c string array
         
             for(k=0;probe[k]!='\0';k++)
             if(!islower(probe[k]))   //checking for lower case
                 chk++;
        
             if(k>6|| k<4 || chk>0)  //checking if all are lowercase and words between 4 to 6 letters
             { cout<<"Your probe word must be a word of 4 to 6 lower case letters."<<endl;
                 ctr--;   //not counting that try
                 continue;
             }
         int t=0;
         for(j=0;j<nWords;j++)
             if(strcmp(probe,words[j])==0)
             { t=1;
               break;
             }
         if(t==0)  //checking if probe word is present in the array of words
         {cout<<"I don't know that word."<<endl;
             ctr--; //not counting that try
             continue;
         }
         rocks=0;
         for(k=0;probe[k]!='\0';k++)  //calculating rocks by comparing same element number of the two arrays
         { if(probe[k]==a[k])
            {probe[k]='*';
             a[k]='+';
             rocks++;
            }
         }
         
         
         int peb=0;
         
         for(j=0;a[j]!='\0';j++)     // counting pebbles
         { for(k=0;probe[k]!=0;k++)
              if(probe[k]==a[j])
                {probe[k]='*';  //temporarily changing probe so that same letter isn't encountered again
                 peb++;
                 break;
                }
                 
         }
         
        
         if(strcmp(b, words[wordnum])==0)
             break;
         
         cout<<"Rocks: "<<rocks<<", Pebbles: "<<peb<<endl;
         
             
     }while(strcmp(b, words[wordnum])!=0);
    
    
         
    return ctr;  //returning score
    

}

int main()
{
    char wordList[MAXWORDS][MAXWORDLEN+1];                 //array containing words
    int nWords= loadWords(wordList, MAXWORDS);
    if(nWords<1)                                         //checking if words were loaded
    { cout<<"No words were loaded, so I can't play the game."<<endl;
        return 0;
    }
 
    int rounds,sec,score,min, max;
    double avg = 0.0, sum=0;
    cout<<"How many rounds do you want to play? ";
    cin>>rounds;
    if(rounds<=0)
    {  cout<<"The number of rounds must be positive."<<endl;
        return 0;
    }
    cin.ignore(1000,'\n');
    int t[rounds];  //integer array collecting all scores
    for(int i=0;i<rounds;i++)
    { cout<<endl<<"Round "<<i+1<<endl;
        sec=randInt(0,nWords-1);
        cout<<"The secret word is "<< strlen(wordList[sec])<<" letters long."<<endl;
        
     
        score=manageOneRound(wordList,nWords,sec);
        if(score==1)
            cout<<"You got it in 1 try."<<endl;
        else
            cout<<"You got it in "<<score<<" tries."<<endl;
        
        
        t[i]=score;   //adding scores to the array
        sum=sum+t[i];
        avg=sum/(i+1);  //calculating average
        min=max=t[0];
        for(int j=1;j<=i;j++)   //calculating maximum and minimums after i rounds
           if(t[i]>max)
               max=t[i];
        
        for(int j=1;j<=i;j++)
            if(t[j]<min)
                min=t[i];
        cout.setf(ios::fixed);
        cout.precision(2);
        cout<<"Average: "<<avg<<", minimum: "<<min<<", maximum: "<<max<<endl;
    }
}
