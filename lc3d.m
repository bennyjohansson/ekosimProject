function ret = lc3d(matri)

  ##Takes a matrix [depth, Intensity] and creates a 3Dmap together with
  ##a gaussian function (here g16r)

  ##loading gaussians
  gauss
  Isa = matri;
     xlen = size(matri)(1);
     ##Adding a x-axis if not there (choosing 0-1200nm)
     if(size(matri)(2) == 1);
       step = 1200/(xlen-2);
       matr2 = ones(xlen, 2);
       matr2(1,1) = step/2;
       for i = 2:xlen/2
	 matr2(i,1) = matr2(i-1,1)+step;
       endfor
       matr2(xlen/2+1, 1) = matr2(xlen/2,1);
       for i = (xlen/2 + 2):xlen
	 matr2(i,1) = matr2(i-1,1)+step;
       endfor
       xlen;
       matr2;
       size(matr2);
       matr = ones(xlen, 2);
       matr2(:,2) = matri;
       matr = matr2;
     else
       matr = ones(xlen, 2);
       matr = matri;
     endif
     ##gaussianv2(F, xi, w, length, points, ax)

     ##Old rubbish to be deleted
     d = matr(:,1);
     Is = matr(:,2);
     param = g16r();
     F = param(1);
     xi = param(2);
     w = param(3);
     gausslen = 100;
     emax = 3;
				#clg
				#figure(1)
     g = gaussianv2(F, xi, w, 3, gausslen, 0);
     
     
     
     ##Wavelengthvector:
     wlstart = 350;
     wlstop = 900;
     wlstep = (wlstop - wlstart)/xlen;
     wlvec = ones(xlen,1);
     wlvec(1) = 3500;
     for i = 2:xlen
     wlvec(i) = wlvec(i-1)+wlstep;
     endfor
     if(1)
       gv2 = gaussianv2(F, xi, w, 3, gausslen, 0)
       xvec = matr(:,1);
       plotdata = ones(xlen*gausslen, 3);
       a=1;
       matr
       for i = 1:xlen
	 for j = 1:gausslen
				#zcoord = matr(i,2)*g(i);
	   plotdata(a,1) = xvec(i);
	   plotdata(a,2) = j*3/gausslen;
	   plotdata(a,3) = Isa(i)*gv2(j);#gaussian(F, xi, w, j*3/gausslen);
	   a++;
     endfor
   endfor
 endif		#xlen = size(matr)(1);
 save -ascii surf2.dat plotdata
 z = ones(xlen, xlen);
				#gv = ones(xlen).*g;
 estep = emax/xlen;
 edata = 0:estep:emax-0.0001;
 
 a = 1;
  #for i = 1:xlen

  for j = 1:xlen
				#z(1,a) = d(j);
				#z(2,a) = edata(i);
    #z(j,:) = 0.1*g(j)*Is'; 
				#z(3,a) = g(i)*Is(i);
    a++;
  endfor
  #endfor

  hold off
  figure(2);
  clg;
  ret = z;
  gshow surface
  gset ticslevel 0
  gset noautoscale
  gset nohidden3d
  gset title "Intensity vs wavelength and depth"
  gset xlabel "Wavelength"
  gset ylabel "Depth"
  gset zlabel "Intensity"
  gset yrange [0:3]
  gset xrange [0:1300]
  gset zrange [0:65000]
  gset dgrid3d 30,100,1000
  #gset grid
  #gset noline

  #gunset parametric
  #gset dummy
  #gset hidden3d
  gset view 45,50,1
  #gset size 1
  #gset contour
  #gset dgrid3d 32,100,1
  fileplot2(3)
  ##  fileplot2("depth3d.eps")
  #gset contour
  #gset palette defined (0 "blue", 4000 "white", 8000 "red")
  #gset contour
  #gset cntrparam levels 10
  #gset cntrparam levels incremental 0, 100, 1000
  #gset dgrid3d  50, 50.
  gsplot "surf2.dat"
  #@fileplot2(2)
  #@gsplot "surf.dat"
  ##smooth csplines #acsplines
  #lette defined (-3 "blue", 0 "white", 1 "red")
  ##gnuplot> splot (2*sin(x)-1)*exp(-y) with pm3d
  a = 1;
  b = 45;
  c = 1;
  cflag = 0;
  if(0)
    for i = 0:2:360
      if(i==180 || i==360 || i == 540)
	a=0;
	b =1;
	cflag = 1;
      endif
      filename = "animation"
      ang1 = num2str(a);
      ang2 = num2str(b);
      dist = num2str(c);
      dat = strcat(ang1, ", ", ang2, ", ", dist);
      eval(strcat("gset view ", dat));
      eval(strcat("fileplot2(", filename, int2str(i/2), ")"))
      #eval(strcat("mogrify -density 120 -format jpg ",  filename, int2str(i/2), ".eps")) 
      replot
      a = a + 1;
				#b = b+2;
      b = 1+0.2*sin(0.5*i*pi/180);
      if(a>90)
	c = i/10;
      endif
      if(!cflag)
	c = i/30;
      endif
    endfor
  endif
  
  a = 0;
  aflag = true;
  if(0)
    for i = 1:4:360
      if (i == 360 || i == 720 || i == 900)
	#b = 0;
	a = 0;
	#aflag = !aflag;
      endif
      b = 1+0.8*abs(sin(0.25*i*pi/180));
     
      a = a+4;
      
      filename = strcat("animation", int2str(i/2), ".eps");

      #set terminal tgif animate delay 4
      #set output "animate.gif"
      #set title "This is an animated gif"
      #gsplot "anidata.dat"
      ##limits number of iterations if nonzero
      ##load "gnuplot.rot
      #fileplot2(filename)
      ang = num2str(a);
      dist = num2str(b);
      dat = strcat("45", ", ", ang, ", ", dist);
      eval(strcat("gset view ", dat));
      replot
      #eval(strcat("mogrify -density 120 -format tgif ",  filename)) 
      ##reset
      endfor
    endif
				#for i = 180:-4:1
				#  dist = num2str((181-i)/10);
				#  ang1 = num2str(i);
  #  dat = strcat(ang, ", ", ang1, ", ", dist);
  #  eval(strcat("gset view ", dat));
  #  replot
  #  a = a*0.99;
  #endfor
  #a = 180;
 #for i = 1:4:180
 #   dist = num2str((180-i)/100);
 #   ang1 = num2str(i);
 #   ang2 = "0";
 #   dat = strcat(ang2, ", ", ang1, ", ", dist);
 #   eval(strcat("gset view ", dat));
 #   replot
 #   a = a*0.99;
 # endfor

endfunction





