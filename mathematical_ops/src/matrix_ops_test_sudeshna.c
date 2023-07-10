#include<stdio.h>
#include <math.h>
#include <stdlib.h>

double tangent(double argument)
{
    if ( ((int)(argument/(M_PI / 2.0)) % 2) != 0)
    {
        printf("\nArgument to tangent is odd multiple of PI/2!!!!\n");
        printf("Accuracy of tangent is decreased to float!!\n");
        argument -= 1E-7;
        return (double)tanf((float)argument);
    } 
    return tan(argument);
}
double arcTangent2(double num, double den)
{
    if (fabs(den) < 1E-15)
    {
        printf("denominator for atan2 is less than 1E-15!!!!\n");
        den = 1E-15;
        return (double)atan2f((float)num, (float)den);
    }
    return atan2(num, den);
}
double arcCosine(double argument)
{
    if (argument > 1.0)
    {
        printf("Argument of acos() is greater than 1!!!!\n");
        double error = (argument - 1.0);
        if (error < 1E-7f)
        {
            argument = 1.0;
            printf("Error handled accuracy reduced to float\n");
            return (float)acosf((float)argument);
        }
        else {
            printf("Argument error cannot be handled!!\n");
            exit(1);
        }
    }
    else if (argument < -1.0)
    {
        printf("Argument of acos() is less than -1!!!!\n");
        double error = (argument + 1.0);
        if (error > -1E-7f)
        {
            argument = -1.0;
            printf("Error handled accuracy reduced to float\n");
            return (float)acosf((float)argument);
        }
        else {
            printf("Argument error cannot be handled!!\n");
            exit(1);
        }
    }
    else{
        return acos(argument);
    }
}
double arcSine(double argument)
{
    if (argument > 1.0)
    {
        printf("Argument of asin() is greater than 1!!!!\n");
        double error = (argument - 1.0);
        if (error < 1E-7f)
        {
            argument = 1.0;
            printf("Error handled accuracy reduced to float\n");
            return (float)asinf((float)argument);
        }
        else {
            printf("Argument error cannot be handled!!\n");
            exit(1);
        }
    }
    else if (argument < -1.0)
    {
        printf("Argument of asin() is less than -1!!!!\n");
        double error = (argument + 1.0);
        if (error > -1E-7f)
        {
            argument = -1.0;
            printf("Error handled accuracy reduced to float\n");
            return (float)asinf((float)argument);
        }
        else {
            printf("Argument error cannot be handled!!\n");
            exit(1);
        }
    }
    else{
        return asin(argument);
    }
}
void MatrixTranspose_General(double *M, int numRows, int numCols)
{
    double temp=0;
    for (int i=0; i<numRows; i++)
    {
        for (int j=i; j<numCols; j++)
        {
            if (i!=j)
            {
                temp = M[i*numCols + j];
                M[i*numCols + j] = M[j*numCols + i];
                M[j*numCols + i] = temp;
            }
        }
    }
    // fflush(stdin);
}
int main()
{
    double arr[2][3]= {{1,2,3},{4,5,6}};
    
    double * M = arr;
    MatrixTranspose_General(M,2,3);
    // for(int i = 0;i<2;i++)
    // {
    //     for(int j =0;j<3;j++)
    //     {
    //         printf("%f ",arr[i][j]);
    //     }
    //     printf("\n");
    // }
    // double temp=0;
    // for (int i=0; i<2; i++)
    // {
    //     for (int j=i; j<3; j++)
    //     {
    //         if (i!=j)
    //         {
    //             temp = M[i*3 + j];
    //             M[i*3 + j] = M[j*3 + i];
    //             M[j*3 + i] = temp;
    //         }
    //     }
    // }
    // for(int i = 0;i<3;i++)
    // {
    //     for(int j =0;j<2;j++)
    //     {
    //         printf("%f ",arr[i][j]);
    //     }
    //     printf("\n");
    // }
    printf("hello world"); fflush(stdout);
    /* function tangent() done
    printf("value of tan(0) %lf\n",tangent(0));
    printf("value of tan(pi/6) %lf\n",tangent(M_PI/6));
    printf("value of tan(pi/4) %lf\n",tangent(M_PI/4));
    printf("value of tan(pi/3) %lf\n",tangent(M_PI/3));
    printf("value of tan(pi/2) %lf\n",tangent(M_PI/2));
    */
    /*function arcTangent() done
    printf("inverse value of tan(0/1) %lf\n", arcTangent2(0,1));
    printf("inverse value of tan(0/0) %lf\n", arcTangent2(0,0));
    printf("inverse value of tan(1/0) %lf\n", arcTangent2(1,0));
    printf("inverse value of tan(1/root) %lf\n", arcTangent2(1,sqrt(3)));
    printf("inverse value of tan(root3/1) %lf\n", arcTangent2(sqrt(3),1));
    */
   /*function arcCosine() not handling values >1 & <-1, program is exiting
   printf("the value of cos_inverse(-1) %lf\n",arcCosine(-1));
   printf("the value of cos_inverse(-1.1) %lf\n",arcCosine(-1.1));
   printf("hello world");
   printf("the value of cos_inverse(2) %lf\n",arcCosine(2.0));
   */
    // double arr[10] = {-1, }
    // printf("the value of cos_inverse(-1) %lf\n",arcSine(-1));
    // printf("the value of cos_inverse(1) %lf\n",arcCosine(1));
    // printf("the value of cos_inverse() %lf\n",arcCosine(-1.1)); 
    return(0);


}