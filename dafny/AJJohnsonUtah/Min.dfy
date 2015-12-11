method Min(a:int, b:int, c:int) returns (m:int)
  ensures (a >= 0 && m <= a) || (a < 0 && m <= -1*a);
  ensures (b >= 0 && m <= b) || (b < 0 && m <= -1*b);
  ensures (c >= 0 && m <= c) || (c < 0 && m <= -1*c);
  ensures m >= 0;
{
  var a_abs:int := a;
  var b_abs:int := b;
  var c_abs:int := c;
  
  if(a_abs < 0)
  {
    a_abs := a_abs * -1;
  }
  if(b_abs < 0)
  {
    b_abs := b_abs * -1;
  }
  if(c_abs < 0)
  {
    c_abs := c_abs * -1;
  }
  if(a_abs <= b_abs && a_abs <= c_abs)
  {
    m := a_abs;
  }
  else if (b_abs <= a_abs && b_abs <= c_abs)
  {
    m := b_abs;
  }
  else if (c_abs <= a_abs && c_abs <= b_abs)
  {
    m := c_abs;
  }    
}