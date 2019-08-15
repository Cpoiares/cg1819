function [] = guardaCores(V)

NQ=size(V,2)/4;

R=[1 0 0 1 0 0 1 0 0 1 0 0];
G=[0 1 0 0 1 0 0 1 0 0 1 0];
B=[0 0 1 0 0 1 0 0 1 0 0 1];

fileID = fopen('cores.txt','w');
for i=1:NQ    
    
    if mod(i,3)==0  %piso
       X=R;
    elseif mod(i,3)==1  %piso 
       X=G;
    else
       X=B;
    end
    for j=1:length(X)
        fprintf(fileID,'%f', X(j) );
        fprintf(fileID,'%c ', ',' );    
    end    
end
fclose(fileID);
