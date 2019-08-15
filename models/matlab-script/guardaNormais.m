function [] = guardaVertices( V)

NQ=size(V,2)/4;
espelho=[0 0 1 0 0 1 0 0 1 0 0 1];
piso   =[0 1 0 0 1 0 0 1 0 0 1 0];

fileID = fopen('normais.txt','w');
for i=1:NQ    
    if mod(i,2)==0  %piso
       X=piso;
    else
       X=espelho;
    end
    for j=1:length(X)
        fprintf(fileID,'%f', X(j) );
        fprintf(fileID,'%c ', ',' );    
    end    
end
fclose(fileID);
