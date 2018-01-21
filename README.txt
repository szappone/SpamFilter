1 - initially I coded the backbone of the program - prompting and taking inputs in a loop until the user inputted ’n’. That worked great! But once I got to functions, I wrote a whole bunch of functions (that called each other) without first unit testing them that thoroughly. So it got pretty messy. While the logic of my program was done, I kept getting this out_of_range exception so the spam score was not coming out right. I ended up starting a whole new project on Xcode and copy/pasting segment at a time testing each one until I finally got it going! Another learning point was using functions to call other functions, that was quite helpful.

function declarations

main {

variable declarations
while (the user has not inputed ’n’)

Prompt: “Enter the subject line of the email: “
Read in subject

check condition #1
       if (uppercase words > 90%)
        spamScore += 30
       
check condition #2
        get the last word
        if (the last word is gibberish)
            spamScore += 40
        
check condition #3
        if (subject has multiple exclamation marks)
            spamScore += 20
        
Prompt: "Enter the body of the email.  Press Enter on an empty line to finish.”
Read in body
             
check condition #4
         if (uppercase words > 50%)
            spamScore +=40
        
check condition #5
	get the number of trigger words
	multiply by 5 to get the number to add
        spamScore += numToAdd;
    
output whether the message is classified as spam (spamScore > 100) or legitimate

in a nested while: while (the user does not input ‘y’ or ’n’)
	ask if they would like to classify another email. Change parent while and nested while accordingly.

} //end main, functions follow


3 Test Data
Testing Conditions 1 - 3 (subject)
1: input subject with exactly 90% upper case words
ex. There are ten words in THIS sentence but ones uppercase.
input uppercase words hidden inside symbols
ex. !LOOK! &AN& **UPPERCASE** &&word.
2: When the consonants are mixed upper and lower case
ex. This is not a jKMdff valid sentence.
3: input exclamations at very beginning, very end, and inside symbols:
ex: !!!Hello, Hello!!!, **!!!**
Texting Conditions 4 & 5 (body)
4: input subject with exactly 50% upper case words
ex. HALF of these ARE UPPER case
input uppercase words hidden inside symbols
ex. !LOOK! &AN& **UPPERCASE** &&word.
5. input trigger words in: all lowercase, all uppercase, combined
ex: buy, BUY, bUy
input longer words with trigger words hidden inside
ex: freedom, know, cheapskate
input the same word repeated without space
freefreefreefree