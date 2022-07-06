import time
import asyncio

async def good_night(message):
    #await asyncio.sleep(1)
    print(message)
    return "thank you, " + message

async def main(messages):
    task = [good_night(message) for message in messages]
    ret = await asyncio.gather(*task)
    return ret

for i in range(10):
    print(f"start : {time.strftime('%X')}")
    messages = ["good", "night"]
    ret = asyncio.run(main(messages))
    print(ret)
    print(f"end : {time.strftime('%X')}")
