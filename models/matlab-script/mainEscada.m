%---------------------------------------------
%   CG - 2018/19
%   Construcao de uma escada
%   Estrutura ={lances , patamares}   %podem ser repetifos
%       Lance   - ND   : numero degraus
%       Patamar - (-1)
%
%   Saida: vertices, normais, cores
%          Uso em vertexArrat - openGL
%
%------  Blondel formula 2*E+P
%---------------------------------------------
close all
clear

%-------------------------------------
%-------------------------------------
L=800;      % largura
E=16;       % espelho
P=64-2*E;   % piso
A=3*P;      % patamar

show=0;
estrutura=[ -1 3 -1 2 -1 -1 4 ];  % lance=postivos / patamar=negativo

STAIR=escada( L, E, P, A, estrutura, show);
desenhaPoligonos(STAIR,'b');
guardaVertices(STAIR);
guardaNormais(STAIR);
guardaCores(STAIR);

