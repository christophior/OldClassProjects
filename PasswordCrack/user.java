import java.util.*;

public class user {
	public String username;
	public String salt;
	public String encryptedPassword;
	public String uid;
	public String gid;
	public String name;
	public String homedir;
	public String shell;
	public ArrayList<String> userWords;
	public boolean isCracked = false;
	public ArrayList<String> mangledWords;
	public boolean roundTwo;
	
	public user(String un, String sa, String enc, String ui, String gi, String na, String hd, String sh){
		username = un;
		salt = sa;
		encryptedPassword = enc;
		uid = ui;
		gid = gi;
		name = na;
		homedir = hd;
		shell = sh;
		roundTwo = false;
		get_user_specific_words();
	}
	
	private void get_user_specific_words(){
		userWords = new ArrayList<String>();
		String[] names = name.split(" +");
		for (String n : names){
			userWords.add(n);
		}
	}
}
