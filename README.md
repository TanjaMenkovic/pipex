The program will be executed as follows:
./pipex file1 cmd1 cmd2 file2

In mandatory part it must take 4 arguments:
• file1 and file2 are file names.
• cmd1 and cmd2 are shell commands with their parameters.
It must behave exactly the same as the shell command below:
$> < file1 cmd1 | cmd2 > file2

=============================================

Bonus part:

• Handle multiple pipes.
This:
$> ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
Should behave like:
< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

• Support « and » when the first parameter is "here_doc".
This:
$> ./pipex here_doc LIMITER cmd cmd1 file
Should behave like:
cmd << LIMITER | cmd1 >> file

=============================================

My testing:

NOT ENOUGH ARG:

./pipex 
./pipex 1
./pipex 1 2
./pipex 1 2 3 
./pipex 1 2 3 4 5
Out:
pipex: invalid number of arguments.

---------------------------------------------

CORRECT INPUT:

./pipex sorted_file.txt "ls -l" "wc -l" outfile
< sorted_file.txt ls -l | wc -l > out
Out: 18

./pipex sorted_file.txt "grep Hello" "wc -w" outfile
< sorted_file.txt grep Hello | wc -w > out
Out: 235

< sorted_file.txt grep Hello | wc -l > output
./pipex sorted_file.txt "grep Hello" "wc -l" outfile
Out: 6

-----------------------------------------------

INCORRECT INPUT (with non existent file name in command):

< sorted_file.txt fizzBuzz | ls -l src/ > output
./pipex sorted_file.txt fizzBuzz "ls -l src/" outfile
My:
pipex: command not found: fizzBuzz
ls: src/: No such file or directory
Built-in:
zsh: command not found: fizzBuzz
ls: src/: No such file or directory

< sorted_file.txt ls -l src/ | buzzFizz > output
./pipex sorted_file.txt "ls -l src/" fizzBuzz outfile
My:
pipex: command not found: fizzBuzz <- MINE IS NOT RETURNING THE SAME
Built-in:
zsh: command not found: buzzFizz
ls: src/: No such file or directory

./pipex sorted_file.txt "ls -l src/" cat outfile 
< sorted_file.txt ls -l src/ | cat > output
Out: 
ls: src/: No such file or directory

./pipex sorted_file.txt cat "ls -l src/" outfile
< sorted_file.txt cat | ls -l src/ > output 
Out:
ls: src/: No such file or directory

---------------------------------------------

EMPTY INPUT:

./pipex in "" "" outfile
< in "" | "" > out
Out:
My:
pipes: no such file or directory: in
pipex: permission denied:
Built-in:
zsh: no such file or directory: in
zsh: permission denied: 

./pipex in cat "" outfile
< in cat | "" > out
Out:
My:
pipex: no such file or directory: in
pipex: permission denied:
Built-in:
zsh: no such file or directory: in
zsh: permission denied:

./pipex in "" cat outfile
< in "" | cat > out
Out:
My:
pipex: no such file or directory: in
Built-in:
zsh: no such file or directory: in

< sorted_file.txt "" | "" > out
./pipex sorted_file.txt "" "" outfile
Out:
My:
pipex: permission denied:
pipex: permission denied:
Built-in:
zsh: permission denied:
zsh: permission denied: 

./pipex sorted_file.txt cat "" outfile
< sorted_file.txt cat | "" > out
Out:
My:
pipex: permission denied:
Built-in:
zsh: permission denied: 

./pipex sorted_file.txt "" cat outfile
< sorted_file.txt "" | cat > out
Out:
My:
pipex: permission denied:
Built-in:
zsh: permission denied: 

--------------------------------------------

DOT IN COMMAND:

< in "." | "." > out
./pipex in "." "." outfile
Out:
My:
pipex: no such file or directory: in
pipex: .: not enough arguments
Built-in:
zsh: no such file or directory: in
.: not enough arguments

./pipex in cat "." outfile
< in cat | "." > out
Out:
My:
pipex: no such file or directory: in
pipex: .: not enough arguments
Built-in:
zsh: no such file or directory: in
.: not enough arguments

./pipex in "." cat outfile
< in "." | cat > out
Out:
My:
pipex: no such file or directory: in
Built-in:
zsh: no such file or directory: in

< sorted_file.txt "." | "." > out
./pipex sorted_file.txt "." "." outfile
Out:
My:
pipex: .: not enough arguments
pipex: .: not enough arguments
Built-in:
.: not enough arguments
.: not enough arguments

./pipex sorted_file.txt cat "." outfile
< sorted_file.txt cat | "." > out
Out:
My:
pipex: .: not enough arguments
Built-in:
.: not enough arguments 

./pipex sorted_file.txt "." cat outfile
< sorted_file.txt "." | cat > out
Out:
My:
pipex: .: not enough arguments
Built-in:
.: not enough arguments

---------------------------------------------

INCORRECT INPUT:

./pipex 1 2 3 4
< 1 2 | 3 > 4
Out:
My:
pipex: no such file or directory: 1
pipex: command not found: 3
Built-in:
zsh: no such file or directory: 1
zsh: command not found: 3

./pipex 1 cat 3 4
< 1 cat | 3 > 4
My:
pipex: no such file or directory: 1
pipex: command not found: 3
Built-in:
zsh: no such file or directory: 1
zsh: command not found: 3

./pipex 1 2 cat 4  
< 1 2 | cat > 4
Out:
My:
pipex: no such file or directory: 1
Built-in:
zsh: no such file or directory: 1

./pipex sorted_file.txt 2 cat 4 
< sorted_file.txt 2 | cat > 4
My:
pipex: command not found: 2
Built-in:
zsh: command not found: 2

./pipex sorted_file.txt cat 3 4 
< sorted_file.txt cat | 3 > 4
My: 
pipex: command not found: 3
built_in:
zsh: command not found: 3

---------------------------------------

QUOTES:

< sorted_file.txt grep Hello | awk '{count++} END {print count}' > out
./pipex sorted_file.txt "grep Hello" "awk '{count++} END {print count}'" outfile 
Out: 6

< sorted_file.txt grep Hello | awk "{count++} END {print count}" > out
./pipex sorted_file.txt "grep Hello" 'awk "{count++} END {print count}"' outfile 
Out: 6

< sorted_file.txt grep Hello | awk '"{count++} END {print count}"' > out
./pipex sorted_file.txt "grep Hello" "awk '\"{count++} END {print count}\"'" outfile
Out: 
Hello Text Message Scam
In the digital age, scams, and fraudulent activities continue to evolve, targeting unsuspecting individuals through various means. One such deceptive tactic is the “Hello Text Message Scam”. Seemingly harmless, these innocent-sounding messages aim to elicit a response from the recipient, providing scammers with valuable information to exploit. This article sheds light on this particular scam and offers advice on how to protect yourself from falling victim to such schemes.
The Anatomy of the Hello Text Message Scam
The Hello Text Message Scam follows a simple modus operandi. Scammers send a message containing common words or phrases like “hi,” “hello,” or “I found this number on my phone.” These messages appear harmless, intending to initiate a conversation with the recipient. Upon responding, the victim unknowingly confirms the validity of their phone number, which the scammer can exploit in various ways.
While it’s impossible to completely eliminate the risk of encountering scams, you can take proactive measures to protect yourself from the Hello Text Message Scam:
The Hello Text Message Scam preys on unsuspecting individuals by exploiting their tendency to respond to innocent-sounding messages. While these messages may appear harmless, they can have severe consequences, including spam, phishing attempts, and harassment. By remaining vigilant, exercising caution, and following the aforementioned preventive measures, you can protect yourself from falling victim to such scams. Stay informed, stay alert, and stay safe in the digital world.

< sorted_file.txt grep Hello | awk "'{count++} END {print count}'" > out
./pipex sorted_file.txt "grep Hello" "awk \"'{count++} END {print count}'\"" outfile 
Out: 
awk: syntax error at source line 1
 context is
	 >>> ' <<< 
awk: bailing out at source line 1

----------------------------------------

NONEXISTING FIRST COMMAND:

./pipex "sorted_file.txt" "notexisting" "wc" "out"
< "sorted_file.txt" "notexisting" | "wc" > out
My:
pipex: command not found: notexisting
Built-in:
zsh: command not found: notexisting
Out: 0 0 0
