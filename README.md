Kipling Gillespie
CS485
11/03/2017

toraw

This program takes input from the keyboard in 3 formats. 
Hex: The user can type in 1 byte values in hex seperated with spaces
and the program will translate them to their associated ASCII 
value and display the result. Any value greater than 7F will be reported as 
being undisplayable and the input will not be displayed.

Dec: The user can start their input with -d and follow their input with integers
seperated by spaces. The input will be converted to their ASCII character values
and displayed. Any decimal value greater than 127 will be reported as being 
undisplayable and the input will not be displayed.

Char: The user can start their input with -c and the rest of their input that 
follows will be copied as characters and displayed. 

Comments:
comment blocks /* This is a comment block */ can be included in any of the 3
format's inputs, but the contents of the comment block will not be displayed.


Known Issues:
To quit input you must press Ctrl-d twice, otherwise the program doesn't 
register the input. 
