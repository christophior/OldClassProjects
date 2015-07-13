import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;
import java.util.*;

public class file {
	String name;
	String permission;
	int mode;
	user owner;
	String group;
	
	public file(String n, user u, int m){
		name = n;
		owner = u;
		group = u.group;
		permission = "---------";
		setModeAndPermissions(m);
	}
	
	public void setModeAndPermissions(int m){
		mode = m;
		String mask = "rwxrwxrwx";
		String bin = String.format("%12s", Integer.toBinaryString(m)).replace(' ', '0');
		String specialBits = "";
		int[] executeSpaces = {2, 5, 8};
		
		specialBits = bin.substring(0,3);
		bin = bin.substring(3,bin.length());
		
		StringBuilder result = new StringBuilder();
		for (int i=0; i<9; ++i){
			char curr = mask.charAt(i);
			curr = bin.charAt(i) == '1' ? curr : '-';
			result.append(curr);
		}
		
		for (int i=0; i<specialBits.length(); ++i){
			if (specialBits.charAt(i) == '1'){
				if (i < 2){
					if (result.charAt(executeSpaces[i]) != '-'){
						result.setCharAt(executeSpaces[i], 's');
					} else {
						result.setCharAt(executeSpaces[i], 'S');
					}
				} else {
					if (result.charAt(executeSpaces[i]) != '-'){
						result.setCharAt(executeSpaces[i], 't');
					} else {
						result.setCharAt(executeSpaces[i], 'T');
					}
				}
			}
		}
		permission = result.toString();
	}
}

class fileList {
	static HashMap<String, file> list;
	
	public fileList(){
		list = new HashMap<String, file>();
	}
	
	public void addFile(String filename, user user, int mode){
		list.put(filename, new file(filename, user, mode));
	}
	
	public static boolean containsFile(String name){
		return list.containsKey(name);
	}
	
	public static file getFile(String name){
		return list.get(name);
	}
	
	public static void printList(){
		System.out.println("FILES:");
		ArrayList<String> keys = new ArrayList<String>(list.keySet());
		Collections.sort(keys);
		for (String k : keys){
			file u = list.get(k);
			System.out.println(u.permission + " " + u.owner.name + " " + u.group + " " + u.name);
		}
		System.out.println("");
	}
	
	public static void writeLog() throws FileNotFoundException, UnsupportedEncodingException{
		PrintWriter writer = new PrintWriter("state.log", "UTF-8");
		ArrayList<String> keys = new ArrayList<String>(list.keySet());
		Collections.sort(keys);
		for (String k : keys){
			file u = list.get(k);
			writer.println(u.permission + " " + u.owner.name + " " + u.group + " " + u.name);
		}
		writer.close();
	}
}