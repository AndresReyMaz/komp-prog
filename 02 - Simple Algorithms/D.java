// Status: Accepted
import java.math.*;
import java.util.Scanner;

public class D{
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		BigInteger f,lim;
		int t = sc.nextInt();
		for(int TC = 1; TC <= t; TC++){
			f = sc.nextBigInteger();
			BigInteger lo = BigInteger.ZERO,
			     hi =new BigInteger("1000000000000000");
			while(lo.compareTo(hi)<0){
				BigInteger m = (lo.add(hi)).divide(new BigInteger("2"));
				if(f.compareTo((m.multiply((m.add(BigInteger.ONE)).multiply((m.multiply(new BigInteger("2"))).add(BigInteger.ONE)))).divide(new BigInteger("6"))) < 0)
					hi = m;
				else
					lo = m.add(BigInteger.ONE);
			}
			System.out.println("Case #" + TC + ": " + (hi.add(BigInteger.ONE)));
		}

	}
}
