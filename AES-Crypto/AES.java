import java.io.*;
import java.util.*;

public class AES {
	/* s-box */
	final private static byte[][] sbox = {
		{0x63, 0x7c, 0x77, 0x7b, (byte) 0xf2, 0x6b, 0x6f, (byte) 0xc5, 0x30, 0x01, 0x67, 0x2b, (byte) 0xfe, (byte) 0xd7, (byte) 0xab, 0x76}, 
		{(byte)0xca, (byte)0x82, (byte) 0xc9, 0x7d, (byte) 0xfa, 0x59, 0x47, (byte) 0xf0, (byte) 0xad, (byte) 0xd4, (byte) 0xa2, (byte)0xaf, (byte) 0x9c, (byte)0xa4, 0x72, (byte) 0xc0},
		{(byte)0xb7, (byte)0xfd, (byte)0x93, 0x26, 0x36, 0x3f, (byte) 0xf7, (byte)0xcc, 0x34, (byte)0xa5, (byte)0xe5, (byte)0xf1, 0x71, (byte)0xd8, 0x31, 0x15},
		{0x04, (byte)0xc7, 0x23, (byte)0xc3, 0x18, (byte)0x96, 0x05, (byte)0x9a, 0x07, 0x12, (byte)0x80, (byte)0xe2, (byte)0xeb, 0x27,(byte) 0xb2, 0x75},
		{0x09, (byte)0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, (byte)0xa0, 0x52, 0x3b, (byte)0xd6,(byte)0xb3, 0x29, (byte)0xe3, 0x2f, (byte)0x84}, 
		{0x53, (byte)0xd1, 0x00, (byte)0xed, 0x20, (byte)0xfc, (byte)0xb1, 0x5b, 0x6a, (byte)0xcb, (byte)0xbe, 0x39, 0x4a, 0x4c, 0x58, (byte)0xcf}, 
		{(byte)0xd0, (byte)0xef, (byte)0xaa, (byte)0xfb, 0x43, 0x4d, 0x33, (byte)0x85, 0x45, (byte)0xf9, 0x02, 0x7f, 0x50, 0x3c, (byte)0x9f, (byte)0xa8}, 
		{0x51, (byte)0xa3, 0x40, (byte)0x8f, (byte)0x92, (byte)0x9d, 0x38, (byte)0xf5, (byte)0xbc, (byte)0xb6, (byte)0xda, 0x21, 0x10, (byte)0xff, (byte)0xf3, (byte)0xd2},
		{(byte)0xcd, 0x0c, 0x13, (byte)0xec, 0x5f, (byte)0x97, 0x44, 0x17, (byte)0xc4, (byte)0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
		{0x60, (byte)0x81, 0x4f, (byte)0xdc, 0x22, 0x2a, (byte)0x90, (byte)0x88, 0x46, (byte)0xee, (byte)0xb8, 0x14, (byte)0xde, 0x5e, 0x0b, (byte)0xdb},
		{(byte)0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, (byte)0xc2, (byte)0xd3, (byte)0xac, 0x62, (byte)0x91, (byte)0x95, (byte)0xe4, 0x79}, 
		{(byte)0xe7, (byte)0xc8, 0x37, 0x6d, (byte)0x8d, (byte)0xd5, 0x4e, (byte)0xa9, 0x6c, 0x56, (byte)0xf4, (byte)0xea, 0x65, 0x7a, (byte)0xae, 0x08}, 
		{(byte)0xba, 0x78, 0x25, 0x2e, 0x1c, (byte)0xa6, (byte)0xb4, (byte)0xc6, (byte)0xe8, (byte)0xdd, 0x74, 0x1f, 0x4b, (byte)0xbd, (byte)0x8b, (byte)0x8a},
		{0x70, 0x3e, (byte)0xb5, 0x66, 0x48, 0x03, (byte)0xf6, 0x0e, 0x61, 0x35, 0x57, (byte)0xb9, (byte)0x86, (byte)0xc1, 0x1d, (byte)0x9e}, 
		{(byte)0xe1, (byte)0xf8, (byte)0x98, 0x11, 0x69, (byte)0xd9, (byte)0x8e, (byte)0x94, (byte)0x9b, 0x1e, (byte)0x87, (byte)0xe9, (byte)0xce, 0x55, 0x28, (byte)0xdf}, 
		{(byte)0x8c, (byte)0xa1, (byte)0x89, 0x0d, (byte)0xbf, (byte)0xe6, 0x42, 0x68, 0x41, (byte)0x99, 0x2d, 0x0f, (byte)0xb0, 0x54, (byte)0xbb, 0x16} 
	};
	/* inverse x-box */
	final private static byte[][] inv_sbox = {
		{0x52,0x09,0x6a,(byte)0xd5,0x30,0x36,(byte)0xa5,0x38,(byte)0xbf,0x40,(byte)0xa3,(byte)0x9e,(byte)0x81,(byte)0xf3,(byte)0xd7,(byte)0xfb},
		{0x7c,(byte)0xe3,0x39,(byte)0x82,(byte)0x9b,0x2f,(byte)0xff,(byte)0x87,0x34,(byte)0x8e,0x43,0x44,(byte)0xc4,(byte)0xde,(byte)0xe9,(byte)0xcb},
		{0x54,0x7b,(byte)0x94,0x32,(byte)0xa6,(byte)0xc2,0x23,0x3d,(byte)0xee,0x4c,(byte)0x95,0x0b,0x42,(byte)0xfa,(byte)0xc3,0x4e},
		{0x08,0x2e,(byte)0xa1,0x66,0x28,(byte)0xd9,0x24,(byte)0xb2,0x76,0x5b,(byte)0xa2,0x49,0x6d,(byte)0x8b,(byte)0xd1,0x25},
		{0x72,(byte)0xf8,(byte)0xf6,0x64,(byte)0x86,0x68,(byte)0x98,0x16,(byte)0xd4,(byte)0xa4,0x5c,(byte)0xcc,0x5d,0x65,(byte)0xb6,(byte)0x92},
		{0x6c,0x70,0x48,0x50,(byte)0xfd,(byte)0xed,(byte)0xb9,(byte)0xda,0x5e,0x15,0x46,0x57,(byte)0xa7,(byte)0x8d,(byte)0x9d,(byte)0x84},
		{(byte)0x90,(byte)0xd8,(byte)0xab,0x00,(byte)0x8c,(byte)0xbc,(byte)0xd3,0x0a,(byte)0xf7,(byte)0xe4,0x58,0x05,(byte)0xb8,(byte)0xb3,0x45,0x06},
		{(byte)0xd0,0x2c,0x1e,(byte)0x8f,(byte)0xca,0x3f,0x0f,0x02,(byte)0xc1,(byte)0xaf,(byte)0xbd,0x03,0x01,0x13,(byte)0x8a,0x6b},
		{0x3a,(byte)0x91,0x11,0x41,0x4f,0x67,(byte)0xdc,(byte)0xea,(byte)0x97,(byte)0xf2,(byte)0xcf,(byte)0xce,(byte)0xf0,(byte)0xb4,(byte)0xe6,0x73},
		{(byte)0x96,(byte)0xac,0x74,0x22,(byte)0xe7,(byte)0xad,0x35,(byte)0x85,(byte)0xe2,(byte)0xf9,0x37,(byte)0xe8,0x1c,0x75,(byte)0xdf,0x6e},
		{0x47,(byte)0xf1,0x1a,0x71,0x1d,0x29,(byte)0xc5,(byte)0x89,0x6f,(byte)0xb7,0x62,0x0e,(byte)0xaa,0x18,(byte)0xbe,0x1b},
		{(byte)0xfc,0x56,0x3e,0x4b,(byte)0xc6,(byte)0xd2,0x79,0x20,(byte)0x9a,(byte)0xdb,(byte)0xc0,(byte)0xfe,0x78,(byte)0xcd,0x5a,(byte)0xf4},
		{0x1f,(byte)0xdd,(byte)0xa8,0x33,(byte)0x88,0x07,(byte)0xc7,0x31,(byte)0xb1,0x12,0x10,0x59,0x27,(byte)0x80,(byte)0xec,0x5f},
		{0x60,0x51,0x7f,(byte)0xa9,0x19,(byte)0xb5,0x4a,0x0d,0x2d,(byte)0xe5,0x7a,(byte)0x9f,(byte)0x93,(byte)0xc9,(byte)0x9c,(byte)0xef},
		{(byte)0xa0,(byte)0xe0,0x3b,0x4d,(byte)0xae,0x2a,(byte)0xf5,(byte)0xb0,(byte)0xc8,(byte)0xeb,(byte)0xbb,0x3c,(byte)0x83,0x53,(byte)0x99,0x61},
		{0x17,0x2b,0x04,0x7e,(byte)0xba,0x77,(byte)0xd6,0x26,(byte)0xe1,0x69,0x14,0x63,0x55,0x21,0x0c,0x7d}
	};

	final static int[] LogTable = {
		0,   0,   25,  1,   50,  2,   26,  198, 75,  199, 27,  104, 51,  238, 223, 3, 
		100, 4,   224, 14,  52,  141, 129, 239, 76,  113, 8,   200, 248, 105, 28,  193, 
		125, 194, 29,  181, 249, 185, 39,  106, 77,  228, 166, 114, 154, 201, 9,   120, 
		101, 47,  138, 5,   33,  15,  225, 36,  18,  240, 130, 69,  53,  147, 218, 142, 
		150, 143, 219, 189, 54,  208, 206, 148, 19,  92,  210, 241, 64,  70,  131, 56, 
		102, 221, 253, 48,  191, 6,   139, 98,  179, 37,  226, 152, 34,  136, 145, 16, 
		126, 110, 72,  195, 163, 182, 30,  66,  58,  107, 40,  84,  250, 133, 61,  186, 
		43,  121, 10,  21,  155, 159, 94,  202, 78,  212, 172, 229, 243, 115, 167, 87, 
		175, 88,  168, 80,  244, 234, 214, 116, 79,  174, 233, 213, 231, 230, 173, 232, 
		44,  215, 117, 122, 235, 22,  11,  245, 89,  203, 95,  176, 156, 169, 81,  160, 
		127, 12,  246, 111, 23,  196, 73,  236, 216, 67,  31,  45,  164, 118, 123, 183, 
		204, 187, 62,  90,  251, 96,  177, 134, 59,  82,  161, 108, 170, 85,  41,  157, 
		151, 178, 135, 144, 97,  190, 220, 252, 188, 149, 207, 205, 55,  63,  91,  209, 
		83,  57,  132, 60,  65,  162, 109, 71,  20,  42,  158, 93,  86,  242, 211, 171, 
		68,  17,  146, 217, 35,  32,  46,  137, 180, 124, 184, 38,  119, 153, 227, 165, 
		103, 74,  237, 222, 197, 49,  254, 24,  13,  99,  140, 128, 192, 247, 112, 7};

	final static int[] AlogTable = {
		1,   3,   5,   15,  17,  51,  85,  255, 26,  46,  114, 150, 161, 248, 19,  53, 
		95,  225, 56,  72,  216, 115, 149, 164, 247, 2,   6,   10,  30,  34,  102, 170, 
		229, 52,  92,  228, 55,  89,  235, 38,  106, 190, 217, 112, 144, 171, 230, 49, 
		83,  245, 4,   12,  20,  60,  68,  204, 79,  209, 104, 184, 211, 110, 178, 205, 
		76,  212, 103, 169, 224, 59,  77,  215, 98,  166, 241, 8,   24,  40,  120, 136, 
		131, 158, 185, 208, 107, 189, 220, 127, 129, 152, 179, 206, 73,  219, 118, 154, 
		181, 196, 87,  249, 16,  48,  80,  240, 11,  29,  39,  105, 187, 214, 97,  163, 
		254, 25,  43,  125, 135, 146, 173, 236, 47,  113, 147, 174, 233, 32,  96,  160, 
		251, 22,  58,  78,  210, 109, 183, 194, 93,  231, 50,  86,  250, 21,  63,  65, 
		195, 94,  226, 61,  71,  201, 64,  192, 91,  237, 44,  116, 156, 191, 218, 117, 
		159, 186, 213, 100, 172, 239, 42,  126, 130, 157, 188, 223, 122, 142, 137, 128, 
		155, 182, 193, 88,  232, 35,  101, 175, 234, 37,  111, 177, 200, 67,  197, 84, 
		252, 31,  33,  99,  165, 244, 7,   9,   27,  45,  119, 153, 176, 203, 70,  202, 
		69,  207, 74,  222, 121, 139, 134, 145, 168, 227, 62,  66,  198, 81,  243, 14, 
		18,  54,  90,  238, 41,  123, 141, 140, 143, 138, 133, 148, 167, 242, 13,  23, 
		57,  75,  221, 124, 132, 151, 162, 253, 28,  36,  108, 180, 199, 82,  246, 1};

	static byte[][] rcon = {
		{0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, (byte) 0x80, 0x1b, 0x36},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
	};

	static byte[][] st;
	static byte[][] ck;
	static ArrayList<byte[][]> roundKeys;

	public static void main(String args[]) throws IOException{
		
		String keyFile, inputFile; 
		try{
			keyFile = args[1];
			inputFile = args[2];
		} catch (Exception e){
			System.err.println("Did not input valid command!");
			System.err.println("Command format: (e/d) <keyFile> <inputFile>");
			return;
		}

		readKey(keyFile);
		expandKey();
		long startTime = System.currentTimeMillis();
		
		if ( (args[0].toLowerCase()).equals("e") ){
			System.out.println("Encrypting... ");
			encrypt(inputFile);
			long endTime = System.currentTimeMillis();
			System.out.println("done encrypting in " +  ((double)(endTime - startTime)/1000.0) + " seconds");
		} else if ((args[0].toLowerCase()).equals("d") ){
			System.out.println("Decrypting... ");
			decrypt(inputFile);
			long endTime = System.currentTimeMillis();
			System.out.println("done decrypting in " + ((double)(endTime - startTime)/1000.0) + " seconds");
		} else {
			System.err.println("You did not choose a valid option! (e or d)");
			return;
		}
	}

	public static void readKey(String keyFile) throws IOException{
		ck = new byte[4][4];
		BufferedReader br = new BufferedReader(new FileReader(keyFile));
		String line;
		line = br.readLine();
		line = line.replaceAll("\\s+","");
		for (int i=0; i<4; ++i){
			for (int j=0; j<4; ++j){
				int index = (8*i) + (2 * j);
				String hexVal = "" + line.charAt(index) + line.charAt(index+1);
				ck[j][i] = (byte) Integer.parseInt(hexVal, 16);
			}
		}
		br.close();

		roundKeys = new ArrayList<byte[][]>();
		roundKeys.add(ck);
	}

	public static void encrypt(String inputFile) throws IOException{

		PrintWriter writer = new PrintWriter(inputFile + ".enc");
		BufferedReader br = new BufferedReader(new FileReader(inputFile));
		String line;
		boolean firstline = true;

		while ((line = br.readLine()) != null){
			if (line.length() > 32){
				line = br.readLine();
				if (line == null)
					break;
			}
			
			if (!firstline) writer.println();

			readInState(line);
			printMatrix(st);

			addRoundKey(roundKeys.get(0));
			System.out.println("After addRoundKey(0):");
			printMatrix(st);

			for (int i=1; i<10; ++i){
				subBytes();
				System.out.println("After subBytes:");
				printMatrix(st);

				shiftRows();
				System.out.println("After shiftRows:");
				printMatrix(st);

				mixColumns();
				System.out.println("After mixColumn:");
				printMatrix(st);

				addRoundKey(roundKeys.get(i));
				System.out.println("After addRoundKey(" + i + "):");
				printMatrix(st);
			}
			subBytes();
			System.out.println("After subBytes:");
			printMatrix(st);

			shiftRows();
			System.out.println("After shiftRows:");
			printMatrix(st);

			addRoundKey(roundKeys.get(10));
			System.out.println("The ciphertext:");
			printMatrix(st);

			writeToFile(writer);
			firstline = false;
		}
		writer.close();
	}

	public static void decrypt(String inputFile) throws IOException{

		PrintWriter writer = new PrintWriter(inputFile + ".dec");

		BufferedReader br = new BufferedReader(new FileReader(inputFile));
		String line;
		boolean firstline = true;
		
		while ((line = br.readLine()) != null){
			if (line.length() > 32){
				line = br.readLine();
				if (line == null)
					break;
			}
			
			if (!firstline) writer.println();

			readInState(line);
			printMatrix(st);

			addRoundKey(roundKeys.get(10));
			System.out.println("After addRoundKey(10):");
			printMatrix(st);

			invSubBytes();
			System.out.println("After invSubBytes:");
			printMatrix(st);

			invShiftRows();
			System.out.println("After invShiftRows:");
			printMatrix(st);

			for (int i=9; i>0; --i){
				addRoundKey(roundKeys.get(i));
				System.out.println("After addRoundKey(" + i + "):");
				printMatrix(st);

				invMixColumns();
				System.out.println("After invMixColumn:");
				printMatrix(st);

				invSubBytes();
				System.out.println("After invSubBytes:");
				printMatrix(st);

				invShiftRows();
				System.out.println("After invShiftRows:");
				printMatrix(st);
			}

			addRoundKey(roundKeys.get(0));
			System.out.println("The decryption of the ciphertext:");
			printMatrix(st);

			writeToFile(writer);
			firstline = false;
		}
		writer.close();
	}

	private static void writeToFile(PrintWriter writer) throws FileNotFoundException{
		for (int i=0; i<st.length; ++i){
			for (int j=0; j<st[0].length; ++j){
				String yolo = Integer.toHexString(0xFF&st[j][i]);
				yolo = yolo.length() == 2 ? yolo : "0"+yolo;
				writer.print(yolo);
			}
		}
	}

	public static void expandKey(){

		for (int round=0; round<10; ++round){
			byte[][] lastKey = roundKeys.get(roundKeys.size() - 1);
			byte[][] result = new byte[4][4];
			byte[] wi4 = new byte[4];
			byte[] wi1 = new byte[4];
			byte[] currRcon = new byte[4];

			for (int i=0; i<4; ++i){
				currRcon[i] = rcon[i][round];
				wi1[i] = lastKey[i][3];
				wi4[i] = lastKey[i][0];
			}		

			//rot wi1
			byte temp = wi1[0];
			for (int i=0; i<3; ++i){
				wi1[i] = wi1[i+1];
			}
			wi1[3] = temp;

			//subBytes
			byte mask = 0xF;
			for (int i=0; i<wi1.length; ++i){
				byte index = wi1[i];
				byte x = (byte) (index>>4 & mask);
				byte y = (byte) (index & mask);
				wi1[i] = sbox[x][y];
			}

			for (int i=0; i<4; ++i){
				result[i][0] = (byte) (wi4[i] ^ wi1[i] ^ currRcon[i]);
			}

			for (int i=1; i<4; ++i){
				wi1 = getMatrixColumn(result, i-1);
				wi4 = getMatrixColumn(lastKey, i);
				for (int j=0; j<4; ++j){
					result[j][i] = (byte) (wi4[j] ^ wi1[j]);
				}
			}

			roundKeys.add(result);
		}
	}

	private static byte[] getMatrixColumn(byte[][] matrix, int column){
		byte[] result = new byte[4];
		for (int i=0; i<4; ++i){
			result[i] = matrix[i][column];
		}
		return result;
	}

	private static byte[] getMatrixRow(byte[][] matrix, int row){
		byte[] result = new byte[4];
		for (int i=0; i<4; ++i){
			result[i] = matrix[row][i];
		}
		return result;
	}

	private static void readInState(String line){
		st = new byte[4][4];
		for (int i=0; i<4; ++i){
			for (int j=0; j<4; ++j){
				int index = 8*i + 2*j;
				char one, two;
				try{
					one = line.charAt(index);
				} catch (Exception e) {
					one = '0';
				}
				try{
					two = line.charAt(index+1);
				} catch (Exception e) {
					two = '0';
				}
				String hexVal = "" + one + two;
				st[j][i] = (byte) Integer.parseInt(hexVal, 16);
			}
		}
	}

	private static void printMatrix(byte[][] matrix){
		for (int i=0; i<matrix.length; ++i){
			for (int j=0; j<matrix[0].length; ++j){
				String yolo = Integer.toHexString(0xFF&matrix[i][j]);
				yolo = yolo.length() == 2 ? yolo : "0"+yolo;
				System.out.print(yolo + " ");
			}
			System.out.println();
		}
		System.out.println();
	}	

	public static void addRoundKey(byte[][] roundKey){
		for (int i=0; i<4; ++i){
			byte[] rkColumn = getMatrixColumn(roundKey, i);
			byte[] stColumn = getMatrixColumn(st, i);
			for (int j=0; j<4; ++j){
				st[j][i] = (byte) (stColumn[j] ^ rkColumn[j]);
			}
		}
	}

	public static void subBytes(){
		byte mask = 0xF;
		for (int i=0; i<st.length; ++i){
			for (int j=0; j<st[0].length; ++j){
				byte index = st[i][j];
				byte x = (byte) (index>>4 & mask);
				byte y = (byte) (index & mask);
				st[i][j] = sbox[x][y];
			}
		}
	}

	public static void invSubBytes(){
		byte mask = 0xF;
		for (int i=0; i<st.length; ++i){
			for (int j=0; j<st[0].length; ++j){
				byte index = st[i][j];
				byte x = (byte) (index>>4 & mask);
				byte y = (byte) (index & mask);
				st[i][j] = inv_sbox[x][y];
			}
		}
	}

	public static void shiftRows(){
		for (int i=0; i<st.length; ++i){
			byte[] row = getMatrixRow(st, i);
			byte[] rotatedRow = rotateRow(row, i);
			for (int j=0; j<st[0].length; ++j){
				st[i][j] = rotatedRow[j];
			}
		}
	}

	private static byte[] rotateRow(byte[] row, int rotate){
		byte[] result = new byte[4];
		for (int i=0; i<result.length; ++i){
			int newIndex = i-rotate;
			newIndex = newIndex < 0 ? newIndex + 4 : newIndex;
			result[newIndex] = row[i];
		}
		return result;
	}

	public static void invShiftRows(){
		for (int i=0; i<st.length; ++i){
			byte[] row = getMatrixRow(st, i);
			byte[] rotatedRow = inverseRotateRow(row, i);
			for (int j=0; j<st[0].length; ++j){
				st[i][j] = rotatedRow[j];
			}
		}
	}

	private static byte[] inverseRotateRow(byte[] row, int rotate){
		byte[] result = new byte[4];
		for (int i=0; i<result.length; ++i){
			int newIndex = i+rotate;
			newIndex = newIndex > 3 ? newIndex - 4 : newIndex;
			result[newIndex] = row[i];
		}
		return result;
	}

	public static void mixColumns(){
		mixColumn(0);
		mixColumn(1);
		mixColumn(2);
		mixColumn(3);
	}

	public static void invMixColumns(){
		invMixColumn(0);
		invMixColumn(1);
		invMixColumn(2);
		invMixColumn(3);
	}

	public static void mixColumn (int c) {

		byte a[] = new byte[4];

		for (int i = 0; i < 4; i++) 
			a[i] = st[i][c];

		st[0][c] = (byte)(mul(2,a[0]) ^ a[2] ^ a[3] ^ mul(3,a[1]));
		st[1][c] = (byte)(mul(2,a[1]) ^ a[3] ^ a[0] ^ mul(3,a[2]));
		st[2][c] = (byte)(mul(2,a[2]) ^ a[0] ^ a[1] ^ mul(3,a[3]));
		st[3][c] = (byte)(mul(2,a[3]) ^ a[1] ^ a[2] ^ mul(3,a[0]));
	}

	public static void invMixColumn (int c) {
		byte a[] = new byte[4];

		for (int i = 0; i < 4; i++) 
			a[i] = st[i][c];

		st[0][c] = (byte)(mul(0xE,a[0]) ^ mul(0xB,a[1]) ^ mul(0xD, a[2]) ^ mul(0x9,a[3]));
		st[1][c] = (byte)(mul(0xE,a[1]) ^ mul(0xB,a[2]) ^ mul(0xD, a[3]) ^ mul(0x9,a[0]));
		st[2][c] = (byte)(mul(0xE,a[2]) ^ mul(0xB,a[3]) ^ mul(0xD, a[0]) ^ mul(0x9,a[1]));
		st[3][c] = (byte)(mul(0xE,a[3]) ^ mul(0xB,a[0]) ^ mul(0xD, a[1]) ^ mul(0x9,a[2]));
	}

	private static byte mul (int a, byte b) {
		int inda = (a < 0) ? (a + 256) : a;
		int indb = (b < 0) ? (b + 256) : b;

		if ( (a != 0) && (b != 0) ) {
			int index = (LogTable[inda] + LogTable[indb]);
			byte val = (byte)(AlogTable[ index % 255 ] );
			return val;
		}
		else 
			return 0;
	}
}
