function [] = guardaVertices( V)

V=V(1:3,:);
V=V(:);
fileID = fopen('vertices.txt','w');
for i=1:length(V)-1
    fprintf(fileID,'%f', V(i) );
    fprintf(fileID,'%c ', ',' );    
end
fprintf(fileID,'%f', V(end) );
fclose(fileID);
