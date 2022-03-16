import java.util.Scanner;

public class Hanoi {
    public static void main(String[] args) {
        // get the # of disks, there's only gonna be 3 places to put them
        int diskNum = new Scanner(System.in).nextInt();

        for (char[] step : hanoi(diskNum)) {
            System.out.print(step[0]);
            System.out.print(" -> ");
            System.out.println(step[1]);
        }
    }

    private static char[][] hanoi(int diskNum) {
        /*
         * https://en.wikipedia.org/wiki/Tower_of_Hanoi
         * the min # of moves to complete the tower is gonna be 2^diskNum - 1
         */
        char[][] sol = new char[(1 << diskNum) - 1][2];
        // the middle move is always gonna be this
        sol[sol.length / 2] = new char[] {'A', 'C'};

        if (diskNum == 1) {
            return sol;
        }

        char[][] prev = hanoi(diskNum - 1);
        for (int i = 0; i < prev.length; i++) {
            char[] prevStep = prev[i];
            int ind2 = sol.length / 2 + i + 1;
            if (prevStep[0] == 'A') {
                sol[i] = new char[] {'A', ternary(prevStep[1] == 'B', 'C', 'B')};
                sol[ind2] = new char[] {'B', ternary(prevStep[1] == 'C', 'C', 'A')};
            } else if (prevStep[0] == 'B') {
                sol[i] = new char[] {'C', ternary(prevStep[1] == 'A', 'A', 'B')};
                sol[ind2] = new char[] {'A', ternary(prevStep[1] == 'A', 'B', 'C')};
            } else if (prevStep[0] == 'C') {
                sol[i] = new char[] {'B', ternary(prevStep[1] == 'B', 'C', 'A')};
                sol[ind2] = new char[] {'C', ternary(prevStep[1] == 'A', 'B', 'A')};
            }
        }
        return sol;
    }

    // i'd use the built-in ternary but we can't use anything we haven't learned
    private static char ternary(boolean cond, char yes, char no) {
        if (cond) {
            return yes;
        }
        return no;
    }
}
