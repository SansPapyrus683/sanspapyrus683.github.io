import java.io.*;
import java.math.BigInteger;
import java.util.*;

/**
 * 2020 us open gold
 * also this is slow mostly bc of the bigintegers
 * if you want like super speed, just switch to longs and do everything mod the mod idk
 */
public final class Exercise {
    public static void main(String[] args) throws IOException {
        StringTokenizer initial = new StringTokenizer(
                new BufferedReader(new FileReader("exercise.in")).readLine()
        );
        int cowNum = Integer.parseInt(initial.nextToken());
        BigInteger mod = new BigInteger(initial.nextToken());

        // the sum of all the LCMs of the prime powers that sum to i (the array index)
        BigInteger[] totalWithSum = new BigInteger[cowNum + 1];
        Arrays.fill(totalWithSum, BigInteger.ZERO);
        totalWithSum[0] = new BigInteger("1");
        for (int i = 2; i <= cowNum; i++) {
            if (!prime(i)) {
                continue;
            }

            /*
             * keep another array where we store the updates so the prime
             * powers of a single number don't go harrassing each other
             */
            BigInteger[] updatedTotal = totalWithSum.clone();
            for (int p = i; p <= cowNum; p *= i) {  // go through all prime powers
                for (int from = 0; from + p <= cowNum; from++) {
                    updatedTotal[from + p] = updatedTotal[from + p].add(
                            totalWithSum[from].multiply(new BigInteger(String.valueOf(p)))
                    );
                }
            }
            totalWithSum = updatedTotal;
        }

        BigInteger total = BigInteger.ZERO;
        for (BigInteger prod : totalWithSum) {
            total = total.add(prod);
        }
        total = total.mod(mod);

        PrintWriter written = new PrintWriter("exercise.out");
        written.println(total);
        written.close();
    }

    // sauce: https://www.geeksforgeeks.org/primality-test-set-1-introduction-and-school-method
    private static boolean prime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;

        for (int i = 5; i * i <= n; i = i + 6)
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        return true;
    }
}
