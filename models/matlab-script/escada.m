function EE = escada( L, E, P, A, EST, show)


lances=find(EST>0);
ND=EST(lances);

EE=[];
nTP=0;
nTE=0;
nTA=0;
for i=1:length(EST)
    
    if EST(i)>0
        nd = EST(i);
        DD = degraus( L, E, P, nd, 0 );
        DD = translate(DD, 0, nTE*E, nTP*P + nTA*A);
        EE = [EE DD];
        nTE= nTE+nd;
        nTP= nTP+nd-1;        
    else
        %------------------------- patamar 1
        PP = patamar(L,A,0);
        PP = translate(PP,0, nTE*E, nTP*P + nTA*A);
        EE = [EE PP];
        nTA= nTA+1;        
    end
end



