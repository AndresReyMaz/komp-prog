// Status: Accepted
import java.math.*;
import java.util.Arrays;
import java.util.Scanner;

public class PS4D{
	public static boolean valid(int[][] inc,int a, int b){
		return (inc[a][b] == 0) ? true : false;
	}
	public static void main(String[] args){
		Scanner sc = new Scanner(System.in);
		
		int r = sc.nextInt();
		int s = sc.nextInt();
		int m = sc.nextInt();
		int d = sc.nextInt();
		int n = sc.nextInt();
		// Reading the ingredients
		int ings[] = new int[r+1];
		for(int i = 1; i <= r; i++)
			ings[i] = sc.nextInt();
		// Creating the matrices
		int dishes[][] = new int[77][22];
		int inc[][] = new int[77][77];
		for(int i = 0; i < 77; i++){
			for(int j = 0; j < 77; j++)
				inc[i][j] = 0;
		}
		// Reading all the dishes
		int t = s+d+m;
		for(int i = 1; i <= t; i++){
			dishes[i][0] = sc.nextInt();
			int tmp[] = new int[dishes[i][0]+1];
			for(int j = 1; j <= dishes[i][0]; j++){
				tmp[j] = sc.nextInt();
			}
			Arrays.sort(tmp);
			for(int j = 1; j <= dishes[i][0]; j++){
				dishes[i][j] = tmp[j];
			}
		}
		/*
		// DEBUG: Printing out dishes
		for(int i = 1; i <= t; i++){
			System.out.print(dishes[i][0]);
			for(int j = 1; j<= dishes[i][0];j++){
				System.out.print(" "+dishes[i][j]);
			}
			System.out.println();
		}*/

		// Reading the incompatible pairs of dishes
		for(int i = 1; i <= n; i++){
			int a = sc.nextInt();
			int b = sc.nextInt();
			int tmp = a;
			a = Math.min(a,b);
			b = Math.max(tmp,b);
			inc[a][0]++; // Keeps the number of incompatibilities for that dish so far
			inc[a][b] = 1;
		}
		/*
		// DEBUG: Printing out incompatible pairs
		for(int i = 1; i <= t; i++){
			for(int j = 0; j <= t; j++){
				System.out.print(inc[i][j]+" ");
			}
			System.out.println();
		}*/

		// The meat of it:
		BigInteger cnt = BigInteger.ZERO;
		BigInteger lim = new BigInteger("1000000000000000000");
		for(int i = 1; i <= s; i++){
			for(int j = s+1; j <= s+m; j++){
				if(valid(inc,i,j)){
					for(int k = s+m+1; k <= t; k++){
						if(valid(inc,i,k) && valid(inc,j,k)){
							boolean there[] = new boolean[r+1];
							for(int sing = 1; sing <= dishes[i][0]; sing++){
								there[dishes[i][sing]] = true;
							}
							for(int ming = 1; ming <= dishes[j][0]; ming++){
								there[dishes[j][ming]] = true;
							}
							for(int ding = 1; ding <= dishes[k][0]; ding++){
								there[dishes[k][ding]] = true;
							}
							BigInteger mul = BigInteger.ONE;
							for(int ing = 1; ing <= r; ing++){
								if(there[ing]){
									mul = mul.multiply(BigInteger.valueOf(ings[ing]));
								}
							}
							cnt = cnt.add(mul);
							if(cnt.compareTo(lim) > 0){
								System.out.println("too many");
								System.exit(0);
							}
						}
					}
				}
			}
		}
		if(cnt.compareTo(lim) > 0){
			System.out.println("too many");
			System.exit(0);
		}
		System.out.println(cnt);
	}
}
