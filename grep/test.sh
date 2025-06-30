MyArray=(" " "-e" "-i" "-v" "-c" "-l" "-n" "-h" "-s"  "-o")

success=0
fail=0
text=(" " "jo" "Jo" "пр" "Пр")
files=(" " "../datasets/file1" "../datasets/file1 ../datasets/file2" "../datasets/file1 ../datasets/file2 ../datasets/file3" "../datasets/file2" "gfdg" "../datasets/file3")
count=0

for a in ${MyArray[@]}; do 
	for t in ${text[@]}; do 
        for f in ${files[@]}; do 
            (( count++ ))

            grep $a $t $f 1>res1 2>>res3
            ./s21_grep $a $t $f 1>res2 2>>res3
            if [ "$?" != "0" ]
                then
                echo "$a $t $f" >> segfault.txt
            fi
            res="$(diff -s res1 res2)"

            if [ "$res" == "Files res1 and res2 are identical" ]
                    then
                    (( success++ ))
                    else
                        echo "$a $t $f" >> log.txt
                        (( fail++ ))
            fi
        done
	done
done

f_file=("../datasets/file_reg" " " "../datasets/file_reg_2" "../datasets/file_reg_3")


for f_f in ${f_file[@]}; do 
        for f in ${files[@]}; do 
            (( count++ ))

            grep -f $f_f $f 1>res1 2>>res3
            ./s21_grep -f $f_f $f 1>res2 2>>res3
            if [ "$?" != "0" ]
                then
                echo "$f_f $f" >> segfault.txt
            fi
            res="$(diff -s res1 res2)"

            if [ "$res" == "Files res1 and res2 are identical" ]
                    then
                    (( success++ ))
                    else
                    echo "$f_f $f" >> log.txt
                    (( fail++ ))
            fi
        done
done


text1=(" " "jo" "Jo" "пр" "Пр" "gdfg")
text2=(" " "jo" "Jo" "пр" "Пр")


for t1 in ${text1[@]}; do 
        for t2 in ${text2[@]}; do 
                for f in ${files[@]}; do 
                        (( count++ ))

                        grep -e $t1 -e $t2 $f 1>res1 2>>res3
                        ./s21_grep -e $t1 -e $t2 $f 1>res2 2>>res3
                        if [ "$?" != "0" ]
                                then
                                echo "$t1 $t2 $f" >> segfault.txt
                        fi
                        res="$(diff -s res1 res2)"

                        if [ "$res" == "Files res1 and res2 are identical" ]
                                then
                                (( success++ ))
                        else
                                echo  "$t1 $t2 $f"  >> log.txt
                                (( fail++ ))
                        fi
                done
        done
done



for t1 in ${text1[@]}; do 
        for t2 in ${text2[@]}; do 
                for t3 in ${text2[@]}; do 
                        for f in ${files[@]}; do 
                                (( count++ ))
                                grep -e $t1 -e $t2 -e $t3 $f 1>res1 2>>res3
                                ./s21_grep -e $t1 -e $t2 -e $t3 $f 1>res2 2>>res3
                                if [ "$?" != "0" ]
                                        then
                                        echo "$t1 $t2 $t3 $f" >> segfault.txt
                                fi
                                res="$(diff -s res1 res2)"

                                if [ "$res" == "Files res1 and res2 are identical" ]
                                        then
                                        (( success++ ))
                                        else
                                        echo  "$t1 $t2 $t3 $f"  >> log.txt
                                        (( fail++ ))
                                fi
                        done   
                done
        done
done





for t1 in ${text1[@]}; do 
        for t2 in ${text2[@]}; do 
                for t3 in ${text2[@]}; do 
                        for f1 in ${files[@]}; do 
                                for f2 in ${files[@]}; do 
                                        (( count++ ))
                                        grep -e $t1 -e $t2 -e $t3 $f1 $f2 1>res1 2>>res3
                                        ./s21_grep -e $t1 -e $t2 -e $t3 $f1 $f2 1>res2 2>>res3
                                        if [ "$?" != "0" ]
                                                then
                                                echo "$t1 $t2 $t3 $f1 $f2" >> segfault.txt
                                        fi
                                        res="$(diff -s res1 res2)"

                                        if [ "$res" == "Files res1 and res2 are identical" ]
                                                then
                                                (( success++ ))
                                                else
                                                echo  "$t1 $t2 $t3 $f1 $f2"  >> log.txt
                                                (( fail++ ))
                                        fi
                                done
                        done   
                done
        done
done






for t1 in ${text1[@]}; do 
        for t2 in ${text2[@]}; do 
                for t3 in ${text2[@]}; do 
                        for f in ${files[@]}; do 
                                (( count++ ))
                                grep -e jo -e jo -e jo $f 1>res1 2>>res3
                                ./s21_grep -e jo -e jo -e jo $f 1>res2 2>>res3
                                if [ "$?" != "0" ]
                                        then
                                        echo "$t1 $t2 $t3 $f" >> segfault.txt
                                fi
                                res="$(diff -s res1 res2)"

                                if [ "$res" == "Files res1 and res2 are identical" ]
                                        then
                                        (( success++ ))
                                        else
                                        echo  "$t1 $t2 $t3 $f"  >> log.txt
                                        (( fail++ ))
                                fi
                        done   
                done
        done
done



echo "SUCCESS: $success"
echo "FAIL: $fail"