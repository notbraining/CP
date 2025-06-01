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
