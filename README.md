[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/pAwGQi_N)

# PA4 Skeleton Code
We expect a fully functioninig command line REPL application for an inventory querying system. Feel free to modify the skeleton code as you see fit.

### How to run the current skeleton code
`make` will compile and execute the skeleton code

Feel free to modify Makefile as you see fit.


Test Cases:
* For lowercaseify() I selected "nkvcxoiuou\t\n qwrbsmvxzlj" & "BIGBROWNDOGgotsenttothegulag" as the first tests if lowercaseify()
ignores tabs, end lines, spaces, & lowercase characters and the second tests if lowercaseify() can handle uppercase letters correctly.
* For testing import_data() I decided to check if all lines read by import data were contained in the hash map after import_data()
executed and after rehashing, ensuring that the rehashing function works as well
* For deemptify_string() I used the common_trailing_characters string, to test if it will return an empty string and a string
with some of the elements of common_trailing_characters in the middle of the string to check that it ignores anything between text
* For testing skip_false_comma_delimeters(), I used the string "before false delim, after false delim,after real,,,delim"
to check that it only returns values corresponding to positions in the string that contain "," and not ", " when "," is surrounded by text, with a tripple comma and a case with ", ".
