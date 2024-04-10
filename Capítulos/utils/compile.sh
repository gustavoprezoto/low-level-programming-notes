#!/bin/bash

if [ "$#" -ne 1 ]; then
	echo "Uso: $0 <nome_do_arquivo> (sem extensão)"
	exit 1
fi

fileName=$1
echo "$fileName compilando."

nasm -felf64 $fileName.asm -o $fileName.o
ld -o "$fileName" "$fileName".o
chmod u+x "$fileName"

echo "$fileName compilado."
