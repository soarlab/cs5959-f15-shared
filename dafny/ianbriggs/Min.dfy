method Min(a:int, b:int, c:int) returns (m:int)
 ensures (m >= 0);
 ensures m in [a,b,c,-a,-b,-c];
 ensures (m <= a) || (m<=-a);
 ensures (m <= b) || (m<=-b);
 ensures (m <= c) || (m<=-c);
{
  var ap:int, bp:int, cp:int;

  if (a >= 0) {ap := a;} else {ap := -a;}
  if (b >= 0) {bp := b;} else {bp := -b;}
  if (c >= 0) {cp := c;} else {cp := -c;}
  assert ((ap >= 0) && (bp >= 0) && (cp >= 0)); // Not needed, but shows intent

  m := -1;
  if ((ap <= bp) && (ap <= cp)) {m := ap;}
  if ((bp <= ap) && (bp <= cp)) {m := bp;}
  if ((cp <= ap) && (cp <= bp)) {m := cp;}
  assert (m != -1); // Not needed, but shows intent
}