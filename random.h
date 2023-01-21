/* Aidan Blaney
   CIS 3207 Introduction to Systems Programming and Operating Systems
   Professor Fiore
   January 20 2023 
*/

/* function for running randomized characters */
char* randchar()
{

    char* randchar = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"[rand() % 26]; //Generate random letter in the 26 letter alphabet
    return(randchar);

}
