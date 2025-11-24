int fastpow(int base, int power){
    if(power == 0)
        return 1;
    if(power == 1)
        return base;
    int f = (fastpow(base, power / 2) % MOD);
    if(power % 2 == 0){
        //return (fastpow((base*base)%MOD,power/2)%MOD);
        return (f) * (f) % MOD % MOD;
    } else{
        //return (fastpow((base*base)%MOD, power/2)*base)%MOD;
        return (f) * (f) % MOD * base % MOD;
    }
}
	choose[0][0] = 1;
	for (i = 1; i <= n / 2; ++i) {
		choose[i][0] = 1;
		for (int j = 1; j <= i; ++j)
			choose[i][j] = choose[i - 1][j]+choose[i - 1][j - 1]);
	}
