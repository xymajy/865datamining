#!/bin/bash


# $1 correct_result 
# $2 compared result

num=`cat $1 | grep "Query point" | wc -l`

# echo `cat co_result_0.5 | grep "Query point" | wc -l`
# echo $num


# i=0; while[$i -le $num];do name=`printf"test%03d.txt $i"`; touch "$name"; i=$(($i)+1);done
# i=0
# while [$i -le 10]; do 
# 	name=`printf"test%03d.txt $i"` 
# 	touch "$name"
# 	let i=i+1
# done

# generate temp files
# if[ ! -d "./temp" ]; then 
# 	mkdir ./temp
# fi

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
    # touch ./temp/$name


cd ..

# `cat $1 | awk 'BEGIN{ }
# 				{
# 					for(i=1;i<782;){
# 						if($i>$(i+1)){
# 							if($i > $(i+2)) printf("%f ",$i);
# 							else printf("%f ",$(i+2));
# 						}else{
# 							if($(i+1) > $(i+2)) printf("%f ",$(i+1));
# 							else printf("%f ",$(i+2));
# 						}
# 						i+=3;
# 					}
# 					printf("\n");
# 				 }
# 				END{
# 				}' > temp.dat `

# echo "${1}.dat"
# d-dimension
# `cat $1 | awk 'BEGIN{ }
# 				{
# 					for(i=1;i<782;){
# 						if($i>$(i+1)){
# 							if($i > $(i+2)) printf("%f ",$i);
# 							else printf("%f ",$(i+2));
# 						}else{
# 							if($(i+1) > $(i+2)) printf("%f ",$(i+1));
# 							else printf("%f ",$(i+2));
# 						}
# 						i+=3;
# 					}
# 					printf("\n");
# 				 }
# 				END{
# 				}' > temp.dat `

# #norm
# `cat temp.dat | awk 'BEGIN{ }
# 				{
# 					temp = 0;
# 					for(i=1;i<260;i++){
# 						temp = temp + $i * $i;
# 					}
# 					roo = sqrt(temp);
# 					for(i=1;i<260;i++){
# 						printf("%f ",$i / roo);
# 					}
# 					printf("\n");
# 				 }
# 				END{
# 				}' > ${1}.dat `


# rm temp.dat

# `cat $1 | awk 'BEGIN{ }
# 				{
# 					for(i=0;i<200;i++){
# 						printf("%f ",$i);
# 					}
# 					printf("\n");
# 				 }
# 				END{
# 				}' > ${1}.dat `

#compute norm
# `cat ${1}.dat | awk 'BEGIN{ }
# 				{
# 					roo =0;
# 					for(i=1;i<260;i++){
# 						roo = roo + $i * $i;
# 					}
# 					printf("%f \n", roo);
# 				 }
# 				END{
# 				}' > norm.dat `
