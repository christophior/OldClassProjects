import java.util.*;

public class user {
	String name;
	String group;
	
	public user(String n, String g){
		name = n;
		group = g;
	}
}


class userList{
	static HashMap<String, user> list;

	public userList(){
		list = new HashMap<String, user>();
	}
	
	public void addUser(String name, String group){
		list.put(name, new user(name, group));
	}
	
	public static boolean containsUser(String name){
		return list.containsKey(name);
	}
	
	public static user getUser(String name){
		return list.get(name);
	}
	
	public static void printList(){
		System.out.println("USERS:");
		ArrayList<String> keys = new ArrayList<String>(list.keySet());
		Collections.sort(keys);
		for (String k : keys){
			user u = list.get(k);
			System.out.println(u.name + " : " + u.group);
		}
		System.out.println("");
	}
}