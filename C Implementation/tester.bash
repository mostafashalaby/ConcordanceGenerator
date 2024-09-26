#!/bin/bash
 
fail_check[1]=$(./concord3 in01.txt | diff out01.txt -)
fail_check[2]=$(./concord3 in02.txt | diff out02.txt -)
fail_check[3]=$(./concord3 in03.txt -e english.txt | diff out03.txt -)
fail_check[4]=$(./concord3 in04.txt -e english.txt | diff out04.txt -)
fail_check[5]=$(./concord3 in05.txt -e english.txt | diff out05.txt -)
fail_check[6]=$(./concord3 in06.txt -e english.txt | diff out06.txt -)
fail_check[7]=$(./concord3 in07.txt -e english.txt | diff out07.txt -)
fail_check[8]=$(./concord3 in08.txt -e latin.txt | diff out08.txt -)
fail_check[9]=$(./concord3 in09.txt -e latin.txt | diff out09.txt -)
fail_check[10]=$(./concord3 in10.txt -e deutsch.txt | diff out10.txt -)
fail_check[11]=$(./concord3 in11.txt -e english.txt | diff out11.txt -)
fail_check[12]=$(./concord3 in12.txt -e english-2.txt | diff out12.txt -)
fail_check[13]=$(./concord3 in13.txt -e english-2.txt | diff out13.txt -)
fail_check[14]=$(./concord3 in14.txt -e english-2.txt | diff out14.txt -)
fail_check[15]=$(./concord3 in15.txt -e latin.txt | diff out15.txt -)
fail_check[16]=$(./concord3 in16.txt -e latin.txt | diff out16.txt -)
fail_check[17]=$(./concord3 in17.txt -e latin-2.txt | diff out17.txt -)
fail_check[18]=$(./concord3 in18.txt -e latin-2.txt | diff out18.txt -)
fail_check[19]=$(./concord3 in19.txt -e deutsch-2.txt | diff out19.txt -)
fail_check[20]=$(./concord3 in20.txt -e deutsch-2.txt | diff out20.txt -)
fail_check[21]=$(./concord3 -e english.txt in03.txt | diff out03.txt -)
fail_check[22]=$(./concord3 -e english.txt in04.txt | diff out04.txt -)
fail_check[23]=$(./concord3 -e english.txt in05.txt | diff out05.txt -)
fail_check[24]=$(./concord3 -e english.txt in06.txt | diff out06.txt -)
fail_check[25]=$(./concord3 -e english.txt in07.txt | diff out07.txt -)
fail_check[26]=$(./concord3 -e latin.txt in08.txt | diff out08.txt -)
fail_check[27]=$(./concord3 -e latin.txt in09.txt | diff out09.txt -)
fail_check[28]=$(./concord3 -e deutsch.txt in10.txt | diff out10.txt -)
fail_check[29]=$(./concord3 -e english.txt in11.txt | diff out11.txt -)
fail_check[30]=$(./concord3 -e english-2.txt in12.txt | diff out12.txt -)
fail_check[31]=$(./concord3 -e english-2.txt in13.txt | diff out13.txt -)
fail_check[32]=$(./concord3 -e english-2.txt in14.txt | diff out14.txt -)
fail_check[33]=$(./concord3 -e latin.txt in15.txt | diff out15.txt -)
fail_check[34]=$(./concord3 -e latin.txt in16.txt | diff out16.txt -)
fail_check[35]=$(./concord3 -e latin-2.txt in17.txt | diff out17.txt -)
fail_check[36]=$(./concord3 -e latin-2.txt in18.txt | diff out18.txt -)
fail_check[37]=$(./concord3 -e deutsch-2.txt in19.txt | diff out19.txt -)
fail_check[38]=$(./concord3 -e deutsch-2.txt in20.txt | diff out20.txt -) 

n=1
for i in "${fail_check[@]}"
do
    echo ====================
    if ["$i" == ""]
    then
        echo Test "$n" passed
    else
        echo Test "$n" failed
    fi
    echo ==================== 
    echo
 
    let "n++"
done
