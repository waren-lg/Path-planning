axis([0 12 0 12]);
hold on ; 
fichier = fopen('resultat_points.txt', 'r');
str=fgetl(fichier);
if strcmp(str,'DEPART')
    str=fgetl(fichier);
    D= sscanf(str,'%f');
    x=[D(1)];
    y=[D(2)];
end
str=fgetl(fichier);    
while strcmp(str,'OBSTACLE')
    str=fgetl(fichier);
    O=sscanf(str,'%f');
    X=[O(1)];
    Y=[O(2)];
    str=fgetl(fichier);
    str=fgetl(fichier);
    while strcmp(str,'FIN_OBSTACLE')==0 & strcmp(str,'ARRIVEE')==0 & strcmp(str,'OBSTACLE')==0  
        O=sscanf(str,'%f');
        X=[X,O(1)];
        Y=[Y,O(2)];
        str=fgetl(fichier);
        str=fgetl(fichier);
    end
    %fill(X,Y,'green');
    x=[x,X];
    y=[y,Y];
    clear X;
    clear Y;
end

if strcmp(str,'ARRIVEE')
    str=fgetl(fichier);
    A = sscanf(str,'%f');
    x=[x,A(1)];
    y=[y,A(2)];
end
fichier = fopen('coordonnees.txt', 'r');
str=fgetl(fichier);
if strcmp(str,'DEPART')
    str=fgetl(fichier);
    D= sscanf(str,'%f');
    x1=[D(1)];
    y1=[D(2)];
end
str=fgetl(fichier);    
while strcmp(str,'OBSTACLE')
    str=fgetl(fichier);
    O1=sscanf(str,'%f');
    X1=[O1(1)];
    Y1=[O1(2)];
    str=fgetl(fichier);
    str=fgetl(fichier);
    while strcmp(str,'FIN_OBSTACLE')==0 & strcmp(str,'ARRIVEE')==0 & strcmp(str,'OBSTACLE')==0  
        O1=sscanf(str,'%f');
        X1=[X1,O1(1)];
        Y1=[Y1,O1(2)];
        str=fgetl(fichier);
        str=fgetl(fichier);
    end
    fill(X1,Y1,'blue');
    x1=[x1,X1];
    y1=[y1,Y1];
    clear X1;
    clear Y1;
end

if strcmp(str,'ARRIVEE')
    str=fgetl(fichier);
    A = sscanf(str,'%f');
    x1=[x1,A(1)];
    y1=[y1,A(2)];
end


fichier = fopen('dijkstra.txt', 'r');
str=fgetl(fichier);
p=sscanf(str,'%f');
p=p';
p=p+1;

%Ax=fgetl()
%X1=[0,0,2,2,1,1];%pour dresser le polygone 1
%Y1=[4,0,0,1,1,4];
%X2=[3,4,4,3];%pour dresser le polygone 2
%Y2=[1,1,3,3];
%pour la planification 
%y=[4,Y1,Y2,2];
%p=[0,0,0,2,6,6,1,6,7,6,6,9];
%p=p+1;
n=length(p);
%fill(X1,Y1,'red');
%fill(X2,Y2,'red');
while (p(n)~=1)
   plot([x(p(n)),x(n)],[y(p(n)),y(n)],'red');
   n=p(n);
end
plot([x(p(n)),x(n)],[y(p(n)),y(n)],'r-');
hold off;  

