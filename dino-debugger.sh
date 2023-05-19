#! /usr/bin/bash

declare -a answers
answers=("Hmmmmmm" "Are you sure?" "Aha" "Aha aha" "Of course" "Tell me more" "No. Really?"
	"That sounds interesting" "That sounds REALLY interesting" "No, you are kidding"
	"Yes, but how much wood would a woodchuck chuck if a woodchuck could chuck wood?"
	"Aha aha aha"

	"Yes, but did you know I have an oscilloscope?"

	"You don't say" "Say whaaaaat?" )

RANDOM=`(date +%M%S)`
echo $RANDOM

cowsay -f stegosaurus "Explain the program to me." # Line - by - line."
echo ""
echo -n "> "

while [ 1 ]; do
	read str
	if [ "$str" = "Bye" -o "$str" = "Goodbye" -o "$str" = "bye" -o "$str" = "goodbye" ]; then
		cowsay -f stegosaurus "Goodbye, Sir"
		echo ""
		exit 0
	fi
	if [ "$str" = "quit" -o "$str" = "exit" ]; then
		cowsay -f stegosaurus "Goodbye would have been more polite, but ok"
		echo ""
		exit 0
	fi

	cowsay -f stegosaurus ${answers[($RANDOM % ${#answers[@]})]}
	echo ""
	echo ""
	echo -n "> "
done
