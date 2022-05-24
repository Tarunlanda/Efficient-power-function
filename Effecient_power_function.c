#include<stdio.h>//returning can be double if power is negative
/*BT20CSE074_CPL_Assignment_1*/
#include<math.h>//for using fabs 
#define FTL_EPSILON 1.1920920E-07F//The least significant positive value of the float //such that 1+FTL_EPSILON=1 approximately
//Assumtion : The value of the x^y is assumed to be real value and the value of x^y is in the limit of double data type
double int_power(int x,int y)//function call for x,y both are integers
{
    double product,pseq;//we used double because there is possibility of -ve power
	int n=y;
	product=1;
	pseq=x;//product sequence
	if(n<0)
	{
	    n=n*-1;
	}
	while(n>0)
	{
		if(n%2==1)//when n is odd then we are multiplying with 
		{
			product=product*pseq;
		}
		n=n/2;
		pseq=pseq*pseq;
	}
	if(y<0)//power negative case
	{
	    product=1/product;
	}
    return product;//returning the power
}
/*The expansion of the logx are 
logx= (x-1) - (1/2)(x-1)^2 + (1/3)(x-1)^3.......
logx=2*(arctan(x-1/x+1)=2( (x-1/x+1) + (1/3)(x-1/x+1)^3 + (1/5)(x-1/x+1)^5 + ......)
so we convert x^y = e^(ln(x^y))=e^(yln(x)) */
double logfn(double p)//function for calculating log value
{
	double term=(p-1)/(p+1),sum=0,pt;
	pt=term*term;
	int i=0;
	while(fabs(term) >= FTL_EPSILON)//until term is greater than the significant float value the loop should continue
	{
		sum=sum+term;
		i++;
		term=(term*pt*(2*i-1))/(2*i+1);//new term
	}
	sum=2*sum;
	return sum;
}
/*e^x expansion = 1 + x/1! + x^2/2! + x^3/3! + .......
here in place of x we keep yln(x) */
double real_power(int x,double y)//function call for x,y both are integers
{
    double n=y,term=1.0,sum=0,p=logfn(x);
    p= y*p;//part of value that needed to be multiplied to new term
    int i=0;
	while(fabs(term) >= FTL_EPSILON)//until term is greater than the significant float value the loop should continue
	{
		sum=sum+term;
		i++;
		term=term*(p/i);//new term
	}
    return sum;
}
//given base is always an Integer
int main()
{
    printf("Enter the Input 1 if exponent is an Integer. \n Enter the Input 2 if exponent is real\n Enter the number= ");
    int select;//selecting exponent as integer or real
    scanf("%d",&select);
    while(select!=1&&select!=2)
    {
        printf("Please enter valid number only\nEnter the Input 1 if exponent is an Integer\nEnter the Input 2 if exponent is real\nEnter the number= ");
        scanf("%d",&select);//Input taking 1/2 for exponent as integer or real
    }
    if(select==1)
    {
        int x,y;
        printf("Enter the integer base value to find power = ");
	    scanf("%d",&x);//given base is always an Integer
	    printf("Enter the integer exponent value to find power = ");
	    scanf("%d",&y);//Exponent is an Integer
        if(x==0 && y<0)//0 power negative case
        {
            printf("Negative power of zero cannot be defined\n");
        }
        else if(x==0&&y==0)//0 power 0 case
        {
            double value=1;
            printf("The value is %lf\n",value);
        }
        else if(y==1)
        {
            double value=x;
            printf("The value is %d\n",value);
        }
        else
        {
            double value=int_power(x,y);
            printf("The value is %lf\n",value);
        }
    }
    else if(select==2)
    {
        int x;
        double y;
        printf("Enter the Integer base value to find power = ");
	    scanf("%d",&x);//given base is always an Integer
	    printf("Enter the exponent value to find power = ");
	    scanf("%lf",&y);//exponent is a real number
        if(x==0&&y<0)//negative power's of 0
        {
            printf("Negative power of zero cannot be defined\n");
        }
        else if(y==1)
        {
            double value=x;
            printf("The value is %lf\n",value);
        }
        else if(x==0&&y==0)//0 power 0 case
        {
            double value=1;
            printf("The value is %lf\n",value);
        }
        else if(x==0&&y>0)//positive powers of 0
        {
            double value=0.0;
            printf("The value is %lf\n",value);
        }
        else if(x<0)//if base is negative and power is real we get imaginary numbers
        {
            printf("Please enter properly because fractional powers of the negative numbers are not real");
        }
        else
        {
            double value=real_power(x,y);
            printf("The value is %lf\n",value);
        }
    }
}
