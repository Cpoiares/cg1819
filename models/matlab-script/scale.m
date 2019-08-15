function P1 = scale( P, x,y,z)

M=[x 0 0 0
   0 y 0 0
   0 0 z 0
   0 0 0 1];
P1= M*P;
