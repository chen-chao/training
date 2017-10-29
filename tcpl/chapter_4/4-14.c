/* The C Programming Language, 2nd Edition, by Kernighan and Ritchie,
 * Exercise 4.14 on page 91. Define a macro swap(t,x,y) that
 * interchanges two arguments of type t . (Block structure will
 * help.) */


/* menonsahab's comment on the answer website: Lars's solution: The
solution seems nice. The problem revolves around the temporary
variable.Specifically there are two problems: 1) What if the name that
we choose for the temporary variable is already being used.  2)
Assuming that we select a fixed name for the temporary variable, the
swap() will work fine for the first time.  But when the next swap is
encountered with a different data type, it will show an error because
the code will attempt to change the storage class of a variable that
has already been defined.

Also let me just add that I'm not a big fan of the do-while loop. You
can always use '\' to have a multi line block.

Lars has made a great attempt to solve the above mentioned problems to
a great extent. But his code breaks at a very simple input such as:
swap(double, 53.24, 78.99) This is because you can't append a floating
point number in the name of a variable.  I have a simple workaround
for this. Avoid using a temporary variable.

#define swap(t, x, y) \	
	x = x + y; \ 	
	y = x - y; \	
	x = x - y; 

 The above code solves all problems related to the creation of the
temporary variable.  It works for chars, ints, floats and doubles. In
fact the data type does not need to be passed as an argument.  The
only drawback of this function is that it won't work for pointers. */


/* However, the 2) is not right. Because the fixed name is a auto
 * variable in the do-while block(that's why a block is
 * needed). Solution provided by menonsahab is more smart, but there's
 * no efficiency advantage.*/


#include <stdio.h>

#define swap(t, x, y) do {t _MACRO_TMP; _MACRO_TMP=(x); (x)=(y); (y)=_MACRO_TMP; } while (0)


int main(){
        int x = 10, y = 100;

        printf("Before swap: x = %d, y = %d\n", x, y);
        swap(int, x, y);
        printf("After swap: x = %d, y = %d\n", x, y);

        char a = 'a', b = 'b';
        printf("Before swap: a = %c, b = %c\n", a, b);
        swap(char, a, b);
        printf("After swap: a = %c, b = %c\n", a, b);

        double c = 1.2, d = 100.9;
        printf("Before swap: c = %.8g, d = %.8g\n", c, d);
        swap(double, c, d);
        printf("After swap: c = %.8g, d = %.8g\n", c, d);

        return 0;
}
