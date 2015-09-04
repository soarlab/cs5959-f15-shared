#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<inttypes.h>

typedef enum { scalene, isosceles, equilateral } side;
typedef enum { acute, obtuse, right } angle;

side getSideType(int64_t aSquared, int64_t bSquared, int64_t cSquared);
angle getAngleType(int64_t aSquared, int64_t bSquared, int64_t cSquared);
int64_t absoluteValue(int64_t input);
int64_t S64(const char *s);

int main(void)
{
	static const int64_t MAX_VALUE=1073741823;
	static const int64_t MIN_VALUE=-1073741823;
	int64_t x1,x2,x3,y1,y2,y3;
	int64_t aSquared, bSquared, cSquared;
	int64_t deltaX1, deltaX2, deltaY1, deltaY2;
	int64_t swap;
	int64_t coords[6];
	angle angleType;
	side sideType;
	char buffer[74];
	
	fgets(buffer, sizeof(buffer), stdin);
	
	char* token = strtok(buffer, " ");
	int x=0;
	while (token) {
		//Remove newline character from fgets (stupid fgets)
		size_t ln = strlen(token) - 1;
		if (token[ln] == '\n')token[ln] = '\0';
		//Convert token into 64bit int and place into array
		coords[x] = S64(token);
		//Check if overflow or higher/lower than allowed
		if(coords[x]<MIN_VALUE || coords[x]>MAX_VALUE )
		{
			printf("error\n");
			return 0;
		}
		token = strtok(NULL, " ");
		x++;
	}
	if(x!=6)
	{
		printf("error\n");
		return 0;
	}
	//After parsing args place into variables for readability
	x1=coords[0];
	y1=coords[1];
	x2=coords[2];
	y2=coords[3];
	x3=coords[4];
	y3=coords[5];
	
	deltaX1=x2-x1;
	deltaX2=x3-x1;
	deltaY1=y2-y1;
	deltaY2=y3-y1;
	//Check if the signs match
	if((deltaX1<0 && deltaX2<0) || (deltaX1>0 && deltaX2>0))
	{
		if((deltaY1>0 && deltaY1>0) || (deltaY1<0 && deltaY1<0))
		{
			deltaX1=absoluteValue(x2-x1);
			deltaX2=absoluteValue(x3-x1);
			deltaY1=absoluteValue(y2-y1);
			deltaY2=absoluteValue(y3-y1);
			if(deltaX1*deltaY2==deltaX2*deltaY1)
			{
				//Not A Triangle
				printf("not a triangle\n");
				return 0;
			}
		}
	}
	else 
	{
		if((deltaY1>0 && deltaY1<0) || (deltaY1<0 && deltaY1>0))
		{
			deltaX1=absoluteValue(x2-x1);
			deltaX2=absoluteValue(x3-x1);
			deltaY1=absoluteValue(y2-y1);
			deltaY2=absoluteValue(y3-y1);
			if(deltaX1*deltaY2==deltaX2*deltaY1)
			{
				//Not A Triangle
				printf("not a triangle\n");
				return 0;
			}
		}
	}
	
	if((x1==x2 && y1==y2) || (x1==x3 && y1==y3) || (x3==x2 && y3==y2))
	{
		//Not A Triangle
		printf("not a triangle\n");
		return 0;
	}
	

	
	aSquared=((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	bSquared=((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
	cSquared=((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
	sideType=getSideType(aSquared, bSquared, cSquared);
	
	if(aSquared>=bSquared && aSquared>=cSquared)
	{
		swap=cSquared;
		cSquared=aSquared;
		aSquared=swap;
	}
	else if(bSquared>=aSquared && bSquared>=cSquared)
	{
		swap=cSquared;
		cSquared=bSquared;
		bSquared=swap;
	}
	angleType=getAngleType(aSquared, bSquared, cSquared);
	
	//Check return and print accordingly (I didn't want to print inside the function)
	if(sideType==scalene)
	{
		printf("scalene ");
	}
	else if(sideType==isosceles)
	{
		printf("isosceles ");
	}
	else
	{
		//There is a case here despite the fact that 
		//this should not be mathematically possible given integer coordinates.
		printf("equilateral ");
	}
	
	if(angleType==acute)
	{
		printf("acute\n");
	}
	else if(angleType==obtuse)
	{
		printf("obtuse\n");
	}
	else
	{
		printf("right\n");
	}
	return 0;
}

//Gets the absolute value of the input without other libraries
//Adapted for 64bit from https://graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
int64_t absoluteValue(int64_t input)
{
	int64_t const ABSValueMask =  input >> sizeof(int64_t) * 8 - 1;
	return (input + ABSValueMask) ^ ABSValueMask;
}

side getSideType(int64_t aSquared, int64_t bSquared, int64_t cSquared)
{
	if(aSquared==bSquared && bSquared==cSquared)
	{
		//There is a case here despite the fact that 
		//this should not be mathematically possible given integer coordinates.
		return equilateral;
	}
	else if(aSquared==bSquared || cSquared==bSquared || aSquared==cSquared)
	{
		return isosceles;
	}
	else
	{
		return scalene;
	}
}

angle getAngleType(int64_t aSquared, int64_t bSquared, int64_t cSquared)
{
	if((aSquared+bSquared)==cSquared)
	{
		return right;
	}
	else if((aSquared+bSquared)>cSquared)
	{
		return acute;
	}
	else
	{
		return obtuse;
	}
}

//adapted from https://stackoverflow.com/questions/17002969/how-to-convert-string-to-int64-t
int64_t S64(const char *s) {
  int64_t i;
  char c =0;
  int scanned = sscanf(s, "%" SCNd64 "%c" , &i, &c);
  if (scanned == 1 ) return i;
  //return max int if there are more or less arguments parsed than expected.
  //This works because INT64_MAX is also considered an error condition which we handle the same.
  return INT64_MAX;  
}