//********************************************************************
//* Rudimentary encryption program
//* by James McConnel
//* Reads in a text file character by character and then outputs it
//* with the extension ".enc" and all the characters offset down the
//* ascii table a certain number of intervals.
//********************************************************************/ 

//Includes
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//Prototypes
void encrypt(char* f, char* p);
void decrypt(char* f, char* p);
void help(void);

//Main: Opens files, handles errors etc...
main(int argc, char *argv[]){

   //Program will accept 4 and only 4 parameters.
   //argv[0] should be the program name: "jcrypt"
   //argv[1] should be the action flag: "-e" or "-d"
   //argv[2] should be the file name.
   //argv[3] should be a password which is used as the key to encrypt/decrypt the text.
   if((argc <= 3) || (argc > 4)){
      help();
      exit(1);
   }
   
   string option (argv[1]);
   if(option == "-d"){// decrypt flag
      decrypt(argv[2], argv[3]);
   }else if(option == "-e"){// encrypt flag
      encrypt(argv[2], argv[3]);
   }else{
      help();
      exit(1);
   }
   
}//main

//encrypts file.
void encrypt(char* f, char* p){
   ifstream in (f, fstream::in);
   string s (f);
   if(s.find('.', 0) != string::npos){
      s.replace(s.find('.', 0), 1, 1, '_');
   }
   s.append(".enc");
   ofstream out (s.c_str());
   string key (p);
   while(in.good()){
      for(string::iterator i = key.begin(); i<key.end(); i++){
         int c = in.get();
         if(c != EOF){
            c = c + *i;
            while(c >= 256){
               c = c - 256;
               if(c == EOF){
                  cout << "Encryption failed: EOF generated.\n";
                  exit(1);
               }
            }
            out.put(char(c));
         }
      }
   }
   out.close();
   in.close();
}


//Decrypts an encrypted file
void decrypt(char* f, char* p){
   ifstream in (f, fstream::in);
   string s (f);
   if(s.find(".enc", 0) != string::npos && s.find(".enc", 0) == s.length()-4){ //ends in .enc
      s.erase(s.length()-4, s.length());
      if(s.rfind('_') != string::npos){
         s.replace(s.rfind('_'), 1, 1, '.');
      }
   }
   ofstream out (s.c_str());
   string key (p);
   while(in.good()){
      for(string::iterator i = key.begin(); i<key.end(); i++){
         int c = in.get();
         if(c != EOF){
            c = c - *i;
            while(c < 0){
               c = c + 256;
            }
            out.put(char(c));
         }
      }
   }
   out.close();
   in.close();
}

//Prints the how to use the program.
void help(void){
   cout << "Usage: jcrypt [options] [filename] [password]\n";
   cout << "Options: \n";
   cout << "   -e Encrypt the file.\n";
   cout << "   -d Decrypt the file.\n";
   cout << "Password is required.\n\n";
   cout << "(c) James McConnel (2008)\n";
   cout << "A simple ecryption/decryption program.\n";
   cout << "Files are assumed to be ASCII text.";
}
