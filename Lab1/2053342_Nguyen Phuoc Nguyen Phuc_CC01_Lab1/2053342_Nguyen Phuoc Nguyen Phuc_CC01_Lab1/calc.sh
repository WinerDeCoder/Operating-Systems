#! /bin/bash
array=()
i="1"
count=0
while [ $i == "1" ]
do  
  read -p ">> " a op b
  
  if [ $a == 'EXIT' ]
  then
    break
  fi
  if [ $a == 'HIST' ]
  then
    for o in {1..5} 
    do
       if [ $((count-o)) == -1 ]
       then
         break
       fi
    	echo ${array[$((count-o))]}
    done
    continue
  fi  
  t=$a$op$b=
  if [ $a == 'ANS' ]
  then 
    FILE=hello.sh
    if [ -f "$FILE" ]; then
      read a < hello.sh
    else
      a=0
    fi
  fi
  if [ "$b" == "ANS" ]
  then 
    FILE=hello.sh
    if [ -f "$FILE" ]; then
      read b < hello.sh
    else
      b=0
    fi
  fi
  if [ "$op" == "+" ]
  then
    e=$(echo $a + $b | bc) 
    t+=$e
    array+=($t)
    echo $e
    echo $e > hello.sh
    ((count++))
  elif [ "$op" == "-" ]
  then
    e=$(echo $a - $b | bc) 
    t+=$e
    array+=($t)
    echo $e
    echo $e > hello.sh
    ((count++))
  elif [ "$op" == "*" ]
  then
    e=$(echo $a \* $b | bc) 
    t+=$e
    array+=($t)
    echo $e > hello.sh
    echo $e
    ((count++))
  elif [ "$op" == "/" ]
  then
    if [ $b == '0' ]
    then 
      echo MATH ERROR
      continue
    else      
      e=$(echo "scale=2; $a / $b" | bc )
      echo $e > hello.sh
      echo $e
      t+=$e
      array+=($t)
      ((count++))
    fi
  elif [ "$op" == "%" ]
  then
    if [ $b == '0' ]
    then 
      echo MATH ERROR
      continue
    else      
      e=$(echo  $a / $b | bc )
      echo $e > hello.sh
      echo $e
      t+=$e
      array+=($t)
      ((count++))
    fi
  else
    delete=$t
    array=( "${array[@]/$delete}" )
    echo SYNTAX ERROR
  fi
  
done