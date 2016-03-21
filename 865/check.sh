#!/bin/bash


# $1 correct_result 
# $2 compared result

num=`cat $1 | grep "Query point" | wc -l`

if [ ! -d "temp" ]; then
  mkdir ./temp
fi

cnt=0  
while [  $cnt -le $num ]; do  
    # echo The cnt is $cnt  
    name=`echo $cnt."txt.dat"`
    touch ./temp/$name
    name2=`echo $cnt."txt"`
    touch ./temp/$name2
    let cnt=cnt+1   
done  

cnt=0  
while [  $cnt -le $num ]; do  
	awk -v awk_num="$cnt" 'BEGIN{ check=0; }
					{
						if($1=="Query"){
							if($3 == (awk_num""":")) check = 1;
							else check = 0;
						}
						if(check==1){
							if($1 != "Total" && $1 !="Query") print $1;
						}
					 }
					END{
					}' $1 > ./temp/$cnt.txt 
    let cnt=cnt+1   
done  

cnt=0  
while [  $cnt -le $num ]; do  
	awk -v awk_num="$cnt" 'BEGIN{ check=0; }
					{
						if($1=="Query"){
							if($3 == (awk_num""":")) check = 1;
							else check = 0;
						}
						if(check==1){
							if($1 != "Total" && $1 !="Query" && $1 !="Mean") print $1;
						}
					 }
					END{
					}' $2 > ./temp/$cnt.txt.dat 
    let cnt=cnt+1   
done  

cd ./temp

#compare files

cnt=0  
while [  $cnt -le $num ]; do  
    # name co; name2 LSH; name3 com_result
    
    name=`echo $cnt."txt"`
    name2=`echo $cnt."txt.dat"`
    name3=`echo "com".$cnt`
	diff $name $name2 > $name3
	
    let cnt=cnt+1   
done  

#compute precision and recall

cnt=0
# n=`head -1 $1 | awk '{print $3}'`  
# echo $n
totalP=0
totalTP=0
totalFP=0
while [  $cnt -le $num ]; do  
    # name co; name2 LSH; name3 com_result
    name2=`echo $cnt."txt.dat"`
    name3=`echo "com".$cnt`
    FP=`cat $name3 | grep "<" | wc -l`
    FN=`cat $name3 | grep ">" | wc -l`
    P=`cat $name2 | wc -l`
    TP=`expr $P - $FN`
    totalP=`expr $totalP + $P`
    totalTP=`expr $totalTP + $TP`
	if [ -n "$3" ] ;then
	    temp=`expr $TP + $FP`
		precision=`awk -v tp=$TP -v temp=$temp 'BEGIN{if(temp!=0) printf "%.2f\n", tp/temp; else printf("1.00\n");}'`
		recall=`awk -v tp=$TP -v p=$P 'BEGIN{if(p!=0) printf "%.2f\n", tp/p; else printf("1.00\n");}'`
		echo "For Query Point "$cnt" :"
		echo "Precision is "$precision", Recall is "$recall 
	fi

	
    let cnt=cnt+1   
done  

echo ""
echo "For total: Precision is "`awk -v tp=$totalTP -v fp=$totalFP 'BEGIN{if((tp+fp)!=0) printf "%.2f\n", tp/(tp+fp); else printf("1.00\n");}'`", Recall is "`awk -v tp=$totalTP -v p=$totalP 'BEGIN{if(p!=0) printf "%.2f\n", tp/p; else printf("1.00\n");}'`
echo ""

cd ..

rm -rf ./temp
