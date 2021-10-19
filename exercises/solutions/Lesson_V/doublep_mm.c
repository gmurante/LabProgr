int** matMult(int **a, int num_rows_a, int num_cols_a, int** b, int num_rows_b, int num_cols_b){

    int **c;

    c  = (int**)malloc(sizeof(int*)*num_rows_a);

    for(i=0;i<num_rows_a;i++)
         c[i]=malloc(sizeof(int)*num_cols_b);  


    for (int i = 0; i < num_rows_a; i++) {
        for (int j = 0; j < num_cols_b; j++) {
            int sum = 0;
            for (int k = 0; k < num_cols_a; k++) {

                c[i][j] = a[i][k] * b[k][j] + sum;
                sum = c[i][j]; //so that previous answer gets stored 
            }
        }

    }
    return c;
}

