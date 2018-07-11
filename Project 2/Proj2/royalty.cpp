//
//  main.cpp
//  Proj2
//
//  Created by Sparsh Arora on 10/14/15.
//  Copyright © 2015 Sparsh Arora. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int units;
    double base, royal;
    string title, premium;  //declaring all variables
    
    cout<<"Units sent : ";   //accepting values for the variables
    cin>> units;
    cin.ignore(10000, '\n');
    cout<<"Title : ";
    getline (cin,title);
    cout<<"Base Price : ";
    cin>>base;
    cin.ignore(10000, '\n');
    cout<<"Premium item? (y/n) : ";
    getline (cin,premium);
    cout<<"---"<<endl;           // the three hyphen output
    
  
    
    if(units<0)                                                         //checking for errors
        cout<<"The number of units sent must be nonnegative.";
    else if(title=="")
        cout<<"You must enter a title.";
    else if(base<0)
    cout<<"The base price must be nonnegative.";
   
    else if((premium!="n") && (premium!="y") )
        cout<<"You must enter y or n.";
    else                                                            // calculating royalty because no errors were spotted
        
    {   cout.setf(ios::fixed);
        cout.precision(2);
    
   if(units<=400)                   // if units are less than 400
       royal=(0.09)*base*units;
    else if((units>400) && (units<=1200))       // if units are between 400 and 1200
    {
        int diff=units-400;
       
        if(premium=="y")
    
        royal=((0.09)*base*400)+((0.16)*base*(diff));
    
        else
            royal=((0.09)*base*400)+((0.13)*base*(diff));
    }
    else
    {
        int diff=units-1200;
        
        if(premium=="y")
            
            royal=((0.09)*base*400)+((0.16)*base*(800)+((0.14)*diff*base));
        
        else
            royal=((0.09)*base*400)+((0.13)*base*(800)+((0.14)*diff*base));
    }
    
    cout<<title<< " earned $"<<royal<<" in royalties.";
     }
    cout<<endl;
    
}


