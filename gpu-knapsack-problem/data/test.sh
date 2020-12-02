file="https://people.sc.fsu.edu/~jburkardt/datasets/knapsack_01/p%s_%s.txt\n"

for ((i = 1; i <= 8; i++))
do
    if [[ $i -lt 10 ]]; then
        p="0$i"
    else
        p=$i
    fi

    file_to_download_c=`printf $file $p "c"`
    file_to_download_w=`printf $file $p "w"`
    file_to_download_p=`printf $file $p "p"`
    file_to_download_s=`printf $file $p "s"`
    
    wget $file_to_download_c
    wget $file_to_download_w
    wget $file_to_download_p
    wget $file_to_download_s
done
