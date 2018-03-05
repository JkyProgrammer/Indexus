typeset -i buildNum=$(cat logs/buildcounter)
echo $(($buildNum+1)) > logs/buildcounter
echo "Indexus Builder started"
DATE=`date +%d-%m-%Y`
fileName=$DATE"."$buildNum
echo "Entering dev/src/"
cd dev/src/
echo "Copying script files"
bash ../../copyScripts.sh
truncate -s 0 ../bin/final.cc
echo "Searching for source files";
for file in *.cc
do
 echo "Including source file $file"
 name=`echo "$file" | cut -d'.' -f1`
# g++ $file -o "../bin/$name.o"
 fileinc=\"../src/$file\"
 echo "#include "$fileinc"" >> ../bin/final.cc
done
echo "Leaving dev/src/"
echo "Entering dev/bin"
cd ../bin
echo "Inclusion file looks like this:"
cat final.cc | while read line
do
  echo "$line"
done
echo "Compiling sources"
g++ final.cc -std=c++11 -o "Indexus-$fileName"
echo "Cleaning up"
rm final.cc
cp "Indexus-$fileName" "../../Indexus-Latest"
