
echo "max_cardinality vertices edges phases maximal_extraction elapsed_time" > "experiment-all"
echo "vertices edges phases maximal_extraction min_time elapsed_time max_time" >> "experiment-time"
echo "vertices edges min_phases phases max_phases" >> "experiment-phases"
echo "vertices edges min_maximal_extraction maximal_extraction max_maximal_extraction" >> "experiment-max-extraction"
for ((i = 10; i <= 450; i+=10))
do
  echo "N = $i"
  for ((j = 0; j < 20; j++))
  do
    echo "Execution $j"
    ./genmatch $i 0.5 > "test-$i-$j.gr"
    ./matching < "test-$i-$j.gr" 2>> "run.tmp"
    rm "test-$i-$j.gr"
  done
  vertices=$(awk '{x+=$1;next}END{print x/NR}' "run.tmp")
  edges=$(awk '{x+=$2;next}END{print x/NR}' "run.tmp")
  phases=$(awk '{x+=$3;next}END{printf x/NR}' "run.tmp")
  maximal_extraction=$(awk '{x+=$4;next}END{printf x/NR}' "run.tmp")
  elapsed_time=$(awk '{x+=$5;next}END{printf("%.20f", x/NR)}' "run.tmp")
  max_phases=$(awk '{if (x<=$3) x=$3; next}END{print x}' "run.tmp")
  min_phases=$(awk 'BEGIN{x=9999999999}{if (x>=$3) x=$3; next}END{print x}' "run.tmp")
  max_maximal_extraction=$(awk '{if (x<=$4) x=$4; next}END{print x}' "run.tmp")
  min_maximal_extraction=$(awk 'BEGIN{x=9999999999}{if (x>=$4) x=$4; next}END{print x}' "run.tmp")
  max_time=$(awk '{if (x<=$5) x=$5; next}END{print x}' "run.tmp")
  min_time=$(awk 'BEGIN{x=9999999999}{if (x>=$5) x=$5; next}END{print x}' "run.tmp")
  cat run.tmp >> "experiment-all"
  rm run.tmp
  echo $vertices $edges $phases $maximal_extraction $min_time $elapsed_time $max_time >> "experiment-time"
  echo $vertices $edges $min_phases $phases $max_phases >> "experiment-phases"
  echo $vertices $edges $min_maximal_extraction $maximal_extraction $max_maximal_extraction >> "experiment-max-extraction"
done  

echo "max_cardinality vertices edges phases maximal_extraction elapsed_time" > "experiment3a-all"
echo "vertices edges phases maximal_extraction min_time elapsed_time max_time" >> "experiment3a-time"
echo "vertices edges min_phases phases max_phases" >> "experiment3a-phases"
echo "vertices edges min_maximal_extraction maximal_extraction max_maximal_extraction" >> "experiment3a-max-extraction"
for ((i = 10; i <= 450; i+=10))
do
  echo "N = $i"
  for ((j = 0; j < 20; j++))
  do
    echo "Execution $j"
    ./genmatch $i 0.1 > "test-$i-$j.gr"
    ./matching < "test-$i-$j.gr" 2>> "run.tmp"
  done
  vertices=$(awk '{x+=$1;next}END{print x/NR}' "run.tmp")
  edges=$(awk '{x+=$2;next}END{print x/NR}' "run.tmp")
  phases=$(awk '{x+=$3;next}END{printf x/NR}' "run.tmp")
  maximal_extraction=$(awk '{x+=$4;next}END{printf x/NR}' "run.tmp")
  elapsed_time=$(awk '{x+=$5;next}END{printf("%.20f", x/NR)}' "run.tmp")
  max_phases=$(awk '{if (x<=$3) x=$3; next}END{print x}' "run.tmp")
  min_phases=$(awk 'BEGIN{x=9999999999}{if (x>=$3) x=$3; next}END{print x}' "run.tmp")
  max_maximal_extraction=$(awk '{if (x<=$4) x=$4; next}END{print x}' "run.tmp")
  min_maximal_extraction=$(awk 'BEGIN{x=9999999999}{if (x>=$4) x=$4; next}END{print x}' "run.tmp")
  max_time=$(awk '{if (x<=$5) x=$5; next}END{print x}' "run.tmp")
  min_time=$(awk 'BEGIN{x=9999999999}{if (x>=$5) x=$5; next}END{print x}' "run.tmp")
  cat run.tmp >> "experiment3a-all"
  rm run.tmp
  echo $vertices $edges $phases $maximal_extraction $min_time $elapsed_time $max_time >> "experiment3a-time"
  echo $vertices $edges $min_phases $phases $max_phases >> "experiment3a-phases"
  echo $vertices $edges $min_maximal_extraction $maximal_extraction $max_maximal_extraction >> "experiment3a-max-extraction"
done

echo "max_cardinality vertices edges phases maximal_extraction elapsed_time" > "experiment3b-all"
echo "vertices edges phases maximal_extraction min_time elapsed_time max_time" >> "experiment3b-time"
echo "vertices edges min_phases phases max_phases" >> "experiment3b-phases"
echo "vertices edges min_maximal_extraction maximal_extraction max_maximal_extraction" >> "experiment3b-max-extraction"
for ((i = 10; i <= 450; i+=10))
do
  echo "N = $i"
  for ((j = 0; j < 20; j++))
  do
    echo "Execution $j"
    ./genmatch $i 0.9 > "test-$i-$j.gr"
    ./matching < "test-$i-$j.gr" 2>> "run.tmp"
    rm "test-$i-$j.gr"
  done
  vertices=$(awk '{x+=$1;next}END{print x/NR}' "run.tmp")
  edges=$(awk '{x+=$2;next}END{print x/NR}' "run.tmp")
  phases=$(awk '{x+=$3;next}END{printf x/NR}' "run.tmp")
  maximal_extraction=$(awk '{x+=$4;next}END{printf x/NR}' "run.tmp")
  elapsed_time=$(awk '{x+=$5;next}END{printf("%.20f", x/NR)}' "run.tmp")
  max_phases=$(awk '{if (x<=$3) x=$3; next}END{print x}' "run.tmp")
  min_phases=$(awk 'BEGIN{x=9999999999}{if (x>=$3) x=$3; next}END{print x}' "run.tmp")
  max_maximal_extraction=$(awk '{if (x<=$4) x=$4; next}END{print x}' "run.tmp")
  min_maximal_extraction=$(awk 'BEGIN{x=9999999999}{if (x>=$4) x=$4; next}END{print x}' "run.tmp")
  max_time=$(awk '{if (x<=$5) x=$5; next}END{print x}' "run.tmp")
  min_time=$(awk 'BEGIN{x=9999999999}{if (x>=$5) x=$5; next}END{print x}' "run.tmp")
  cat run.tmp >> "experiment3b-all"
  rm run.tmp
  echo $vertices $edges $phases $maximal_extraction $min_time $elapsed_time $max_time >> "experiment3b-time"
  echo $vertices $edges $min_phases $phases $max_phases >> "experiment3b-phases"
  echo $vertices $edges $min_maximal_extraction $maximal_extraction $max_maximal_extraction >> "experiment3b-max-extraction"
done


echo "vertices edges elapsed_time" > "experiment2a-all"
echo "vertices edges min_time elapsed_time max_time" >> "experiment2a-time"
for ((i = 10; i <= 450; i+=10))
do
  echo "hopcroftkarp N = $i"
  for ((j = 0; j < 20; j++))
  do
    echo "Execution $j"
    ./genmatch $i 0.5 > "test-$i-$j.gr"
    ./matching < "test-$i-$j.gr" 2>> "run.tmp"
  done
  vertices=$(awk '{x+=$1;next}END{print x/NR}' "run.tmp")
  edges=$(awk '{x+=$2;next}END{print x/NR}' "run.tmp")
  elapsed_time=$(awk '{x+=$5;next}END{printf("%.20f", x/NR)}' "run.tmp")
  max_time=$(awk '{if (x<=$5) x=$5; next}END{print x}' "run.tmp")
  min_time=$(awk 'BEGIN{x=9999999999}{if (x>=$5) x=$5; next}END{print x}' "run.tmp")
  cat run.tmp >> "experiment2a-all"
  rm run.tmp
  echo $vertices $edges $min_time $elapsed_time $max_time >> "experiment2a-time"
done
echo "vertices edges elapsed_time" > "experiment2b-all"
echo "vertices edges min_time elapsed_time max_time" >> "experiment2b-time"
for ((i = 10; i <= 450; i+=10))
do
  echo "fordfulkerson N = $i"
  for ((j = 0; j < 20; j++))
  do
    echo "Execution $j"
    ./maxflowreduction < "test-$i-$j.gr" 2>> "run.tmp"
    rm "test-$i-$j.gr"
  done
  vertices=$(awk '{x+=$2;next}END{print x/NR}' "run.tmp")
  edges=$(awk '{x+=$3;next}END{print x/NR}' "run.tmp")
  elapsed_time=$(awk '{x+=$5;next}END{printf("%.20f", x/NR)}' "run.tmp")
  max_time=$(awk '{if (x<=$5) x=$5; next}END{print x}' "run.tmp")
  min_time=$(awk 'BEGIN{x=9999999999}{if (x>=$5) x=$5; next}END{print x}' "run.tmp")
  cat run.tmp >> "experiment2b-all"
  rm run.tmp
  echo $vertices $edges $min_time $elapsed_time $max_time >> "experiment2b-time"
done    
