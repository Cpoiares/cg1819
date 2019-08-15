function P = quadrado( tam )

T=tam/2;
p1=[-T -T 0]';
p2=[ T -T 0]';
p3=[ T  T 0]';
p4=[-T  T 0]';
P =[p1 p2 p3 p4];
P =[P;
    ones(1,4)];
