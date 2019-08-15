function [] = desenhaPoligonos( V , cor)
if nargin==1
    cor='k';
end

NQ=size(V,2)/4;

xlabel('x')
ylabel('z')
zlabel('y')
view([45 45])
figure(1)
hold on
for i=1:NQ
    ini=(i-1)*4+1;
    fim=ini+3;    
    P=[ V(:,ini:fim) V(:,ini)];
    plot3(P(1,:),P(3,:),P(2,:),cor, ...
          P(1,:),P(3,:),P(2,:),'k.' )
end
