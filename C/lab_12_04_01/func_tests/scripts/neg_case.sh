#!/bin/bash

# проверка количества аргументов
if [ $# -lt 1 ]; then
	exit 1
fi

in_test=$1

if [ $# -eq 3 ]; then
	out_test=$3
fi

out_prog="out.txt"
# command="../../app.exe $in_test"
# command="../../app.exe"
args_test=$(cat "$2")
cd ../../
command="./app.exe $args_test"

# Коды ошибок
test_p="0"
test_f="1"

# if [ $# -eq 2 ]; then
# 	command="$command $(cat "$2") "
# fi

# $command > "$out_prog"
$command
error="$?"

cd ./func_tests/scripts/

# проверка завершения программы
if [ "$error" -eq 0 ]; then								# нулевой код ошибки
	exit "$test_f"
else													# не нулевой код ошибки
	# exit "$test_p"
	# сравниваем выходные данные программы и данные в тесте
	if [ $# -eq 3 ]; then
		if ! ./comparator.sh "../../$out_prog" "$out_test"; then		# неверный тест
			exit "$test_f"
		else													# верный тест
			exit "$test_p"
		fi
	else
		exit "$test_p"
	fi
fi