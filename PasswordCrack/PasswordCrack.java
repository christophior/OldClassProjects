import java.util.*;
import java.io.*;

public class PasswordCrack {
	
	static ArrayList<user> users;
	static ArrayList<String> dictionary;
	static List<String> keyboard_chars = Arrays.asList("a","b","c","d","e","f","g","h","i","j","k","l"
			,"m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G"
			,"H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
			,"0","1","2","3","4","5","6","7","8","9","!","@","#","$","%","^","&","*","(",")"
			,"`","~","-","_","=","+","[","]","{","}","\\","|",";",":","'", "\"", ",", "<", ".", ">", "?", "/");
	
	static long startTime;
	
	public static void main(String args[]) throws IOException{
		if (args.length != 2){
			System.err.println("Incorrect input!");
			System.err.println("Input format: java PasswordCrack <dictionary> <passwords to crack>");
		} else {
			System.out.println("Reading in dictionary and passwords to crack.");
			try{ // try to open files
				BufferedReader dictionaryReader = new BufferedReader(new FileReader(args[0]));
				BufferedReader passwordsToCrackReader = new BufferedReader(new FileReader(args[1]));
				System.out.println("Gathering users...");
				read_in_users(passwordsToCrackReader);
				passwordsToCrackReader.close();
				read_in_dictionary(dictionaryReader);
				dictionaryReader.close();
				startTime = System.currentTimeMillis();
				crack_passwords();
			} catch (Exception e){ //throw error; not able to open files
				System.err.println("Unable to read files, check input!");
			}
		}
	}
	
	public static void crack_passwords(){
//		System.out.println("\nStarting tier1 crack...");
//		System.out.println("-----");
		for(user u : users)
			if (!u.isCracked)
				tier1_crack(u);
		
//		System.out.println("\nStarting tier 2 crack...");
//		System.out.println("-----");
		for(user u : users)
			if (!u.isCracked){
				u.mangledWords = new ArrayList<String>();
				tier2_crack(u);
			}
	
//		System.out.println("\nStarting tier 3 crack...");
//		System.out.println("-----");
		for(user u : users)
			if (!u.isCracked)
				tier3_crack(u);
	}
	
	public static boolean tier1_crack(user u){
		
		for (String userWord : u.userWords){ // user specific words
			if(isPassword(u, userWord))
				return true;
		}
		
		for (String userWord : dictionary){ // dictionary words
			if(isPassword(u, userWord))
				return true;
		}
		return false;
	}
	
	public static boolean tier2_crack(user u){
		u.roundTwo = true;
		if (mangles.otherMangleCracks(u, u.userWords)) return true;
		if (mangles.otherMangleCracks(u, dictionary)) return true;
		if (mangles.ncapitalizeCrack(u, u.userWords)) return true;
		if (mangles.ncapitalizeCrack(u, dictionary)) return true;
		if (mangles.pendCracks(u, u.userWords)) return true;
		if (mangles.pendCracks(u, dictionary)) return true;
		return false;
	}
	
	public static boolean tier3_crack(user u){
		u.roundTwo = false;
		if (mangles.otherMangleCracks(u, u.mangledWords)) return true;
		if (mangles.ncapitalizeCrack(u, u.mangledWords)) return true;
		if (mangles.pendCracks(u, u.mangledWords)) return true;
		return false;
	}
	
	public static void read_in_users(BufferedReader passwordsToCrackReader) throws IOException{
		users = new ArrayList<user>();
		String line;
		int linenumber = 0;
		
		while ((line = passwordsToCrackReader.readLine()) != null) {			
			// try to create user object from line
			try{
				String[] parts = line.split(":");
				String homedir = parts.length == 7 ? parts[6] : "";
				users.add(new user(parts[0], parts[1].substring(0, 2), parts[1], parts[2], parts[3], parts[4], parts[5], homedir));
			} 
			// or print error because line is not formatted correctly
			catch (Exception e){ 
				System.err.println("Line number " + linenumber + " is not in the correct format");
				System.err.println("Format: <account>:<encrypted password data>:<uid>:<gid>:<GCOS-field>:<homedir>:<shell>");
			}
			++linenumber;
		}
		
	}
	
	public static void read_in_dictionary(BufferedReader dictionaryReader) throws IOException{
		dictionary = new ArrayList<String>();
		String line;
		while ((line = dictionaryReader.readLine()) != null){
			dictionary.add(line);
		}
	}
	
	public static boolean isPassword(user u, String word){
		if (u.roundTwo)
			u.mangledWords.add(word);
		if (jcrypt.crypt(u.salt, word).equals(u.encryptedPassword)){
			System.out.println("(" + (System.currentTimeMillis() - startTime)/1000.0 + " seconds) cracked password for user '" + u.username + "': " + word);
			u.isCracked = true;
			return true;
		}
		return false;
	}

}
