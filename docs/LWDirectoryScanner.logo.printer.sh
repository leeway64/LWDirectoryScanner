# For loops in Bash
for i in {1..100};
do
    # printf can print formatted output, kind of like the C printf
    printf "="
done
    
printf "\n"


# Find the line_number at which the credits start
line_number=$(grep -n "This" LWDirectoryScanner.logo.txt | cut -f1 -d:)

# Decrement line_number, so we're considering the last line of the logo
((line_number=line_number-1))

# cat prints the contents of the filename passed in as the argument to the terminal.
# Pipe the output of cat into the head command. The -$line_number argument tells head to only
# print the first line_number lines from LWDirectoryScanner.logo.txt.
# The pipe command (|) sends the output of the first command into the input of the second command.
cat LWDirectoryScanner.logo.txt | head -$line_number


# While loops in Bash
n=93
while [ $n -gt 0 ];
do
    printf "="
    ((n--))  # Another way to decrement a variable
done


# Arrays in Bash
bottom_border1=("=" "=" "=" "=" "=")
# Print every element in the bottom_border1 array 1 element at a time
for j in "${bottom_border1[@]}"
do
   printf "$j"
done


bottom_border2=("=")
# Print every element in the bottom_border2 array all at once
printf ${bottom_border2[*]}


# if statements in Bash
# If the directory exists, then execute the code in the if block
if [ -d "$../" ]; then
    printf "="
fi

# The echo command prints its arguments to the terminal
echo "="

