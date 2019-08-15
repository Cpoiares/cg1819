function P1 = rotateX( P, a )

PI=acos(-1);
a=a*PI/180;

M=[1 0 0 0
   0 cos(a)  -sin(a) 0 
   0 sin(a)  sin(a) 0
   0 0 0 1];
P1= M*P;
