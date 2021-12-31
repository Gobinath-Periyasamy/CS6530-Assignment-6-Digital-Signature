#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>

// Random number
signed long long int randoms(signed long long int upper, signed long long int lower)

{
    signed long long int num = ( rand()%
                (upper - lower +1)) + lower;
    return num;

}

//Find whether given number is prime or not

signed long long int prime(signed long long int n)
{
    signed long long int i, flag = 0;
    for (i=2;i<n/2; ++i)
    {
        //condition for non-prime
        if (n % i == 0)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

// get random and prime
signed long long int prime_ran(signed long long int upper,signed long long int lower)
{
    signed long long int p;
    signed long long int flag = 1;
    while(flag)
    {
        p = randoms(upper, lower);
        flag = prime(p);
    }
    return p;
}

// Euclid Algorithm
signed long long int Euc_gcd(signed long long int a, signed long long int b)
{
    if (a == 0)
        return b;
    return Euc_gcd(b % a, a);
}

//Modular Exponentiation
signed long long int power(signed long long int  x, signed long long int y, signed long long int p)
{
    signed long long int res = 1;     // Initialize result

    x = x % p; // Update x if it is more than or
                // equal to p

    if (x == 0) return 0; // In case x is divisible by p;

    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;

        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;
    }
    return res;
}

// Exponent
signed long long int Exponent(signed long long int bit, signed long long int n, signed long long int* y, signed long long int* a)
{
    if (bit == 1) {
        *y = (*y * (*a)) % n;
    }
 
    *a = (*a) * (*a) % n;
}
 

// Finding t_value
signed long long int t_value(signed long long int a, signed long long int m, signed long long int n)
{
    signed long long int r;
    signed long long int y = 1;
 
    while (m > 0)
    {
        r = m % 2;
        Exponent(r, n, &y, &a);
        m = m / 2;
    }
 
    return y;
}


// Finding Primitive Root
signed long long int PrimitiveRoot(signed long long int p)
{
    signed long long int flag;
    for (signed long long int a = 2; a < p; a++)
    {
        flag = 1;
        for (signed long long int i = 1; i < p; i++)
        {
            if (t_value(a, i, p) == 1 && i < p - 1) {
                flag = 0;
            }
            else if (flag && t_value(a, i, p) == 1 && i == p - 1) {
                return a;
            }
        }
    }
}




// Choosing x
signed long long int x_value(signed long long int p)

{
        signed long long int x_arr[sizeof(p)];

        signed long long int z_len;
        z_len = p - 2;
//                                            printf("z_len : %d",z_len);
        signed long long int arr[z_len];
        signed long long int size, i, toSearch = 3, found = 0;

        for(i=2; i<z_len; i++)
        {
            signed long long int z_val = i % p;
            // printf("Zp values : %d ", z_val);
            arr[i] = z_val;
        }

    while ((found == 0))
    {

        toSearch = randoms(p,2);


        /* Assume that element does not exists in array */
        found = 0; 
        
        for(i=0; i<z_len; i++)
        {
            /* 
            * If element is found in array then raise found flag
            * and terminate from loop.
            */
            if(arr[i] == toSearch)
            {
                found = 1;
                break;
            }
        }
    }

    return toSearch;



}

signed long long int modInverse(signed long long int e, signed long long int phi)
{
    signed long long int i,Temp;
    //printf("%d",phi);
    for(i = 0; i<phi; i++)
    {
        long long mul = e*i;
        Temp = mul%phi;
        //printf("e : %d \t i: %d \t phi = %d \t Temp : %d \n", e, i, phi, Temp);
        if(Temp == 1)
        {
            //printf("%d",i);
            return i;
        }
    }
}

//Driver code

int main()

{

    // Key Generation :

    signed long long int q,a,xa,ya;

    signed long long int upper = 100000;
    signed long long int lower = (upper-1000);

    srand (time(0));

    signed long long int  s1 = 0,s2 = 0;
    signed long long int m, K, K_inv, q_1;

    printf("*******************************************************************************************************\n");

    printf("\n**********************************\n");
    printf("* Digital Signature Verification *\n");
    printf("**********************************\n\n");


    printf("Name    : GOBINATH             \n");
    printf("Roll No : CS21M501             \n\n");
    printf("*******************************************************************************************************\n\n");
    while (s1 == 0 || s2 == 0)
    {
    // Choose Random Prime P
        q = prime_ran(upper,lower);
        q_1 = q - 1;
        
        // Finding Primitive Root of P:
        a = PrimitiveRoot(q);

        xa = randoms(q-1,1);

        ya = power(a,xa,q);

         m = randoms(q-1, q-1000);
        K = randoms(q-1,1);

        s1 = power(a,K,q);
        
        K_inv = modInverse(K, q-1);

        s2 = (K_inv * (m - (xa*s1)));
        // printf("s2 : %d\n",s2);


        s2 = s2 % q_1;
        if (s2 < 0)
        s2 = s2 + q_1;
    }


        printf("Private key Xa is : %d\n", xa);
        
        printf("Public key q : %d, ", q);
        printf("a : %d, ", a);
        printf("Ya : %d, ", ya);
        printf("Hash Message hm : %d\n",m);
    printf("s1 : %d\n", s1);
    printf("s2 : %d\n", s2);

    char user_input = 'y';

    while (user_input == 'Y' || user_input == 'y')
    {
            printf("Please Enter the Signatures (Printed above) \n");
            printf("\tEnter the s1 : ");
            scanf("%d", &s1);
            printf("\tEnter the s2 : ");
            scanf("%d", &s2);

            signed long long int v1 = power(a,m,q);

            signed long long int v2_pre = power(ya,s1,q);
            signed long long int v2_suf = power(s1,s2,q);


            signed long long int v2 = (v2_pre * v2_suf) % q;

            printf("V1 : %d\n", v1);
            printf("v2 : %d\n", v2);



    printf("*******************************************************************************************************\n");

            if (v1 == v2)
            {
                printf("*  V1 and V2 for given signatures are MATCHing. Message sent by the correct Sender \n");
            }
            else
            {
                printf("*  V1 and V2 for given signatures are NOT matching, Message NOT sent by  the correct Sender \n");
            }

    printf("*******************************************************************************************************\n");

            printf("Want to verify for other Signatures ? \n");
            printf("(Please give your input as (Y or y)) : ");
            scanf(" %c", &user_input);
            printf("user_input : %c \n", user_input);

    }
        system("PAUSE");
    return 0;
}
