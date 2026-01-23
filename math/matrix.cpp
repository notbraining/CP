struct Matrix{
    int a[100][100];
    Matrix(){
        memset(a, 0, sizeof a);
    }
    void I(){
        for(int i = 0; i < 100; ++i){
            for(int j = 0; j < 100; ++j){
                a[i][j] = (i == j ? 1 : 0);
            }
        }
    }
    Matrix operator * (const Matrix& other){
        Matrix product;
        for(int i = 0; i < 100; ++i){
            for(int j = 0; j < 100; ++j){
                for(int k = 0; k < 100; ++k){
                    product.a[j][k] += a[j][i] * other.a[i][k];
                    product.a[j][k] %= MOD;
                }
            }
        }
        return product;
    }
};
