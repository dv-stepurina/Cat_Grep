MyArray=("-b" "-e" "-v" "-t" "-et" "-n" "-s" "-bs" "-bn" "-b -n" "-b -s" "-s -n" "-T" "-E" "-TE" "-r"  "--number" "--squeeze-blank" "--number-nonblank"  "--squeeze-blank --number-nonblank")
success=0
fail=0

txt=("" "1_txt" "fmgjkhj" "2_txt" "3_txt" "4_txt")

for i in ${txt[@]}; do 
	for t in ${MyArray[@]}; do 
		cat $t $i 1> file1 2>>file3
		./s21_cat $t $i 1> file2 2>>file3

		res="$(diff -s file1 file2)"
        if [ "$res" == "Files file1 and file2 are identical" ]
                then
                  (( success++ ))
                else
                  echo "$t $i" >> log.txt
                  (( fail++ ))
        fi
		rm file1 file2
	done
done

echo "SUCCESS: $success"
echo "FAIL: $fail"