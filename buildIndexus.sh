echo "Indexus builder started"
DATE=`date +%d-%m-%Y-%H:%M`
echo "Entering dev/src/"
cd dev/src/
truncate -s 0 ../bin/final.cc
for file in *.cc
do
 echo "Found source file $file"
 name=`echo "$file" | cut -d'.' -f1`
# g++ $file -o "../bin/$name.o"
 fileinc=\"../src/$file\"
 echo "Including"
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
g++ final.cc -std=c++11 -o "Indexus-$DATE"
echo "Cleaning up"
rm final.cc
cp "Indexus-$DATE" "../../Indexus-Latest"
