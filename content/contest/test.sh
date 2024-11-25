# Test your solution with the brute force one.
# Usage: $ sh test.sh
while true; do
./gen > tmp.in
./bf < tmp.in > bf.out
./sol < tmp.in > sol.out
if diff bf.out sol.out; then
echo AC
else
echo WA
echo Input
cat tmp.in
echo BF
cat bf.out
echo SOL
cat sol.out
exit 0
fi
done