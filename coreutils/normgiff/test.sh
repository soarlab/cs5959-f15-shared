function tester()
{
	#echo "$1"
	#echo "$2"
	if [ "$1" == "$2" ];
	then
		echo "$(tput setaf 1)FAIL! $(tput sgr0)"
	else
		echo "$(tput setaf 2)Test Iteration $3 - PASS! $(tput sgr0)"
	fi


}

function random_string()
{
	cat /dev/urandom | env LC_CTYPE=C tr -dc 'a-zA-Z' | fold -w "$1" | head -n 1

}

python_base64=$(python -c "import base64; print base64.b64encode('$H');")
echo $python_base64
coreutil_base64=$(echo $H|./base64)
#echo $coreutil_base64
#ran_num=10
#let num=$ran_num

#rand="$(random_string $num)"
#echo "The random string" $rand

#core=$(echo $rand|./base64)
#echo "coreutil: " $core


#pyth=$(python -c "import base64; print base64.b64encode('$rand');")
#echo "python: " $pyth


for i in $(seq 2000 100000)
do
	let num=$i*1000
	rand="$(random_string $num)"
	#python=$(python -c "import base64; print base64.b64encode('$rand');")
	#coreutil=$(echo '$rand'|./base64)
	START=$(date +%s)
	#tester "$coreutil" "$python" "$i"
	tester "($rand|./base64|./base64 -d)" "$rand" "$i"
	END=$(date +%s)
	echo $((END-START)) >> times_lin.txt
	echo "Time Duration: " $((END-START))
done