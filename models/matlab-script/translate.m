function P1 = translate( P, x,y,z)

M=[1 0 0 x
   0 1 0 y
   0 0 1 z
   0 0 0 1];
P1= M*P;
