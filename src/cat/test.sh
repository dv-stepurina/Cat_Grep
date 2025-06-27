#!/bin/bash

MyArray=("-b" "-e" "-v" "-t" "-et" "-n" "-s" "-bs" "-bn" "-b -n" "-b -s" "-s -n" "-T" "-E" "-TE" "-r"  "--number" "--squeeze-blank" "--number-nonblank"  "--squeeze-blank --number-nonblank")
success=0
fail=0

txt=("" "../datasets/1_txt" "fmgjkhj" "../datasets/2_txt" "../datasets/3_txt" "../datasets/4_txt")


if [[ "$OSTYPE" == "darwin"* ]]; then
  if ! command -v gcat &> /dev/null; then
    echo "ERROR: GNU cat not found. Install with: brew install coreutils"
    exit 1
  fi
  REF_CAT="gcat"
  echo "⚠️  Using gcat for macOS compatibility"
else
  REF_CAT="cat"
fi

for i in ${txt[@]}; do 
	for t in ${MyArray[@]}; do 
		$REF_CAT $t $i 1> file1 2>>file3
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