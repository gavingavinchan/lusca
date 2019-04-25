for i in {1..9}
do
  echo "cycle, $i"
  gpio mode 24 OUT
  gpio write 24 1
  sleep 0.000005s
  gpio mode 24 up
  gpio mode 24 IN
  sleep 0.000005s
done
gpio mode 24 UP

