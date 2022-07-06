import time
import asyncio

async def good_night(message):
    await asyncio.sleep(1)
    print(message)

async def main():
    await asyncio.gather(
        good_night('good'),
        good_night('night')
    )

for i in range(10):
    print(f"start : {time.strftime('%X')}")
    asyncio.run(main())
    print(f"end : {time.strftime('%X')}")
