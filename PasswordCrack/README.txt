PasswordCrack
-------------
A program that takes in a world-readable password file of encrypted passwords for unix users and a file of dictionary words and cracks the passwords by using a dictionary attack along with common password creation methods. 

clone repository: git clone https://github.com/christophior/PasswordCrack.git
compile: javac *.java
run: java PasswordCrack <dictionary> <passwords> (eg. java PasswordCrack words.txt passwd1.txt)
