// Status: Accepted
import java.util.Scanner;
import java.math.BigInteger;

class A{
	static BigInteger[] mem = new BigInteger[10009];

	static BigInteger lucas(int n){
		if(n == 0)
			return new BigInteger("2");
		if(n == 1)
			return BigInteger.ONE;
		if(mem[n] != BigInteger.ZERO)
			return mem[n];
		return mem[n] = lucas(n-2).add(lucas(n-1));
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		for(int j = 0; j < 10009; j++){
			mem[j] = BigInteger.ZERO;
		}
		while(sc.hasNext()){
			int x = sc.nextInt();
			System.out.println(lucas(x));
		}
	}
}
