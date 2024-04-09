#!/bin/bash

# проверка количества аргументов
if [ $# -lt 2 ]; then
	exit 1
fi

in_test=$1
out_test=$2
args_test=$(cat "$3")
out_prog="out.txt"
# command="../../app.exe $args_test"
cd ../../
command="./app.exe $args_test"

# Коды ошибок
test_p="0"
test_f="1"
# $command > "$out_prog"
$command
error="$?"

cd ./func_tests/scripts/

# проверка завершения программы
if ! [ "$error" -eq 0 ]; then							# не нулевой код ошибки
	exit "$test_f"
fi

# сравниваем выходные данные программы и данные в тесте
if ! ./comparator.sh "../../$out_prog" "$out_test"; then # неверный тест
	exit "$test_f"
else													# верный тест
	exit "$test_p"
fi