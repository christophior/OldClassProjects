import java.util.*;
import java.util.concurrent.Callable;


public class mangles {
	static List<String> keyboard_chars = Arrays.asList("a","b","c","d","e","f","g","h","i","j","k","l"
			,"m","n","o","p","q","r","s","t","u","v","w","x","y","z","A","B","C","D","E","F","G"
			,"H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
			,"0","1","2","3","4","5","6","7","8","9","!","@","#","$","%","^","&","*","(",")"
			,"`","~","-","_","=","+","[","]","{","}","\\","|",";",":","'", "\"", ",", "<", ".", ">", "?", "/");

	public static boolean pendCracks(user u, List<String> words){
		for (String singleWord : words){
			for (String keyboardKey : keyboard_chars){
				String newWord = prepend(singleWord,keyboardKey);
				if(PasswordCrack.isPassword(u, newWord))
					return true;
				newWord = append(singleWord,keyboardKey);
				if(PasswordCrack.isPassword(u, newWord))
					return true;
			}
		}
		return false;
	}


	public static boolean otherMangleCracks(user u, List<String> words){
		for (String singleWord : words){
			String newWord = deleteFirst(singleWord);
			if(PasswordCrack.isPassword(u, newWord))
				return true;
			newWord = deleteLast(singleWord);
			if(PasswordCrack.isPassword(u, newWord))
				return true;
			newWord = reverse(singleWord);
			if(PasswordCrack.isPassword(u, newWord))
				return true;
			newWord = duplicate(singleWord);
			if(PasswordCrack.isPassword(u, newWord))
				return true;
			newWord = reflect(singleWord);
			if(PasswordCrack.isPassword(u, newWord))
				return true;
			newWord = uppercase(singleWord);
			if(PasswordCrack.isPassword(u, newWord))
				return true;
			newWord = lowercase(singleWord);
			if(PasswordCrack.isPassword(u, newWord))
				return true;
			newWord = capitalize(singleWord);
			if(PasswordCrack.isPassword(u, newWord))
				return true;
			newWord = toggleCase(singleWord, true);
			if(PasswordCrack.isPassword(u, newWord))
				return true;

			newWord = toggleCase(singleWord, false);
			if(PasswordCrack.isPassword(u, newWord))
				return true;
		}
		return false;
	}

	public static boolean ncapitalizeCrack(user u, List<String> words){
		for (String singleWord : words){
			for (int i=0; i<singleWord.length(); ++i){
				String newWord = ncapitalize(singleWord,i);
				if(PasswordCrack.isPassword(u, newWord))
					return true;
			}}
		return false;
	}

	private static String deleteFirst(String word){
		if (word.length() > 0)
			return word.substring(1);
		return "";
	}

	private static String deleteLast(String word){
		if (word.length() > 0)
			return word.substring(0, word.length()-1);
		return "";
	}

	private static String prepend(String word, String pre){ return pre + word; }
	private static String append(String word, String post){ return word + post; }
	private static String reverse(String word){ return new StringBuilder(word).reverse().toString(); }
	private static String duplicate(String word){ return word + word; }
	private static String reflect(String word){ return word + new StringBuilder(word).reverse().toString(); }
	private static String uppercase(String word){ return word.toUpperCase(); }
	private static String lowercase(String word){ return word.toLowerCase(); }

	private static String capitalize(String word){
		if (word.length() > 0)
			return (word.charAt(0) + "").toUpperCase() + word.substring(1);
		return "";
	}

	private static String ncapitalize(String word, int n){
		word = lowercase(word);
		if (word.length() > 0)
			return word.substring(0, n) + (word.charAt(n) + "").toUpperCase() + word.substring(n+1, word.length());
		return "";
	}

	private static String toggleCase(String word, boolean even){
		StringBuilder result = new StringBuilder();
		word = lowercase(word);

		for (int i=0; i<word.length(); ++i){
			if (even){
				if (i%2 == 0)
					result.append((word.charAt(i) + "").toUpperCase());
				else 
					result.append(word.charAt(i) + "");
			} else {
				if (i%2 == 1)
					result.append((word.charAt(i) + "").toUpperCase());
				else
					result.append(word.charAt(i) + "");
			}
		}
		return result.toString();
	}
}