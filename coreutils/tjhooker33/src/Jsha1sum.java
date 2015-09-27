/*******************************************************************************************
 * AUTHOR :     Taylor Wilson
 * UID :        U0323893
 *
 * DATE :       September 26, 2015
 *
 * PURPOSE :    Written for CS 5959 Writing Solid Code, Fall 2015
 *              University of Utah
 */

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.io.*;

public class Jsha1sum {

  private static BufferedInputStream BIS;

  public static byte[] readFile(String filePath, int size) throws IOException {
    byte[] buffer = new byte[size];
    BIS = new BufferedInputStream(new FileInputStream(filePath));
    BIS.read(buffer);
    return buffer;
  }

  public static void main(String[] args) throws NoSuchAlgorithmException, IOException {
    MessageDigest sha = MessageDigest.getInstance("SHA-1");
    String filePath = args[0];
    sha.update(readFile(filePath, Integer.parseInt(args[1])));
    System.out.println(getHexString(sha.digest()) + "  " + filePath);
  }

  /**
   * CITE: This function was obtain from an online resource. The author of the code is unknown.
   *       I made minor modifications to the code.
   * 
   *       http://snipplr.com/view/18368/
   *       
   *       This function returns a Hex formatted String produced from the byte array.
   *       
   * @param byteArray : a byte array to format into hex
   * @return String   : a hex formatted string
   */
  public static String getHexString(byte[] byteArray) {
    StringBuilder builder = new StringBuilder();
    for (int i = 0; i < byteArray.length; i++) {
      builder.append(Integer.toString((byteArray[i] & 0xff) + 0x100, 16).substring(1));
    }

    return builder.toString();
  }
}
