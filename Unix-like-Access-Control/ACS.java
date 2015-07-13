import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.util.*;

public class ACS {
	
	static userList users;
	static fileList files;
	static boolean createRoot;
	
	public static void main(String args[]) throws IOException{
		System.out.println("Starting Access Control...");

		createRoot = true;
		BufferedReader userList, fileList;// = new BufferedReader(new FileReader(keyFile));
		int index = 0;

		users = new userList();
		files = new fileList();

		// check if there is an option flag
		if (args.length == 3){
			index++;
			if (args[0].equals("-r"))
				createRoot = false;
			else 
				System.err.println("The given option is not valid; no root user created.");
		}

		// open files
		try{
			userList = new BufferedReader(new FileReader(args[index]));
			fileList = new BufferedReader(new FileReader(args[index+1]));
		} catch (Exception e){
			System.err.println("Unable to open the user/file list file.");
			return;
		}
		

		
		// create users and files
		System.out.println("Gathering Users and Files...");
		parseFile(userList, users, true);
		parseFile(fileList, files, false);			
		userList.close();
		fileList.close();

		
		System.out.println("Begin action execution");
		System.out.println("-----");
		executeActions();
	}
	
	public static void executeActions() throws FileNotFoundException, UnsupportedEncodingException{
		Scanner s = new Scanner(System.in);
		while (s.hasNext()) {
		    String line = s.nextLine();
		    System.out.println("Input:\n" + line);
		    String[] parsedLine = line.split("\\s+");
		    System.out.println("Output:");
		    
		    //read, write, execute, chmod, exit
		    if ((parsedLine[0].toLowerCase()).equals("read")){
		    	Read(userList.getUser(parsedLine[1]), fileList.getFile(parsedLine[2]));
		    } else if ((parsedLine[0].toLowerCase()).equals("write")){
		    	Write(userList.getUser(parsedLine[1]), fileList.getFile(parsedLine[2]));
		    } else if ((parsedLine[0].toLowerCase()).equals("execute")){
		    	Execute(userList.getUser(parsedLine[1]), fileList.getFile(parsedLine[2]));
		    } else if ((parsedLine[0].toLowerCase()).equals("chmod")){
		    	Chmod(userList.getUser(parsedLine[1]), fileList.getFile(parsedLine[2]), Integer.parseInt(parsedLine[3],8));
		    } else if ((parsedLine[0].toLowerCase()).equals("exit")){
		    	Exit();
		    	break;
		    }
		}
	}
	
	public static void Read(user u, file f){

		int readable=0;
		
		if ((u.name).equals(f.owner.name)){
			readable = (f.permission).charAt(0) == 'r' ? 1 : 0;
		} else if ((u.group).equals(f.group)){
			readable = (f.permission).charAt(3) == 'r' ? 1 : 0;
		} else {
			readable = (f.permission).charAt(6) == 'r' ? 1 : 0;
		}
		
		System.out.println("READ " + u.name + " " + u.group + " " + readable);
	}
	
	public static void Write(user u, file f){

		int writeable=0;
		
		if ((u.name).equals(f.owner.name)){
			writeable = (f.permission).charAt(1) == 'w' ? 1 : 0;
		} else if ((u.group).equals(f.group)){
			writeable = (f.permission).charAt(4) == 'w' ? 1 : 0;
		} else {
			writeable = (f.permission).charAt(7) == 'w' ? 1 : 0;
		}
		
		System.out.println("WRITE " + u.name + " " + u.group + " " + writeable);
	}
	
	public static void Execute(user u, file f){
		int executable = 0;
		
		if ((u.name).equals(f.owner.name)){
			executable = (f.permission).charAt(2) == 'x' || (f.permission).charAt(2) == 's' ? 1 : 0;
			if ((f.permission).charAt(2) == 's' || (f.permission).charAt(2) == 'S'){
				f.owner = u;
			}
		} else if ((u.group).equals(f.group)){
			executable = (f.permission).charAt(5) == 'x' || (f.permission).charAt(5) == 's' ? 1 : 0;
			if ((f.permission).charAt(5) == 's' || (f.permission).charAt(5) == 'S'){
				f.owner = u;
			}
		} else {
			executable = (f.permission).charAt(8) == 'x' || (f.permission).charAt(8) == 't' ? 1 : 0;
			if ((f.permission).charAt(8) == 't' || (f.permission).charAt(8) == 'T'){
				f.owner = u;
			}
		}
		
		System.out.println("EXECUTE " + u.name + " " + u.group + " " + executable);
	}
	
	public static void Chmod(user u, file f, int mode){
		if ((u.name).equals(f.owner.name) || u.group.equals("root")){
			f.setModeAndPermissions(mode);
			System.out.println("CHMOD " + u.name + " " + u.group + " 1");
			return;
		}
		System.out.println("CHMOD " + u.name + " " + u.group + " 0");
	}
	
	public static void Exit() throws FileNotFoundException, UnsupportedEncodingException{
		fileList.printList();
		fileList.writeLog();
	}
	
	public static void parseFile(BufferedReader reader, Object list, boolean parsingUsers) throws IOException{
		String line;
		int lineNumber = 0;
		
		while ((line = reader.readLine()) != null) {
			try{
				String[] parsedLine = line.split("\\s+");
				if (parsingUsers){
					((userList)list).addUser(parsedLine[0], parsedLine[1]);
				}
				else{
					user u = userList.getUser(parsedLine[1]);
					((fileList)list).addFile(parsedLine[0], u, Integer.parseInt(parsedLine[2],8));
				}
			} catch (Exception e){
				System.err.println("Incorrect line format for line number " + lineNumber);
			}
			++lineNumber;
		}
		
		if (parsingUsers && createRoot){
			((userList)list).addUser("root", "root");
		}
	}
}
