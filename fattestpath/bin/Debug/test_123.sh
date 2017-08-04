
echo "type:"
read type
echo "arg1:"
read arg1
echo "arg2:"
read arg2
echo "arg3:"
read arg3
echo "upper_limit vertices edges iter_count elapsed_time" > "experiment-$arg1-$arg2-$arg3-all"
echo "upper_limit total_vertices total_edges min_time elapsed_time max_time" >> "experiment-$arg1-$arg2-$arg3-time"
echo "upper_limit total_vertices total_edges min_count_iter count_iter max_count_iter" >> "experiment-$arg1-$arg2-$arg3-iter"
for ((i = 5; i <= arg1; i++))
do
  for ((j = 0; j < 20; j++))
  do
    echo "Execution $j"
    d1=$(echo "$arg1 * $i / $arg1" | bc)
    echo $d1
    d2=$(echo "$arg2 * $i / $arg1" | bc)
    echo $d2
    ./new_washington $type $d1 $d2 $arg3 "test-$type-$arg1-$arg2-$arg3.gr"
    ./stmaxflow < "test-$type-$arg1-$arg2-$arg3.gr" 2>> "run.tmp"
    rm "test-$type-$arg1-$arg2-$arg3.gr"
  done
  upper_limit=$(awk '{x+=$1;next}END{print x/NR}' "run.tmp")
  total_vertices=$(awk '{x+=$2;next}END{print x/NR}' "run.tmp")
  total_edges=$(awk '{x+=$3;next}END{print x/NR}' "run.tmp")
  count_iter=$(awk '{x+=$4;next}END{printf("%.20f", x/NR)}' "run.tmp")
  elapsed_time=$(awk '{x+=$5;next}END{printf("%.20f", x/NR)}' "run.tmp")
  max_count_iter=$(awk '{if (x<=$4) x=$4; next}END{print x}' "run.tmp")
  min_count_iter=$(awk 'BEGIN{x=9999999999}{if (x>=$4) x=$4; next}END{print x}' "run.tmp")
  max_time=$(awk '{if (x<=$5) x=$5; next}END{print x}' "run.tmp")
  min_time=$(awk 'BEGIN{x=9999999999}{if (x>=$5) x=$5; next}END{print x}' "run.tmp")
  cat run.tmp >> "experiment-$arg1-$arg2-$arg3-all"
  rm run.tmp
  echo $arg3 $total_vertices $total_edges $min_time $elapsed_time $max_time >> "experiment-$arg1-$arg2-$arg3-time"
  echo $upper_limit $total_vertices $total_edges $min_count_iter $count_iter $max_count_iter >> "experiment-$arg1-$arg2-$arg3-iter"
done  
