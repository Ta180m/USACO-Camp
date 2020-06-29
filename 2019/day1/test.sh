for i in {6..1000}
do
	echo $i >> in
    .vscode/3 < in | .vscode/1 > out
    if !(cmp -s in out); then
		echo $i
	fi
	rm in
done