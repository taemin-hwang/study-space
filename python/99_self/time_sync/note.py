import datetime

start = datetime.datetime.now()
#print(now)
#print(now.timestamp() * 1000)
time.sleep(0.1)
end = datetime.datetime.now()
delta = end.timestamp() - start.timestamp()
print(delta)

