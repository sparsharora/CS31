//
//  main.cpp
//  Proj 3
//
//  Created by Sparsh Arora on 10/26/15.
//  Copyright © 2015 Sparsh Arora. All rights reserved.
//

#include "grid.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cassert>
using namespace std;
bool isRouteWellFormed(string route);                        //function prototypes
int navigateSegment(int r, int c, char dir, int maxSteps);
int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps);
void row(int &sr, int &sc, int max, char r )   //new function to update sr,sc and to help check for wall to return 3
{int y;

    if(r=='n'|| r=='N')   //check if N/E/W/S
      {   y=navigateSegment(sr, sc, 'N', max);
          sr-=y;//updating sr and sc depending on direction (r)
          if(sr==1 && y!=max) //checking if goes of the grid for function 3
              sr--;
          if(sr>1 && sc>=1 && sr<=getRows() && sc<=getCols() && max!=y && isWall(sr-1,sc))
              sr--;    //helps to check for wall in function navigateRoute
          
      }
    else if(r=='s'|| r=='s')
    {   y=navigateSegment(sr, sc, 'S', max);
        sr+=y;
        if(sr==getRows() && y!=max)
            sr++;
        if(sr>=1 && sc>=1 && sr<getRows() && sc<=getCols() && max!=y && isWall(sr+1,sc))
            sr++;
        
    }
    else if(r=='w'|| r=='W')
    {   y=navigateSegment(sr, sc, 'W', max);
        sc-=y;
        if(sc==1 && y!=max)
            sc--;
        if(sr>=1 && sc>1 && sr<=getRows() && sc<=getCols() && max!=y && isWall(sr,sc-1))
            sc--;
       
    }
    else if(r=='e'|| r=='E')
        {   y=navigateSegment(sr, sc, 'E', max);
            sc+=y;
            if(sc==getCols() && y!=max)
                sc++;
            if(sr>=1 && sc>=1 && sr<=getRows() && sc<getCols() && max!=y && isWall(sr,sc+1))
                sc++;
            
        }
}
bool isRouteWellFormed(string route)  // check if program is syntactically valid
{
    int cur=0; int max=0;
    
    if(route[0]!='N'&& route[0]!='W'&& route[0]!='E'&& route[0]!='S'&& route[0]!='n'&& route[0]!='w'&& route[0]!='e'&& route[0]!='s')
        return(false); //checking if first letter is either N,E,W,S or n,e,w,s
    else
        for(int i=1;i<route.size();i++)
        { if(!isalpha(route[i])&&!isdigit(route[i])) //checking if all charecters are digits and alphabets only
            return false;
        else
        { if(isdigit(route[i]))
            cur++;
        else
        { if(route[i]=='N'||route[i]=='W'||route[i]=='E'||route[i]=='S'||route[i]=='n'||route[i]=='w'||route[i]=='e'||route[i]=='s')
               {if(max<cur)   //to count number of simaltaneous digits
                 max=cur;
                cur=0;
                }
        else
            return false;
            
        }
        }
        }
    if(max<cur)
        max=cur;
   
    if(max>=3)              //checking if no more than 2 simaltaneous digits
        return false;
    else
        return true;
    
}

int navigateSegment(int r, int c, char dir, int maxSteps) //to navigate in one direction and return maximum steps
{  int trial=0;
    
    if(isWall(r,c)|| maxSteps<0 ||(dir!='n' && dir!='e' && dir!='w' && dir!='s' && dir!='N' && dir!='E' && dir!='W' && dir!='S'))
        return(-1);
    else if(dir=='n'|| dir=='N') //case north
        { while(r>1)
            {r--;
            if(!isWall(r,c))  //checking to see if there is no wall
                trial++;       //incrememnting steps in that direction
            else
                break;    //leaving because a wall was encountered
             }
        }
    else if(dir=='s'||dir=='S')
        { while(r<getRows())
        {r++;
            if(!isWall(r,c))
            trial++;
            else
                break;
        }
        }
    else if(dir=='w'|| dir=='W')
    { while(c>1)
          { c--;
            if(!isWall(r,c))
            trial++;
            else
                break;
    }
    }
    else
    { while(c<getCols())
    { c++;
        if(!isWall(r,c))
        trial++;
        else
            break;
    }
        
    }
    
    
    if(maxSteps<trial)     //to check if the intended steps by the route are less than steps possible
        return maxSteps;
    else
        return trial; //returning maximum steps possible in the direction
}

int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps) //navigate entire route
{ int steps=0;
    if(!isRouteWellFormed(route) || isWall(sr,sc) || isWall(er,ec))
    return 2;
  else
      for(int i=0;i<route.size();i++)
      { if(isdigit(route[i]))  //moving to next iteration if a digit is encountered
          continue;
          else
          {
          if(route[i]=='N'|| route[i]=='W'|| route[i]=='E'|| route[i]=='S'|| route[i]=='n'|| route[i]=='w'|| route[i]=='e'|| route[i]=='s')
          {
            if(isdigit(route[i+1]))
            { if(isdigit(route[i+2])) //case when there are 2 digits after an alphabet n/N,e/E,w/W,s/S
            {
            steps+=navigateSegment(sr, sc, route[i], (((route[i+1]-'0')*10)+(route[i+2]-'0'))); //increments steps
            row(sr,sc,(((route[i+1]-'0')*10)+(route[i+2]-'0')),route[i]); //updating sr and sc
                if( sr==0 || sc==0 || sr>getRows()|| sc>getCols())//checking if runs off the grid
                { nsteps=steps;
                    cout<<"no";return 3;
                }
                if(isWall(sr,sc))  //checking for wall or off the grid to return 3
                { nsteps=steps;
                    return 3;
                }
                
            }
            else    //case when there is only 1 digit after an alphabet n/N,e/E,w/W,s/S
            {
                steps+=navigateSegment(sr,sc, route[i],route[i+1]-'0'); // using -'0' to not use ascii values
                row(sr,sc,route[i+1]-'0', route[i]);
                if ( sr==0 || sc==0 || sr>getRows()|| sc>getCols())
                {
                    nsteps=steps;
                    return 3;
                }
                
                if(isWall(sr,sc))
                { nsteps=steps;
                    return 3;
               }
            }
            }
             else if(route[i+1]=='N'|| route[i+1]=='W'|| route[i+1]=='E'|| route[i+1]=='S'|| route[i+1]=='n'|| route[i+1]=='w'|| route[i+1]=='e'|| route[i+1]=='s') //case when there are no digits after n/N,e/E,w/W,s/S
             { steps+=navigateSegment(sr, sc, route[i], 1);
                 row(sr,sc,1,route[i]);
                 if( sr==0 || sc==0 || sr>getRows()|| sc>getCols())
                 {
                     nsteps=steps;
                     return 3;
                 }
                 if(isWall(sr,sc))
                 {
                     nsteps=steps;
                     return 3;
                 }
                    
             }
          
             else
             { steps+=navigateSegment(sr, sc, route[i], 1);
                 row(sr,sc,1,route[i]);
                 if(sr==0 || sc==0 || sr>getRows()|| sc>getCols())
                 {
                     nsteps=steps;
                     return 3;
                 }
                 if(isWall(sr,sc))
                 {   nsteps=steps;
                     return 3;
                 }
             }

          
      }
      }
      }
    nsteps=steps; //assigning temporary variable value to nsteps
    
    if(sr==er&&sc==ec) //case when reaches destination
        return 0;

    else
        return 1;
    
    
}

    

bool isRouteWellFormed(string);
int navigateSegment(int, int, char, int);
int navigateRoute(int, int, int, int, string, int&);

void makemaze()
{
    //   123456789012
    // 1 ............
    // 2 ......*.....
    // 3 ............
    // 4 ..*.........
    // 5 ......*.....
    
    setSize(5,12);
    setWall(4,3);
    setWall(2,7);
    setWall(5,7);
}

void testone(int n)
{
    int ns = 0;
    switch (n)
    {
        default: {
            cout << "Bad argument" << endl;
        } break; case  1: {
            assert(isRouteWellFormed(""));
        } break; case  2: {
            assert(!isRouteWellFormed("x"));
        } break; case  3: {
            assert(!isRouteWellFormed("3"));
        } break; case  4: {
            assert(!isRouteWellFormed("@"));
        } break; case  5: {
            assert(!isRouteWellFormed("x1"));
        } break; case  6: {
            assert(!isRouteWellFormed("12"));
        } break; case  7: {
            assert(isRouteWellFormed("E03"));
        } break; case  8: {
            assert(!isRouteWellFormed("E003"));
        } break; case  9: {
            assert(!isRouteWellFormed("n1#"));
        } break; case 10: {
            assert(isRouteWellFormed("W"));
        } break; case 11: {
            assert(isRouteWellFormed("e2"));
        } break; case 12: {
            assert(isRouteWellFormed("N10"));
        } break; case 13: {
            assert(isRouteWellFormed("n98"));
        } break; case 14: {
            assert(isRouteWellFormed("SW"));
        } break; case 15: {
            assert(isRouteWellFormed("S1W"));
        } break; case 16: {
            assert(isRouteWellFormed("SW1"));
        } break; case 17: {
            assert(isRouteWellFormed("S1W2"));
        } break; case 18: {
            assert(isRouteWellFormed("s12w3"));
        } break; case 19: {
            assert(isRouteWellFormed("n1e12"));
        } break; case 20: {
            assert(isRouteWellFormed("n12e12"));
        } break; case 21: {
            assert(isRouteWellFormed("n1e12s"));
        } break; case 22: {
            assert(!isRouteWellFormed("n12n12x"));
        } break; case 23: {
            assert(!isRouteWellFormed("n12n12x1"));
        } break; case 24: {
            assert(!isRouteWellFormed("n12e12sx"));
        } break; case 25: {
            makemaze();
            assert(navigateSegment(0,4,'S',2) == -1);
        } break; case 26: {
            makemaze();
            assert(navigateSegment(6,4,'N',2) == -1);
        } break; case 27: {
            makemaze();
            assert(navigateSegment(3,0,'E',2) == -1);
        } break; case 28: {
            makemaze();
            assert(navigateSegment(3,13,'W',2) == -1);
        } break; case 29: {
            makemaze();
            assert(navigateSegment(4,3,'E',2) == -1);
        } break; case 30: {
            makemaze();
            assert(navigateSegment(3,4,'E',-1) <= 0);
        } break; case 31: {
            makemaze();
            assert(navigateSegment(3,4,'E',0) == 0);
        } break; case 32: {
            makemaze();
            assert(navigateSegment(3,4,'e',2) == 2);
        } break; case 33: {
            makemaze();
            assert(navigateSegment(1,3,'s',2) == 2);
        } break; case 34: {
            makemaze();
            assert(navigateSegment(1,3,'w',2) == 2);
        } break; case 35: {
            makemaze();
            assert(navigateSegment(3,7,'n',0) == 0);
        } break; case 36: {
            makemaze();
            assert(navigateSegment(3,7,'E',2) == 2);
        } break; case 37: {
            makemaze();
            assert(navigateSegment(3,6,'S',2) == 2);
        } break; case 38: {
            makemaze();
            assert(navigateSegment(3,6,'N',2) == 2);
        } break; case 39: {
            makemaze();
            assert(navigateSegment(2,3,'S',3) == 1);
        } break; case 40: {
            makemaze();
            assert(navigateSegment(2,8,'W',3) == 0);
        } break; case 41: {
            makemaze();
            assert(navigateSegment(4,7,'N',2) == 1);
        } break; case 42: {
            makemaze();
            assert(navigateSegment(2,3,'E',8) == 3);
        } break; case 43: {
            makemaze();
            assert(navigateSegment(4,5,'W',8) == 1);
        } break; case 44: {
            makemaze();
            assert(navigateSegment(3,4,'W',4) == 3);
        } break; case 45: {
            makemaze();
            assert(navigateSegment(3,4,'e',10) == 8);
        } break; case 46: {
            makemaze();
            assert(navigateSegment(3,4,'S',3) == 2);
        } break; case 47: {
            makemaze();
            assert(navigateSegment(3,4,'N',4) == 2);
        } break; case 48: {
            makemaze();
            assert(navigateRoute(0,4,1,4,"s",ns) == 2);
        } break; case 49: {
            makemaze();
            assert(navigateRoute(1,13,1,12,"w",ns) == 2);
        } break; case 50: {
            makemaze();
            assert(navigateRoute(5,2,6,2,"s",ns) == 2);
        } break; case 51: {
            makemaze();
            assert(navigateRoute(2,7,2,6,"w",ns) == 2);
        } break; case 52: {
            makemaze();
            assert(navigateRoute(3,4,2,4,"?",ns) == 2);
        } break; case 53: {
            makemaze();
            assert(navigateRoute(2,6,2,7,"E",ns) == 2);
        } break; case 54: {
            makemaze();
            ns = 999;
            navigateRoute(2,6,2,7,"E",ns);
            assert(ns == 999);
        } break; case 55: {
            makemaze();
            assert(navigateRoute(4,7,1,7,"n3",ns) == 3  &&  ns == 1);
        } break; case 56: {
            makemaze();
            assert(navigateRoute(4,6,2,8,"n2e2",ns) == 3  &&  ns == 2);
        } break; case 57: {
            makemaze();
            assert(navigateRoute(4,5,2,8,"n2e3",ns) == 3  &&  ns == 3);
        } break; case 58: {
            makemaze();
            assert(navigateRoute(3,11,4,5,"e2sw3",ns) == 3  &&  ns == 1);
        } break; case 59: {
            makemaze();
            assert(navigateRoute(5,11,4,5,"N2E2SW3",ns) == 3  &&  ns == 3);
        } break; case 60: {
            makemaze();
            assert(navigateRoute(4,4,4,4,"EW2",ns) == 3  &&  ns == 2);
        } break; case 61: {
            makemaze();
            assert(navigateRoute(4,5,5,4,"s2",ns) == 3  &&  ns == 1);
        } break; case 62: {
            makemaze();
            ns = 999;
            navigateRoute(4,5,5,4,"s2",ns);
            assert(ns == 1);
        } break; case 63: {
            makemaze();
            assert(navigateRoute(5,3,5,4,"",ns) == 1  &&  ns == 0);
        } break; case 64: {
            makemaze();
            assert(navigateRoute(5,3,5,3,"",ns) == 0  &&  ns == 0);
        } break; case 65: {
            makemaze();
            assert(navigateRoute(2,1,2,4,"E3",ns) == 0  &&  ns == 3);
        } break; case 66: {
            makemaze();
            assert(navigateRoute(2,1,2,3,"E3",ns) == 1  &&  ns == 3);
        } break; case 67: {
            makemaze();
            assert(navigateRoute(2,1,2,5,"E3",ns) == 1  &&  ns == 3);
        } break; case 68: {
            makemaze();
            assert(navigateRoute(5,3,5,3,"E",ns) == 1  &&  ns == 1);
        } break; case 69: {
            makemaze();
            ns = 999;
            navigateRoute(5,3,5,3,"E",ns);
            assert(ns == 1);
        } break; case 70: {
            makemaze();
            assert(navigateRoute(5,3,2,8,"E2NE3N2",ns) == 0  &&  ns == 8);
        } break; case 71: {
            makemaze();
            assert(navigateRoute(5,3,2,8,"E2NE3N3",ns) == 1  &&  ns == 9);
        }
    }
}

int main()
{
    cout << "Enter test number: ";
    int n;
    cin >> n;
    testone(n);
    cout << "Passed!" << endl;
}