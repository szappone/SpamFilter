//  JeeMail
//  Created by Sarah on 7/11/15.

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// function declarations
bool hasMultipleExclamations(string subj);
string getFirstWord(string text);
string getLastWord(string text);
string extractWord(string& text);
bool isUppercase(string text);
string makeUppercase(string text);
bool isGibberishWord(string text);
bool isConsonant (char thisChar);
int triggerWordChecker(string text);
int getNumWords (string text);
int getNumUpper (string subj);
bool percUpper (string text, int perc);

int main() {
    
    // variable and constant declarations
    string bod;
    int spamScore = 0;
    string subj;
    int numSpam = 0;
    int numLeg = 0;
    bool cont = true;
    bool miniWhile = true;
    char yesOrNo;
    int THRESH = 100;
    
    // big while loop prompts and takes input from user
    while (cont) {
        
        spamScore = 0;
        cout << "Enter the subject line of the email: ";
        getline(cin, subj);
        
        //check condition #1
        // if subject has < 1 word, and > 90% have only uppercase letters, add 30 pts to spamScore
        if (percUpper(subj, 90))
            spamScore += 30;
        
        // check condition #2
        // if last word of subject has > 3 consecutive consonants, add 40 pts to spamScore
        string theLast = getLastWord(subj);
        if (isGibberishWord(theLast))
            spamScore += 40;
        
        // check condition #3
        // if subject line >= 3 contiguous exclamation points, add 20 pts to spamScore
        if (hasMultipleExclamations(subj))
            spamScore += 20;
        
        cout << "Enter the body of the email.  Press Enter on an empty line to finish." << endl;
        getline(cin, bod);
        
        //check condition #4 **problem
        // if the body has > 1 word, and > 50% of them are all uppercase, add 40 pts to spamScore
        if (percUpper(bod, 50))
            spamScore +=40;
        
        //check condition #5
        // each time a trigger word appears in the body, add 5 points to spamScore
        int numTriggers = triggerWordChecker(bod);
        int numToAdd = numTriggers * 5;
        spamScore += numToAdd;
                
        // output whether spamScore > 100 (it is spam) or < 100 (it is legitimate)
        if (spamScore > THRESH) {
            numSpam++;
            cout << "This email is classified as spam, because its spam score is " << spamScore << "." << endl;
        } else {
            numLeg++;
            cout << "This email is classified as legitimate, because its spam score is " <<spamScore << "." << endl;
        }
        
        // nested mini while loop continues prompting user to continue until
        // inputted a 'y' (go back up to big while) or a 'n' (end big while loop)
        while (miniWhile) {
            
            cout << "Would you like to classify another email (y or n)? ";
            cin >> yesOrNo;
            cin.ignore(10000, '\n');
            
            if (yesOrNo == 'y') {
                miniWhile = false;
            } else if (yesOrNo == 'n') {
                miniWhile = false;
                cont = false;
            } else
                cout << "Please enter y or n." << endl;
        }
        miniWhile = true;
    }
    
    // output numbers of spam nand legitimate messages each on seperate line
    cout << endl << "Number of spam messages: " << numSpam << endl;
    cout << "Number of legitimate messages: " << numLeg << endl;
    
    
}

// FUNCTIONS!


/*
 returns true if > perc of words in text are uppercase
 param text the text to be analyzed
 param perc the percent threshold
 */
bool percUpper (string text, int perc) {
    double wordCount = getNumWords(text);
    double upperCount = getNumUpper(text);
    double percUpper = ( upperCount / wordCount ) * 100;
    if (percUpper > perc)
        return true;
    else
        return false;
}

/*
 returns the number of uppercase words
 param subj the text of which the words are counted
 */
int getNumUpper (string subj) {
    int numWords = getNumWords(subj);
    string thisWord = extractWord(subj);
    
    int numUp = 0;
    for (int i = 0;i < numWords; i++) {
        if (isUppercase(thisWord))
            numUp++;
        thisWord = extractWord(subj);
    }
    return numUp;
}

/*
 returns the number of words in the text
 param text the text of which the words are counted
 */
int getNumWords (string text) {
    
    int numWords = 0;
    while (extractWord(text) != "")
        numWords++;
    return numWords;
    
}


/*
 returns first word and modifies text to be all but first word
 param text the text that the word is extracted and which is modified
 */
string extractWord(string& text) {
    
    string first = getFirstWord(text);
    
    if (first == "")
        text = "";
    
    else {
        int indexFirstWord;
        indexFirstWord = (int) text.find(first);
        
        int lengthFirstWord = (int) first.size();
        int textLength = (int) text.size();
        
        int start = indexFirstWord + lengthFirstWord;
        text = text.substr(start, textLength - start);
    }
    return first;
}

/*
 returns true if the text contains more than three consecutive consonants
 param text the text that is analyzed
 */
bool isGibberishWord (string text) {
    int numCons = 0;
    for (int i = 0; i < (int) text.size() - 2; i++) {
        for (int j = i; j <= i + 3; j++) {
            if (isConsonant(text[j]))
                numCons++;
        }
        if (numCons > 3)
            return true;
        numCons = 0;
    }
    return false;
}


/*
 checks condition 3: returns true if subject has three or more contiguous exclamation marks
 param subj the text that is analyzed
 */
bool hasMultipleExclamations(string subj) {
    if (subj == "")
        return false;
    for (int i = 0; i < (int) subj.size() - 2; i++) {
        if (subj.substr(i, 3) == "!!!")
            return true;
    }
    return false;
}


/*
 returns the first word in the string
 param text the text the first word is extracted from
 */
string getFirstWord(string text) {
    if (text == "")
        return "";
    
    int i = 0;
    bool noMoreLetters = true;
    while (text[i] != '\0') {
        if (isalpha(text[i]))
            noMoreLetters = false;
        i++;
    }
    if (noMoreLetters)
        return "";
    
    
    i = 0;
    int dontInc = 0;
    while (!isalpha(text[i])) {
        i++;
        dontInc++;
    }
    while (isalpha(text[i]))
        i++;
    return text.substr(0 + dontInc, i - dontInc);
}



/*
 returns the last word in the string
 param text the text the last word is extracted from
 */
string getLastWord(string text) {
    if (text == "")
        return "";
    int i = 0;
    int dontInc = 0;
    while (text[i]!= '\0')
        i++;
    while (!isalpha(text[i-1])) {
        i--;
        dontInc++;
    }
    while (isalpha(text[i -1]))
        i--;
    int length = (int) text.size() - i;
    return text.substr(i, length - dontInc);
}

/*
 returns true if text is upper case
 param text the word tested
 */
bool isUppercase(string text) {
    bool allUp = true;
    for (int i = 0; i < (int) text.size(); i++) {
        if (isalpha(text[i]) && !isupper(text[i])) {
            allUp = false;
            return allUp;
        }
    }
    return allUp;
}

/*
 makes the text upper case
 param text the text that is warped and returned
 */
string makeUppercase(string text) {
    string upString;
    for (int i = 0; i < (int) text.size(); i++)
        upString += toupper(text[i]);
    return upString;
}

/*
 returns number of instances of trigger words
 param text the text that is tested
 */
int triggerWordChecker(string text) {
    if (text == "")
        return 0;
    
    int numTrigs = 0;
    string newString = makeUppercase(text);
    string thisWord;
    
    do {
        thisWord = extractWord(newString);
        if (thisWord == "BUY" || thisWord == "CHEAP" || thisWord == "CLICK" || thisWord == "DIPLOMA" || thisWord == "ENLARGE" || thisWord == "FREE" || thisWord == "LONELY" || thisWord == "MONEY" || thisWord == "NOW" || thisWord == "OFFER" || thisWord == "ONLY" || thisWord == "PILLS" || thisWord == "SEX")
            numTrigs++;
    } while (thisWord != "");
    
    return numTrigs;
}

/*
 checks if the character is a consonant
 param thisChar the character to test
 */
bool isConsonant (char thisChar) {
    if (thisChar =='B' || thisChar =='b' || thisChar =='C' || thisChar =='c' || thisChar =='D' || thisChar =='d' || thisChar =='F' || thisChar =='f' || thisChar =='G' || thisChar =='g' || thisChar =='H' || thisChar =='h' || thisChar =='J' || thisChar =='j' || thisChar =='K' || thisChar =='k' || thisChar =='L' || thisChar =='l' || thisChar =='M' || thisChar =='m' || thisChar =='N' || thisChar =='n' || thisChar =='P' || thisChar =='p' || thisChar =='Q' || thisChar =='q' || thisChar =='R' || thisChar =='r' || thisChar =='S' || thisChar =='s' || thisChar =='T' || thisChar =='t' || thisChar =='V' || thisChar =='v' || thisChar =='W' || thisChar =='w' ||thisChar =='X' || thisChar =='x' || thisChar =='Y' || thisChar =='y' || thisChar =='Z' || thisChar =='z')
        return true;
    else
        return false;
}