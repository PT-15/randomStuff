#!/usr/bin/bash

declare -a wordDict
declare -a wordsToCheck

read -p "Enter word length: " wordLength
echo "Enter letters separated by space: "
declare -a letters
while read letter ; do
    letters+=${letter} 
done
#mapfile -t wordDict < american-english.txt
mapfile -t wordsToCheck < <( ./randomWordGenerator ${wordLength} ${letters} )
mapfile -t wordDict < <( cat american-english.txt | awk 'length($0) == 5' )

for word in "${wordsToCheck[@]}"; do

    #BINARY SEARCH
    declare -i left=0
    declare -i right=${#wordsToCheck[@]}
    declare -i middle
    while $right -ge $left; do
        middle=$((left + right))/2
        if $word > $wordDict[middle]; then
            left=${middle}
        else
            right=${middle}
        fi
    done
    if ${wordDict[right]} -eq $word; then
        echo ${word}
    fi

done
