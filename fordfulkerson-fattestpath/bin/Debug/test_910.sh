
echo "type:"
read type
echo "arg1:"
read arg1
for ((i = 6302; i <= 6302; i++))
do
  for ((j = 0; j < 20; j++))
  do
    echo "Execution $j"
    d1=$(echo "$arg1 * $i / $arg1" | bc)
    echo $d1
    ./new_washington $type $d1 "test-$type-$arg1.gr"
    ./stmaxflow < "test-$type-$arg1.gr" 2>> "run.tmp"
    rm "test-$type-$arg1.gr"
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
  cat run.tmp >> "experiment-$arg1-all"
  rm run.tmp
  echo $upper_limit $total_vertices $total_edges $min_time $elapsed_time $max_time >> "experiment-$arg1-time"
  echo $upper_limit $total_vertices $total_edges $min_count_iter $count_iter $max_count_iter >> "experiment-$arg1-iter"
done  
