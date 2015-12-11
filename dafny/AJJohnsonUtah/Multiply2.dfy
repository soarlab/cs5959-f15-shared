
method Multiply2(n:int) returns (r:int)
 requires 0 <= n;
 ensures r == 2*n;
{
 r := 0;
 var i:int := 0;
 while (i < n)
   invariant r == 2*i;
   invariant i <= n;
 {
   r := r + 2;
   i := i + 1;
 }
}