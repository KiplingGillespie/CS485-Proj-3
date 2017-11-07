/*
	Kipling Gillespie
	CS485
	Project 3
	Date: 10/23/2017

	"The purpose of this project is to introduce me to systems programming in C.
	I must complete this in ANSI C, not C99, C++, or C#. This program must compile and run
	on my virtual machine, although I may develop on any machine I like.

	I developed the code on my windows 10 laptop using Code::Blocks 13.12 as an IDE.

	My goal is to take input from standard input in one of 3 formats.
	Hex: will be default and will accept 1-byte hex values that will be converted
        into characters.
	Decimal: Input will be preceded by -d, then cast to a characters.
	Character: Input will be preceded by -c, I will take input and just chop off first few characters.
    Comments: Using block style comments is allowed, but will be removed before output.
    Input Ends: upon reaching the end of a file that has been fed in, or
        by the user typing Ctrl-d and pressing enter.
*/

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "ctype.h"

#define bufsize 1024

int GetInput(char* output);

int ParseString(char* output);

int ReadHex(char* output);

int ReadDecimal(char* output);

int ReadCharacters(char* output);

int main()
{
	
	// Create and initialize my buffer to NULL
	char buffer[bufsize];
	memset(buffer, 0, bufsize);

	int error = 0;
	int inputError = 0;
	int parseError = 0;
	
	while(1)
    	{
		// Get input from keyboard and store it in buffer
        	inputError = GetInput(buffer);

		// Parse buffer and modify it.
       		parseError = ParseString(buffer);

		// Accumulate errors from input and parse
        	error = inputError | parseError;

		// Display the input if there were no errors. 
        	if(error != -1)
            		printf("%s\n", buffer);
            
		// Clear out the buffer for the next input.
		memset(buffer, 0, bufsize);
	}


	return 0;
}

int GetInput(char* output)
{
    // Get user input from keyboard and store it in output, removing leading white spaces
    // and comment blocks.
    char c;
    int i = 0;

    // clear out leading white spaces
    while(1)
    {
        c = getchar();
        if(!isspace(c))
        {
            ungetc(c, stdin);
            break;
        }
    }

    c = getchar();
    while(c != '\n' && i < bufsize)
    {
        switch(c)
        {
        case 4:
            {
                // c is the end of transmission character
                exit(0);
            }
        case EOF:
            {
                // end of file was detected.
                exit(0);
            }
        case '/':
            {
                // Beginning of comment block.
                c = getchar();

                // There is an error if the next character isn't a star.
                if(c != '*')
                    return -1;

                // clear out comment's
                c = getchar();
                while(1)
                {
                    c = getchar();
                    // check for end of comment
                    if(c == '*')
                    {
                        c = getchar();
                        // found end of comment
                        if( c == '/')
                            break;

                    }
                }
                break;
            }
        default:
            {
                // this is a valid character, add it to the list.
                output[i] = c;
                i++;
            }
        }

        // get next character
        c = getchar();
    }

    return 0;
}

int ParseString(char* output)
{
	// This function will determine if the input
	// string is hex, decimal, or character.
    	int error = 0;
    	int DecimalError = 0;
	int CharactersError = 0;
	int HexErrors = 0;
	//int spaceError = 0;
    	
	// A -d or -c tag were the first characters
	if(output[0] == '-')
    	{
        	if(output[1] == 'd')
            		DecimalError = ReadDecimal(output);
        	else if(output[1] == 'c')
            		CharactersError = ReadCharacters(output);
        	else
		{
            		printf("ERROR: Invalid tag.");
			error = -1;
		}
    	}	
    	else
        	HexErrors = ReadHex(output);

    //spaceError = RemoveTrailingSpaces(output);

    error = error | DecimalError | CharactersError | HexErrors;// | spaceError;

    return error;
}

int ReadHex(char* output)
{
    // Get my input string
    char input[bufsize];
    strcpy(input, output);

    char letter[4];

    // clear my output;
    memset(output, 0, bufsize);
    size_t i = 0;
    size_t j = 0;
    size_t len = strlen(input);

    while(i < len && i < bufsize && j < bufsize)
    {
        memset(letter, 0, 4);

        switch(input[i])
        {
        case ' ':
            {
                //skip white spaces
                i++;
                break;
            }
        default:
            {
                // 1 character hex values are invalid
                if(isspace(input[i+1] || input[i+1] == 0))
                {
                    letter[0] = input[i];
                    printf("%s is not a displayable hex value.\n", letter);
                    return -1;
                }


                letter[0] = input[i];
                letter[1] = input[i+1];
                int character = (int)strtol(letter, NULL, 16);

                //3 character hex value's are invalid
                if(!isspace(input[i+2]) && input[i+2] != 0)
                {
                       letter[2] = input[i+2];
                       printf("%s is not a displayable character.\n", letter);
                       return -1;
                }

                // check if character is non-displayable
                if(character > 127)
                {
                    printf("%s is a non-displayable character.\n", letter);
                    return -1;
                }
                output[j] = (char)character;

                // incrementing i by 3 will skip the following whitespace.
                i += 2;
                j += 1;
            }
        }
    }

	return 0;
}


int ReadDecimal(char* output)
{
    // Get my input string
    char characters[4];
    char input[bufsize];
    strcpy(input, output);
    size_t len = strlen(input);
    int num = 0;

    // clear my output;
    memset(output, 0, bufsize);
    memset(characters, 0, 4);

    // start i after -d
    int i = 3;
    int j = 0;

    // remove leading spaces
    while(i < len && input[i] == ' ')
    {
        i++;
    }

    // If inject is 1 we are ready to save our character buffer to our output.
    int inject = 0;
    while( i < len)
    {
        int k = 0;
        while(input[i] != ' ' && input[i] != (char)0)
        {
            // we have read in too many characters. This is not a decimal for a character.
            if(k > 2)
                return -1;

            characters[k] = input[i];
            // Since we have added characters we know it can be printed once we end the loop.
            inject = 1;

            // Increment our input and our character buffer
            k++;
            i++;
        }
        //  we are ready to convert our character buffer to a character
        if(inject)
        {
            
	    num = (int)strtol(characters, NULL, 10);
	  
            // check to see if character is displayable.
            if(num > 127)
            {
                printf("%s is a non-displayable character.\n", characters);
                return -1;
            }

	    output[j] = (char)num;
            memset(characters, 0, 4);
            j++;

            // We have printed, we don't need to inject again until we have added more values to characters.
            inject = 0;
        }
        // increment our input
        i++;
    }

    return 0;
}

int ReadCharacters(char* output)
{
    // Get my input string
    char input[bufsize];
    strcpy(input, output);
    size_t len = strlen(input);

    // clear my output;
    memset(output, 0, bufsize);

    // copy every thing from input after "-c " to the output.
    memcpy(output, &input[3], len - 3);

    return 0;
}
