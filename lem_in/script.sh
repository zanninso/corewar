for i in {1..1000000}
do  echo $i
    (./generator\ \(1\) --big > file && ./lem-in < file| grep "L" | wc -l && cat file | grep "req") >> output
done