#!/bin/bash

javac Parser.java

java Parser "a+(a*a)"
echo "------------------"
java Parser "(a+a)*(a+a)"
echo "------------------"
java Parser "a"
echo "------------------"
java Parser "a-a"
echo "------------------"
java Parser "a+a*"
