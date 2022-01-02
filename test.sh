#!/usr/bin/env bash
PROGRAM=./bwt

testcase() {
    echo 'input: ' "$1"
    echo -n 'output: '
    echo -n "$1" | $PROGRAM
    echo; echo
}

testcase '$BANANA'
testcase '$DOGWOOD'
testcase '$ABRACADABRA'
testcase '$TEXYDSTEIXIXIXXSSMPPSBESEUSFXDIIOIIIT'

testcase '$ACTGTTACGT'
testcase '$CTGTCTATTAAATGCTGATCTA'
testcase '$AAAACCATTCACAGCACAAATGACCCGATCGCATTGACACGCGTTTGGCCGATAATCTCGAAACGTCTGAACGTGACTT'
