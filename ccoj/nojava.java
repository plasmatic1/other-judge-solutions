public class Remove {
    public static void main(String[] args) throws Exception {
        char[] buf = new char[110];
        int ptr = 0;
        for (; ptr == 0 || buf[ptr - 1] != '\n'; buf[ptr++] = (char) System.in.read());
        for (int i = 0; i < ptr; i++) {
            if ((buf[i] | 32) == 'j' && (buf[i + 1] | 32) == 'a' && (buf[i + 2] | 32) == 'v' && (buf[i + 3] | 32) == 'a') i += 3;
            else System.out.print(buf[i]);
        }
    }
}
