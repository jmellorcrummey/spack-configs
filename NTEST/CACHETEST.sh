#/bin/sh

cd /home/msi3/NTEST/

CACHEDIR=/home/msi3/NTEST/MYCACHE


echo "Removing MYCACHE and anything left from previous run" 
echo "" 
make clobber  
echo "============================================" 
echo "============================================" 
echo "" 
echo "Running with no HPCTOOLKIT_HPCSTRUCT_CACHE set"
echo "		hpcstruct gcc.gputest"
echo "  Verify ADVICE message"
echo "  Verify gcc.gputest was not added to cache; Verify path is set to this directory"
echo "  Then remove struct file"
echo "--------------------------------------------"
export HPCTOOLKIT_HPCSTRUCT_CACHE=
/bin/time -p hpcstruct gcc.gputest
echo "" 
grep "<LM" *.hpcstruct  
rm gcc.gputest.hpcstruct

echo "============================================" 
echo "============================================" 
echo "Running with no HPCTOOLKIT_HPCSTRUCT_CACHE set and --nocache argument"
echo "		 hpcstruct --nocache gcc.gputest"
echo "  Verify absence of ADVICE message"
echo "  Verify gcc.gputest was not added to cache; Verify path is set to this directory"
echo "  Then remove struct file"
echo "--------------------------------------------"
export HPCTOOLKIT_HPCSTRUCT_CACHE=
/bin/time -p hpcstruct --nocache gcc.gputest
echo "" 
grep "<LM" *.hpcstruct  
rm gcc.gputest.hpcstruct

echo "============================================" 
echo "============================================" 
echo "Test with -c argument"
echo "		 hpcstruct -c $CACHEDIR gcc.gputest"
echo "  Verify gcc.gputest was added to cache; Verify path is set to this directory"
echo "  Remove struct file"
echo "--------------------------------------------"
/bin/time -p hpcstruct -c $CACHEDIR gcc.gputest
echo "" 
grep "<LM" *.hpcstruct  
rm gcc.gputest.hpcstruct

echo "============================================" 
echo "============================================" 
echo "Test with -c argument, and file cached"
echo "		 hpcstruct -c $CACHEDIR gcc.gputest"
echo "  Verify gcc.gputest was copied from cache; Verify path is set to this directory"
echo "  Remove struct file"
echo "--------------------------------------------"
/bin/time -p hpcstruct -c $CACHEDIR gcc.gputest
echo "" 
grep "<LM" *.hpcstruct  
rm gcc.gputest.hpcstruct

echo "============================================" 
echo "============================================" 
echo "Test with file cached, but --nocache argument"
echo "		 hpcstruct --nocache gcc.gputest"
echo "  Verify cache not specified; Verify path is set to this directory"
echo "  Remove struct file"
echo "--------------------------------------------"
/bin/time -p hpcstruct --nocache gcc.gputest
echo "" 
grep "<LM" *.hpcstruct  
rm gcc.gputest.hpcstruct


echo "" 
echo "============================================" 
echo "============================================" 
echo "Set the environment variable for the cache" 
export HPCTOOLKIT_HPCSTRUCT_CACHE=/home/msi3/NTEST/MYCACHE
echo "" 
echo "Running in nvidia/omp.gcc subdirectory" 
echo "" 
echo "--------------------------------------------"
(cd nvidia/omp.gcc;  make struct )  
echo "" 
(cd nvidia/omp.gcc ;grep "<LM" *.hpcstruct ) 

echo "============================================" 
echo "============================================" 
echo "" 


echo " Note make hpct1 and hpctpc1 use --gpucfg no; the corresponding 2's use --gpucfg yes."
echo " Note make hpct3 is like hpct1 with the addition of --nocache"
echo "" 
echo "Running hpct1" 
echo "  Verify all struct files except gcc.gputest were added to cache"
echo "   gcc.gputest was copied from cache, since it was cached above"
echo "   Verify struct files in meas.1.c.g.t point to the correct directory" 
echo "" 
echo "--------------------------------------------"
(cd nvidia/omp.gcc;  make hpct1 )  
echo "" 

(cd nvidia/omp.gcc/meas.1.c.g.t/structs; grep "<LM" *.hpcstruct ) 

echo "============================================" 
echo "============================================" 
echo "Running hpct2" 
echo "  Verify all struct files except *.gpubin were copied from cache"
echo "  Verify *.gpubin was added to cache, since its gpucfg flag was different"
echo "  Verify struct files in meas.2.c.g.t point to the correct directory" 
echo "" 

echo "--------------------------------------------"
(cd nvidia/omp.gcc;  make hpct2 )  
echo "" 
(cd nvidia/omp.gcc/meas.2.c.g.t/structs; grep "<LM" *.hpcstruct )  

echo "============================================" 
echo "============================================" 
echo "Running hpct3" 
echo "  Verify all struct files show cache disabled"
echo "  Verify struct files in meas.2.c.g.t point to the correct directory" 
echo "" 

echo "--------------------------------------------"
(cd nvidia/omp.gcc;  make hpct3 )  
echo "" 
(cd nvidia/omp.gcc/meas.3.c.g.t/structs; grep "<LM" *.hpcstruct )  


echo "============================================" 
echo "============================================" 
echo "" 
echo "Showing net cache utilization"  
echo "" 

du -sh $CACHEDIR

