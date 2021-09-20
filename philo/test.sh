echo 'philo (){
	rm log
    for COUNT in `seq 1 $6`
    do
        ./philo $1 $2 $3 $4 $5 | grep -rnE "eat|die" >> log
		echo $COUNT
		echo "\n\n" >> log
		echo $COUNT >> log
		echo "\n" >> log
		grep -rnE "die|$7" log
    done
}' >> ~/.zshrc
